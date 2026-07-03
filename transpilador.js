import antlr4 from "antlr4";
import AxolangLexer from "./AxolangLexer.js";
import AxolangParser from "./AxolangParser.js";
import AxolangListener from "./AxolangListener.js";

// Estructura fija de C (Corregida para evitar nombres duplicados en la unión)
const HEADER_C = `
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <uchar.h>
#include <wchar.h>
#include <inttypes.h>

static inline void axo_print_c8(char8_t c) {
    // char8_t es UTF-8 nativo, se puede imprimir directamente como carácter o string
    printf("%c\t", (char)c);
}

static inline void axo_print_c16(char16_t c) {
    // Conversión rápida rudimentaria o formateada para UTF-16
    printf("%lc\t", (wint_t)c);
}

static inline void axo_print_char32(char32_t c) {
    char buf[5] = {0};
    mbstate_t st = {0};
    c32rtomb(buf, c, &st);
    printf("%s\t", buf);
}

static inline void axo_print_float_complex(float complex c) {
    printf("%f + %fi\t", crealf(c), cimagf(c));
}

static inline void axo_print_double_complex(double complex c) {
    printf("%lf + %lfi\t", creal(c), cimag(c));
}

#define axo_print_single(X) _Generic((X), \
    bool:                printf((X) ? "true\t" : "false\t"), \
    int8_t:              printf("%" PRId8 "\t", (int8_t)(X)), \
    uint8_t:             printf("%" PRIu8 "\t", (uint8_t)(X)), \
    int16_t:             printf("%" PRId16 "\t", (int16_t)(X)), \
    uint16_t:            printf("%" PRIu16 "\t", (uint16_t)(X)), \
    int32_t:             printf("%" PRId32 "\t", (int32_t)(X)), \
    uint32_t:            printf("%" PRIu32 "\t", (uint32_t)(X)), \
    int64_t:             printf("%" PRId64 "\t", (int64_t)(X)), \
    uint64_t:            printf("%" PRIu64 "\t", (uint64_t)(X)), \
    _Float16:            printf("%f\t", (float)(X)), \
    float:               printf("%f\t", (float)(X)), \
    double:              printf("%f\t", (double)(X)), \
    long double:         printf("%Lf\t", (long double)(X)), \
    char32_t:            _axo_print_char32(X), \
    char*:               printf("%s\t", (char*)(X)), \
    const char*:         printf("%s\t", (const char*)(X)), \
    float complex:       _axo_print_float_complex(X), \
    double complex:      _axo_print_double_complex(X), \
    _Decimal64:          printf("%Df\t", (_Decimal64)(X)), \
    _Decimal128:         printf("%DDf\t", (_Decimal128)(X)), \
    default:             printf("[Objeto/Bloque void*]\t") \
)

typedef struct {
    int64_t value;       
    bool has_error;      
    int32_t error_code;  
} axo_result_t;

// === Nivel 1: xsvar (Unión pura de 16 bits / 2 Bytes) ===
typedef union {
  int8_t axo_int;
  uint8_t axo_intu;
  char8_t axo_chara;
  bool axo_boo;
} xxsvar;

typedef union {
    int16_t   axo_int;    
    uint16_t  axo_intu;   
    _Float16  axo_flt;
    char16_t axo_chara;
    bool axo_boo;
} xsvar;

// === Nivel 2: svar (Unión pura de 32 bits / 4 Bytes) ===
typedef union {
    char32_t axo_chara;
    bool axo_boo;
    int32_t   axo_int;     
    uint32_t  axo_intu;    
    float     axo_flt;     
    _Float16 complex axo_com;
    _Decimal32 axo_dec; // Nombre corregido para evitar colisión
} svar;

// === Nivel 3: var / lvar (Unión pura de 64 bits / 8 Bytes) ===
typedef union {
    char32_t axo_chara;
    bool axo_boo;
    int64_t   axo_int;      
    uint64_t  axo_intu;     
    double    axo_flt;      
    float complex axo_com; 
    _Decimal64 axo_dec;
    void* axo_other;
} var;
typedef union {
  char32_t axo_chara;
  bool axo_boo;
  _BitInt(128) axo_int;
  unsigned _BitInt(128) axo_intu;
  long double axo_flt;
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
  long double axo_com;
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
                    this.outputC += `xxsvar ${id};
                    ${id}.axo_boo = ${value};
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `xxsvar ${id};
                  ${id}.axo_chara = u${value};
                  `;
                } else if (value.includes("u")) {
                    value = value.replace(/u$/, "");
                    this.outputC += `xxsvar ${id};
                    ${id}.axo_intu = ${value};
                    `;
                } else {
                    this.outputC += `xxsvar ${id};
                    ${id}.axo_int = ${value};
                    `;
                }
                break;
            case "xsvar":
                if (value.includes(".")) {
                    this.outputC += `xsvar ${id};
                  ${id}.axo_flt = ${value};
                  `;
                } else if (value.includes("★") || value.includes("†")) {
                    value.includes("★")
                        ? (value = value.replace(/★$/, "true"))
                        : (value = value.replace(/†$/, "false"));
                    this.outputC += `xsvar ${id};
                    ${id}.axo_boo = ${value};
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `xsvar ${id};
                  ${id}.axo_chara = u${value};
                  `;
                } else if (value.includes("u")) {
                    value = value.replace(/u$/, "");
                    this.outputC += `xsvar ${id};
                    ${id}.axo_intu = ${value};
                    `;
                } else {
                    this.outputC += `xsvar ${id};
                    ${id}.axo_int = ${value};
                    `;
                }
                break;
            case "svar":
                if (value.includes(".")) {
                    if (value.includes("D")) {
                        value = value.replace(/D$/, "DF");
                        this.outputC += `svar ${id};
                  ${id}.axo_dec = ${value};
                  `;
                    } else if (value.includes("i")) {
                        value = value.replace(/i$/, " * I");
                        this.outputC += `svar ${id};
                  ${id}.axo_com = ${value};
                  `;
                    } else {
                        this.outputC += `svar ${id};
                  ${id}.axo_flt = ${value};
                  `;
                    }
                } else if (value.includes("★") || value.includes("†")) {
                    value.includes("★")
                        ? (value = value.replace(/★$/, "true"))
                        : (value = value.replace(/†$/, "false"));
                    this.outputC += `svar ${id};
                    ${id}.axo_boo = ${value};
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `svar ${id};
                  ${id}.axo_chara = u${value};
                  `;
                } else if (value.includes("u")) {
                    value = value.replace(/u$/, "");
                    this.outputC += `svar ${id};
                    ${id}.axo_intu = ${value};
                    `;
                } else {
                    this.outputC += `svar ${id};
                    ${id}.axo_int = ${value};
                    `;
                }
                break;
            case "var":
                if (value.includes(".")) {
                    if (value.includes("D")) {
                        value = value.replace(/D$/, "DD");
                        this.outputC += `var ${id};
                  ${id}.axo_dec = ${value};
                  `;
                    } else if (value.includes("i")) {
                        value = value.replace(/i$/, " * I");
                        this.outputC += `var ${id};
                  ${id}.axo_com = ${value};
                  `;
                    } else {
                        this.outputC += `var ${id};
                  ${id}.axo_flt = ${value};
                  `;
                    }
                } else if (value.includes("★") || value.includes("†")) {
                    value.includes("★")
                        ? (value = value.replace(/★$/, "true"))
                        : (value = value.replace(/†$/, "false"));
                    this.outputC += `var ${id};
                    ${id}.axo_boo = ${value};
                    `;
                } else if (value.includes("\'")) {
                    this.outputC += `var ${id};
                  ${id}.axo_chara = u${value};
                  `;
                } else if (value.includes("{") && value.includes("\n")) {
                    this.outputC += `var ${id}
                    ${id}.axo_other = &(struct ${value}){};\n
                    `;
                } else if (value.includes("u")) {
                    value = value.replace(/u$/, "");
                    this.outputC += `var ${id};
                    ${id}.axo_intu = ${value};
                    `;
                } else {
                    this.outputC += `var ${id};
                    ${id}.axo_int = ${value};
                    `;
                }
                break;
        }
    }
    enterAssignmentStatement(ctx) {
        const id = ctx.IDENTIFIER().getText();
        let value = ctx.expression().getText();
        let nuevoTipo = "int"; // Por defecto

        // Detectamos dinámicamente qué tipo de dato le están metiendo a la unión
        if (value.includes(".")) {
            nuevoTipo = value.toUpperCase().includes("D") ? "dec" : "flt";
        } else if (value.includes("i")) {
            nuevoTipo = "com";
        } else if (
            value.includes("true") ||
            value.includes("false") ||
            value.includes("★") ||
            value.includes("†")
        ) {
            nuevoTipo = "boo";
        } else if (value.includes("\'")) {
            nuevoTipo = "chara";
        }

        // !!! EL SECRETO DEL DINAMISMO !!!
        // Actualizamos la tabla de símbolos en tiempo de compilación
        this.tablaSimbolos.set(id, nuevoTipo);

        // Escribimos en C la asignación apuntando al nuevo campo de la unión pura
        const campoC = this.obtenerCampoUnion(nuevoTipo);

        // Tratamiento de booleanos y complejos nativos de Axolang
        value = value
            .replace(/★$/, "true")
            .replace(/†$/, "false")
            .replace(/[iI]$/, " * I");

        this.outputC += `    ${id}.${campoC} = ${value};\n`;
    }
    enterMatchStatement(ctx) {
        const exprText = ctx.IDENTIFIER().getText();
        const tipoVariable = this.tablaSimbolos.get(exprText) || "int";
        const esComplejo = tipoVariable.includes("com");

        if (!esComplejo) {
            // Obtenemos el campo correcto mapeado por tu tabla de símbolos
            const campoC = this.obtenerCampoUnion(tipoVariable);
            this.outputC += `    switch (${exprText}.${campoC}) {\n`;
        } else {
            this.outputC += `    // Cascada lógica para tipo complejo\n`;
            this.isComplexMatch = true;
            this.matchExpr = exprText;
            this.caseCount = 0;
        }
    }

    // Función auxiliar para tu listener que mapea tu tabla al campo en C
    obtenerCampoUnion(tipo) {
        const mapaCampos = {
            boo: "axo_boo",
            chara: "axo_chara",
            int: "axo_int",
            uint: "axo_intu",
            flt: "axo_flt",
            dec: "axo_dec",
            xsint: "axo_xsint",
            xsintu: "axo_xsintu",
            xsflt: "axo_xsflt",
            xxsint: "axo_xxsint",
            xxsintu: "axo_xxsintu"
        };
        return mapaCampos[tipo] || "axo_int";
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
                // Averiguamos si es xscom, scom, com o lcom desde tu tabla
                const tipoComplex = this.tablaSimbolos.get(this.matchExpr);
                let campoComplex = "axo_scom"; // Por defecto de 'var'

                if (tipoComplex === "xscom") campoComplex = "axo_xscom";
                else if (tipoComplex === "scom") campoComplex = "axo_scom";
                else if (tipoComplex === "com") campoComplex = "axo_com";
                else if (tipoComplex === "lcom") campoComplex = "axo_lcom";

                // En el C generado inyectamos el campo exacto:
                this.outputC += `${prefix} (creal(${this.matchExpr}.${campoComplex}) == creal(${caseExpr}) && cimag(${this.matchExpr}.${campoComplex}) == cimag(${caseExpr})) {\n`;
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
var letra = 'a'
var entero = 45u
var onoff = ★
var flotante = 2.2
var Decimal = 4.5D
var complejo = - 5 + 7.8i
var paquete = {
  var numero
  var nombre
}
`;

console.log(transpile(codigoAxolang));
