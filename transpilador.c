#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Enumeración de Tokens para Axolang
typedef enum {
  TOKEN_EOF,
  TOKEN_NEWLINE,
  TOKEN_UNKNOWN,
  TOKEN_INT,
  TOKEN_DEC,
  TOKEN_COM,
  TOKEN_CHAR,
  TOKEN_BOOL,
  TOKEN_PKG,
  TOKEN_FUNC,
  TOKEN_PUNT,
  TOKEN_ANY,
  TOKEN_AUTO,
  TOKEN_VOID,
  TOKEN_ADD,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_CHAR_LITERAL,
  TOKEN_ASSIGN,
  TOKEN_REF_ARROW,
  TOKEN_COLON,
  TOKEN_COMMA,
  TOKEN_SEMICOLON,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_LARRAY,
  TOKEN_RARRAY,
  TOKEN_OP_MULT,
  TOKEN_OP_DIV,
  TOKEN_OP_SQRT,
  TOKEN_OP_EXP,
  TOKEN_OP_AND,
  TOKEN_OP_OR,
  TOKEN_OP_NOT,
  TOKEN_OP_XOR,
  TOKEN_OP_EQUAL,
  TOKEN_OP_GE,
  TOKEN_OP_LE,
  TOKEN_OP_NOTEQUAL
} TokenType;

typedef struct {
  TokenType type;
  char lexeme[512];
} Token;

// Búferes globales para almacenar código extraído
char funciones_extraidas[16384] = "";
char constructores_inicializadores[16384] = "";

