// --- C23 AUTO-GENERATED CODE FROM AXOLANG ---
#include <complex.h>
#include <math.h>
#include <tgmath.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { TYPE_INT, TYPE_DEC, TYPE_COMPLEX, TYPE_CHAR, TYPE_STRING, TYPE_FUNC, TYPE_PKG } AxoType;
typedef struct {
    AxoType type;
    union {
        int i_val;
        double d_val;
        double _Complex cmplx_val;
        char c_val;
        char* s_val;
        void (*func_val)();
        void* pkg_val;
    };
} Axoany_Struct;

typedef struct { int* data; size_t length; } Axoarray_int;
typedef struct { double* data; size_t length; } Axoarray_dec;
typedef struct { char* data; size_t length; } Axoarray_char;
typedef struct { Axoany_Struct* data; size_t length; } Axoarray_any;


int num[] = { 0 , 3 , 5 , 7 , 3  };
char saludo[] = "hola" ;
double _Complex miComplejo = 2 + 2.1 * _Complex_I;
int edad = 25 ;
double pi = 3.1416 ;
bool activo = true ;
auto miCopia = *edad ;
typedef struct {

char letra ;
double gd ;
    Axoarray_char (*saludar)();

    Axoarray_dec (*suma)(double a, double b);

} algo;


Axoany_Struct variableComodin = 2 * _Complex_I;
Axoany_Struct dinamico2 = "xd" ;
Axoany_Struct dinfun = (Axoany_Struct){ .type = TYPE_FUNC, .func_val = &__axo_lambda_1 };
void hola2() {

printf ( "Hola desde funcion globql\n" ) ;
}


// --- PROTOTIPOS DE LAMBDAS EXTRAÍDAS ---
Axoarray_any __axo_lambda_1();


// --- METODOS DE COMPORTAMIENTO EXTRAIDOS ---
Axoarray_char algo_saludar() {

return (Axoarray_char){ .data = "Hola desde variable", .length = 19 };
;
}

Axoarray_dec algo_suma(double a, double b) {


double* sum = malloc(2 * sizeof(double));
    sum[0] = a + b;
    sum[1] = a * b;
sum[0] = a + b ;
sum[1] = a * b ;
return (Axoarray_dec){ .data = sum, .length = 2 };
;
}

Axoarray_any __axo_lambda_1() {
    
    printf ( printf("Hola desde variable dinamica\n") ) ;
    ;
}

// --- CONSTRUCTORES DE INICIALIZACION ---
algo init_algo() {
    algo instancia;
    instancia.saludar = &algo_saludar;
    instancia.suma = &algo_suma;
    return instancia;
}


int main() {

algo p1 = init_algo();
p1.letra = 'a' ;
printf ( "%s\n" , saludo ) ;
printf ( "%s\n" , p1.saludar ( ) ) ;
printf ( "%c\n" , p1.letra ) ;
printf ( "%.1fI\n" , cimag ( variableComodin ) ) ;
for ( int i = 0 ; i < 5 ; i ++ ) { 
printf ( "%d\n" , num[i] ) ;
}

hola2 ( ) ;
printf ( "%.1f %.1fi\n" , creal ( miComplejo ) , cimag ( miComplejo ) ) ;
printf ( "%p\n" , miCopia ) ;

auto resultado = p1.suma ( 2.5 , pi ) ;
printf ( "Resultado 1: %f\n" , resultado.data[0] ) ;
printf ( "Resultado 2: %f\n" , resultado.data[1] ) ;
printf ( "Elementos devueltos: %zu\n" , resultado.length ) ;
exit(0);
}
