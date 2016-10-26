/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.4               | 20.09.2016 13:31:36
 Otimização da aplicação do quimioterápico.

 versao 0.43              | 10.10.2016 13:31:36
 testando pontos do espaço de parâmetros.

 versao 0.45              | 18.10.2016 07:57:04
 Após x ir a zero com a aplicação do quimioterápico para ntx0 tempos,
 não se aplica mais quimio e observa-se o comportamento do sistema.

 versao 0.46              | 23.10.2016 15:49:06
 Melhoramento da aplicação do quimioterápico, com uma função exponencial
 até um certo limite

 versao 0.47              | 25.10.2016 14:39:06
 Melhoramento da aplicação do quimioterápico, com controle do phiMax.

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

const char  vers_id[8]    = "v0.47";
const char  date_id[16]   = "25/10/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.47.h"                         // parametros/variaveis
#include "bts-util-0.47.h"                         // bibliotecas
#include "bts-ydot-0.4.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador

double      y[NN];

//  ---------------------------------------------------------------------
int main () {
  int         ind, loop, i, j, timex0, ext_tumor;
  double      phi0;
  double      t, tout, w[NN * 9], c[24], sumx;

  char file[256];
  FILE *a;
  sprintf(file,"bts-%s.dat", vers_id);
  if((a = fopen(file, "w")) == NULL) return 1;

  make_header (stdout);
  make_header (a);

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

          y[0] = 0.2e0;                                 // x
          y[1] = 0.9e0;                                 // y
          y[2] = 0.1e0;                                 // z
          y[3] = phi_max;                               // q

          t    = 0.0e0;
          ind  = 1;
          loop = 0;
          iT   = 1;
          nT   = td2;                                   // começa com aplicação
          timex0 = 0;                                   // contagem de tempo em que x=0
          ext_tumor = 0;                                // extinção do tumor? (FLAG)
          sumx   = 0.0e0;                               // média de x
          dt1    = 0.0e0;
          t1     = 0.0e0;
          t2     = 0.0e0;
          td1_3  = td1/3.0e0;
          Gamma  = log(phiMax)/td1_3;                   // taxa de crescimento e descrescimento de phi

          // órbita
          while (t <= tmax) {
             if(loop % 1 == 0) fprintf(a,"%5.2f %12.6f %12.6f %12.6f %12.6f %12.6f\n", t, y[0], y[1], y[2], y[3], phi);

              if(ext_tumor == 0) {                      // tumor foi extinto?
                apli_qui(phi0, phiMax, t);              // função que aplica o quimioterápico
              }

              tout = t + h;
              dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
              if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
              loop++;

             if(ext_tumor == 0) {
                if(fabs(y[0]) <= epst){                 // x=0?
                  timex0++;
                  sumx+=y[1];                           // Média de y
                  if(timex0 == ntx0){                   // x=0 para ntx0 tempo?
                    ext_tumor = 1;                      // tumor foi extinto por ntx0 tempos
                    phi = 0.0e0;                        // sem câncer por ntx0 tempos? então paramos de aplicar quimioterápico.
                    //y[3] = 0.0e0;
                    //break;
                  }
              }
              else {
                timex0 = 0;
                sumx   = 0.0e0;
              }
             }
          }  // end loop while
        }   //end loop td2
      }    // and single region
    }     //end loop phi0
  }

 fclose (a);
 return 0;
}
