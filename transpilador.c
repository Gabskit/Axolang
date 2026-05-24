#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <ctype.h>

#define MAX_LINE_LEN 65536
#define MAX_BUFFER_FUNCTIONS 65536
#define MAX_METHODS 655

// --- Variables globales de control de estado ---
char funciones_paquetes[MAX_BUFFER_FUNCTIONS] = {
  0
};
char buffer_structs[MAX_BUFFER_FUNCTIONS] = {
  0
};
bool in_pkg = false;
bool in_func_inside_pkg = false;
char current_pkg[655] = {
  0
};

// NUEVO: Control de retornos de arreglos
bool inside_any_function = false;
bool actual_func_retorna_int_array = false;
bool actual_func_retorna_dec_array = false;

// Estructura para registrar métodos dinámicamente
char lista_metodos[MAX_METHODS][1024];
int total_metodos = 0;
typedef struct {
  char items[65536][1024];
  int count;
} Includes;

void add_include(Includes *inc, const char *lib) {
  for (int i = 0; i < inc->count; i++) {
    if (strcmp(inc->items[i], lib) == 0) return;
  }
  strcpy(inc->items[inc->count++], lib);
}

void replace_string(char *orig, const char *rep, const char *with, char *output) {
  char buffer[MAX_LINE_LEN] = {
    0
  };
  char *insert_point = orig;
  char *tmp = buffer;
  int rep_len = strlen(rep);
  int with_len = strlen(with);

  while (1) {
    char *p = strstr(insert_point, rep);
    if (p == nullptr) {
      // Usando nullptr nativo de C23
      strcpy(tmp, insert_point);
      break;
    }
    memcpy(tmp, insert_point, p - insert_point);
    tmp += p - insert_point;
    memcpy(tmp, with, with_len);
    tmp += with_len;
    insert_point = p + rep_len;
  }
  strcpy(output, buffer);
}

