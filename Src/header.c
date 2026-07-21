#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <uchar.h>
#include <wchar.h>
#include <inttypes.h>

// ============================================================================
// MACROS PARA M ANIPULACIÓN DE BIT-ARRAYS SEMÁNTICOS POR VALOR
// ============================================================================
// Lee el bit en la posición 'idx' (devuelve 0 o 1)
#define PAXO_GET_BIT(var, idx)      (((var).paxo_intu >> (idx)) & 1)

// Enciende el bit en la posición 'idx' (asigna ✓) respetando el tipo del contenedor
#define PAXO_SET_BIT_1(var, idx)    ((var).paxo_intu |= ((__typeof__((var).paxo_intu))1 << (idx)))

// Apaga el bit en la posición 'idx' (asigna ×) respetando el tipo del contenedor
#define PAXO_SET_BIT_0(var, idx)    ((var).paxo_intu &= ~((__typeof__((var).paxo_intu))1 << (idx)))

// ============================================================================
// MACROS PARA MANIPULACIÓN DE TRIT-ARRAYS (2 BITS POR TRIT)
// ============================================================================

// Lee el trit en la posición 'idx' (devuelve 0 para ×, 1 para •, 2 para ✓)
#define PAXO_GET_TRIT(var, idx)    (((var).paxo_intu >> ((idx) * 2)) & 3)

