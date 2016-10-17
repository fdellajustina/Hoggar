/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.0               | 01.09.2016 20:37:48
 Integrando com o DVERK o sistema de equações que modela um crescimento
 tumoral, baseado "Avoiding healthy cells extinction in a cancer model",
 com adição de quimioterápico.

 versao 0.3               | 09.09.2016 10:10:54
 Bacia de atração.

 versao 0.4               | 20.09.2016 13:31:36
 Otimização da aplicação do quimioterápico.

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

const char  vers_id[8]    = "v0.4";
const char  date_id[16]   = "20/09/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.4.h"                          // parametros/variaveis
#include "bts-util-0.4.h"                          // bibliotecas
#include "bts-ydot-0.4.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador

double      y[NN];

//  ---------------------------------------------------------------------
int main () {
  //FILE *o=fopen("bts-bacia.dat","w");
  FILE *o=fopen("bts.dat","w");
  int         ind, loop, i, j, iT, timex0, ntx0;
  int         nphi, n10step, stepmax;
  double      phi_min, phi_max, phi0, td1, td2, eps, epst, nT;
  double      t, tout, w[NN * 9], c[24];

  make_header (stdout);
  make_header (o);

  ntx0    = 200.0e0 / h; // numero de tempo seguidos com x=0
  td1     = 40.0e0;      // tempo sem aplicação do quimio
  td2     = 10.0e0;      // tempo de aplicação do quimio
  eps     = h;           // contagem do período
  epst    = 1.0e-4;      // extinção do tumor
  nphi    = 1;
  stepmax = 1;
  phi_min = 1.0e0;      // dose de quimioterapico
  phi_max = 10.0e0;

  n10step = 1000;       // se h=1.0e-2, a cada 1000 iteradas temos 10 tempos de integração

  //#pragma omp parallel private(i,j)
  //{
    //for (i = 0; i < nphi; i++){
      //phi0 = dequant(i, 0, nphi, phi_min, phi_max);
      phi0 = 5.0e0;
      //printf("phi = %6.2f i = %d \n", phi0, i);                                  // print na tela, controle!

      ////#pragma omp single
      ////{
        //for (j = 1; j <=  stepmax; j++){

          //fflush(o);

          y[0] = 0.1e0;                                        // x
          y[1] = 0.9e0;                                        // y
          y[2] = 0.8e0;                                        // z
          y[3] = 0.0e0;

          t    = 0.0e0;
          ind  = 1;
          loop = 0;
          iT   = 1;
          nT   = td2;     // começa com aplicação
          timex0 = 0;     // contagem de tempo em que x=0

          // órbita
          while (t <= tmax) {
            if(loop % 1 == 0) fprintf(o,"%5.2f %12.6f %12.6f %12.6f %12.6f\n", t, y[0], y[1], y[2], y[3]);
            //if(loop % 1000 == 0) printf("%5.2f %d %6.2f %6.2f %6.2f\n", phi, iT, nT, t, nT - t);
            //printf("%5.2f %d %6.2f %6.2f %6.2f\n", phi, iT, nT, t, nT - t);

            if(((iT+1) % 2 == 0)){
              phi = phi0;
              if((nT - t) < eps){
                 iT++;
                 nT += td1;
              }
            }
            else{
              phi = 0.0e0;
              if((nT - t) < eps){
                 iT++;
                 nT += td2;
              }
            }

            tout = t + h;
            dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
            if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
            loop++;

            if(y[1] <= epst){
              timex0++;
              if(timex0 == ntx0){
                fprintf(o,"\n#%12.6f %12.6f %12.6f\n", td2, phi0, t);
                printf("\n#%12.6f %12.6f %12.6f\n", td2, phi0, t);
                break;
              }
            }
            else timex0 = 0;
          }  // end loop while

          //fprintf(o,"%12.6f %8d %12.6f %12.6f %12.6f %12.6f\n", phi0, j, y[0], y[1], y[2], y[3]);
        //} //end loop j
        //fprintf (o, "\n");  // separa um bloco de outro
      //}  // and single region

    //}  //end loop phi0
  //}

 fclose (o);
 return 0;
}
