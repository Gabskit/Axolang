/* Código C23 generado automáticamente por Axolang (axoc) */
typedef struct {
    int* data;
    size_t length;
} AxoArray_int;
typedef struct {
    double* data;
    size_t length;
} AxoArray_dec;
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/* Definición de Estructuras Axolang */
typedef struct {
    char letra;
    double gd;
    char* (*saludar)();
    int* (*suma)(int a, int b);
} algo;


/* Métodos Extraídos de Paquetes Axolang */
char* _algo_saludar() {
    return "Hola desde variable";
}

int* _algo_suma(int a, int b) {
    int sum[2];
    sum[0] = a + b;
    sum[1] = a + a + b;
    return sum;
}



    int num[] = {0,3,5,7,3};
    char saludo[] = "hola";
    double complex miComplejo = 2.1 * I;
    int edad = 25;
    double pi = 3.1416;
    bool activo = true;
    auto miCopia = &edad;
    void* variableComodin = "adios";
    void hola2() {
    printf("Hola desde funcion globql\n");
    }
    int main() {
    algo p1;
    p1.saludar = _algo_saludar;
    p1.suma = _algo_suma;
    p1.letra = 'a';
    printf("%s\n",saludo);
    printf("%s\n", p1.saludar());
    printf("%c\n", p1.letra);
    printf("%s\n", (char*)variableComodin);
    for (int i = 0; i < 5; i++){
    printf("%d\n", num[i]);
    }
    hola2();
    printf("%.1f %.1fi\n", creal(miComplejo), cimag(miComplejo));
    printf("%p\n", miCopia);
    printf("%ls\n", p1.suma(2,4));
    return 0;
    }
