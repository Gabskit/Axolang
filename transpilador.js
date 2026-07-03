import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

// Estructura fija de C (Corregida para evitar nombres duplicados en la unión)
const HEADER_C = `
#include <stdint.h>
#include <complex.h>
typedef struct {
    int64_t value;       
    bool has_error;      
    int32_t error_code;  
} axo_result_t;

// === Nivel 1: xsvar (Unión pura de 16 bits / 2 Bytes) ===
typedef union {
  int8_t axo_xxsint;
  uint8_t axo_xxsintu;
  char axo_chara;
  bool axo_boo;
} xxsvar;

typedef union {
    int16_t   axo_xsint;    
    uint16_t  axo_xsintu;   
    _Float16  axo_xsflt;
    char axo_chara;
    bool axo_boo;
} xsvar;

// === Nivel 2: svar (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
    char axo_chara;
    bool axo_boo;
    int32_t   axo_sint;     
    uint32_t  axo_sintu;    
    float     axo_sflt;     
    _Float16 complex axo_xscom;
    _Decimal32 axo_sdec; // Nombre corregido para evitar colisión
} svar;

// === Nivel 3: var / lvar (Unión pura de 64 bits / 8 Bytes) ===
typedef union {
    char axo_chara;
    bool axo_boo;
    int64_t   axo_int;      
    uint64_t  axo_intu;     
    double    axo_flt;      
    float complex axo_scom; 
    _Decimal64 axo_dec;
    void* axo_other;
} var;
typedef union {
  char axo_chara;
  bool axo_boo;
  _BitInt(128) axo_lint;
  unsigned _BitInt(128) axo_lintu;
  long double axo_lflt;
  double complex axo_com;
  _Decimal128 axo_dec;
  void* axo_other;
} lvar;
typedef union {
  char axo_chara;
  bool axo_boo;
  _BitInt(256) axo_xlint;
  unsigned _BitInt(256) axo_xlintu;
  _Float256 axo_xlflt;
  long double axo_lcom;
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

        // TABLA DE SÍMBOLOS: Tu idea de 'savedvars' estructurada como un mapa de clase profesional
        this.tablaSimbolos = new Map();
    }

    // Se ejecuta al leer una declaración de variable (ej: auto x = 10;)
    enterVarDeclaration(ctx) {
        const id = ctx.IDENTIFIER().getText();
        let value = ctx.expression().getText();
        let type = ctx.getChild(0).getText();

        // INFERENCIA AUTOMÁTICA
        if (type === "auto") {
            if (value.includes(".")) {
                if (value.toUpperCase().includes("D")) {
                    type = "dec";
                } else {
                    type = "flt";
                }
            } else if (value.includes("i")) {
                type = "com";
            } else if (value.includes("true") || value.includes("false")) {
                type = "boo";
            } else {
                type = "int";
            }
        }

        // Guardamos el tipo de la variable de forma estática en la Tabla de Símbolos
        this.tablaSimbolos.set(id, type);

        // Traducir los tipos de Axolang a tipos primitivos de C
        switch (type) {
            case "xxsvar":
                if (value.includes("★") || value.includes("†")) {
                    value.includes("★")
                        ? (value = value.replace(/★$/, "true"))
                        : (value = value.replace(/†$/, "false"));
                    this.outputC += `xxsvar ${id};\n
                    ${id}.axo_boo = ${value};\n
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `xxsvar ${id};\n
                  ${id}.axo_chara = ${value};\n
                  `;
                } else if (value.includes("u") || value.includes("U")) {
                    value = value.replace(/[uU]$/, "");
                    this.outputC += `xxsvar ${id};\n
                    ${id}.axo_xxsintu = ${value};\n
                    `;
                } else {
                    this.outputC += `xxsvar ${id};\n
                    ${id}.axo_xxsint = ${value};\n
                    `;
                }
                break;
            case "xsvar":
                if (value.includes(".")) {
                    this.outputC += `xsvar ${id};\n
                  ${id}.axo_xsflt = ${value};\n
                  `;
                } else if (value.includes("★") || value.includes("†")) {
                    value.includes("★")
                        ? (value = value.replace(/★$/, "true"))
                        : (value = value.replace(/†$/, "false"));
                    this.outputC += `xsvar ${id};\n
                    ${id}.axo_boo = ${value};\n
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `xsvar ${id};\n
                  ${id}.axo_chara = ${value};\n
                  `;
                } else if (value.includes("u") || value.includes("U")) {
                    value = value.replace(/[uU]$/, "");
                    this.outputC += `xsvar ${id};\n
                    ${id}.axo_xsintu = ${value}
                    `;
                } else {
                    this.outputC += `xsvar ${id};\n
                    ${id}.axo_xsint = ${value}
                    `;
                }
                break;
        }
    }

    enterMatchStatement(ctx) {
        const exprText = ctx.IDENTIFIER().getText();

        // CORRECCIÓN: Consultamos la Tabla de Símbolos en vez de evaluar las letras del nombre de la variable
        const tipoVariable = this.tablaSimbolos.get(exprText) || "int";
        const esComplejo = tipoVariable.includes("com");

        if (!esComplejo) {
            this.outputC += `    switch (${exprText}) {\n`;
        } else {
            this.outputC += `    // Cascada lógica para tipo complejo\n`;
            this.isComplexMatch = true;
            this.matchExpr = exprText;
            this.caseCount = 0;
        }
    }

    enterMatchCase(ctx) {
        // Extraemos limpiamente el bloque de la acción usando división por flecha para evitar fallos de nodos vacíos
        const matchCaseText = ctx.getText();
        let actionExpr = matchCaseText.split("->")[1] || "";

        // Limpiamos las llaves si el bloque viene envuelto en { }
        actionExpr = actionExpr.replace(/^\{|\}$/g, "").trim();

        // 1. REEMPLAZO DINÁMICO DE SUFIJOS DECIMALES USANDO TU LOGIC DE TABLA DE SÍMBOLOS
        // Busca un patrón 'variable = numeroD' de forma segura mediante expresiones regulares globales
        actionExpr = actionExpr.replace(
            /([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([+-]?[0-9]+(?:\.[0-9]+)?)[dD]\b/g,
            (match, varName, numValue) => {
                const tipoDestino = this.tablaSimbolos.get(varName) || "dec";
                let sufijoC = "DD"; // Por defecto 'dec' -> _Decimal64

                if (tipoDestino === "sdec") sufijoC = "DF";
                else if (tipoDestino === "ldec") sufijoC = "DL";

                return `${varName} = ${numValue}${sufijoC}`;
            }
        );

        // 2. REEMPLAZO DE UNIDADES IMAGINARIAS COMPLEJAS EN EL BLOQUE
        actionExpr = actionExpr.replace(/[iI]$/, " * I");

        // Aseguramos el punto y coma final de la instrucción en C
        if (actionExpr && !actionExpr.endsWith(";")) {
            actionExpr += ";";
        }

        // Inyección estructurada en C
        if (!this.isComplexMatch) {
            const caseExpr = ctx.expression(0).getText();
            if (ctx.getChild(0).getText() === "_") {
                this.outputC += `        default:\n            ${actionExpr}\n            break;\n`;
            } else {
                this.outputC += `        case ${caseExpr}:\n            ${actionExpr}\n            break;\n`;
            }
        } else {
            if (ctx.getChild(0).getText() === "_") {
                this.outputC += `    else {\n        ${actionExpr}\n    }\n`;
            } else {
                const caseExpr = ctx.expression(0).getText();
                let prefix = this.caseCount === 0 ? "    if" : "    else if";
                this.outputC += `${prefix} (creal(${this.matchExpr}) == creal(${caseExpr}) && cimag(${this.matchExpr}) == cimag(${caseExpr})) {\n        ${actionExpr}\n    }\n`;
                this.caseCount++;
            }
        }
    }

    exitMatchStatement(ctx) {
        if (!this.isComplexMatch) {
            this.outputC += `    }\n`;
        }
        this.isComplexMatch = false;
    }
}

// Función principal del Transpilador
function transpile(inputCode) {
    const chars = new antlr4.InputStream(inputCode);
    const lexer = new AxolangLexer(chars);
    const tokens = new antlr4.CommonTokenStream(lexer);
    const parser = new AxolangParser(tokens);
    const tree = parser.program();

    const listener = new AxolangToCListener();
    antlr4.tree.ParseTreeWalker.DEFAULT.walk(listener, tree);

    let finalCode = HEADER_C + "\nint main() {\n";
    finalCode += listener.outputC;
    finalCode += "    return 0;\n}";

    return finalCode;
}

// --- PRUEBA DEL TRANSPILADOR ---
const codigoAxolang = `
xsvar letra = 'a'
xsvar onoff = ★
xsvar entero = 45u
xsvar flotante = 2.2
`;

console.log(transpile(codigoAxolang));
