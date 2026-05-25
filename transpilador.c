/* =============================================================
   TRANSPILADOR OFICIAL DE AXOLANG A C23 (axoc) - REVISIÓN ULTRA
   Compilado y ejecutado bajo el estándar estricto -std=c23
   =============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <ctype.h>

#define MAX_LINE_LEN 65536
#define MAX_BUFFER_FUNCTIONS 65536
#define MAX_METHODS 65536

// --- Variables globales de control de estado (C23 bool nativo) ---
char funciones_paquetes[MAX_BUFFER_FUNCTIONS] = {};
char buffer_structs[MAX_BUFFER_FUNCTIONS] = {};
char buffer_globales[MAX_BUFFER_FUNCTIONS] = {};
bool in_pkg = false;
bool in_func_inside_pkg = false;
char current_pkg[65536] = {};

// Control de retornos de arreglos y contextos de función
int nivel_llaves = 0;
bool actual_func_retorna_int_array = false;
bool actual_func_retorna_dec_array = false;
// Registro dinámico de variables de tipo 'any'
char lista_any_vars[512][64] = {};
int total_any_vars = 0;
// Estructura para registrar métodos dinámicamente
char lista_metodos[MAX_METHODS][1024];
int total_metodos = 0;

typedef struct {
  char items[512][1024];
  int count;
} Includes;

void add_include(Includes *inc, const char *lib) {
  for (int i = 0; i < inc->count; i++) {
    if (strcmp(inc->items[i], lib) == 0) return;
  }
  strcpy(inc->items[inc->count++], lib);
}

// Verifica si un carácter es un delimitador válido de variables/palabras clave
[[nodiscard]] bool es_delimitador(char c) {
  return c == '\0' || isspace((unsigned char)c) ||
  c == '(' || c == ')' || c == '{' || c == '}' ||
  c == '[' || c == ']' || c == ';' || c == ',' ||
  c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '&';
}

// Reemplaza palabras clave de modo inteligente evitando colisiones destructivas
void replace_keyword_safe(char *orig, const char *rep, const char *with, char *output) {
  char buffer[MAX_LINE_LEN] = {};
  char *insert_point = orig;
  char *tmp = buffer;
  int rep_len = strlen(rep);
  int with_len = strlen(with);

  while (true) {
    char *p = strstr(insert_point, rep);
    if (p == nullptr) {
      strcpy(tmp, insert_point);
      break;
    }

    bool es_inicio_valido = (p == orig) || es_delimitador(*(p - 1));
    bool es_fin_valido = es_delimitador(*(p + rep_len));

    if (es_inicio_valido && es_fin_valido) {
      memcpy(tmp, insert_point, p - insert_point);
      tmp += p - insert_point;
      memcpy(tmp, with, with_len);
      tmp += with_len;
      insert_point = p + rep_len;
    } else {
      size_t bytes_a_copiar = (p - insert_point) + rep_len;
      memcpy(tmp, insert_point, bytes_a_copiar);
      tmp += bytes_a_copiar;
      insert_point = p + rep_len;
    }
  }
  strcpy(output, buffer);
}

// Función auxiliar estándar para reemplazos simples (Operadores)
void replace_string(char *orig, const char *rep, const char *with, char *output) {
  char buffer[MAX_LINE_LEN] = {};
  char *insert_point = orig;
  char *tmp = buffer;
  int rep_len = strlen(rep);
  int with_len = strlen(with);

  while (true) {
    char *p = strstr(insert_point, rep);
    if (p == nullptr) {
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
// --- Procesador Inteligente de tipos Dinámicos 'any' ---
void darnos_macro_any(const char *val_str, char *macro_out) {
  const char *p = val_str;
  while (isspace((unsigned char)*p)) p++;

  if (strstr(p, "«") || strstr(p, "»") || strstr(p, "\"")) {
    strcpy(macro_out, "ANY_STR");
  } else if (strstr(p, "true") || strstr(p, "false")) {
    strcpy(macro_out, "ANY_BOOL");
  } else if (strchr(p, 'i') && !strstr(p, "printf")) {
    strcpy(macro_out, "ANY_COMPLEX");
  } else if (strchr(p, '*') || strstr(p, "=>")) {
    strcpy(macro_out, "ANY_PTR");
  } else if (strchr(p, '.')) {
    strcpy(macro_out, "ANY_DEC");
  } else {
    strcpy(macro_out, "ANY_INT");
  }
}
void procesar_bloque_any(char *buffer) {
  char *any_ptr = strstr(buffer, "any ");
  if (any_ptr && (any_ptr == buffer || es_delimitador(*(any_ptr - 1)))) {
    char *equal_ptr = strchr(buffer, '=');
    if (equal_ptr) {
      char var_name[128] = {};
      char val_part[MAX_LINE_LEN] = {};
      char *src_name = any_ptr + 4;
      while (isspace((unsigned char)*src_name)) src_name++;
      int i = 0;
      while (src_name[i] && !isspace((unsigned char)src_name[i]) && src_name[i] != '=') {
        var_name[i] = src_name[i];
        i++;
      }
      var_name[i] = '\0';

      // Registrar variable en nuestra tabla de símbolos interna
      if (total_any_vars < 512) {
        strncpy(lista_any_vars[total_any_vars++], var_name, 63);
      }

      strcpy(val_part, equal_ptr + 1);
      int val_len = strlen(val_part);
      while (val_len > 0 && (isspace((unsigned char)val_part[val_len-1]) || val_part[val_len-1] == ';')) {
        val_part[val_len-1] = '\0';
        val_len--;
      }

      char macro[32];
      darnos_macro_any(val_part, macro);

      if (strcmp(macro, "ANY_COMPLEX") == 0) {
        char *pos_i = strrchr(val_part, 'i');
        if (pos_i) {
          *pos_i = '\0'; strcat(val_part, " * I");
        }
      }
      if (strcmp(macro, "ANY_PTR") == 0) {
        char temp_ptr[MAX_LINE_LEN];
        replace_string(val_part, "*", "&", temp_ptr);
        strcpy(val_part, temp_ptr);
      }

      char prefix[MAX_LINE_LEN] = {};
      strncpy(prefix, buffer, any_ptr - buffer);
      prefix[any_ptr - buffer] = '\0';

      sprintf(buffer, "%sAxoAny %s = %s(%s)", prefix, var_name, macro, val_part);
    } else {
      char var_name[128] = {};
      char *src_name = any_ptr + 4;
      while (isspace((unsigned char)*src_name)) src_name++;
      int i = 0;
      while (src_name[i] && !isspace((unsigned char)src_name[i]) && src_name[i] != ';') {
        var_name[i] = src_name[i];
        i++;
      }
      var_name[i] = '\0';

      if (total_any_vars < 512) {
        strncpy(lista_any_vars[total_any_vars++], var_name, 63);
      }

      char prefix[MAX_LINE_LEN] = {};
      strncpy(prefix, buffer, any_ptr - buffer);
      prefix[any_ptr - buffer] = '\0';
      sprintf(buffer, "%sAxoAny %s", prefix, var_name);
    }
  } else if (!any_ptr && strchr(buffer, '=')) {
    // Detectar reasignaciones dinámicas posteriores de variables registradas como 'any'
    char var_name[128] = {};
    char *start_line = buffer;
    while (isspace((unsigned char)*start_line)) start_line++;
    int i = 0;
    while (start_line[i] && !isspace((unsigned char)start_line[i]) && start_line[i] != '=') {
      var_name[i] = start_line[i];
      i++;
    }
    var_name[i] = '\0';
    bool es_any = false;
    for (int j = 0; j < total_any_vars; j++) {
      if (strcmp(lista_any_vars[j], var_name) == 0) {
        es_any = true; break;
      }
    }

    if (es_any) {
      char *equal_ptr = strchr(buffer, '=');
      char val_part[MAX_LINE_LEN] = {};
      strcpy(val_part, equal_ptr + 1);
      int val_len = strlen(val_part);
      while (val_len > 0 && (isspace((unsigned char)val_part[val_len-1]) || val_part[val_len-1] == ';')) {
        val_part[val_len-1] = '\0';
        val_len--;
      }

      char macro[32];
      darnos_macro_any(val_part, macro);

      if (strcmp(macro, "ANY_COMPLEX") == 0) {
        char *pos_i = strrchr(val_part, 'i');
        if (pos_i) {
          *pos_i = '\0'; strcat(val_part, " * I");
        }
      }
      if (strcmp(macro, "ANY_PTR") == 0) {
        char temp_ptr[MAX_LINE_LEN];
        replace_string(val_part, "*", "&", temp_ptr);
        strcpy(val_part, temp_ptr);
      }

      char prefix[MAX_LINE_LEN] = {};
      strncpy(prefix, buffer, start_line - buffer);
      prefix[start_line - buffer] = '\0';

      sprintf(buffer, "%s%s = %s(%s)", prefix, var_name, macro, val_part);
    }
  }
}
void transpile_line(char *line, Includes *inc, char *out_line) {
  char src[MAX_LINE_LEN];
  strcpy(src, line);

  // 1. Trim inicial e izquierdo
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
  add_include(inc, "#include <complex.h>");
  add_include(inc, "#include <math.h>");
  add_include(inc, "#include <tgmath.h>");
  // 2. Directivas de inclusión del ecosistema Axolang (add <...>)
  if (strncmp(start, "add", 3) == 0) {
    if (strstr(start, "<Basic.axo>")) {
      add_include(inc, "#include <stdio.h>");
      add_include(inc, "#include <stdlib.h>");
      add_include(inc, "#include <stddef.h>");
    }
    if (strstr(start, "<Text.axo>")) {
      add_include(inc, "#include <string.h>");
      add_include(inc, "#include <ctype.h>");
    }
    if (strstr(start, "<Time.axo>")) {
      add_include(inc, "#include <time.h>");
    }
    if (strstr(start, "<Signal.axo>")) {
      add_include(inc, "#include <signal.h>");
    }
    strcpy(out_line, "");
    return;
  }

  // Ignorar llamadas directas de main() al final del script
  if (strcmp(start, "main()") == 0 || strcmp(start, "main") == 0) {
    strcpy(out_line, "");
    return;
  }

  char buffer[MAX_LINE_LEN];
  strcpy(buffer, start);

  // Control estricto de cierre de llaves en funciones globales
  if (strcmp(buffer, "}") == 0 && !in_pkg) {
    nivel_llaves--;
    actual_func_retorna_int_array = false;
    actual_func_retorna_dec_array = false;
    strcpy(out_line, "}");
    return;
  }

  // [CORRECCIÓN CRÍTICA]: Clonación dinámica en Heap para evitar Dangling Pointers de arreglos locales
  if (strncmp(buffer, "return ", 7) == 0) {
    if (inside_any_function && (actual_func_retorna_int_array || actual_func_retorna_dec_array)) {
      char var_name[50] = {};
      sscanf(buffer, "return %[^=\n ;]", var_name);
      
      int v_len = strlen(var_name);
      while(v_len > 0 && isspace((unsigned char)var_name[v_len - 1])) {
        var_name[v_len - 1] = '\0';
        v_len--;
      }

      char temp_ret[1024];
      if (actual_func_retorna_int_array) {
        sprintf(temp_ret, 
          "size_t _len = sizeof(%s)/sizeof(%s[0]);\n"
          "    int* _heap_data = malloc(_len * sizeof(int));\n"
          "    if (_heap_data) memcpy(_heap_data, %s, _len * sizeof(int));\n"
          "    AxoArray_int _ret = { .data = _heap_data, .length = _len };\n"
          "    return _ret;", var_name, var_name, var_name);
      }
      else if (actual_func_retorna_dec_array) {
        sprintf(temp_ret, 
          "size_t _len = sizeof(%s)/sizeof(%s[0]);\n"
          "    double* _heap_data = malloc(_len * sizeof(double));\n"
          "    if (_heap_data) memcpy(_heap_data, %s, _len * sizeof(double));\n"
          "    AxoArray_dec _ret = { .data = _heap_data, .length = _len };\n"
          "    return _ret;", var_name, var_name, var_name);
      }

      if (in_pkg && in_func_inside_pkg) {
        strcat(funciones_paquetes, "    ");
        strcat(funciones_paquetes, temp_ret);
        strcat(funciones_paquetes, "\n");
        strcpy(out_line, "");
      } else {
        strcpy(out_line, temp_ret);
      }
      return;
    }
  }

  // =============================================================
  // ESTADO: DENTRO DE UN PAQUETE (pkg)
  // =============================================================
  if (in_pkg) {
    // CASO A: Inicio de un método del paquete (func nombre = ...)
    if (!in_func_inside_pkg && (strncmp(buffer, "func ", 5) == 0)) {
      in_func_inside_pkg = true;
      nivel_llaves++;
      char func_name[50] = {};
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

      // Corrección de tipos en argumentos internos
      replace_keyword_safe(argumentos, "int", "int", argumentos);
      replace_keyword_safe(argumentos, "dec", "double", argumentos);
      replace_keyword_safe(argumentos, "bool", "bool", argumentos);
      replace_keyword_safe(argumentos, "auto", "auto", argumentos);
      replace_keyword_safe(argumentos, "any", "AxoAny", argumentos);
      replace_keyword_safe(argumentos, "char", "char", argumentos);

      char ret_type[30] = "void";
      if (strstr(buffer, ":[]int")) {
        actual_func_retorna_int_array = true;
        strcpy(ret_type, "AxoArray_int");
      }
      else if (strstr(buffer, ":[]dec")) {
        actual_func_retorna_dec_array = true;
        strcpy(ret_type, "AxoArray_dec");
      }
      else if (strstr(buffer, ":int")) strcpy(ret_type, "int");
      else if (strstr(buffer, ":dec")) strcpy(ret_type, "double");
      else if (strstr(buffer, ":char")) strcpy(ret_type, "char");
      else if (strstr(buffer, ":[]char")) strcpy(ret_type, "char*");
      else if (strstr(buffer, ":bool")) strcpy(ret_type, "bool");
      else if (strstr(buffer, ":any")) strcpy(ret_type, "AxoAny");

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
        nivel_llaves--;
        actual_func_retorna_int_array = false;
        actual_func_retorna_dec_array = false;
        strcpy(out_line, "");
        return;
      }

      // Procesamiento global de variables y tipos
      replace_keyword_safe(buffer, "int", "int", buffer);
      replace_keyword_safe(buffer, "dec", "double", buffer);
      replace_keyword_safe(buffer, "bool", "bool", buffer);
      replace_keyword_safe(buffer, "char", "char", buffer);
      replace_keyword_safe(buffer, "void", "void", buffer);
      replace_keyword_safe(buffer, "auto", "auto", buffer);
      replace_keyword_safe(buffer, "any", "AxoAny", buffer);

      procesar_bloque_any(buffer);
      // Números complejos Axolang (2.1i -> 2.1 * I)
      if (strstr(buffer, "com ") || strncmp(buffer, "com", 3) == 0) {
        replace_keyword_safe(buffer, "com", "double complex", buffer);
        char *pos_i = strrchr(buffer, 'i');
        if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
          char temp[MAX_LINE_LEN] = {};
          strncpy(temp, buffer, pos_i - buffer);
          strcat(temp, " * I");
          if (*(pos_i + 1) == ';') strcat(temp, ";");
          strcpy(buffer, temp);
        }
      }

      // Punteros (*variable -> &variable)
      if (strstr(buffer, "punt ") || strncmp(buffer, "punt", 4) == 0) {
        replace_keyword_safe(buffer, "punt", "auto", buffer);
        replace_string(buffer, "= *", "= &", buffer);
      }

      // Parseo de arreglos « » locales
      bool is_array_loc = (strstr(buffer, "[]") != nullptr && strchr(buffer, '=') != nullptr);
      bool is_char_array_loc = (strstr(buffer, "char") != nullptr);
      if (is_array_loc && !is_char_array_loc) {
        char *open_quote = strstr(buffer, "«");
        char *close_quote = strstr(buffer, "»");
        if (open_quote && close_quote && (close_quote > open_quote)) {
          char parte_izq[MAX_LINE_LEN] = {}; char parte_der[MAX_LINE_LEN] = {}; char contenido[MAX_LINE_LEN] = {};
          size_t izq_len = open_quote - buffer;
          strncpy(parte_izq, buffer, izq_len);
          strcpy(parte_der, close_quote + 2);
          size_t cont_len = close_quote - (open_quote + 2);
          strncpy(contenido, open_quote + 2, cont_len);
          for (size_t i = 0; i < strlen(contenido); i++) {
            if (contenido[i] == ' ' || contenido[i] == ',') contenido[i] = ',';
          }
          sprintf(buffer, "%s{%s}%s", parte_izq, contenido, parte_der);
        }
      } else {
        replace_string(buffer, "«", "\"", buffer);
        replace_string(buffer, "»", "\"", buffer);
      }

      replace_string(buffer, "=>", "&", buffer);
      replace_string(buffer, "×", "*", buffer);
      replace_string(buffer, "÷", "/", buffer);
      replace_string(buffer, "√", "sqrt", buffer);
      replace_string(buffer, "≠", "!=", buffer);
      replace_string(buffer, "≤", "<=", buffer);
      replace_string(buffer, "≥", ">=", buffer);
      replace_string(buffer, "X|", "^", buffer);

// [MEJORA EXCLUSIVA]: Interceptor inteligente de la Arquitectura Dinámica 'AxoAny'
  if (strstr(buffer, "AxoAny ")) {
    char var_name[64] = {};
    char *p = strstr(buffer, "AxoAny ");
    if (sscanf(p + 7, "%63s", var_name) == 1) {
      char *eq = strchr(var_name, '='); if (eq) *eq = '\0';
      char *sc = strchr(var_name, ';'); if (sc) *sc = '\0';
      if (total_any_vars < 100 && strlen(var_name) > 0) {
        strcpy(axo_any_vars[total_any_vars++], var_name);
      }
    }
    
    // Si se inicializa un AxoAny con un número complejo directo (ej: 2i;) lo envuelve en la macro helper
    char *pos_i = strrchr(buffer, 'i');
    if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
      char temp[MAX_LINE_LEN] = {};
      char *equal_sign = strchr(buffer, '=');
      if (equal_sign) {
        size_t left_len = (equal_sign - buffer) + 1;
        strncpy(temp, buffer, left_len);
        strcat(temp, " ANY_COMPLEX(");
        char val_str[64] = {};
        char *val_start = equal_sign + 1;
        while (isspace((unsigned char)*val_start)) val_start++;
        strncpy(val_str, val_start, pos_i - val_start);
        strcat(temp, val_str);
        strcat(temp, " * I);");
        strcpy(buffer, temp);
      }
    }
  }
  
      int len_int = strlen(buffer);
      if (len_int > 0) {
        char last_c = buffer[len_int - 1];
        if (last_c != '{' && last_c != ';' && last_c != ',' && last_c != '/' &&
          (last_c != '}' || strstr(buffer, "=") != nullptr || strstr(buffer, "[]") != nullptr)) {
          strcat(buffer, ";");
        }
      }

      strcat(funciones_paquetes, "    ");
      strcat(funciones_paquetes, buffer);
      strcat(funciones_paquetes, "\n");

      strcpy(out_line, "");
      return;
    }

    // CASO C: Fin de toda la estructura del paquete
    if (strcmp(buffer, "}") == 0 && !in_func_inside_pkg) {
      nivel_llaves--;
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

    // Procesamiento global de variables y tipos
    replace_keyword_safe(buffer, "int", "int", buffer);
    replace_keyword_safe(buffer, "dec", "double", buffer);
    replace_keyword_safe(buffer, "bool", "bool", buffer);
    replace_keyword_safe(buffer, "char", "char", buffer);
    replace_keyword_safe(buffer, "void", "void", buffer);
    replace_keyword_safe(buffer, "auto", "auto", buffer);
    replace_keyword_safe(buffer, "any", "AxoAny", buffer);


    // Números complejos Axolang (2.1i -> 2.1 * I)
    if (strstr(buffer, "com ") || strncmp(buffer, "com", 3) == 0) {
      replace_keyword_safe(buffer, "com", "double complex", buffer);
      char *pos_i = strrchr(buffer, 'i');
      if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
        char temp[MAX_LINE_LEN] = {};
        strncpy(temp, buffer, pos_i - buffer);
        strcat(temp, " * I");
        if (*(pos_i + 1) == ';') strcat(temp, ";");
        strcpy(buffer, temp);
      }
    }

    // Punteros (*variable -> &variable)
    if (strstr(buffer, "punt ") || strncmp(buffer, "punt", 4) == 0) {
      replace_keyword_safe(buffer, "punt", "auto", buffer);
      replace_string(buffer, "= *", "= &", buffer);
    }


    // Números complejos Axolang (2.1i -> 2.1 * I)
    if (strstr(buffer, "com ") || strncmp(buffer, "com", 3) == 0) {
      replace_keyword_safe(buffer, "com", "double complex", buffer);
      char *pos_i = strrchr(buffer, 'i');
      if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
        char temp[MAX_LINE_LEN] = {};
        strncpy(temp, buffer, pos_i - buffer);
        strcat(temp, " * I");
        if (*(pos_i + 1) == ';') strcat(temp, ";");
        strcpy(buffer, temp);
      }
    }

    // Punteros (*variable -> &variable)
    if (strstr(buffer, "punt ") || strncmp(buffer, "punt", 4) == 0) {
      replace_keyword_safe(buffer, "punt", "auto", buffer);
      replace_string(buffer, "= *", "= &", buffer);
    }

    int len_p = strlen(buffer);
    if (len_p > 0 && buffer[len_p - 1] != ';') strcat(buffer, ";");

    strcat(buffer_structs, "    ");
    strcat(buffer_structs, buffer);
    strcat(buffer_structs, "\n");
    strcpy(out_line, "");
    return;
  }

  // =============================================================
  // ESTADO: ÁMBITO GLOBAL / FUERA DE PAQUETES
  // =============================================================
  if (strncmp(buffer, "pkg ", 4) == 0) {
    in_pkg = true;
    nivel_llaves = 1;
    total_metodos = 0;
    char name[50] = {};
    sscanf(buffer, "pkg %s", name);
    char *bracket = strchr(name, '{'); if (bracket) *bracket = '\0';
    strcpy(current_pkg, name);

    sprintf(buffer, "typedef struct {\n");
    strcat(buffer_structs, buffer);
    strcpy(out_line, "");
    return;
  }

  // Procesamiento global de variables y tipos
  replace_keyword_safe(buffer, "int", "int", buffer);
  replace_keyword_safe(buffer, "dec", "double", buffer);
  replace_keyword_safe(buffer, "bool", "bool", buffer);
  replace_keyword_safe(buffer, "char", "char", buffer);
  replace_keyword_safe(buffer, "void", "void", buffer);
  replace_keyword_safe(buffer, "auto", "auto", buffer);
  replace_keyword_safe(buffer, "any", "AxoAny", buffer);

  procesar_bloque_any(buffer);
  // Números complejos Axolang (2.1i -> 2.1 * I)
  if (strstr(buffer, "com ") || strncmp(buffer, "com", 3) == 0) {
    replace_keyword_safe(buffer, "com", "double complex", buffer);
    char *pos_i = strrchr(buffer, 'i');
    if (pos_i && (pos_i == buffer + strlen(buffer) - 1 || *(pos_i + 1) == ';')) {
      char temp[MAX_LINE_LEN] = {};
      strncpy(temp, buffer, pos_i - buffer);
      strcat(temp, " * I");
      if (*(pos_i + 1) == ';') strcat(temp, ";");
      strcpy(buffer, temp);
    }
  }

  // Punteros (*variable -> &variable)
  if (strstr(buffer, "punt ") || strncmp(buffer, "punt", 4) == 0) {
    replace_keyword_safe(buffer, "punt", "auto", buffer);
    replace_string(buffer, "= *", "= &", buffer);
  }

  // Inicialización de Arreglos Globales o Locales « »
  bool is_array_glob = (strstr(buffer, "[]") != nullptr && strchr(buffer, '=') != nullptr);
  bool is_char_array_glob = (strstr(buffer, "char") != nullptr);
  if (is_array_glob && !is_char_array_glob) {
    char *open_quote = strstr(buffer, "«");
    char *close_quote = strstr(buffer, "»");
    if (open_quote && close_quote && (close_quote > open_quote)) {
      char parte_izq[MAX_LINE_LEN] = {}; char parte_der[MAX_LINE_LEN] = {}; char contenido[MAX_LINE_LEN] = {};
      size_t izq_len = open_quote - buffer;
      strncpy(parte_izq, buffer, izq_len);
      strcpy(parte_der, close_quote + 2);
      size_t cont_len = close_quote - (open_quote + 2);
      strncpy(contenido, open_quote + 2, cont_len);
      for (size_t i = 0; i < strlen(contenido); i++) {
        if (contenido[i] == ' ' || contenido[i] == ',') contenido[i] = ',';
      }
      sprintf(buffer, "%s{%s}%s", parte_izq, contenido, parte_der);
    }
  } else {
    replace_string(buffer, "«", "\"", buffer);
    replace_string(buffer, "»", "\"", buffer);
  }

  // Detección y parseo de Funciones Globales
  if (strncmp(buffer, "func ", 5) == 0) {
    nivel_llaves++;
    char func_name[50] = {};

    if (sscanf(buffer, "%*s %[^= ]", func_name) == 1) {
      char argumentos[256] = "";
      char *open_p = strchr(buffer, '(');
      char *close_p = strchr(buffer, ')');
      if (open_p && close_p && (close_p > open_p + 1)) {
        size_t arg_len = close_p - (open_p + 1);
        strncpy(argumentos, open_p + 1, arg_len);
        argumentos[arg_len] = '\0';
      }

      replace_keyword_safe(argumentos, "int", "int", argumentos);
      replace_keyword_safe(argumentos, "dec", "double", argumentos);
      replace_keyword_safe(argumentos, "bool", "bool", argumentos);
      replace_keyword_safe(argumentos, "char", "char", argumentos);
      replace_keyword_safe(argumentos, "any", "AxoAny", argumentos);

      if (strcmp(func_name, "main") == 0) {
        sprintf(buffer, "int main() {");
      } else {
        char ret_type[30] = "void";
        if (strstr(buffer, ":[]int")) {
          actual_func_retorna_int_array = true;
          strcpy(ret_type, "AxoArray_int");
        }
        else if (strstr(buffer, ":[]dec")) {
          actual_func_retorna_dec_array = true;
          strcpy(ret_type, "AxoArray_dec");
        }
        else if (strstr(buffer, ":int")) strcpy(ret_type, "int");
        else if (strstr(buffer, ":dec")) strcpy(ret_type, "double");
        else if (strstr(buffer, ":char")) strcpy(ret_type, "char");
        else if (strstr(buffer, ":[]char")) strcpy(ret_type, "char*");
        else if (strstr(buffer, ":bool")) strcpy(ret_type, "bool");
        else if (strstr(buffer, ":any")) strcpy(ret_type, "AxoAny");

        sprintf(buffer, "%s %s(%s) {", ret_type, func_name, argumentos);
      }
      strcpy(out_line, buffer);
      return;
    }
  }

  // Enlace y enlace vtable dinámico para instanciar structs
  if (isalpha((unsigned char)buffer[0]) && !strchr(buffer, '=') && !strchr(buffer, '(') && !strchr(buffer, '}')) {
    char tipo_posible[50] = {}; char var_posible[50] = {};
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
          sprintf(linea_enlace, "\n    %s.%s = _%s_%s;", var_posible, lista_metodos[m], tipo_posible, lista_metodos[m]);
          strcat(buffer_instancia, linea_enlace);
        }
        strcpy(out_line, buffer_instancia);
        return;
      }
    }
  }

  // Ajustes de operadores de Axolang y funciones IO
  replace_string(buffer, ",system", "", buffer);
  replace_string(buffer, ", system", "", buffer);
  replace_string(buffer, "=>", "&", buffer);
  if (strstr(buffer, "Stop(system)")) strcpy(buffer, "return 0;");
  replace_string(buffer, "×", "*", buffer);
  replace_string(buffer, "÷", "/", buffer);
  replace_string(buffer, "√", "sqrt", buffer);
  replace_string(buffer, "≠", "!=", buffer);
  replace_string(buffer, "≤", "<=", buffer);
  replace_string(buffer, "≥", ">=", buffer);
  replace_string(buffer, "X|", "^", buffer);

  if (strchr(buffer, '{') != nullptr && strchr(buffer, '}') == nullptr) {
    nivel_llaves++;
  }
  // Regla estricta de punto y coma al final
  int len = strlen(buffer);
  if (len > 0) {
    char last_char = buffer[len - 1];
    if (last_char != '{' && last_char != ';' && last_char != ',' &&
      strncmp(buffer, "if", 2) != 0 && strncmp(buffer, "for", 3) != 0 && strncmp(buffer, "while", 5) != 0 && (last_char != '}' || strstr(buffer, "=") != NULL || strstr(buffer, "[]") != NULL)) {
      strcat(buffer, ";");
    }
  }

  // CRÍTICO: Si no estamos dentro de una función, la instrucción es una asignación global
  if (nivel_llaves == 0) {
    strcat(buffer_globales, buffer);
    strcat(buffer_globales, "\n");
    strcpy(out_line, "");
  } else {
    strcpy(out_line, buffer); // CORREGIDO: Copiar las líneas internas de la función al cuerpo del archivo
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Uso: %s <archivo.axo> [-o <nombre_ejecutable>]\n", argv[0]);
    return 1;
  }

  auto input_filename = argv[1];
  char output_executable[256] = "a.out";
  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
      strcpy(output_executable, argv[i + 1]);
      break;
    }
  }

  FILE *input = fopen(input_filename, "r");
  if (input == nullptr) {
    perror("Error al abrir el archivo Axolang");
    return 1;
  }

  char temp_c_file[] = "_temp_axoc_output.c";
  FILE *output = fopen(temp_c_file, "w");
  if (output == nullptr) {
    perror("Error al crear archivo C temporal");
    fclose(input);
    return 1;
  }

  Includes inc = {};
  size_t body_capacity = 32768;
  char *code_body = malloc(body_capacity);
  if (code_body == nullptr) {
    perror("Error crítico: Memoria insuficiente");
    fclose(input); fclose(output); return 1;
  }
  code_body[0] = '\0';
  size_t body_len = 0;

  char line[1024];
  char transpiled_line[1024];

  while (fgets(line, sizeof(line), input)) {
    transpile_line(line, &inc, transpiled_line);
    if (strlen(transpiled_line) > 0) {
      size_t espacio_necesario = body_len + strlen(transpiled_line) + 6;
      if (espacio_necesario >= body_capacity) {
        body_capacity *= 2;
        char *new_ptr = realloc(code_body, body_capacity);
        if (new_ptr == nullptr) {
          free(code_body); fclose(input); fclose(output); return 1;
        }
        code_body = new_ptr;
      }
      strcat(code_body, "    ");
      strcat(code_body, transpiled_line);
      strcat(code_body, "\n");
      body_len = strlen(code_body);
    }
  }
  fclose(input);
  // === ARMADO DE ARQUITECTURA E INYECCIÓN JERÁRQUICA ===
  fprintf(output, "/* Código C23 generado automáticamente por Axolang (axoc) */\n");
  for (int i = 0; i < inc.count; i++) {
    fprintf(output, "%s\n", inc.items[i]);
  }

  fprintf(output, "\n/* Definiciones Base de Arreglos de Axolang */\n");
  fprintf(output, "typedef struct {\n    int* data;\n    size_t length;\n} AxoArray_int;\n");
  fprintf(output, "typedef struct {\n    double* data;\n    size_t length;\n} AxoArray_dec;\n\n");

  // --- INYECCIÓN DE LA ARQUITECTURA DINÁMICA AXOANY ---
  fprintf(output, "/* Arquitectura Dinámica 'any' de Axolang */\n");
  fprintf(output, "typedef enum { T_INT, T_DEC, T_COMPLEX, T_STRING, T_BOOL, T_POINTER } AxoTipo;\n");
  fprintf(output, "typedef struct {\n");
  fprintf(output, "    AxoTipo tipo;\n");
  fprintf(output, "    union {\n");
  fprintf(output, "        int v_int;\n");
  fprintf(output, "        double v_dec;\n");
  fprintf(output, "        double complex v_complex;\n");
  fprintf(output, "        char* v_string;\n");
  fprintf(output, "        bool v_bool;\n");
  fprintf(output, "        void* v_ptr;\n");
  fprintf(output, "    } dato;\n");
  fprintf(output, "} AxoAny;\n\n");

  // Inyección de Macros de Asignación por literales compuestos (C23 standard compliant)
  fprintf(output, "#define ANY_INT(val)     ((AxoAny){ .tipo = T_INT,     .dato.v_int = (val) })\n");
  fprintf(output, "#define ANY_DEC(val)     ((AxoAny){ .tipo = T_DEC,     .dato.v_dec = (val) })\n");
  fprintf(output, "#define ANY_COMPLEX(val) ((AxoAny){ .tipo = T_COMPLEX, .dato.v_complex = (val) })\n");
  fprintf(output, "#define ANY_STR(val)     ((AxoAny){ .tipo = T_STRING,  .dato.v_string = (val) })\n");
  fprintf(output, "#define ANY_BOOL(val)    ((AxoAny){ .tipo = T_BOOL,    .dato.v_bool = (val) })\n");
  fprintf(output, "#define ANY_PTR(val)     ((AxoAny){ .tipo = T_POINTER, .dato.v_ptr = (val) })\n\n");

  if (strlen(buffer_structs) > 0) {
    fprintf(output, "\n/* Definición de Estructuras Axolang */\n");
    fprintf(output, "%s\n", buffer_structs);
  }

  if (strlen(funciones_paquetes) > 0) {
    fprintf(output, "\n/* Métodos Extraídos de Paquetes Axolang */\n");
    fprintf(output, "%s\n", funciones_paquetes);
  }

  // SECCIÓN CORRECTA: Variables Globales inyectadas en el Top-Level de C
  if (strlen(buffer_globales) > 0) {
    fprintf(output, "\n/* Variables Globales de Axolang */\n");
    fprintf(output, "%s\n", buffer_globales);
  }

  fprintf(output, "\n%s", code_body);
  fclose(output);
  free(code_body);

  char compile_command[512];
  sprintf(compile_command, "gcc -std=c23 %s -lm -o %s", temp_c_file, output_executable);
  printf("[axoc] Transpilando %s...\n", input_filename);
  printf("[axoc] Compilando en modo C23 nativo puro mediante GCC...\n");

  int result = system(compile_command);
  if (result == 0) {
    printf("[axoc] ¡Éxito! Ejecutable nativo C23 generado con éxito: '%s'\n", output_executable);
  } else {
    printf("[axoc] Error: Falló la compilación nativa en GCC.\n");
    return 1;
  }

  return 0;
}