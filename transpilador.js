import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

const HEADER_C = `
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <uchar.h>
#include <wchar.h>
#include <inttypes.h>

// Parche de compatibilidad Unicode para consolas Windows
#ifdef _WIN32
#include <windows.h>
#define AXO_INIT_CONSOLE() SetConsoleOutputCP(CP_UTF8)
#else
#define AXO_INIT_CONSOLE() (void)0
#endif
typedef struct {
  int64_t value;
  bool has_error;
  int32_t error_code;
} axo_result_t;

// === Nivel 1: xxsvar y xsvar (Uniones puras de 16 bits / 2 Bytes) ===
typedef union {
  int8_t axo_int;
  uint8_t axo_intu;
  char8_t axo_chara;
  bool axo_boo;
} xxsvar;

typedef union {
  int16_t axo_int;
  uint16_t axo_intu;
  _Float16 axo_flt;
  char16_t axo_chara;
  bool axo_boo;
} xsvar;

// === Nivel 2: svar (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int32_t axo_int;
  uint32_t axo_intu;
  float axo_flt;
  _Float16 complex axo_com;
  _Decimal32 axo_dec;
} svar;

// === Nivel 3: var, lvar y xlvar (Contenedores dinámicos de 64 bits a más) ===
typedef union {
  char32_t axo_chara;
  bool axo_boo;
  int64_t axo_int;
  uint64_t axo_intu;
  double axo_flt;
  float complex axo_com;
  _Decimal64 axo_dec;
  void* axo_other;
} var;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(128) axo_int;
  unsigned _BitInt(128) axo_intu;
  _Float128 axo_flt;
  double complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} lvar;

typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(256) axo_int;
  unsigned _BitInt(256) axo_intu;
  _Float256 axo_flt;
  _Float128 complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} xlvar;
`;
class AxolangToCListener extends AxolangListener {
	constructor() {
		super();
		this.outputC = "";
		this.isComplexMatch = false;
		this.matchExpr = "";
		this.caseCount = 0;
		this.tablaSimbolos = new Map();
	}
	enterVarDeclaration(ctx) {
		let cp = ctx.parentCtx;
		while (cp) {
			if (
				cp.constructor.name === "PkgContext" ||
				cp.constructor.name === "Pkg"
			) {
				return;
			}
			cp = cp.parentCtx;
		}
		const id = ctx.IDENTIFIER().getText();
		let type = ctx.getChild(0).getText();

		if (ctx.arrayLiteral()) {
			this.tablaSimbolos.set(id, "array");
			const items = ctx.arrayLiteral().expression();
			const elementsCount = ctx.INT_LITERAL()
				? ctx.INT_LITERAL().getText()
				: items.length;

			let chkmrk = ["", "DD", "U", ""];
			if (type.startsWith("xxs")) {
				chkmrk = ["", "", "", ""];
			} else if (type.startsWith("xs")) {
				chkmrk = ["f16", "", "u", ""];
			} else if (type.startsWith("s")) {
				chkmrk = ["f", "DF", "U", "f16i"];
			} else if (type.startsWith("l")) {
				chkmrk = ["f128", "DL", "U", "* I"];
			} else if (type.startsWith("xl")) {
				chkmrk = ["f256", "DL", "U", "f128i"];
			} else {
				chkmrk = ["", "DD", "U", "* I"];
			}
			const transformarExpresion = nodoExpression => {
				let value = nodoExpression.getText().trim();

				// CASO 1: Es un sub-array (Recursividad Real)
				let lowerVal = value.toLowerCase();
				if (nodoExpression.arrayLiteral()) {
					const subCtx = nodoExpression.arrayLiteral();
					const subExpressions = subCtx.expression();
					let subInicializadores = [];

					for (let a = 0; a < subExpressions.length; a++) {
						// LLAMADA RECURSIVA: evaluamos cada celda del sub-array
						subInicializadores.push(transformarExpresion(subExpressions[a]));
					}

					// Retorna el sub-array formateado como Compound Literal estático en C23
					return `{ .axo_other = (${type}[${subExpressions.length}]){ ${subInicializadores.join(", ")} } }`;
				} else if (nodoExpression.pkg()) {
					// 1. Obtenemos la lista de variables del paquete
					const pkgbody = nodoExpression.pkg().varDeclaration();
					let structMembers = [];
					let structInitializers = [];

					for (let p = 0; p < pkgbody.length; p++) {
						const decl = pkgbody[p];

						// Extraemos el tipo (primer hijo, ej: "xxsvar") y el identificador (ej: "a")
						const pType = decl.getChild(0).getText();
						const pId = decl.IDENTIFIER().getText();

						// Creamos la definición limpia para el cuerpo del struct en C: "xxsvar a;"
						structMembers.push(`${pType} ${pId};`);

						// Si la variable del paquete tiene un valor asignado (ej: = 5)
						if (decl.expression()) {
							const pExpr = decl.expression();
							// LLAMADA RECURSIVA: transpilamos el valor asignado con el formato correcto (.axo_int, etc.)
							const pValTranspiled = transformarExpresion(pExpr);
							structInitializers.push(`.${pId} = ${pValTranspiled}`);
						}
					}

					// 2. Retornamos un Compound Literal de C23 perfectamente formateado
					// Nota que usamos un puntero '&' para que quepa en el campo '.axo_other' de la unión
					return `{ .axo_other = &(struct { ${structMembers.join(" ")} }){ ${structInitializers.join(", ")} } }`;
				} else if (value.includes(".")) {
					value += chkmrk[0];
					return `{ .axo_flt = ${value} }`;
				} else if (value.endsWith("D")) {
					value = value.replace(/D$/, chkmrk[1]);
					return `{ .axo_dec = ${value} }`;
				} else if (value.endsWith("i")) {
					value = value.replace(/i$/, chkmrk[3]);
					return `{ .axo_com = ${value} }`;
				} else if (value.startsWith("'")) {
					value = value.replace(/^/, chkmrk[2]);
					return `{ .axo_chara = ${value} }`;
				} else if (value.startsWith('"')) {
					value = value.replace(/^/, chkmrk[2]);
					return `{ .axo_other = ${value} }`;
				} else if (
					(lowerVal.includes("true") || lowerVal.includes("false")) &&
					!value.startsWith("'")
				) {
					return `{ .axo_boo = ${value} }`;
				} else if (value.startsWith("&")) {
					return `{ .axo_other = ${value} }`;
				} else if (nodoExpression.IDENTIFIER()) {
					return `{ .axo_other = ${value} }`;
				} else if (value.endsWith("u")) {
					value = value.replace(/u$/, "");
					return `{ .axo_intu = ${value} }`;
				} else {
					return `{ .axo_int = ${value} }`;
				}
			};
			// ========================================================

			// Evaluamos los elementos principales de la raíz del array
			let inititem = [];
			for (let i = 0; i < items.length; i++) {
				inititem.push(transformarExpresion(items[i]));
				if (i != items.length - 1) {
					inititem.push(",");
				}
			}

			// Agregamos el cierre del array y formateamos la salida de C
			inititem.push(`};`);
			this.outputC += `    ${type} ${id}[${elementsCount}] = { ${inititem.join(" ")}\n`;
		} else {
			this.outputC += `\n ${type} ${id};`;
			const globalvar = ctx => {
			if (ctx.expression()) {
				let valvar = ctx.expression().getText();

				switch (type) {
					case "xxsvar":
						if (valvar.startsWith("'")) {
							this.outputC += `\n ${id}.axo_chara = ${valvar};`;
						} else if (
							(valvar.toLowerCase().includes("true") ||
								valvar.toLowerCase().includes("false")) &&
							!valvar.startsWith('"')
						) {
							this.outputC += `\n ${id}.axo_boo = ${valvar};`;
						} else if (valvar.endsWith("u")) {
							valvar = valvar.replace(/u$/, "");
							this.outputC += `\n ${id}.axo_intu = ${valvar};`;
						} else if (ctx.expression().IDENTIFIER()) {
							this.outputC += `\n ${id} = ${valvar};`;
						} else {
							this.outputC += `\n ${id}.axo_int = ${valvar};`;
						}
						break;
					case "xsvar":
						if (valvar.includes(".")) {
							this.outputC += `\n ${id}.axo_flt = ${valvar}f16;`;
						} else if (valvar.startsWith("'")) {
							this.outputC += `\n ${id}.axo_chara = u${valvar};`;
						} else if (
							(valvar.toLowerCase().includes("true") ||
								valvar.toLowerCase().includes("false")) &&
							!valvar.startsWith('"')
						) {
							this.outputC += `\n ${id}.axo_boo = ${valvar};`;
						} else if (valvar.endsWith("u")) {
							valvar = valvar.replace(/u$/, "");
							this.outputC += `\n ${id}.axo_intu = ${valvar};`;
						} else if (ctx.expression().IDENTIFIER()) {
							this.outputC += `\n ${id} = ${valvar};`;
						} else {
							this.outputC += `\n ${id}.axo_int = ${valvar};`;
						}
						break;
					case "svar":
						if (valvar.includes(".")) {
							this.outputC += `\n ${id}.axo_flt = ${valvar}f;`;
						} else if (valvar.endsWith("D")) {
							valvar = valvar.replace(/D$/, "DF");
							this.outputC += `\n ${id}.axo_dec = ${valvar};`;
						} else if (valvar.endsWith("i")) {
							valvar = valvar.replace(/i$/, "f16i");
							this.outputC += `\n ${id}.axo_com = ${valvar};`;
						} else if (valvar.startsWith("'")) {
							this.outputC += `\n ${id}.axo_chara = U${valvar};`;
						} else if (
							(valvar.toLowerCase().includes("true") ||
								valvar.toLowerCase().includes("false")) &&
							!valvar.startsWith('"')
						) {
							this.outputC += `\n ${id}.axo_boo = ${valvar};`;
						} else if (valvar.endsWith("u")) {
							valvar = valvar.replace(/u$/, "");
							this.outputC += `\n ${id}.axo_intu = ${valvar};`;
						} else if (ctx.expression().IDENTIFIER()) {
							this.outputC += `\n ${id} = ${valvar};`;
						} else {
							this.outputC += `\n ${id}.axo_int = ${valvar};`;
						}
						break;
					case "var":
						if (valvar.includes(".")) {
							this.outputC += `\n ${id}.axo_flt = ${valvar};`;
						} else if (valvar.endsWith("D")) {
							valvar = valvar.replace(/D$/, "DD");
							this.outputC += `\n ${id}.axo_dec = ${valvar};`;
						} else if (valvar.endsWith("i")) {
							valvar = valvar.replace(/i$/, "* I");
							this.outputC += `\n ${id}.axo_com = ${valvar};`;
						} else if (valvar.startsWith("'")) {
							this.outputC += `\n ${id}.axo_chara = U${valvar};`;
						} else if (valvar.startsWith('"')) {
							this.outputC += `\n ${id}.axo_other = U${valvar};`;
						} else if (
							(valvar.toLowerCase().includes("true") ||
								valvar.toLowerCase().includes("false")) &&
							!valvar.startsWith('"')
						) {
							this.outputC += `\n ${id}.axo_boo = ${valvar};`;
						} else if (ctx.expression().pkg()) {
							// 1. Obtenemos la lista de variables del paquete
							const pkgbody = ctx.expression().pkg().varDeclaration();
							let structMembers = [];
							let structInitializers = [];

							for (let p = 0; p < pkgbody.length; p++) {
								const decl = pkgbody[p];

								// Extraemos el tipo (primer hijo, ej: "xxsvar") y el identificador (ej: "a")
								const pType = decl.getChild(0).getText();
								const pId = decl.IDENTIFIER().getText();

								// Creamos la definición limpia para el cuerpo del struct en C: "xxsvar a;"
								structMembers.push(`${pType} ${pId};`);

								// Si la variable del paquete tiene un valor asignado (ej: = 5)
								if (decl.expression()) {
									const pExpr = decl.expression();
									// LLAMADA RECURSIVA: transpilamos el valor asignado con el formato correcto (.axo_int, etc.)
									structInitializers.push(`.${pId} = .${pvaltype} =`);
								}
							}

							// 2. Retornamos un Compound Literal de C23 perfectamente formateado
							// Nota que usamos un puntero '&' para que quepa en el campo '.axo_other' de la unión
							this.outputC += `\n  ${id}.axo_other = &(struct { ${structMembers.join(" ")} }){ ${structInitializers.join(", ")} } `;
						} else if (valvar.endsWith("u")) {
							valvar = valvar.replace(/u$/, "");
							this.outputC += `\n ${id}.axo_intu = ${valvar};`;
						} else if (ctx.expression().IDENTIFIER()) {
							this.outputC += `\n ${id} = ${valvar};`;
						} else {
							this.outputC += `\n ${id}.axo_int = ${valvar};`;
						}
						break;
					default:
				}
			}}
		}
	}

	exitMatchStatement(ctx) {
		if (!this.isComplexMatch) {
			this.outputC += `    }\n`;
		}
		this.isComplexMatch = false;
	}
}

function transpile(inputCode) {
	const chars = new antlr4.InputStream(inputCode);
	const lexer = new AxolangLexer(chars);
	const tokens = new antlr4.CommonTokenStream(lexer);
	const parser = new AxolangParser(tokens);
	const tree = parser.program();
	//console.log(tree);

	const listener = new AxolangToCListener();
	antlr4.tree.ParseTreeWalker.DEFAULT.walk(listener, tree);

	let finalCode = HEADER_C + "\nint main() {\n";
	finalCode += listener.outputC;
	finalCode += "    return 0;\n}";
	return finalCode;
}
const test = `
var hi[] = «5, 6u, «7.5, {
  var uno = 6
  var dod = 9i
}»»
var go = {
  var algo = "Hola desde pkg"
}
var text = go
`;
console.log(transpile(test));