Token get_next_token(const char **src) {
  Token token = {
    TOKEN_EOF,
    ""
  };

  while (**src == ' ' || **src == '\t') (*src)++;

  if (strncmp(*src, "//", 2) == 0) {
    while (**src != '\n' && **src != '\r' && **src != '\0') (*src)++;
  }

  if (**src == '\n' || **src == '\r') {
    token.type = TOKEN_NEWLINE;
    token.lexeme[0] = **src; token.lexeme[1] = '\0';
    (*src)++; return token;
  }

  if (**src == '\0') return token;

  if (strncmp(*src, "=>", 2) == 0) {
    token.type = TOKEN_REF_ARROW; strcpy(token.lexeme, "=>"); *src += 2; return token;
  }
  if (strncmp(*src, "++", 2) == 0) {
    token.type = TOKEN_UNKNOWN; strcpy(token.lexeme, "++"); *src += 2; return token;
  }
  if (strncmp(*src, "×", 2) == 0) {
    token.type = TOKEN_OP_MULT; strcpy(token.lexeme, "×"); *src += 2; return token;
  }
  if (strncmp(*src, "÷", 2) == 0) {
    token.type = TOKEN_OP_DIV; strcpy(token.lexeme, "÷"); *src += 2; return token;
  }
  if (strncmp(*src, "§", 2) == 0) {
    token.type = TOKEN_OP_XOR; strcpy(token.lexeme, "§"); *src += 2; return token;
  }
  if (strncmp(*src, "≥", 3) == 0) {
    token.type = TOKEN_OP_GE; strcpy(token.lexeme, "≥"); *src += 3; return token;
  }
  if (strncmp(*src, "≤", 3) == 0) {
    token.type = TOKEN_OP_LE; strcpy(token.lexeme, "≤"); *src += 3; return token;
  }
  if (strncmp(*src, "≠", 3) == 0) {
    token.type = TOKEN_OP_NOTEQUAL; strcpy(token.lexeme, "≠"); *src += 3; return token;
  }
  if (strncmp(*src, "√", 3) == 0) {
    token.type = TOKEN_OP_SQRT; strcpy(token.lexeme, "√"); *src += 3; return token;
  }

  if (strncmp(*src, "«", 2) == 0) {
    const char *lookahead = *src + 2;
    bool has_comma = false;
    while (*lookahead != '\0' && strncmp(lookahead, "»", 2) != 0) {
      if (*lookahead == ',') {
        has_comma = true; break;
      }
      lookahead++;
    }
    if (has_comma) {
      token.type = TOKEN_LARRAY; strcpy(token.lexeme, "«"); *src += 2; return token;
    } else {
      *src += 2; int i = 0;
      while (**src != '\0' && strncmp(*src, "»", 2) != 0) {
        token.lexeme[i++] = **src; (*src)++;
      }
      if (strncmp(*src, "»", 2) == 0) *src += 2;
      token.lexeme[i] = '\0'; token.type = TOKEN_STRING; return token;
    }
  }
  if (strncmp(*src, "»", 2) == 0) {
    token.type = TOKEN_RARRAY; strcpy(token.lexeme, "»"); *src += 2; return token;
  }

  if (strncmp(*src, "==", 2) == 0) {
    token.type = TOKEN_OP_EQUAL; strcpy(token.lexeme, "=="); *src += 2; return token;
  }
  if (**src == '=') {
    token.type = TOKEN_ASSIGN; strcpy(token.lexeme, "="); (*src)++; return token;
  }
  if (**src == '(') {
    token.type = TOKEN_LPAREN; strcpy(token.lexeme, "("); (*src)++; return token;
  }
  if (**src == ')') {
    token.type = TOKEN_RPAREN; strcpy(token.lexeme, ")"); (*src)++; return token;
  }
  if (**src == '{') {
    token.type = TOKEN_LBRACE; strcpy(token.lexeme, "{"); (*src)++; return token;
  }
  if (**src == '}') {
    token.type = TOKEN_RBRACE; strcpy(token.lexeme, "}"); (*src)++; return token;
  }
  if (**src == ':') {
    token.type = TOKEN_COLON; strcpy(token.lexeme, ":"); (*src)++; return token;
  }
  if (**src == ',') {
    token.type = TOKEN_COMMA; strcpy(token.lexeme, ","); (*src)++; return token;
  }
  if (**src == ';') {
    token.type = TOKEN_SEMICOLON; strcpy(token.lexeme, ";"); (*src)++; return token;
  }

  if (**src == '\'') {
    int i = 0; token.lexeme[i++] = **src; (*src)++;
    while (**src != '\0' && **src != '\'') {
      token.lexeme[i++] = **src; (*src)++;
    }
    if (**src == '\'') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0'; token.type = TOKEN_CHAR_LITERAL; return token;
  }

  if (**src == '"') {
    int i = 0; (*src)++;
    while (**src != '\0' && **src != '"') {
      token.lexeme[i++] = **src; (*src)++;
    }
    if (**src == '"') (*src)++;
    token.lexeme[i] = '\0'; token.type = TOKEN_STRING; return token;
  }

  if ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z') || **src == '_' || **src == '*' || **src == '[' || **src == ']') {
    int i = 0;
    while ((**src >= 'a' && **src <= 'z') || (**src >= 'A' && **src <= 'Z') || (**src >= '0' && **src <= '9') || **src == '_' || **src == '.' || **src == '*' || **src == '[' || **src == ']') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0';

    if (strcmp(token.lexeme, "int") == 0) token.type = TOKEN_INT;
    else if (strcmp(token.lexeme, "dec") == 0) token.type = TOKEN_DEC;
    else if (strcmp(token.lexeme, "com") == 0) token.type = TOKEN_COM;
    else if (strcmp(token.lexeme, "char") == 0) token.type = TOKEN_CHAR;
    else if (strcmp(token.lexeme, "bool") == 0) token.type = TOKEN_BOOL;
    else if (strcmp(token.lexeme, "pkg") == 0) token.type = TOKEN_PKG;
    else if (strcmp(token.lexeme, "func") == 0) token.type = TOKEN_FUNC;
    else if (strcmp(token.lexeme, "punt") == 0) token.type = TOKEN_PUNT;
    else if (strcmp(token.lexeme, "any") == 0) token.type = TOKEN_ANY;
    else if (strcmp(token.lexeme, "auto") == 0) token.type = TOKEN_AUTO;
    else if (strcmp(token.lexeme, "void") == 0) token.type = TOKEN_VOID;
    else if (strcmp(token.lexeme, "add") == 0) token.type = TOKEN_ADD;
    else token.type = TOKEN_IDENTIFIER;
    return token;
  }

  if ((**src >= '0' && **src <= '9')) {
    int i = 0;
    while ((**src >= '0' && **src <= '9') || **src == '.' || **src == 'i') {
      token.lexeme[i++] = **src; (*src)++;
    }
    token.lexeme[i] = '\0'; token.type = TOKEN_NUMBER; return token;
  }

  token.type = TOKEN_UNKNOWN; token.lexeme[0] = **src; token.lexeme[1] = '\0'; (*src)++; return token;
}

