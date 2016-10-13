/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.0               | 01.09.2016 20:37:48
 Integrando com o DVERK o sistema de equações que modela um crescimento
 tumoral, baseado "Avoiding healthy cells extinction in a cancer model",
 com adição de quimioterápico.

 versao 0.3               | 09.09.2016 10:10:54
 Bacia de atração.

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

const char  vers_id[8]    = "v0.3";
const char  date_id[16]   = "09/09/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.3.h"                          // parametros/variaveis
#include "bts-util-0.3.h"                          // bibliotecas
#include "bts-ydot-0.3.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador
//#include "/home/fdellajustina/util/dverk.c"        // integrador

double      y[NN];

//  ---------------------------------------------------------------------
int main () {
  FILE *o=fopen("bts-bacia.dat","w");
  int         ind, loop, nphi, i, j;
  int         nx, ny;
  double      x_min, x_max, y_min, y_max, x0, y0;
  double      t, tout, w[NN * 9], c[24];

  make_header (stdout);
  make_header (o);

  nx    = 500;
  ny    = 500;
  x_min = 0.1e0;     // celulas tumorais
  x_max = 3.0e0;
  y_min = 1.0e0;     // celulas saudaveis
  y_max = 7.0e0;

  #pragma omp parallel private(i,j)
  {
    for (i = 0; i <= nx; i++){
      x0 = dequant(i, 0, nx, x_min, x_max);
      printf("i = %d \n", i);                     // print na tela, controle!

      #pragma omp single
      {
        for (j = 0; j <= ny; j++){
          y0 = dequant(j, 0, ny, y_min, y_max);

          fflush(o);

          y[0] = x0;                                        // z
          y[1] = y0;                                        // z
          y[2] = 0.2e0;                                        // z
          y[3] = 0.0e0;
          t    = 0.0e0;
          ind  = 1;
          loop = 0;
          nphi = 0;

          // órbita
          while (t <= tmax) {
            if(loop % 10000 == 0){
              if (nphi % 3 == 0) phi = 0.0e0;
              else               phi = 5.0e0;
              nphi++;
            }
            tout = t + h;
            dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
            if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
            loop++;
          }  // end loop while

          fprintf(o,"%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f\n", x0, y0, y[0], y[1], y[2], y[3]);
        } //end loop r3
        fprintf (o, "\n");  // separa um bloco de outro
      }  // and single region

    }  //end loop r2
  }

 fclose (o);
 return 0;
}