// Asigna un valor de trit (0, 1 o 2) en la posición 'idx' limpiando primero esos 2 bits
#define PAXO_SET_TRIT(var, idx, val) ( \
    (var).paxo_intu = ((var).paxo_intu & ~(((__typeof__((var).paxo_intu))3) << ((idx) * 2))) | \
                              (((__typeof__((var).paxo_intu))(val)) << ((idx) * 2)) \
                                                        )

                                                        // Lee el componente de 4 estados (2 bits por elemento)
                                                        #define PAXO_GET_CRIT(var, idx)     (((var).paxo_intu >> ((idx) * 2)) & 3)

                                                        // Escribe el componente de 4 estados
                                                        #define PAXO_SET_CRIT(var, idx, val) ( \
                                                            (var).paxo_intu = ((var).paxo_intu & ~(((__typeof__((var).paxo_intu))3) << ((idx) * 2))) | \
                                                                                  (((__typeof__((var).paxo_intu))(val & 3)) << ((idx) * 2)) \
                                                                                  )

                                                                                  #define dec_complex(type) _dec_complex_##type

                                                                                  typedef _Decimal32  _dec_complex__Decimal32[2];
                                                                                  typedef _Decimal64  _dec_complex__Decimal64[2];
                                                                                  typedef _Decimal128 _dec_complex__Decimal128[2];

                                                                                  typedef void* (*paxo_callable_t)(void* args, int arg_count);

                                                                                  typedef enum {
                                                                                    PAXO_TRIT_FALSE   = 0, // Mapea a ×
                                                                                      PAXO_TRIT_NEUT    = 1, // Mapea a •
                                                                                        PAXO_TRIT_TRUE    = 2  // Mapea a ✓
                                                                                        } paxo_trit_e;

                                                                                        typedef enum {
                                                                                            PAXO_CRIT_0 = 0, // Mapea a ▲
                                                                                                PAXO_CRIT_1 = 1, // Mapea a ►
                                                                                                    PAXO_CRIT_2 = 2, // Mapea a ▼
                                                                                                        PAXO_CRIT_3 = 3  // Mapea a ◄
                                                                                                        } paxo_crit_e;

                                                                                                        typedef struct {
                                                                                                          int64_t value;
                                                                                                            bool has_error;
                                                                                                              int32_t error_code;
                                                                                                              } paxo_result_t;

                                                                                                              typedef union {
                                                                                                                int8_t paxo_int;
                                                                                                                  uint8_t paxo_intu;
                                                                                                                    char paxo_chara;
                                                                                                                      bool paxo_boo;
                                                                                                                      } xxsvar;

                                                                                                                      typedef union {
                                                                                                                        int16_t paxo_int;
                                                                                                                          uint16_t paxo_intu;
                                                                                                                            _Float16 paxo_flt;
                                                                                                                              char16_t paxo_chara;
                                                                                                                                bool paxo_boo;
                                                                                                                                  uint8_t paxo_intuvec2d[2];
                                                                                                                                    int8_t paxo_intvec2d[2];
                                                                                                                                      char paxo_str[2];
                                                                                                                                      } xsvar;

                                                                                                                                      typedef union {
                                                                                                                                        int32_t paxo_int;
                                                                                                                                          uint32_t paxo_intu;
                                                                                                                                            _Float32 paxo_flt;
                                                                                                                                              _Decimal32 paxo_dec;
                                                                                                                                                _Float16 complex paxo_comflt;
                                                                                                                                                  char32_t paxo_chara;
                                                                                                                                                    bool paxo_boo;
                                                                                                                                                      uint8_t paxo_intuvec4d[4];
                                                                                                                                                        int8_t paxo_intvec4d[4];
                                                                                                                                                          uint8_t paxo_intuvec3d[3];
                                                                                                                                                            int8_t paxo_intvec3d[3];
                                                                                                                                                              uint16_t paxo_intuvec2d[2];
                                                                                                                                                                int16_t paxo_intvec2d[2];
                                                                                                                                                                  _Float16 paxo_fltvec2d[2];
                                                                                                                                                                    char paxo_str[4];
                                                                                                                                                                    } svar;

                                                                                                                                                                    typedef union {
                                                                                                                                                                      int64_t paxo_int;
                                                                                                                                                                        uint64_t paxo_intu;
                                                                                                                                                                          _Float64 paxo_flt;
                                                                                                                                                                            _Decimal64 paxo_dec;
                                                                                                                                                                              _Float32 complex paxo_com;
                                                                                                                                                                                dec_complex(_Decimal32) paxo_comdec;
                                                                                                                                                                                  char32_t paxo_chara;
                                                                                                                                                                                    bool paxo_boo;
                                                                                                                                                                                      uint16_t paxo_intuvec4d[4];
                                                                                                                                                                                        int16_t paxo_intvec4d[4];
                                                                                                                                                                                          uint16_t paxo_intuvec3d[3];
                                                                                                                                                                                            int16_t paxo_intvec3d[3];
                                                                                                                                                                                              uint32_t paxo_intuvec2d[2];
                                                                                                                                                                                                int32_t paxo_intvec2d[2];
                                                                                                                                                                                                  _Float32 paxo_fltvec2d[2];
                                                                                                                                                                                                    _Float16 paxo_fltvec3d[3];
                                                                                                                                                                                                      _Float16 paxo_fltvec4d[4];
                                                                                                                                                                                                        char paxo_str[8];
                                                                                                                                                                                                          paxo_callable_t paxo_func;
                                                                                                                                                                                                            struct { uint8_t ip[4]; uint8_t mask_or_port[4]; } paxo_netv4;
                                                                                                                                                                                                              void* paxo_other;
                                                                                                                                                                                                              } var;

                                                                                                                                                                                                              typedef union {
                                                                                                                                                                                                                _BitInt(128) paxo_int;
                                                                                                                                                                                                                  unsigned _BitInt(128) paxo_intu;
                                                                                                                                                                                                                    _Float128 paxo_flt;
                                                                                                                                                                                                                      _Decimal128 paxo_dec;
                                                                                                                                                                                                                        _Float64 complex paxo_com;
                                                                                                                                                                                                                          dec_complex(_Decimal64) paxo_comdec;
                                                                                                                                                                                                                            char32_t paxo_chara;
                                                                                                                                                                                                                              bool paxo_boo;
                                                                                                                                                                                                                                uint32_t paxo_intuvec4d[4];
                                                                                                                                                                                                                                  int32_t paxo_intvec4d[4];
                                                                                                                                                                                                                                    uint32_t paxo_intuvec3d[3];
                                                                                                                                                                                                                                      int32_t paxo_intvec3d[3];
                                                                                                                                                                                                                                        uint64_t paxo_intuvec2d[2];
                                                                                                                                                                                                                                          int64_t paxo_intvec2d[2];
                                                                                                                                                                                                                                            _Float64 paxo_fltvec2d[2];
                                                                                                                                                                                                                                              _Float32 paxo_fltvec3d[3];
                                                                                                                                                                                                                                                _Float32 paxo_fltvec4d[4];
                                                                                                                                                                                                                                                  struct { void* ptr; uint64_t len; } paxo_slice;
                                                                                                                                                                                                                                                    struct { int64_t sec; int64_t nsec; } paxo_time;
                                                                                                                                                                                                                                                      char paxo_str[16];
                                                                                                                                                                                                                                                        paxo_callable_t paxo_func;
                                                                                                                                                                                                                                                          struct { uint8_t ip[4]; uint8_t mask_or_port[4]; } paxo_netv4;
                                                                                                                                                                                                                                                            uint8_t paxo_netv6[16];
                                                                                                                                                                                                                                                              void* paxo_other;
                                                                                                                                                                                                                                                              } lvar;

                                                                                                                                                                                                                                                              typedef union {
                                                                                                                                                                                                                                                                _BitInt(256) paxo_int;
                                                                                                                                                                                                                                                                  unsigned _BitInt(256) paxo_intu;
                                                                                                                                                                                                                                                                    _Float256 paxo_flt;
                                                                                                                                                                                                                                                                      #ifdef __HAVE_DECIMAL256
                                                                                                                                                                                                                                                                        _Decimal256 paxo_dec;
                                                                                                                                                                                                                                                                          #else
                                                                                                                                                                                                                                                                            _Decimal128 paxo_dec;
                                                                                                                                                                                                                                                                              #endif
                                                                                                                                                                                                                                                                                _Float128 complex paxo_com;
                                                                                                                                                                                                                                                                                  dec_complex(_Decimal128) paxo_comdec;
                                                                                                                                                                                                                                                                                    char32_t paxo_chara;
                                                                                                                                                                                                                                                                                      bool paxo_boo;
                                                                                                                                                                                                                                                                                        uint64_t paxo_intuvec4d[4];
                                                                                                                                                                                                                                                                                          int64_t paxo_intvec4d[4];
                                                                                                                                                                                                                                                                                            uint64_t paxo_intuvec3d[3];
                                                                                                                                                                                                                                                                                              int64_t paxo_intvec3d[3];
                                                                                                                                                                                                                                                                                                unsigned _BitInt(128) paxo_intuvec2d[2];
                                                                                                                                                                                                                                                                                                  _BitInt(128) paxo_intvec2d[2];
                                                                                                                                                                                                                                                                                                    _Float128 paxo_fltvec2d[2];
                                                                                                                                                                                                                                                                                                      _Float64 paxo_fltvec3d[3];
                                                                                                                                                                                                                                                                                                        _Float64 paxo_fltvec4d[4];
                                                                                                                                                                                                                                                                                                          struct { void* ptr; uint64_t len; } paxo_slice;
                                                                                                                                                                                                                                                                                                            struct { int64_t sec; int64_t nsec; } paxo_time;
                                                                                                                                                                                                                                                                                                              char paxo_str[32];
                                                                                                                                                                                                                                                                                                                paxo_callable_t paxo_func;
                                                                                                                                                                                                                                                                                                                  struct { uint8_t ip[4]; uint8_t mask_or_port[4]; } paxo_netv4;
                                                                                                                                                                                                                                                                                                                    uint8_t paxo_netv6[16];
                                                                                                                                                                                                                                                                                                                      void* paxo_other; //punteros, pkg, strings largos, etc.
                                                                                                                                                                                                                                                                                                                      } xlvar;