/*********************************************************************
  VARIABLES OF THE CODE:
*********************************************************************/
#define NN            4
#define NVARS         NN*(NN+1)
int          nn     = NN;
int          nvars  = NVARS;

//**********************************************************************

// Parametros do integrador
#define  TOL       1.0e-7                         // tolerância ao erro do dverk

#ifndef TMAX
  #define  TMAX    1.0e3
#endif

#ifndef TRANS
  #define  TRANS    5.0e2
#endif

#ifndef H
  #define  H       1.0e-2
#endif
double   tmax      = TMAX;                        // tempo máximo de integração
double   trans     = TRANS;                       // tempo transiente da dinâmica
double   h         = H;                           // passo de integração do DVERK
double   tol       = TOL;                         // tolerância ao erro

//**********************************************************************

// Parametros do sistema
#define  K3        0.3e0
#define  A12       0.5e0
#define  A13       1.2e0
#define  A14       1.0e-2
#define  A21       4.8e0
#define  A22       1.0e-3
#define  A31       1.1e0
#define  A32       1.0e-5
#define  D3        0.1e0
#define  D4        0.05e0
double   a12       = A12;                         // competition coefficient between GC and CC (normalized)
double   a13       = A13;                         // competition coefficient between GC and CC (normalized)
double   a14       = A14;                         // competition coefficient (termo novo devido ao quimioterápico)
double   a21       = A21;                         // competition coefficient between CC and GC (normalized)
double   a22       = A22;                         // competition coefficient (termo novo devido ao quimioterápico)
double   a31       = A31;                         // competition coefficient between CC and GC (normalized)
double   a32       = A32;                         // competition coefficient (termo novo devido ao quimioterápico)
double   k3        = K3;                          // holling type 2 (normalized)
double   d3        = D3;                          // holling type 2 (normalized)
double   d4        = D4;                          // taxa de difução do quimioterápico

//**********************************************************************

// Espaço de Parametro
#ifndef NR2
  #define NR2     5
#endif

#ifndef NR3
  #define NR3     5
#endif

#ifndef R2_MIN
  #define R2_MIN  0.0e0
#endif

#ifndef R2_MAX
  #define R2_MAX  1.3e0
#endif

#ifndef R3_MIN
  #define R3_MIN  0.0e0
#endif

#ifndef R3_MAX
  #define R3_MAX  1.4e0
#endif
int        nr3     = NR3;                          // divisão da malha em y
int        nr2     = NR2;                          // divisão da malha em x
double     r2      = R2_MAX;                       // proliferation rate
double     r3      = R3_MAX;                       // proliferation rate
double   r2_min    = R2_MIN;                       // valor inferior da malha
double   r2_max    = R2_MAX;                       // valor superior da malha
double   r3_min    = R3_MIN;                       // valor inferior da malha
double   r3_max    = R3_MAX;                       // valor superior da malha

// Parametro de aplicação de quimio na malha
#ifndef NPHI
  #define NPHI     1
#endif

#ifndef NTD2
  #define NTD2     1
#endif

#ifndef PHI_MIN
  #define PHI_MIN  5.0e0
#endif

#ifndef PHI_MAX
  #define PHI_MAX  10.0e0
#endif

#ifndef TD2_MIN
  #define TD2_MIN  10.0e0
#endif

#ifndef TD2_MAX
  #define TD2_MAX  40.0e0
#endif
int        nphi    = NPHI;                        // divisão da malha em x
int        ntd2    = NTD2;                        // divisão da malha em y
double  phi_min    = PHI_MIN;                     // valor inferior da malha
double  phi_max    = PHI_MAX;                     // valor superior da malha
double  td2_min    = TD2_MIN;                     // valor inferior da malha
double  td2_max    = TD2_MAX;                     // valor superior da malha
double      phi    = PHI_MAX;                     // dose do quimioterápico
double   phiMax    = (PHI_MAX+1);                 // dose máxima do quimioterápico
double      td1    = TD2_MIN*3.0e0;               // período sem aplicação do quimioterápico
double      td2    = TD2_MIN;                     // período de aplicação do quimioterápico

// Condições iniciais malha
#ifndef NX
  #define NX     5
#endif

#ifndef NY
  #define NY     5
#endif

#ifndef NZ
  #define NZ     5
#endif

#ifndef X_MIN
  #define X_MIN  0.0e0
#endif

#ifndef X_MAX
  #define X_MAX  1.0e0
#endif

#ifndef Y_MIN
  #define Y_MIN  0.0e0
#endif

#ifndef Y_MAX
  #define Y_MAX  1.0e0
#endif

#ifndef Z_MIN
  #define Z_MIN  0.0e0
#endif

#ifndef Z_MAX
  #define Z_MAX  1.0e0
#endif
int        nx      = NX;                          // divisão da malha em y
double    x_min    = X_MIN;                       // valor inferior da malha
double    x_max    = X_MAX;                       // valor superior da malha
int        ny      = NY;                          // divisão da malha em y
double    y_min    = Y_MIN;                       // valor inferior da malha
double    y_max    = Y_MAX;                       // valor superior da malha
int        nz      = NZ;                          // divisão da malha em y
double    z_min    = Z_MIN;                       // valor inferior da malha
double    z_max    = Z_MAX;                       // valor superior da malha

//**********************************************************************
// Controle de aplicação do quimioterápico
#ifndef TX0
  #define TX0      100.0e0
#endif

#ifndef ESPT
  #define EPST     1.0e-2
#endif
double      eps    = H;                           // contagem do período
double      epst   = EPST;                        // extinção do tumor

double      tx0    = TX0;                         // tempos seguidos com x=0
int         ntx0   = (int) TX0 / H;               // numero de tempo seguidos com x=0

int         iT;
double      Gamma;                                // taxa de crescimento e descrescimento de phi em apli_qui()
double      t1;
double      t2;
double      dt1;                                  // contagem tempo na função de apli_qui()
double      td1_3;                                // um terço de dt1
double      nT;
