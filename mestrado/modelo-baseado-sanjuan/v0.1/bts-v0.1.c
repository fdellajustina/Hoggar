/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.0               | 01.09.2016 20:37:48
 Integrando com o DVERK o sistema de equações que modela um crescimento
 tumoral, baseado "Avoiding healthy cells extinction in a cancer model",
 com adição de quimioterápico.

 versao 0.1               | 09.09.2016 08:00:53
 Implementando o cálculo do expoente de lyapunov.

 Sistema de equações:
 dx/dt = x*(1-x) - a12*x*y - a13*x*z - a14*x*q;
 dy/dt = r2*y*(1-y) - a21*x*y - a2*y*q;
 dz/dt = r3*z*x/(x + k3) - a31*z*x - d3*z - a32*z*q;
 dq/dt = phi - d4*q;
 ********************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

const char  vers_id[8]    = "v0.1";
const char  date_id[16]   = "09/09/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.1.h"                          // parametros/variaveis

double      y[NN];
double      J[N][N];

#include "bts-util-0.1.h"                          // bibliotecas
#include "bts-ydot-0.1.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador
//#include "/home/fdellajustina/util/dverk.c"        // integrador

//  ---------------------------------------------------------------------
int main () {
  FILE *o=fopen("bts.dat","w");
  int         ind, loop, k, nphi, j, irate=10;
  double      t, tout, w[NN * 9], c[24];

  double      lyap[N], lyap_sum[N], znorm[N];
  char        lyap_c[128];

  FILE       *out_ly;
  sprintf (lyap_c, "bts-lyaps-%s.dat", vers_id);
  if ((out_ly = fopen (lyap_c, "w")) == NULL)
    return 1;
  make_header (out_ly);

  make_header (stdout);
  make_header (o);

  t    = 0.0e0;
  ind  = 1;
  nphi = 0;      // aplicação doses de quimioterápico
  loop = 0;
  init (y, lyap_sum);

  // órbita
  while (t <= tmax) {
    if(loop % 10000 == 0) printf("%5.2f\n",t);
    if(loop % 1 == 0) fprintf(o,"%5.2f %12.6f %12.6f %12.6f %12.6f\n", t, y[0], y[1], y[2], y[3]);
    if(loop % 10000 == 0){
      if (nphi % 3 == 0) phi = 0.0e0;
      else               phi = 5.0e0;
      nphi++;
    }
    for (j = 0; j < irate; j++) {
      tout = t + h;
      dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
      if (ind != 3){
        printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
        goto FINISH;
      }
      loop++;
    }

    // ortonormalização por gram-schmidt
    granschmit (znorm, y);

    if (t > trans){
      for (k = 0; k < N; k++)
        if (znorm[k] > 0.e0)
          lyap_sum[k] += log(znorm[k]);
    }

  } // end loop of the while

  for (k = 0; k < N; k++)
    lyap[k] = lyap_sum[k] / (t - trans);

  fprintf (out_ly, "%18.12f %18.12f %18.12f %8.4f %8.4f\n", lyap[0], lyap[1], lyap[2], lyap[3], t);  // salva o espectro de expoentes de lyapunov
  printf ("%18.12f %18.12f %18.12f %8.4f %8.4f\n", lyap[0], lyap[1], lyap[2], lyap[3], t);

 FINISH:fclose(o), fclose (out_ly);

 return 0;
}
