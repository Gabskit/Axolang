/* Código C23 generado automáticamente por Axolang (axoc) */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <complex.h>

/* Definiciones Base de Arreglos de Axolang */
typedef struct {
    int* data;
    size_t length;
} AxoArray_int;
typedef struct {
    double* data;
    size_t length;
} AxoArray_dec;


/* Definición de Estructuras Axolang */
typedef struct {
    char letra;
    double gd;
    char* (*saludar)();
    AxoArray_int (*suma)(int a, int b);
} algo;


/* Métodos Extraídos de Paquetes Axolang */
char* _algo_saludar() {
    return "Hola desde variable";
}

AxoArray_int _algo_suma(int a, int b) {
    // Al transpilearse, interceptamos esto para usar malloc dinámico;
    int sum[] = {0,0};
    sum[0] = a + b;
    sum[1] = a + a + b;
}



    int num[] = {0,3,5,7,3};
    char saludo[] = "hola";
    double complex miComplejo = 2.1 * I;
    int edad = 25;
    double pi = 3.1416;
    bool activo = true;
    auto miCopia = &edad;
    AxoArray_int _ret = { .data = sum, .length = sizeof(sum)/sizeof(sum[0]) };
    return _ret;
    void* variableComodin = "adios";
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
    printf("%s\n", (char*)variableComodin);
    for (int i = 0; i < 5; i++){
    printf("%d\n", num[i]);
    }
    hola2();
    printf("%.1f %.1fi\n", creal(miComplejo), cimag(miComplejo));
    printf("%p\n", miCopia);
    // CAPTURA INTELIGENTE DEL ARREGLO RETORNADO;
    auto resultado = p1.suma(2, 4);
    printf("Resultado 1: %d\n", resultado.data[0]);
    printf("Resultado 2: %d\n", resultado.data[1]);
    printf("Elementos devueltos: %zu\n", resultado.length);
    return 0;
    }
