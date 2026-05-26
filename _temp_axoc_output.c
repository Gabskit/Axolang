/* Código C23 generado automáticamente por Axolang (axoc) */
#include <complex.h>
#include <math.h>
#include <tgmath.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/* Definiciones Base de Arreglos de Axolang */
typedef struct {
    int* data;
    size_t length;
} AxoArray_int;
typedef struct {
    double* data;
    size_t length;
} AxoArray_dec;

/* Arquitectura Dinámica 'any' de Axolang */
typedef enum { T_INT, T_DEC, T_COMPLEX, T_STRING, T_BOOL, T_POINTER } AxoTipo;
typedef struct {
    AxoTipo tipo;
    union {
        int v_int;
        double v_dec;
        double complex v_complex;
        char* v_string;
        bool v_bool;
        void* v_ptr;
    } dato;
} AxoAny;

#define ANY_INT(val)     ((AxoAny){ .tipo = T_INT,     .dato.v_int = (val) })
#define ANY_DEC(val)     ((AxoAny){ .tipo = T_DEC,     .dato.v_dec = (val) })
#define ANY_COMPLEX(val) ((AxoAny){ .tipo = T_COMPLEX, .dato.v_complex = (val) })
#define ANY_STR(val)     ((AxoAny){ .tipo = T_STRING,  .dato.v_string = (val) })
#define ANY_BOOL(val)    ((AxoAny){ .tipo = T_BOOL,    .dato.v_bool = (val) })
#define ANY_PTR(val)     ((AxoAny){ .tipo = T_POINTER, .dato.v_ptr = (val) })


/* Definición de Estructuras Axolang */
typedef struct {
    char letra;
    double gd;
    char* (*saludar)();
    AxoArray_dec (*suma)(double a, double b);
} algo;


/* Métodos Extraídos de Paquetes Axolang */
char* _algo_saludar() {
    return "Hola desde variable";
}

AxoArray_dec _algo_suma(double a, double b) {
    // Al transpilearse, interceptamos esto para usar malloc dinámico;
    double sum[] = {0,0};
    sum[0] = a + b;
    sum[1] = a * b;
    size_t _len = sizeof(sum)/sizeof(sum[0]);
    double* _heap_data = malloc(_len * sizeof(double));
    if (_heap_data) memcpy(_heap_data, sum, _len * sizeof(double));
    AxoArray_dec _ret = { .data = _heap_data, .length = _len };
    return _ret;
}



/* Variables Globales de Axolang */
int num[] = {0,3,5,7,3};
char saludo[] = "hola";
double complex miComplejo = 2 + 2.1 * I;
int edad = 25;
double pi = 3.1416;
bool activo = true;
auto miCopia = &edad;
AxoAny variableComodin = 2i;


    void hola2() {
    printf("Hola desde funcion globql\n");
    }
    int main() {
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    p1.letra = 'a';
    printf("%s\n", saludo);
    printf("%s\n", p1.saludar());
    printf("%c\n", p1.letra);
    printf("%.1fI\n", cimag(variableComodin));
    for (int i = 0; i < 5; i++){
    printf("%d\n", num[i]);
    }
    hola2();
    printf("%.1f %.1fi\n", creal(miComplejo), cimag(miComplejo));
    printf("%p\n", miCopia);
    // CAPTURA INTELIGENTE DEL ARREGLO RETORNADO;
    auto resultado = p1.suma(2.5, pi);
    printf("Resultado 1: %f\n", resultado.data[0]);
    printf("Resultado 2: %f\n", resultado.data[1]);
    printf("Elementos devueltos: %zu\n", resultado.length);
    return 0;
    }
