/*********************************************************************
  VARIABLES OF THE CODE:
*********************************************************************/
#define NN         4
int          nn  = NN;

//**********************************************************************

// Parametros do integrador
#define  TOL       1.0e-7                         // tolerância ao erro do dverk

#ifndef TMAX
  #define  TMAX    3.0e2
#endif

#ifndef H
  #define  H       1.0e-2
#endif
double   tmax      = TMAX;                        // tempo máximo de integração
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
#define  PHI       5.0e0
#define  R2        1.2e0
#define  R3        1.291e0
double   r2        = R2;                          // proliferation rate
double   r3        = R3;                          // proliferation rate
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
double   phi       = PHI;                         // dose do quimioterápico

//**********************************************************************

// Parametros da malha
#ifndef NPHI
  #define NPHI     1
#endif

#ifndef NTD2
  #define NTD2     1
#endif

#ifndef PHI_MIN
  #define PHI_MIN  10.0e0
#endif

#ifndef PHI_MAX
  #define PHI_MAX  15.0e0
#endif

#ifndef TD2_MIN
  #define TD2_MIN  4.0e0
#endif

#ifndef TD2_MAX
  #define TD2_MAX  10.0e0
#endif
int        nphi    = NPHI;                        // divisão da malha em x
int        ntd2    = NTD2;                        // divisão da malha em y
double  phi_min    = PHI_MIN;                     // valor inferior da malha
double  phi_max    = PHI_MAX;                     // valor superior da malha
double  td2_min    = TD2_MIN;                     // valor inferior da malha
double  td2_max    = TD2_MAX;                     // valor superior da malha

//**********************************************************************
// Controle de aplicação do quimioterápico
#ifndef PHIMAX
  #define PHIMAX   10.0e0
#endif

#ifndef TX0
  #define TX0      100.0e0
#endif

#ifndef ESPT
  #define EPST     1.0e-2
#endif
double      eps    = H;                           // contagem do período
double      epst   = 1.0e-2;                      // extinção do tumor

double      tx0    = TX0;                         // tempos seguidos com x=0
int         ntx0   = (int) TX0 / H;               // numero de tempo seguidos com x=0
double      phiMax = (PHIMAX+1);                  // dose máxima do quimioterápico

int         iT;
double      Gamma;                                // taxa de crescimento e descrescimento de phi em apli_qui()
double      td1;                                  // período sem aplicação do quimioterápico
double      t1;
double      t2;
double      dt1;                                  // contagem tempo na função de apli_qui()
double      td1_3;                                // um terço de dt1
double      td2;                                  // período de aplicação do quimioterápico
double      nT;
