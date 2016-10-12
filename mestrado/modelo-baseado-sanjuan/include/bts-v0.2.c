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
#include<omp.h>           // OpenMP include file

const char  vers_id[8]    = "v0.1";
const char  date_id[16]   = "09/09/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.2.h"                          // parametros/variaveis

double      y[NN];
double      J[N][N];

#include "bts-util-0.2.h"                          // bibliotecas
#include "bts-ydot-0.2.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador
//#include "/home/fdellajustina/util/dverk.c"        // integrador

//  ---------------------------------------------------------------------
int main () {
  int         ind, loop, nphi, i, j, k, irate=10;
  int         na14, na22;
  double      a14_min, a14_max, a22_min, a22_max;
  double      t, tout, w[NN * 9], c[24];

  double      lyap[N], lyap_sum[N], znorm[N];
  char        lyap_c[128];

  FILE       *out_ly;
  sprintf (lyap_c, "bts-lyaps-%s.dat", vers_id);
  if ((out_ly = fopen (lyap_c, "w")) == NULL)
    return 1;
  make_header (out_ly);

  make_header (stdout);

  na14    = 500;
  na22    = 500;
  a22_min = 1.0e-1;
  a22_max = 1.0e-4;
  a14_min = 1.0e-1;
  a14_max = 1.0e-4;

  #pragma omp parallel private(i,j)
  {
    for (i = 0; i <= na14; i++){
      a14 = dequant(i, 0, na14, a14_min, a14_max);
      printf("i = %d \n", i);                     // print na tela, controle!

      #pragma omp single
      {
        for (j = 0; j <= na22; j++){
          a22 = dequant(j, 0, na22, a22_min, a22_max);

          fflush( out_ly );

          t    = 0.0e0;
          ind  = 1;
          nphi = 0;      // aplicação doses de quimioterápico
          loop = 0;
          init (y, lyap_sum);

          // órbita
          while (t <= tmax) {
            if(loop % 10000 == 0){
              if (nphi % 3 == 0) phi = 0.0e0;
              else               phi = 5.0e0;
              nphi++;
            }
            for (k = 0; k < irate; k++) {
              tout = t + h;
              dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
              if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
              loop++;
            }

            // ortonormalização por gram-schmidt
            granschmit (znorm, y);

            if (t > trans){
              for (k = 0; k < N; k++)
              if (znorm[k] > 0.e0) lyap_sum[k] += log(znorm[k]);
            }
          } // end loop of the while

          for (k = 0; k < N; k++)
            lyap[k] = lyap_sum[k] / (t - trans);

          fprintf (out_ly, "%8.4f %8.4f %18.12f %18.12f %18.12f %18.12f\n", a22, a14, lyap[0], lyap[1], lyap[2], lyap[3]);  // salva o espectro de expoentes de lyapunov
        } //end loop r3
        fprintf (out_ly, "\n");  // separa um bloco de outro
      }  // and single region

    }  //end loop r2
  }

 fclose (out_ly);

 return 0;
}