void transpile_line(char *line, Includes *inc, char *out_line) {
  char src[MAX_LINE_LEN];
  strcpy(src, line);

  // 1. Trim inicial
  char *start = src;
  while (isspace((unsigned char)*start)) start++;
  if (strlen(start) == 0) {
    strcpy(out_line, "");
    return;
  }
  char *end = start + strlen(start) - 1;
  while (end > start && isspace((unsigned char)*end)) end--;
  *(end + 1) = '\0';

  if (strlen(start) == 0) {
    strcpy(out_line, "");
    return;
  }

  // 2. Directivas de inclusión (add)
  if (strncmp(start, "add", 3) == 0) {
    if (strstr(start, "<Basic.axo>")) {
      add_include(inc, "#include <stdio.h>");
      add_include(inc, "#include <stdlib.h>");
      add_include(inc, "#include <stddef.h>");
    }
    if (strstr(start, "<Math.axo>")) {
      add_include(inc, "#include <math.h>");
      add_include(inc, "#include <tgmath.h>");
    }
    if (strstr(start, "<Text.axo>")) {
      add_include(inc, "#include <string.h>");
      add_include(inc, "#include <ctype.h>");
    }
    if (strstr(start, "<Signal.axo>")) {
      add_include(inc, "#include <signal.h>");
    }
    if (strstr(start, "<Time.axo>")) {
      add_include(inc, "#include <time.h>");
    }
    strcpy(out_line, "");
    return;
  }

  if (strcmp(start, "main()") == 0 || strcmp(start, "main") == 0) {
    strcpy(out_line, "");
    return;
  }

  char buffer[MAX_LINE_LEN];
  strcpy(buffer, start);

  // Control estricto de cierre de llaves en funciones globales
  if (strcmp(buffer, "}") == 0 && !in_pkg) {
    inside_any_function = false;
    actual_func_retorna_int_array = false;
    actual_func_retorna_dec_array = false;
  }

  // =============================================================
  // INTERCEPTOR DE RETURN PARA ARREGLOS (ÁMBITO INTERNO)
  // =============================================================
  if (strncmp(buffer, "return ", 7) == 0) {
    // CORRECCIÓN C23: El interceptor solo actúa si REALMENTE estamos dentro de una función que lo requiere
    if (inside_any_function && (actual_func_retorna_int_array || actual_func_retorna_dec_array)) {
      char var_name[50] = {
        0
      };
      sscanf(buffer, "return %[^=\n ;]", var_name);
      char temp_ret[1024];
      if (actual_func_retorna_int_array) {
        sprintf(out_line, "AxoArray_int _ret = { .data = %s, .length = sizeof(%s)/sizeof(%s[0]) };\n    return _ret;", var_name, var_name, var_name);
        return;
      }
      else if (actual_func_retorna_dec_array) {
        sprintf(out_line, "AxoArray_dec _ret = { .data = %s, .length = sizeof(%s)/sizeof(%s[0]) };\n    return _ret;", var_name, var_name, var_name);
        return;
      }
      if (in_pkg && in_func_inside_pkg) {
        strcat(funciones_paquetes, "    ");
        strcat(funciones_paquetes, temp_ret);
        strcat(funciones_paquetes, "\n");
        strcpy(out_line, "");
      } else {
        strcpy(out_line, temp_ret);
      }
    }
  }

  // =============================================================
  // ESTADO: DENTRO DE UN PAQUETE (pkg)
  // =============================================================
  if (in_pkg) {
    // CASO A: Inicio de un método del paquete
    if (!in_func_inside_pkg && (strncmp(buffer, "func ", 5) == 0 || strncmp(buffer, "Func ", 5) == 0)) {
      in_func_inside_pkg = true;
      inside_any_function = true;
      char func_name[50] = {
        0
      };
      sscanf(buffer, "%*s %[^= \t]", func_name);

      int len_fn = strlen(func_name);
      while(len_fn > 0 && isspace((unsigned char)func_name[len_fn - 1])) {
        func_name[len_fn - 1] = '\0';
        len_fn--;
      }

      if (total_metodos < MAX_METHODS && strlen(func_name) > 0) {
        strcpy(lista_metodos[total_metodos++], func_name);
      }

      char argumentos[256] = "";
      char *open_p = strchr(buffer, '(');
      char *close_p = strchr(buffer, ')');
      if (open_p && close_p && (close_p > open_p + 1)) {
        size_t arg_len = close_p - (open_p + 1);
        strncpy(argumentos, open_p + 1, arg_len);
        argumentos[arg_len] = '\0';
      }

      char ret_type[30] = "void";
      // Primero evaluamos si es un arreglo de enteros o decimales
      if (strstr(buffer, ":[]int") || strstr(buffer, ":[]Int")) {
        actual_func_retorna_int_array = true;
        strcpy(ret_type, "AxoArray_int");
      }
      else if (strstr(buffer, ":[]dec") || strstr(buffer, ":[]Dec")) {
        actual_func_retorna_dec_array = true;
        strcpy(ret_type, "AxoArray_dec");
      }
      // Luego evaluamos los tipos simples comunes
      else if (strstr(buffer, ":int") || strstr(buffer, ":Int")) {
        strcpy(ret_type, "int");
      }
      else if (strstr(buffer, ":dec") || strstr(buffer, ":Dec")) {
        strcpy(ret_type, "double");
      }
      else if (strstr(buffer, ":char") || strstr(buffer, ":Char")) strcpy(ret_type, "char*");
      else if (strstr(buffer, ":[]char") || strstr(buffer, ":[]Char")) strcpy(ret_type, "char*");
      else if (strstr(buffer, ":bool") || strstr(buffer, ":Bool")) strcpy(ret_type, "bool");
      else if (strstr(buffer, ":any") || strstr(buffer, ":Any")) strcpy(ret_type, "void*");

      char cabecera[512];
      sprintf(cabecera, "%s _%s_%s(%s) {\n", ret_type, current_pkg, func_name, argumentos);
      strcat(funciones_paquetes, cabecera);

      sprintf(buffer, "    %s (*%s)(%s);", ret_type, func_name, argumentos);
      strcat(buffer_structs, buffer);
      strcat(buffer_structs, "\n");

      strcpy(out_line, "");
      return;
    }

    // CASO B: Código interno del método del paquete
    if (in_func_inside_pkg) {
      if (strcmp(buffer, "}") == 0) {
        strcat(funciones_paquetes, "}\n\n");
        in_func_inside_pkg = false;
        // Reseteamos las banderas al salir de la función del paquete
        inside_any_function = false;
        actual_func_retorna_int_array = false;
        actual_func_retorna_dec_array = false;
        strcpy(out_line, "");
        return;
      }

      // Reemplazos de tipos de variables locales dentro de funciones de paquetes
      replace_string(buffer, "Int ", "int ", buffer);
      replace_string(buffer, "int ", "int ", buffer);
      replace_string(buffer, "Dec ", "double ", buffer);
      replace_string(buffer, "dec ", "double ", buffer);
      replace_string(buffer, "Bool ", "bool ", buffer);
      replace_string(buffer, "bool ", "bool ", buffer);

      // APLICAMOS TU LÓGICA INTELIGENTE DE ARREGLOS AQUÍ TAMBIÉN
      bool is_array = (strstr(buffer, "[]") != NULL && strchr(buffer, '=') != NULL);
      bool is_char_array = (strncmp(buffer, "char", 4) == 0 || strncmp(buffer, "Char", 4) == 0);
      if (is_array && !is_char_array) {
        char *open_quote = strstr(buffer, "«");
        char *close_quote = strstr(buffer, "»");
        if (open_quote && close_quote) {
          replace_string(buffer, "«", "{", buffer);
          replace_string(buffer, "»", "};", buffer); // Quitamos el ';' interno para evitar duplicados
          char *content = open_quote + 1;
          while (content < close_quote) {
            if (*content == ' ') replace_string(buffer, " ", ",", buffer);
            content++;
          }
        }
      } else {
        replace_string(buffer, "«", "\"", buffer);
        replace_string(buffer, "»", "\"", buffer);
      }

      replace_string(buffer, "Printf", "printf", buffer);
      replace_string(buffer, "printf", "printf", buffer);
      replace_string(buffer, "=>", "&", buffer);

      int len_int = strlen(buffer);
      if (len_int > 0 && buffer[len_int - 1] != '{' && buffer[len_int - 1] != '}' && buffer[len_int - 1] != ';') {
        strcat(buffer, ";");
      }

      strcat(funciones_paquetes, "    ");
      strcat(funciones_paquetes, buffer);
      strcat(funciones_paquetes, "\n");

      strcpy(out_line, "");
      return;
    }

    // CASO C: Fin de toda la estructura del paquete
    if (strcmp(buffer, "}") == 0 && !in_func_inside_pkg) {
      sprintf(buffer, "} %s;\n", current_pkg);
      strcat(buffer_structs, buffer);
      in_pkg = false;
      strcpy(out_line, "");
      return;
    }

    // CASO D: Miembros / Propiedades estándar del struct
    if (strchr(buffer, '=')) {
      char *has_equal = strchr(buffer, '=');
      if (has_equal) *has_equal = '\0';
      int len_c = strlen(buffer);
      while (len_c > 0 && isspace((unsigned char)buffer[len_c - 1])) {
        buffer[len_c - 1] = '\0';
        len_c--;
      }
    }

    replace_string(buffer, "Int ", "int ", buffer);
    replace_string(buffer, "int ", "int ", buffer);
    replace_string(buffer, "Dec ", "double ", buffer);
    replace_string(buffer, "dec ", "double ", buffer);
    replace_string(buffer, "Char ", "char ", buffer);
    replace_string(buffer, "char ", "char ", buffer);
    replace_string(buffer, "Bool ", "bool ", buffer);
    replace_string(buffer, "bool ", "bool ", buffer);

    int len_p = strlen(buffer);
    if (len_p > 0 && buffer[len_p - 1] != ';') strcat(buffer, ";");

    strcat(buffer_structs, "    ");
    strcat(buffer_structs, buffer);
    strcat(buffer_structs, "\n");
    strcpy(out_line, "");
    return;
  }

  // =============================================================
  // ESTADO: ÁMBITO GLOBAL (FUERA DE PAQUETES)
  // =============================================================
  if (strncmp(buffer, "pkg ", 4) == 0) {
    in_pkg = true;
    total_metodos = 0;
    char name[50] = {
      0
    };
    sscanf(buffer, "pkg %s", name);
    char *bracket = strchr(name, '{'); if (bracket) *bracket = '\0';
    char *equal_sign = strchr(name, '='); if (equal_sign) *equal_sign = '\0';
    strcpy(current_pkg, name);

    sprintf(buffer, "typedef struct {\n");
    strcat(buffer_structs, buffer);
    strcpy(out_line, "");
    return;
  }

  // Mapeos globales de tipos nativos
  replace_string(buffer, "Int ", "int ", buffer);
  replace_string(buffer, "int ", "int ", buffer);
  replace_string(buffer, "Dec ", "double ", buffer);
  replace_string(buffer, "dec ", "double ", buffer);
  replace_string(buffer, "Bool ", "bool ", buffer);
  replace_string(buffer, "bool ", "bool ", buffer);
  replace_string(buffer, "Char ", "char ", buffer);
  replace_string(buffer, "char ", "char ", buffer);
  replace_string(buffer, "Void ", "void ", buffer);
  replace_string(buffer, "void ", "void ", buffer);
  replace_string(buffer, "Auto ", "auto ", buffer);
  replace_string(buffer, "auto ", "auto ", buffer);
  replace_string(buffer, "any ", "void* ", buffer);

  // Números complejos
  if (strncmp(buffer, "Com ", 4) == 0 || strncmp(buffer, "com ", 4) == 0) {
    add_include(inc, "#include <complex.h>");
    replace_string(buffer, "Com ", "double complex ", buffer);
    replace_string(buffer, "com ", "double complex ", buffer);
    char *pos_i = strrchr(buffer, 'i');
    if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
      char temp[MAX_LINE_LEN] = {
        0
      };
      strncpy(temp, buffer, pos_i - buffer);
      strcat(temp, " * I");
      if (*(pos_i + 1) == ';') strcat(temp, ";");
      strcpy(buffer, temp);
    }
  }

  // Punteros
  if (strncmp(buffer, "Punt ", 5) == 0 || strncmp(buffer, "punt ", 5) == 0) {
    replace_string(buffer, "Punt ", "auto ", buffer);
    replace_string(buffer, "punt ", "auto ", buffer);
    replace_string(buffer, "= *", "= &", buffer);
  }

  // Inicialización de Arreglos Globales
  bool is_array = (strstr(buffer, "[]") != NULL && strchr(buffer, '=') != NULL);
  bool is_char_array = (strncmp(buffer, "char", 4) == 0);
  if (is_array && !is_char_array) {
    char *open_quote = strstr(buffer, "«");
    char *close_quote = strstr(buffer, "»");
    if (open_quote && close_quote) {
      replace_string(buffer, "«", "{", buffer);
      replace_string(buffer, "»", "};", buffer);
      /*char *content = open_quote + 1;
      while (content < close_quote) {
        if (*content == ' ') replace_string(buffer, " ", ",", buffer);
        content++;
      }*/
    }
  } else {
    replace_string(buffer, "«", "\"", buffer);
    replace_string(buffer, "»", "\"", buffer);
  }

  if (strchr(buffer, '=')) {
    char *assignment = strchr(buffer, '=');
    if (strchr(assignment, '[') && strchr(assignment, ']')) {
      replace_string(assignment, "[", "{", assignment);
      replace_string(assignment, "]", "}", assignment);
    }
  }

  // Funciones Globales estándar
  if (strncmp(buffer, "func ", 5) == 0) {
    inside_any_function = true; // Activa el ámbito seguro de función
    char func_name[50];

    if (sscanf(buffer, "%*s %[^= ]", func_name) == 1) {
      char argumentos[256] = "";
      char *open_p = strchr(buffer, '(');
      char *close_p = strchr(buffer, ')');
      if (open_p && close_p && (close_p > open_p + 1)) {
        size_t arg_len = close_p - (open_p + 1);
        strncpy(argumentos, open_p + 1, arg_len);
        argumentos[arg_len] = '\0';
      }

      if (strcmp(func_name, "main") == 0) {
        sprintf(buffer, "int main() {");
      } else {
        char ret_type[30] = "void";

        // Primero evaluamos si es un arreglo de enteros o decimales en función global
        if (strstr(buffer, ":[]int") || strstr(buffer, ":[]Int")) {
          actual_func_retorna_int_array = true;
          strcpy(ret_type, "AxoArray_int");
        }
        else if (strstr(buffer, ":[]dec") || strstr(buffer, ":[]Dec")) {
          actual_func_retorna_dec_array = true;
          strcpy(ret_type, "AxoArray_dec");
        }
        else if (strstr(buffer, ":int") || strstr(buffer, ":Int")) {
          strcpy(ret_type, "int");
        }
        else if (strstr(buffer, ":dec") || strstr(buffer, ":Dec")) {
          strcpy(ret_type, "double");
        }
        else if (strstr(buffer, ":char") || strstr(buffer, ":Char")) strcpy(ret_type, "char*");
        else if (strstr(buffer, ":[]char") || strstr(buffer, ":[]Char")) strcpy(ret_type, "char*");
        else if (strstr(buffer, ":bool") || strstr(buffer, ":Bool")) strcpy(ret_type, "bool");
        else if (strstr(buffer, ":any") || strstr(buffer, ":Any")) strcpy(ret_type, "void*");

        sprintf(buffer, "%s %s(%s) {", ret_type, func_name, argumentos);
      }
    }
  }

  // =============================================================
  // REGLA: INSTANCIACIÓN INTELIGENTE CON ENLACE DINÁMICO TOTAL
  // =============================================================
  if (isalpha((unsigned char)buffer[0]) && !strchr(buffer, '=') && !strchr(buffer, '(') && !strchr(buffer, '}')) {
    char tipo_posible[50] = {
      0
    };
    char var_posible[50] = {
      0
    };
    if (sscanf(buffer, "%s %s", tipo_posible, var_posible) == 2) {
      if (strcmp(tipo_posible, "int") != 0 && strcmp(tipo_posible, "double") != 0 &&
        strcmp(tipo_posible, "bool") != 0 && strcmp(tipo_posible, "char") != 0 &&
        strcmp(tipo_posible, "void") != 0 && strcmp(tipo_posible, "return") != 0 &&
        strcmp(tipo_posible, "auto") != 0) {

        char buffer_instancia[4096];
        sprintf(buffer_instancia, "%s %s;", tipo_posible, var_posible);

        for (int m = 0; m < total_metodos; m++) {
          if (strlen(lista_metodos[m]) == 0) continue;

          char linea_enlace[256];
          sprintf(linea_enlace, "\n    %s.%s = _%s_%s;",
            var_posible, lista_metodos[m], tipo_posible, lista_metodos[m]);
          strcat(buffer_instancia, linea_enlace);
        }

        strcpy(out_line, buffer_instancia);
        return;
      }
    }
  }

  // Filtros de salida finales
  replace_string(buffer, "Printf", "printf", buffer);
  replace_string(buffer, "printf", "printf", buffer);
  replace_string(buffer, ",system", "", buffer);
  replace_string(buffer, ", system", "", buffer);
  replace_string(buffer, "=>", "&", buffer);
  if (strstr(buffer, "Stop(system)")) {
    strcpy(buffer, "return 0;");
  }

  replace_string(buffer, "≠", "!=", buffer);
  replace_string(buffer, "≤", "<=", buffer);
  replace_string(buffer, "≥", ">=", buffer);
  replace_string(buffer, "X|", "^", buffer);

  int len = strlen(buffer);
  if (len > 0) {
    char last_char = buffer[len - 1];
    if (last_char != '{' && last_char != '}' && last_char != ';' && last_char != ',' &&
      strncmp(buffer, "if", 2) != 0 && strncmp(buffer, "for", 3) != 0 && strncmp(buffer, "while", 5) != 0) {
      strcat(buffer, ";");
    }
  }

  strcpy(out_line, buffer);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Uso: %s <archivo.axo> [-o <nombre_ejecutable>]\n", argv[0]);
    return 1;
  }

  char *input_filename = argv[1];
  char output_executable[256] = "a.out";
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
      strcpy(output_executable, argv[i + 1]);
      break;
    }
  }

  FILE *input = fopen(input_filename, "r");
  if (!input) {
    perror("Error al abrir el archivo Axolang");
    return 1;
  }

  char temp_c_file[] = "_temp_axoc_output.c";
  FILE *output = fopen(temp_c_file, "w");
  if (!output) {
    perror("Error al crear archivo C temporal");
    fclose(input);
    return 1;
  }

  Includes inc = {
    .count = 0
  };
  char code_body[20000] = {
    0
  };
  char line[1024];
  char transpiled_line[1024];

  while (fgets(line, sizeof(line), input)) {
    transpile_line(line, &inc, transpiled_line);
    if (strlen(transpiled_line) > 0) {
      strcat(code_body, "    ");
      strcat(code_body, transpiled_line);
      strcat(code_body, "\n");
    }
  }
  fclose(input);

  // === ESCRITURA JERÁRQUICA C23 PURA ===
  fprintf(output, "/* Código C23 generado automáticamente por Axolang (axoc) */\n");
  for (int i = 0; i < inc.count; i++) {
    fprintf(output, "%s\n", inc.items[i]);
  }

  // NUEVO: Definición única y global de las estructuras de control para arreglos Axolang
  fprintf(output, "\n/* Definiciones Base de Arreglos de Axolang */\n");
  fprintf(output, "typedef struct {\n    int* data;\n    size_t length;\n} AxoArray_int;\n");
  fprintf(output, "typedef struct {\n    double* data;\n    size_t length;\n} AxoArray_dec;\n\n");


  // 1. Estructuras
  if (strlen(buffer_structs) > 0) {
    fprintf(output, "\n/* Definición de Estructuras Axolang */\n");
    fprintf(output, "%s\n", buffer_structs);
  }

  // 2. Métodos aislados de paquetes
  if (strlen(funciones_paquetes) > 0) {
    fprintf(output, "\n/* Métodos Extraídos de Paquetes Axolang */\n");
    fprintf(output, "%s\n", funciones_paquetes);
  }

  // 3. Bloque de lógica de ejecución principal y main()
  fprintf(output, "\n%s", code_body);
  fclose(output);

  char compile_command[512];
  sprintf(compile_command, "gcc -std=c23 %s -o %s", temp_c_file, output_executable);
  printf("[axoc] Transpilando %s...\n", input_filename);
  printf("[axoc] Compilando en modo C23 nativo puro mediante GCC...\n");
  int result = system(compile_command);
  if (result == 0) {
    printf("[axoc] ¡Éxito! Generado el ejecutable nativo en C23: '%s'\n", output_executable);
  } else {
    printf("[axoc] Error: Falló la compilación nativa en GCC. Revisa la sintaxis.\n");
    return 1;
  }
  //remove(temp_c_file);
  return 0;
}