void transpilar(const char *codigo_axolang, FILE *f_salida) {
  const char *ptr = codigo_axolang;
  bool in_pkg = false;
  bool needs_semicolon = false;
  char current_pkg_name[128] = "";
  char temp_constructor[4096] = "";

  fprintf("// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---\n");
  fprintf("#include <complex.h>\n#include <math.h>\n#include <tgmath.h>\n#include <string.h>\n#include <stdbool.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n");

  fprintf("typedef struct { int* data; size_t length; } Axoarray_int;\n");
  fprintf("typedef struct { double* data; size_t length; } Axoarray_dec;\n");
  fprintf("typedef struct { char* data; size_t length; } Axoarray_char;\n");
  fprintf("typedef struct { bool* data; size_t length; } Axoarray_bool;\n");
  fprintf("typedef struct { Axoany_Struct* data; size_t length; } Axoarray_any;\n\n");

  // === INYECTAR AQUÍ EL SOPORTE DEL MODELO ANY ===
  fprintf("typedef enum { TYPE_INT, TYPE_DEC, TYPE_COMPLEX, TYPE_CHAR, TYPE_STRING, TYPE_FUNC, TYPE_PKG } AxoType;\n");
  fprintf("typedef struct {\n");
  fprintf("    AxoType type;\n");
  fprintf("    union {\n");
  fprintf("        int i_val;\n");
  fprintf("        double d_val;\n");
  fprintf("        double _Complex cmplx_val;\n");
  fprintf("        char c_val;\n");
  fprintf("        char* s_val;\n");
  fprintf("        void (*func_val)();\n");
  fprintf("        void* pkg_val;\n");
  fprintf("    };\n");
  fprintf("} Axoany_Struct;\n\n");
  // Nota: Cambiamos el alias de "typedef double _Complex Axoany;" por tu nueva estructura dinámina.
  Token token = get_next_token(&ptr);

  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_NEWLINE) {
      if (needs_semicolon) {
        fprintf(";"); needs_semicolon = false;
      }
      fprintf("\n");
      token = get_next_token(&ptr);
      continue;
    }

    switch (token.type) {
      case TOKEN_ADD: {
        token = get_next_token(&ptr);
        if (strstr(token.lexeme, "Basic.axo")) fprintf("#include <stdio.h>\n#include <stdlib.h>\n#include <stddef.h>\n");
        else if (strstr(token.lexeme, "Text.axo")) fprintf("#include <ctype.h>\n");
        else if (strstr(token.lexeme, "Time.axo")) fprintf("#include <time.h>\n");
        else if (strstr(token.lexeme, "Signal.axo")) fprintf("#include <signal.h>\n");
        while (token.type != TOKEN_NEWLINE && token.type != TOKEN_EOF) token = get_next_token(&ptr);
        needs_semicolon = false;
        continue;
      }

      case TOKEN_INT: fprintf("int "); needs_semicolon = false; break;
      case TOKEN_DEC: fprintf("double "); needs_semicolon = false; break;
      case TOKEN_CHAR: fprintf("char "); needs_semicolon = false; break;
      case TOKEN_BOOL: fprintf("bool "); needs_semicolon = false; break;
      case TOKEN_VOID: fprintf("void "); needs_semicolon = false; break;
      case TOKEN_AUTO: fprintf("auto "); needs_semicolon = false; break;
      case TOKEN_COM: fprintf("double _Complex "); needs_semicolon = false; break;
      case TOKEN_ANY: fprintf("Axoany_Struct "); needs_semicolon = false; break;
      case TOKEN_PUNT: fprintf("auto "); needs_semicolon = false; break;

      case TOKEN_PKG: {
        in_pkg = true;
        token = get_next_token(&ptr);
        strcpy(current_pkg_name, token.lexeme);
        fprintf("typedef struct {\n");

        sfprintf(temp_constructor, "%s init_%s() {\n    %s instancia;\n", current_pkg_name, current_pkg_name, current_pkg_name);

        get_next_token(&ptr); // Consumir '='
        get_next_token(&ptr); // Consumir '{'
        needs_semicolon = false;
        break;
      }

      case TOKEN_FUNC: {
        token = get_next_token(&ptr);
        char func_name[128];
        strcpy(func_name, token.lexeme);

        get_next_token(&ptr); // Consumir '='
        get_next_token(&ptr); // Consumir '('

        char argumentos[256] = "";
        Token arg_token = get_next_token(&ptr);
        while (arg_token.type != TOKEN_RPAREN && arg_token.type != TOKEN_EOF) {
          if (strcmp(arg_token.lexeme, "dec") == 0) strcat(argumentos, "double");
          else if (strcmp(arg_token.lexeme, "int") == 0) strcat(argumentos, "int");
          else if (strcmp(arg_token.lexeme, "char") == 0) strcat(argumentos, "char");
          else strcat(argumentos, arg_token.lexeme);
          strcat(argumentos, " ");
          arg_token = get_next_token(&ptr);
        }

        char ret_type[64] = "void";
        Token next_tok = get_next_token(&ptr);

        if (next_tok.type == TOKEN_COLON) {
          char raw_ret[128] = "";
          next_tok = get_next_token(&ptr);
          while (next_tok.type != TOKEN_LBRACE && next_tok.type != TOKEN_NEWLINE && next_tok.type != TOKEN_EOF) {
            strcat(raw_ret, next_tok.lexeme);
            next_tok = get_next_token(&ptr);
          }
          if (strcmp(raw_ret, "int") == 0) strcpy(ret_type, "int");
          else if (strcmp(raw_ret, "dec") == 0) strcpy(ret_type, "double");
          else if (strcmp(raw_ret, "void") == 0) strcpy(ret_type, "void");
          else if (strcmp(raw_ret, "[]int") == 0) strcpy(ret_type, "Axoarray_int");
          else if (strcmp(raw_ret, "[]dec") == 0) strcpy(ret_type, "Axoarray_dec");
          else if (strcmp(raw_ret, "[]any") == 0) strcpy(ret_type, "Axoarray_any");
          else if (strcmp(raw_ret, "[]char") == 0) strcpy(ret_type, "Axoarray_char");
          else if (strstr(raw_ret, "char")) strcpy(ret_type, "char*");
          else if (strstr(raw_ret, "dec")) strcpy(ret_type, "double*");
        }

        while (next_tok.type != TOKEN_LBRACE && next_tok.type != TOKEN_EOF) next_tok = get_next_token(&ptr);

        // ... Dentro de transpilar(), case TOKEN_FUNC:, sección `if (in_pkg)` ...
        if (in_pkg) {
          fprintf("    %s (*%s)(%s);\n", ret_type, func_name, argumentos);

          char buffer_vinc[256];
          // Asegúrate de que no haya saltos de línea al concatenar:
          sfprintf(buffer_vinc, "    instancia.%s = &%s_%s;\n", func_name, current_pkg_name, func_name);
          strcat(temp_constructor, buffer_vinc);

          char buf_func[8192] = "";
          sfprintf(buf_func, "%s %s_%s(%s) {\n", ret_type, current_pkg_name, func_name, argumentos);

          int brace_count = 1;
          Token cuerpo_tok = get_next_token(&ptr);
          bool linea_necesita_punto_coma = false;

          while (cuerpo_tok.type != TOKEN_EOF) {
            if (cuerpo_tok.type == TOKEN_NEWLINE) {
              if (linea_necesita_punto_coma) {
                strcat(buf_func, ";"); linea_necesita_punto_coma = false;
              }
              strcat(buf_func, "\n");
              cuerpo_tok = get_next_token(&ptr);
              continue;
            }

            if (cuerpo_tok.type == TOKEN_LBRACE) brace_count++;
            if (cuerpo_tok.type == TOKEN_RBRACE) {
              brace_count--;
              if (brace_count == 0) break;
            }

            if (strcmp(cuerpo_tok.lexeme, "dec") == 0) {
              strcat(buf_func, "double* ");
              linea_necesita_punto_coma = false;
            }
            // NUEVO: Si viene el identificador de un arreglo dinámico como 'sum[]', eliminamos los corchetes para el malloc
            else if (strstr(cuerpo_tok.lexeme, "[]") != NULL) {
              char nombre_limpio[128];
              strcpy(nombre_limpio, cuerpo_tok.lexeme);
              // Cortamos los caracteres '[]'
              nombre_limpio[strlen(nombre_limpio) - 2] = '\0';
              strcat(buf_func, nombre_limpio);
              strcat(buf_func, " ");
            }
            // NUEVO: Si viene el operador de asignación '=', revisamos si el siguiente es un arreglo literal '«' para evitar el doble '='
            else if (strcmp(cuerpo_tok.lexeme, "=") == 0) {
              const char *look_ahead_malloc = ptr;
              while(*look_ahead_malloc == ' ' || *look_ahead_malloc == '\t') look_ahead_malloc++;

              if (strncmp(look_ahead_malloc, "«", 2) == 0) {
                // Si el paso que sigue es un arreglo '«', dejamos que '«' escriba todo el '= malloc...' solo
                linea_necesita_punto_coma = false;
              } else {
                strcat(buf_func, "= ");
              }
            }
            else if (strcmp(cuerpo_tok.lexeme, "return") == 0) {
              Token next_val = get_next_token(&ptr);
              if (next_val.type == TOKEN_STRING) {
                char ret_obj[512];
                sfprintf(ret_obj, "return (%s){ .data = \"%s\", .length = %zu }", ret_type, next_val.lexeme, strlen(next_val.lexeme));
                strcat(buf_func, ret_obj);
                linea_necesita_punto_coma = true;
              } else if (strcmp(next_val.lexeme, "sum") == 0) {
                char ret_obj[512];
                sfprintf(ret_obj, "return (%s){ .data = sum, .length = 2 }", ret_type);
                strcat(buf_func, ret_obj);
                linea_necesita_punto_coma = true;
              } else {
                strcat(buf_func, "return ");
                strcat(buf_func, next_val.lexeme);
                linea_necesita_punto_coma = true;
              }
            }
            else if (strcmp(cuerpo_tok.lexeme, "×") == 0) {
              strcat(buf_func, "* ");
              linea_necesita_punto_coma = false;
            }
            else if (strcmp(cuerpo_tok.lexeme, "«") == 0) {
              strcat(buf_func, "= malloc(2 * sizeof(double))");
              while(cuerpo_tok.type != TOKEN_RARRAY && cuerpo_tok.type != TOKEN_EOF) {
                cuerpo_tok = get_next_token(&ptr);
              }
              linea_necesita_punto_coma = true;
            }
            else {
              strcat(buf_func, cuerpo_tok.lexeme);
              strcat(buf_func, " ");
              if (cuerpo_tok.type == TOKEN_IDENTIFIER || cuerpo_tok.type == TOKEN_NUMBER) {
                linea_necesita_punto_coma = true;
              }
            }
            cuerpo_tok = get_next_token(&ptr);
          }
          strcat(buf_func, ";\n}\n\n");
          strcat(funciones_extraidas, buf_func);
          needs_semicolon = false;
        }
        // ...
        else {
          // Si encuentra la función 'main', antes de volcar su definición imprimimos las funciones acumuladas
          if (strcmp(func_name, "main") == 0) {
            fprintf("\n// --- METODOS DE COMPORTAMIENTO EXTRAIDOS ---\n%s", funciones_extraidas);
            fprintf("// --- CONSTRUCTORES DE INICIALIZACION ---\n%s\n", constructores_inicializadores);
            // Vaciamos los buffers para que no se vuelvan a imprimir
            funciones_extraidas[0] = '\0';
            constructores_inicializadores[0] = '\0';
          }
          fprintf("%s %s(%s) {\n", ret_type, func_name, argumentos);
          needs_semicolon = false;
        }
        break;
      }

      case TOKEN_IDENTIFIER: {
        if (in_pkg) {
          char var_member[128];
          strcpy(var_member, token.lexeme);

          const char *look = ptr;
          while (*look == ' ' || *look == '\t') look++;
          if (*look == '=') {
            get_next_token(&ptr); // consumir '='
            Token val_tok = get_next_token(&ptr);

            char buffer_init[256];
            sfprintf(buffer_init, "    instancia.%s = %s;\n", var_member, val_tok.lexeme);
            strcat(temp_constructor, buffer_init);

            fprintf("    ");
            needs_semicolon = true;
            break;
          }
        }

        if (strcmp(token.lexeme, "algo") == 0 || strcmp(token.lexeme, "clase") == 0) {
          char pkg_type[128];
          strcpy(pkg_type, token.lexeme);
          Token obj_tok = get_next_token(&ptr);
          fprintf("%s %s = init_%s()", pkg_type, obj_tok.lexeme, pkg_type);
          needs_semicolon = true;
          break;
        }

        if (strcmp(token.lexeme, "Stop") == 0) {
          const char *look = ptr;
          while (*look == ' ' || *look == '\t') look++;
          if (*look == '(') {
            const char *look2 = look + 1;
            while (*look2 == ' ' || *look2 == '\t') look2++;
            if (strncmp(look2, "system", 6) == 0) {
              const char *look3 = look2 + 6;
              while (*look3 == ' ' || *look3 == '\t') look3++;
              if (*look3 == ')') {
                ptr = look3 + 1; fprintf("exit(0)"); needs_semicolon = true; break;
              }
            }
          }
        }

        fprintf("%s ", token.lexeme);
        needs_semicolon = true;
        break;
      }

      case TOKEN_CHAR_LITERAL: fprintf("%s ", token.lexeme); needs_semicolon = true; break;

      case TOKEN_ASSIGN: {
        // Si estamos procesando propiedades por defecto dentro de un "pkg",
        // dejamos que el transpilador lo ignore para que el constructor lo maneje.
        if (in_pkg) {
          needs_semicolon = false;
          break;
        }

        // --- DETECCIÓN DE LAMBDAS Y COMODINES ANY ---
        // Miramos lo que hay justo después del '=' usando un puntero de exploración temporal
        const char *look_lambda = ptr;
        while (*look_lambda == ' ' || *look_lambda == '\t') look_lambda++;

        // REGLA 1: ¿Viene una función anónima? ej: = ( ) : []any { ... }
        if (*look_lambda == '(') {
          static int lambda_counter = 0;
          char lambda_name[64];
          sfprintf(lambda_name, "__axo_lambda_%d", ++lambda_counter);

          char buf_lambda[4096] = "";
          char ret_type[64] = "void"; // Por defecto si no especifica tipo

          // Avanzamos los tokens temporalmente para extraer la firma y el tipo de retorno (: tipo)
          Token l_tok = get_next_token(&ptr); // Consume el '(' original
          while (l_tok.type != TOKEN_LBRACE && l_tok.type != TOKEN_EOF) {
            if (l_tok.type == TOKEN_COLON) {
              l_tok = get_next_token(&ptr); // Lee el tipo de retorno después de ':'
              if (strcmp(l_tok.lexeme, "[]any") == 0) strcpy(ret_type, "Axoarray_any");
              else if (strcmp(l_tok.lexeme, "int") == 0) strcpy(ret_type, "int");
              else if (strcmp(l_tok.lexeme, "dec") == 0) strcpy(ret_type, "double");
            }
            l_tok = get_next_token(&ptr);
          }

          // Empezamos a escribir la función como si fuera una función global pura de C
          sfprintf(buf_lambda, "%s %s() {\n    ", ret_type, lambda_name);

          // Extraemos recursivamente todo el cuerpo que vive dentro de las llaves { ... }
          int b_count = 1;
          l_tok = get_next_token(&ptr);
          bool lambda_necesita_punto_coma = false;

          while (l_tok.type != TOKEN_EOF) {
            if (l_tok.type == TOKEN_NEWLINE) {
              if (lambda_necesita_punto_coma) {
                strcat(buf_lambda, ";");
                lambda_necesita_punto_coma = false;
              }
              strcat(buf_lambda, "\n    ");
              l_tok = get_next_token(&ptr);
              continue;
            }
            if (l_tok.type == TOKEN_LBRACE) b_count++;
            if (l_tok.type == TOKEN_RBRACE) {
              b_count--;
              if (b_count == 0) break; // Fin de la lambda
            }

            // Re-inyectar comillas si el lexer se comió las comillas en los prints/strings internos
            if (l_tok.type == TOKEN_STRING) {
              char string_formateado[512];
              sfprintf(string_formateado, "\"%s\" ", l_tok.lexeme);
              strcat(buf_lambda, string_formateado);
              lambda_necesita_punto_coma = true;
            } else {
              strcat(buf_lambda, l_tok.lexeme);
              strcat(buf_lambda, " ");
              if (l_tok.type == TOKEN_IDENTIFIER || l_tok.type == TOKEN_NUMBER) {
                lambda_necesita_punto_coma = true;
              }
            }
            l_tok = get_next_token(&ptr);
          }
          strcat(buf_lambda, ";\n}\n\n");

          // Enviamos la lambda generada al búfer global de métodos acumulados
          strcat(funciones_extraidas, buf_lambda);

          // Generamos el Prototipo (Forward Declaration) para que la asignación global no falle
          // Esto se puede acumular en un búfer o imprimir directamente arriba.
          // Para esta arquitectura, la imprimiremos usando literales de C23:
          fprintf("= (Axoany_Struct){ .type = TYPE_FUNC, .func_val = &__axo_lambda_%d }", lambda_counter);
          needs_semicolon = true;
        }

        // REGLA 2: ¿Viene un string directo asignado al any? ej: any var = "xd"
        else if (*look_lambda == '"') {
          Token str_tok = get_next_token(&ptr); // Consumir el string literal
          fprintf("= (Axoany_Struct){ .type = TYPE_STRING, .s_val = \"%s\" }", str_tok.lexeme);
          needs_semicolon = true;
        }

        // REGLA 3: Asignación estándar para cualquier otra variable (int, dec, etc.)
        else {
          fprintf("= ");
          needs_semicolon = false;
        }
        break;
      }

      case TOKEN_REF_ARROW: fprintf("&"); needs_semicolon = false; break;

      case TOKEN_NUMBER: {
        size_t len = strlen(token.lexeme);
        if (len > 0 && token.lexeme[len - 1] == 'i') {
          token.lexeme[len - 1] = '\0';
          fprintf("%s * _Complex_I", token.lexeme);
        } else {
          fprintf("%s ", token.lexeme);
        }
        needs_semicolon = true;
        break;
      }

      case TOKEN_STRING: fprintf("\"%s\" ", token.lexeme); needs_semicolon = true; break;
      case TOKEN_LARRAY: fprintf("{ "); needs_semicolon = false; break;
      case TOKEN_RARRAY: fprintf(" }"); needs_semicolon = true; break;
      case TOKEN_SEMICOLON: fprintf("; "); needs_semicolon = false; break;

      case TOKEN_OP_MULT: fprintf("* "); needs_semicolon = false; break;
      case TOKEN_OP_DIV: fprintf("/ "); needs_semicolon = false; break;
      case TOKEN_OP_SQRT: fprintf("sqrt"); needs_semicolon = false; break;
      case TOKEN_OP_EXP: fprintf("exp"); needs_semicolon = false; break;
      case TOKEN_OP_XOR: fprintf("^ "); needs_semicolon = false; break;
      case TOKEN_OP_AND: fprintf("&& "); needs_semicolon = false; break;
      case TOKEN_OP_OR: fprintf("|| "); needs_semicolon = false; break;
      case TOKEN_OP_NOT: fprintf("! "); needs_semicolon = false; break;
      case TOKEN_OP_GE: fprintf(">= "); needs_semicolon = false; break;
      case TOKEN_OP_LE: fprintf("<= "); needs_semicolon = false; break;
      case TOKEN_OP_NOTEQUAL: fprintf("!= "); needs_semicolon = false; break;

      case TOKEN_LBRACE: fprintf("{ "); needs_semicolon = false; break;
      case TOKEN_RBRACE: {
        if (in_pkg) {
          fprintf("} %s;\n\n", current_pkg_name);

          strcat(temp_constructor, "    return instancia;\n}\n\n");
          strcat(constructores_inicializadores, temp_constructor);

          in_pkg = false;
        } else {
          fprintf("}\n");
        }
        needs_semicolon = false;
        break;
      }

      default:
      fprintf("%s ", token.lexeme);
      if (strcmp(token.lexeme, ")") == 0 || strcmp(token.lexeme, "]") == 0) needs_semicolon = true;
      break;
    }

    token = get_next_token(&ptr);
  }
}
int main(int argc, char* argv[]) {
  // 1. ABRIR Y LEER EL ARCHIVO FUENTE DE AXOLANG
  FILE* origen = fopen(argv[1], "r");
  if (!origen) {
    printf("Error: No se pudo abrir el archivo fuente 'programa.axo'\n");
    return 1;
  }

  // Buscamos el tamaño del archivo para asignarle memoria exacta al buffer
  fseek(origen, 0, SEEK_END);
  long tamano = ftell(origen);
  fseek(origen, 0, SEEK_SET);

  char* codigo_axolang = malloc(tamano + 1);
  if (!codigo_axolang) {
    printf("Error: Memoria insuficiente para cargar el código fuente.\n");
    fclose(origen);
    return 1;
  }

  // Leemos todo el contenido del archivo hacia nuestra cadena de texto
  size_t leidos = fread(codigo_axolang, 1, tamano, origen);
  codigo_axolang[leidos] = '\0'; // Aseguramos el fin de cadena
  fclose(origen);

  // 2. CREAR EL ARCHIVO DONDE SE ESCRIBIRÁ EL C23 AUTO-GENERADO
  FILE* salida_c = fopen(argv[2], "w");
  if (!salida_c) {
    printf("Error: No se pudo crear el archivo de salida 'salida.c'\n");
    free(codigo_axolang);
    return 1;
  }

  // Inyectamos las cabeceras estándar iniciales requeridas antes del código transpilado
  fprintf(salida_c, "// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---\n");
  fprintf(salida_c, "#include <complex.h>\n#include <math.h>\n#include <tgmath.h>\n");
  fprintf(salida_c, "#include <string.h>\n#include <stdbool.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n");

  // Inyectamos el modelo de datos para el soporte de variables dinámicas 'any'
  fprintf(salida_c, "typedef enum { TYPE_INT, TYPE_DEC, TYPE_COMPLEX, TYPE_CHAR, TYPE_STRING, TYPE_FUNC, TYPE_PKG } AxoType;\n");
  fprintf(salida_c, "typedef struct {\n");
  fprintf(salida_c, "    AxoType type;\n");
  fprintf(salida_c, "    union {\n");
  fprintf(salida_c, "        int i_val;\n");
  fprintf(salida_c, "        double d_val;\n");
  fprintf(salida_c, "        double _Complex cmplx_val;\n");
  fprintf(salida_c, "        char c_val;\n");
  fprintf(salida_c, "        char* s_val;\n");
  fprintf(salida_c, "        void (*func_val)();\n");
  fprintf(salida_c, "        void* pkg_val;\n");
  fprintf(salida_c, "    };\n");
  fprintf(salida_c, "} Axoany_Struct;\n\n");

  // Inyectamos las definiciones de estructuras para los Slices estándar de Axolang
  fprintf(salida_c, "typedef struct { int* data; size_t length; } Axoarray_int;\n");
  fprintf(salida_c, "typedef struct { double* data; size_t length; } Axoarray_dec;\n");
  fprintf(salida_c, "typedef struct { char* data; size_t length; } Axoarray_char;\n");
  fprintf(salida_c, "typedef struct { Axoany_Struct* data; size_t length; } Axoarray_any;\n\n");

  // ====================================================================
  // LLAMADA CLAVE A TU FUNCIÓN TRANSPILAR
  // ====================================================================
  // Enviamos la cadena con el código .axo y el puntero al archivo .c
  transpilar(codigo_axolang, salida_c);

  // Inyectamos las lambdas y métodos de comportamiento que se extrajeron durante el parseo
  // Justo antes de terminar de escribir el archivo para que queden disponibles globalmente
  fprintf(salida_c, "\n// --- PROTOTIPOS DE LAMBDAS EXTRAÍDAS ---\n");
  fprintf(salida_c, "%s\n", prototipos_lambdas);

  fprintf(salida_c, "\n// --- MÉTODOS DE COMPORTAMIENTO EXTRAÍDOS ---\n");
  fprintf(salida_c, "%s\n", funciones_extraidas);

  // Cerramos el archivo temporal físico en el disco duro
  fclose(salida_c);
  free(codigo_axolang);

  printf("[Axolang] Código intermedio 'salida.c' generado con éxito.\n");

  // 4. INVOCAR AL COMPILADOR DEL SISTEMA (GCC o CLANG) AUTOMÁTICAMENTE
  printf("[Axolang] Compilando binario nativo en estándar C23...\n");

  // Lanzamos el comando usando system() pasándole el flag -std=c23
  int resultado_compilacion = system("gcc salida.c -o programa_ejecutable -std=c23 -lm");

  if (resultado_compilacion == 0) {
    printf("[Axolang] ¡Compilación exitosa! Ejecutable creado como './programa_ejecutable'\n");
  } else {
    printf("[Axolang] Error durante la compilación nativa de C. Verifica los búferes sintácticos.\n");
  }

  return resultado_compilacion;
}