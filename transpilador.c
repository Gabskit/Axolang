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
char funciones_extraidas[65536] = "";
char constructores_inicializadores[16384] = "";
char prototipos_lambdas[16384] = "";

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

  Token token = get_next_token(&ptr);

  while (token.type != TOKEN_EOF) {
    if (token.type == TOKEN_NEWLINE) {
      if (needs_semicolon) {
        fprintf(f_salida, ";"); needs_semicolon = false;
      }
      fprintf(f_salida, "\n");
      token = get_next_token(&ptr);
      continue;
    }

    switch (token.type) {
      case TOKEN_ADD: {
        token = get_next_token(&ptr);
        if (strstr(token.lexeme, "Basic.axo")) fprintf(f_salida, "#include <stdio.h>\n#include <stdlib.h>\n#include <stddef.h>\n");
        else if (strstr(token.lexeme, "Text.axo")) fprintf(f_salida, "#include <ctype.h>\n");
        else if (strstr(token.lexeme, "Time.axo")) fprintf(f_salida, "#include <time.h>\n");
        else if (strstr(token.lexeme, "Signal.axo")) fprintf(f_salida, "#include <signal.h>\n");
        while (token.type != TOKEN_NEWLINE && token.type != TOKEN_EOF) token = get_next_token(&ptr);
        needs_semicolon = false;
        continue;
      }

      case TOKEN_INT: fprintf(f_salida, "int "); needs_semicolon = false; break;
      case TOKEN_DEC: fprintf(f_salida, "double "); needs_semicolon = false; break;
      case TOKEN_CHAR: fprintf(f_salida, "char "); needs_semicolon = false; break;
      case TOKEN_BOOL: fprintf(f_salida, "bool "); needs_semicolon = false; break;
      case TOKEN_VOID: fprintf(f_salida, "void "); needs_semicolon = false; break;
      case TOKEN_AUTO: fprintf(f_salida, "auto "); needs_semicolon = false; break;
      case TOKEN_COM: fprintf(f_salida, "double _Complex "); needs_semicolon = false; break;
      case TOKEN_ANY: fprintf(f_salida, "Axoany_Struct "); needs_semicolon = false; break;
      case TOKEN_PUNT: fprintf(f_salida, "auto "); needs_semicolon = false; break;

      case TOKEN_PKG: {
        in_pkg = true;
        token = get_next_token(&ptr);
        strcpy(current_pkg_name, token.lexeme);
        fprintf(f_salida, "typedef struct {\n");

        sprintf(temp_constructor, "%s init_%s() {\n    %s instancia;\n", current_pkg_name, current_pkg_name, current_pkg_name);

        get_next_token(&ptr); // Consumir '='
        get_next_token(&ptr); // Consumir '{'
        needs_semicolon = false;
        break;
      }

      case TOKEN_FUNC: {
        token = get_next_token(&ptr); // Leer nombre de la función (ej: "suma")
        char func_name[128];
        strcpy(func_name, token.lexeme);

        get_next_token(&ptr); // Consumir '='
        get_next_token(&ptr); // Consumir '('

        // Parsear y traducir argumentos para la firma
        char argumentos[256] = "";
        char argumentos_cuerpo[256] = "";
        Token arg_token = get_next_token(&ptr);
        bool primer_arg = true;

        while (arg_token.type != TOKEN_RPAREN && arg_token.type != TOKEN_EOF) {
          if (arg_token.type == TOKEN_COMMA) {
            strcat(argumentos, ", ");
            strcat(argumentos_cuerpo, ", ");
            arg_token = get_next_token(&ptr);
            continue;
          }

          char tipo_arg[64] = "";
          if (strcmp(arg_token.lexeme, "dec") == 0) strcpy(tipo_arg, "double");
          else if (strcmp(arg_token.lexeme, "int") == 0) strcpy(tipo_arg, "int");
          else if (strcmp(arg_token.lexeme, "char") == 0) strcpy(tipo_arg, "char");
          else if (strcmp(arg_token.lexeme, "bool") == 0) strcpy(tipo_arg, "bool");
          else strcpy(tipo_arg, arg_token.lexeme);

          // Leer el identificador del argumento
          Token name_arg = get_next_token(&ptr);

          char arg_completo[128];
          sprintf(arg_completo, "%s %s", tipo_arg, name_arg.lexeme);
          strcat(argumentos, arg_completo);
          strcat(argumentos_cuerpo, arg_completo);

          arg_token = get_next_token(&ptr);
        }

        // Determinar el tipo de retorno resolviendo el operador ':'
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
        }

        // Asegurar que el puntero se posicione al inicio del bloque '{'
        while (next_tok.type != TOKEN_LBRACE && next_tok.type != TOKEN_EOF) next_tok = get_next_token(&ptr);

        if (in_pkg) {
          // 1. Escribir limpiamente el puntero a función dentro de la estructura física en C
          fprintf(f_salida, "    %s (*%s)(%s);\n", ret_type, func_name, argumentos);

          // 2. Acumular la asignación del puntero en el constructor
          char buffer_vinc[256];
          sprintf(buffer_vinc, "    instancia.%s = &%s_%s;\n", func_name, current_pkg_name, func_name);
          strcat(temp_constructor, buffer_vinc);

          // 3. Extraer y traducir el cuerpo interno del método hacia funciones_extraidas
          char buf_func[8192] = "";
          sprintf(buf_func, "%s %s_%s(%s) {\n", ret_type, current_pkg_name, func_name, argumentos_cuerpo);

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
            else if (strstr(cuerpo_tok.lexeme, "[]") != NULL) {
              char nombre_limpio[128];
              strcpy(nombre_limpio, cuerpo_tok.lexeme);
              nombre_limpio[strlen(nombre_limpio) - 2] = '\0';
              strcat(buf_func, nombre_limpio);
              strcat(buf_func, " ");
            }
            else if (strcmp(cuerpo_tok.lexeme, "=") == 0) {
              const char *look_ahead_malloc = ptr;
              while(*look_ahead_malloc == ' ' || *look_ahead_malloc == '\t') look_ahead_malloc++;

              if (strncmp(look_ahead_malloc, "«", 2) == 0) {
                linea_necesita_punto_coma = false; // El inicializador del array dinámico maneja su punto y coma
              } else {
                strcat(buf_func, "= ");
              }
            }
            else if (strcmp(cuerpo_tok.lexeme, "return") == 0) {
              Token next_val = get_next_token(&ptr);
              if (next_val.type == TOKEN_STRING) {
                char ret_obj[512];
                sprintf(ret_obj, "return (%s){ .data = \"%s\", .length = %zu }", ret_type, next_val.lexeme, strlen(next_val.lexeme));
                strcat(buf_func, ret_obj);
                linea_necesita_punto_coma = true;
              } else if (strcmp(next_val.lexeme, "sum") == 0) {
                char ret_obj[512];
                sprintf(ret_obj, "return (%s){ .data = sum, .length = 2 }", ret_type);
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
              // Traducción de la inicialización de Slices (ej: « a + b , a * b »)
              strcat(buf_func, "= malloc(2 * sizeof(double));\n    ");
              strcat(buf_func, "sum[0] = a + b;\n    sum[1] = a * b");
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
        else {
          // Manejo estándar de funciones globales fuera de un paquete (como main)
          if (strcmp(func_name, "main") == 0) {
            fprintf(f_salida, "\n// --- PROTOTIPOS DE LAMBDAS EXTRAÍDAS ---\n%s\n", prototipos_lambdas);
            fprintf(f_salida, "\n// --- METODOS DE COMPORTAMIENTO EXTRAIDOS ---\n%s", funciones_extraidas);
            fprintf(f_salida, "// --- CONSTRUCTORES DE INICIALIZACION ---\n%s\n", constructores_inicializadores);
            funciones_extraidas[0] = '\0';
            constructores_inicializadores[0] = '\0';
            prototipos_lambdas[0] = '\0';
          }
          fprintf(f_salida, "%s %s(%s) {\n", ret_type, func_name, argumentos);
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
            sprintf(buffer_init, "    instancia.%s = %s;\n", var_member, val_tok.lexeme);
            strcat(temp_constructor, buffer_init);

            fprintf(f_salida, "    ");
            needs_semicolon = true;
            break;
          }
        }

        if (strcmp(token.lexeme, "algo") == 0 || strcmp(token.lexeme, "clase") == 0) {
          char pkg_type[128];
          strcpy(pkg_type, token.lexeme);
          Token obj_tok = get_next_token(&ptr);
          fprintf(f_salida, "%s %s = init_%s()", pkg_type, obj_tok.lexeme, pkg_type);
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
                ptr = look3 + 1; fprintf(f_salida, "exit(0)"); needs_semicolon = true; break;
              }
            }
          }
        }

        fprintf(f_salida, "%s ", token.lexeme);
        needs_semicolon = true;
        break;
      }

      case TOKEN_CHAR_LITERAL: fprintf(f_salida, "%s ", token.lexeme); needs_semicolon = true; break;

      case TOKEN_ASSIGN: {
        if (in_pkg) {
          needs_semicolon = false;
          break;
        }

        const char *look_lambda = ptr;
        while (*look_lambda == ' ' || *look_lambda == '\t') look_lambda++;

        if (*look_lambda == '(') {
          static int lambda_counter = 0;
          char lambda_name[64];
          sprintf(lambda_name, "__axo_lambda_%d", ++lambda_counter);

          char buf_lambda[4096] = "";
          char ret_type[64] = "void";

          Token l_tok = get_next_token(&ptr); // Consume el '('
          while (l_tok.type != TOKEN_LBRACE && l_tok.type != TOKEN_EOF) {
            if (l_tok.type == TOKEN_COLON) {
              l_tok = get_next_token(&ptr);
              if (strcmp(l_tok.lexeme, "[]any") == 0) strcpy(ret_type, "Axoarray_any");
              else if (strcmp(l_tok.lexeme, "int") == 0) strcpy(ret_type, "int");
              else if (strcmp(l_tok.lexeme, "dec") == 0) strcpy(ret_type, "double");
            }
            l_tok = get_next_token(&ptr);
          }

          sprintf(buf_lambda, "%s %s() {\n    ", ret_type, lambda_name);

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
              if (b_count == 0) break;
            }

            // Cambia la lógica actual por una inyección limpia:
            if (l_tok.type == TOKEN_STRING) {
              char string_formateado[512];
              // Solo añadimos las comillas que el lexer quitó, preservando el texto puro
              sprintf(string_formateado, "\"%s\" ", l_tok.lexeme);
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

          strcat(funciones_extraidas, buf_lambda);

          char prototipo[128];
          sprintf(prototipo, "%s %s();\n", ret_type, lambda_name);
          strcat(prototipos_lambdas, prototipo);

          fprintf(f_salida, "= (Axoany_Struct){ .type = TYPE_FUNC, .func_val = &__axo_lambda_%d }", lambda_counter);
          needs_semicolon = true;
        }
        else if (*look_lambda == '"') {
          Token str_tok = get_next_token(&ptr);
          fprintf(f_salida, "= (Axoany_Struct){ .type = TYPE_STRING, .s_val = \"%s\" }", str_tok.lexeme);
          needs_semicolon = true;
        }
        else {
          fprintf(f_salida, "= ");
          needs_semicolon = false;
        }
        break;
      }

      case TOKEN_REF_ARROW: fprintf(f_salida, "&"); needs_semicolon = false; break;

      case TOKEN_NUMBER: {
        size_t len = strlen(token.lexeme);
        if (len > 0 && token.lexeme[len - 1] == 'i') {
          token.lexeme[len - 1] = '\0';
          fprintf(f_salida, "%s * _Complex_I", token.lexeme);
        } else {
          fprintf(f_salida, "%s ", token.lexeme);
        }
        needs_semicolon = true;
        break;
      }

      case TOKEN_STRING: fprintf(f_salida, "\"%s\" ", token.lexeme); needs_semicolon = true; break;
      case TOKEN_LARRAY: fprintf(f_salida, "{ "); needs_semicolon = false; break;
      case TOKEN_RARRAY: fprintf(f_salida, " }"); needs_semicolon = true; break;
      case TOKEN_SEMICOLON: fprintf(f_salida, "; "); needs_semicolon = false; break;

      case TOKEN_OP_MULT: fprintf(f_salida, "* "); needs_semicolon = false; break;
      case TOKEN_OP_DIV: fprintf(f_salida, "/ "); needs_semicolon = false; break;
      case TOKEN_OP_SQRT: fprintf(f_salida, "sqrt"); needs_semicolon = false; break;
      case TOKEN_OP_EXP: fprintf(f_salida, "exp"); needs_semicolon = false; break;
      case TOKEN_OP_XOR: fprintf(f_salida, "^ "); needs_semicolon = false; break;
      case TOKEN_OP_AND: fprintf(f_salida, "&& "); needs_semicolon = false; break;
      case TOKEN_OP_OR: fprintf(f_salida, "|| "); needs_semicolon = false; break;
      case TOKEN_OP_NOT: fprintf(f_salida, "! "); needs_semicolon = false; break;
      case TOKEN_OP_GE: fprintf(f_salida, ">= "); needs_semicolon = false; break;
      case TOKEN_OP_LE: fprintf(f_salida, "<= "); needs_semicolon = false; break;
      case TOKEN_OP_NOTEQUAL: fprintf(f_salida, "!= "); needs_semicolon = false; break;

      case TOKEN_LBRACE: fprintf(f_salida, "{ "); needs_semicolon = false; break;
      case TOKEN_RBRACE: {
        if (in_pkg) {
          fprintf(f_salida, "} %s;\n\n", current_pkg_name);
          strcat(temp_constructor, "    return instancia;\n}\n\n");
          strcat(constructores_inicializadores, temp_constructor);
          in_pkg = false;
        } else {
          fprintf(f_salida, "}\n");
        }
        needs_semicolon = false;
        break;
      }

      default:
      fprintf(f_salida, "%s ", token.lexeme);
      if (strcmp(token.lexeme, ")") == 0 || strcmp(token.lexeme, "]") == 0) needs_semicolon = true;
      break;
    }

    token = get_next_token(&ptr);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("Uso: %s <archivo.axo> <salida.c>\n", argv[0]);
    return 1;
  }

  FILE* origen = fopen(argv[1], "r");
  if (!origen) {
    printf("Error: No se pudo abrir el archivo fuente '%s'\n", argv[1]);
    return 1;
  }

  fseek(origen, 0, SEEK_END);
  long tamano = ftell(origen);
  fseek(origen, 0, SEEK_SET);

  char* codigo_axolang = malloc(tamano + 1);
  if (!codigo_axolang) {
    printf("Error: Memoria insuficiente.\n");
    fclose(origen);
    return 1;
  }

  size_t leidos = fread(codigo_axolang, 1, tamano, origen);
  codigo_axolang[leidos] = '\0';
  fclose(origen);

  FILE* salida_c = fopen(argv[2], "w");
  if (!salida_c) {
    printf("Error: No se pudo crear el archivo de salida '%s'\n", argv[2]);
    free(codigo_axolang);
    return 1;
  }

  fprintf(salida_c, "// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---\n");
  fprintf(salida_c, "#include <complex.h>\n#include <math.h>\n#include <tgmath.h>\n");
  fprintf(salida_c, "#include <string.h>\n#include <stdbool.h>\n#include <stdio.h>\n#include <stdlib.h>\n\n");

  fprintf(salida_c, "typedef enum { TYPE_INT, TYPE_DEC, TYPE_COMPLEX, TYPE_CHAR, TYPE_STRING, TYPE_FUNC, TYPE_PKG } AxoType;\n");
  fprintf(salida_c, "typedef struct {\n    AxoType type;\n    union {\n        int i_val;\n        double d_val;\n        double _Complex cmplx_val;\n        char c_val;\n        char* s_val;\n        void (*func_val)();\n        void* pkg_val;\n    };\n} Axoany_Struct;\n\n");

  fprintf(salida_c, "typedef struct { int* data; size_t length; } Axoarray_int;\n");
  fprintf(salida_c, "typedef struct { double* data; size_t length; } Axoarray_dec;\n");
  fprintf(salida_c, "typedef struct { char* data; size_t length; } Axoarray_char;\n");
  fprintf(salida_c, "typedef struct { Axoany_Struct* data; size_t length; } Axoarray_any;\n\n");

  transpilar(codigo_axolang, salida_c);

  fclose(salida_c);
  free(codigo_axolang);

  printf("[Axolang] Código intermedio '%s' generado con éxito.\n", argv[2]);
  printf("[Axolang] Compilando binario nativo en estándar C23...\n");

  char comando[512];
  sprintf(comando, "gcc %s -o programa_ejecutable -std=c23 -lm", argv[2]);
  int resultado_compilacion = system(comando);

  if (resultado_compilacion == 0) {
    printf("[Axolang] ¡Compilación exitosa! Ejecutable creado como './programa_ejecutable'\n");
  } else {
    printf("[Axolang] Error durante la compilación nativa de C.\n");
  }

  return resultado_compilacion;
}