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

 versao 0.43              | 10.10.2016 13:31:36
 testando pontos do espaço de parâmetros.

 versao 0.45              | 18.10.2016 07:57:04
 Após x ir a zero com a aplicação do quimioterápico para ntx0 tempos,
 não se aplica mais quimio e observa-se o comportamento do sistema.

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

const char  vers_id[8]    = "v0.45";
const char  date_id[16]   = "18/10/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.45.h"                          // parametros/variaveis
#include "bts-util-0.4.h"                          // bibliotecas
#include "bts-ydot-0.4.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador

double      y[NN];

//  ---------------------------------------------------------------------
int main () {
  //FILE *o=fopen("optimal-q.dat","w");
  FILE *a=fopen("bts-v0.45.dat","w");
  int         ind, loop, i, j, iT, timex0, ntx0, ext_tumor;
  double      phi0, td1, td2, eps, epst, nT;
  //int         ind, loop, i, j, iT, timex0, ntx0, nphi, ntd2, ext_tumor;
  //double      phi_min, phi_max, td2_min, td2_max, phi0, td1, td2, eps, epst, nT;
  double      t, tout, w[NN * 9], c[24], sumx;

  make_header (stdout);
  //make_header (o);
  make_header (a);

  ntx0    = 100.0e0 / h; // numero de tempo seguidos com x=0
  eps     = h;           // contagem do período
  epst    = 1.0e-2;      // extinção do tumor

  #pragma omp parallel private(i,j)
  {
    for (i = 0; i < nphi; i++){
      phi0 = dequant(i, 0, nphi, phi_min, phi_max);
      printf("phi = %6.2f i = %d \n", phi0, i);                                  // print na tela, controle!

      #pragma omp single
      {
        for (j = 0; j <  ntd2; j++){
          td2 = dequant(j,0,ntd2,td2_min,td2_max);      // tempo de aplicação do quimio
          td1 = 3.0e0 * td2;                            // tempo sem aplicação do quimio

          //fflush(o);

          y[0] = 0.2e0;                                       // x
          y[1] = 0.9e0;                                        // y
          y[2] = 0.1e0;                                        // z
          y[3] = phi_max;                                     // q

          t    = 0.0e0;
          ind  = 1;
          loop = 0;
          iT   = 1;
          nT   = td2;     // começa com aplicação
          timex0 = 0;     // contagem de tempo em que x=0
          ext_tumor = 0;  // extinção do tumor? (FLAG)
          sumx   = 0.0e0; // média de x
          //phi    = phi0;

          // órbita
          while (t <= tmax) {
           if(loop % 1 == 0) fprintf(a,"%5.2f %12.6f %12.6f %12.6f %12.6f\n", t, y[0], y[1], y[2], y[3]);

            if(ext_tumor == 0) {
              if(td1 <= 1.0e-5) phi = phi0;
              else{
                if(((iT+1) % 5 == 0)){
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
              }
            }

            tout = t + h;
            dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
            if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
            loop++;

           if(ext_tumor == 0) {
            if(fabs(y[0]) <= epst){
              timex0++;
              sumx+=y[1];
              if(timex0 == ntx0){
                //fprintf(o,"%12.6f %12.6f %12.6f\n", phi0, td2, sumx/(double) timex0);
                ext_tumor = 1;
                phi = 0.0e0;
                y[3] = 0.0e0;
                //break;
              }
            }
            else {
              timex0 = 0;
              sumx   = 0.0e0;
            }
           }

          }  // end loop while

          //if(ext_tumor == 0) fprintf(o,"%12.6f %12.6f %12.6f\n", phi0, td2, -1.0e0);
        }    //end loop td2
        //fprintf (o, "\n");  // separa um bloco de outro
      }      // and single region

    }        //end loop phi0
  }

 fclose (a);
 return 0;
}
