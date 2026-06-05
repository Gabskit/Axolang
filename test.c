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

