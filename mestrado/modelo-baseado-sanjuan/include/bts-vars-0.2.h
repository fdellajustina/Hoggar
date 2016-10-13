/*********************************************************************
  VARIABLES OF THE CODE:

a12    = ????
a13    = ????
a21    = ????
a31    = ????
r2     = ????
r3     = ????
d3     = ????
k3     = ????

TMAX   = TEMPO MÁXIMO DE INTEGRAÇÃO
H      = PASSO DE INTEGRAÇÃO DO DVERK
TOL    = TOLERÂNCIA AO ERRO

TIPO   = INICIALIZAÇÃO ->  0 - Saddle with two positive eigenvalues
                       ->  1 - Saddle with two negative eigenvalues (only normal cells)
                       ->  2 - Stable with eigenvalues small (only tumor cells)
                       ->  3 - Saddle with two stable and one unestable direction
                       ->  4 - Spiral stable
                       ->  5 - Spiral saddle
*********************************************************************/
#define N         4
#define NN        N*(N+1)
int          n  = N;
int          nn = NN;

#define  TIPO     1

#define  TMAX     1.0e3
#define  TRANS    5.0e2
#define  H        1.0e-2
#define  TOL      1.0e-7

// parametros
#define  K3       0.3e0
#define  A12      0.5e0
#define  A13      1.2e0
#define  A14      1.0e-3
#define  A21      4.8e0
#define  A22      1.0e-3
#define  A31      1.1e0
#define  A32      1.0e-5
#define  D3       0.1e0
#define  D4       0.2e0
#define  PHI      5.0e0
#define  R2       1.2e0
#define  R3       1.291e0

// malha do sistema
#ifndef NX
  #define NX = 50
#endif

#ifndef NY
  #define NY = 50
#endif

#ifndef XMIN
  #define XMIN = 0.0e0
#endif

#ifndef XMAX
  #define XMAX = 10.0e0
#endif

#ifndef YMIN
  #define YMIN = 0.0e0
#endif

#ifndef YMAX
  #define YMAX = 10.0e0
#endif
int          nx = NX;                            // divisão da malha em x
int          ny = NY;                            // divisão da malha em y
double     xmin = XMIN;                          // valor inferior da malha
double     xmax = XMAX;                          // valor superior da malha
double     ymin = YMIN;                          // valor inferior da malha
double     ymax = YMAX;                          // valor superior da malha

double   r2     = R2;                            // proliferation rate
double   r3     = R3;                            // proliferation rate
double   a12    = A12;                           // competition coefficient between GC and CC (normalized)
double   a13    = A13;                           // competition coefficient between GC and CC (normalized)
double   a14    = A14;                           // competition coefficient (termo novo devido ao quimioterápico)
double   a21    = A21;                           // competition coefficient between CC and GC (normalized)
double   a22    = A22;                           // competition coefficient (termo novo devido ao quimioterápico)
double   a31    = A31;                           // competition coefficient between CC and GC (normalized)
double   a32    = A32;                           // competition coefficient (termo novo devido ao quimioterápico)
double   k3     = K3;                            // holling type 2 (normalized)
double   d3     = D3;                            // holling type 2 (normalized)
double   d4     = D4;                            // taxa de difução do quimioterápico
double   phi    = PHI;                           // dose do quimioterápico

double   tmax   = TMAX;                          // tempo máximo de integração
double   trans  = TRANS;                         // transiente para o cálculo do exp. Lyapunov
double   h      = H;                             // passo de integração do DVERK
double   tol    = TOL;                           // tolerância ao erro

// tipo de inicialização
int      tipo   = TIPO;                          // 0 - Interessante
                                                 // 1 - Interessante
