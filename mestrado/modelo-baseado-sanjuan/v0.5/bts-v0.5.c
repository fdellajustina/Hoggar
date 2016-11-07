/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.5               | 06.11.2016 08:23:37
 Cálculo do expectro de expoentes de Lyapunov, para inspeção do espaço 
 de parâmetros r2 por r3 

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

const char  vers_id[8]    = "v0.5";
const char  date_id[16]   = "05/11/2016";
const char  auth1_id[128] = "FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "UFPR, DEPARTAMENTO DE FÍSICA";
const char  host1_id[128] = "CURITIBA-PR, BRASIL";

#include "bts-vars-0.5.h"                         // parametros/variaveis

double      J[NN][NN];
double      y[NVARS];

#include "bts-util-0.5.h"                         // bibliotecas
#include "bts-ydot-0.5.h"                          // derivs function
//#include "/home/fernanda/util/dverk.c"             // integrador
#include "/home/jobs/fdellajustina/util/dverk.c"

//  ---------------------------------------------------------------------
int main () {
  int         ind, loop, i, j, k, timex0, ext_tumor;
  double      t, tout, w[NN * 9], c[24], sumy;
  #ifdef BREAK
     int ext;
  #endif

  double      lyap[NN], lyap_sum[NN], znorm[NN];
  char        lyap_c[128];

  FILE       *out_ly;
  sprintf (lyap_c, "bts-lyaps-%s.dat", vers_id);
  if ((out_ly = fopen (lyap_c, "w")) == NULL)
    return 1;
  make_header (out_ly);

  make_header (stdout);

  for (j = 0; j <= nr3; j++){
    r3 = dequant(j, 0, nr3, r3_min, r3_max);
    printf("r3 = %6.2f i = %d \n", r3, j);                                  // print na tela, controle!

    for (i = 0; i <= nr2; i++){
      r2 = dequant(i, 0, nr2, r2_min, r2_max);
  
      fflush( out_ly );
      //td1  = 3.0e0*td2;
  
      init (y, lyap_sum);
       
      // condição inicial
      t    = 0.0e0;
      ind  = 1;
      loop = 0;
      iT   = 1;
      nT   = td2;                                   // começa com aplicação
      timex0 = 0;                                   // contagem de tempo em que x=0
      ext_tumor = 0;                                // extinção do tumor? (FLAG)
      sumy   = 0.0e0;                               // média de x
      dt1    = 0.0e0;
      t1     = 0.0e0;
      t2     = 0.0e0;
      td1_3  = td1/3.0e0;
      Gamma  = log(phiMax)/td1_3;                   // taxa de crescimento e descrescimento de phi
      #ifdef BREAK
        ext = 2 ;
      #endif
  
      // órbita
      while (t <= tmax) {
          tout = t + h;
          dverk (&nvars, &t, y, &tout, &tol, &ind, c, &nvars, w);
          if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
          loop++;
  
          if(ext_tumor == 0) {
  
             apli_qui(phiMax, t);              // função que aplica o quimioterápico
  
             if(fabs(y[0]) <= epst){                 // x=0?
               timex0++;
               sumy+=y[1];                           // Média de y em ntx0 tempos
               if(timex0 == ntx0){                   // x=0 para ntx0 tempo?
                 ext_tumor = 1;                      // tumor foi extinto por ntx0 tempos
                 phi = 0.0e0;                        // sem câncer por ntx0 tempos? então paramos de aplicar quimioterápico.
               }
             }
           else {
             timex0 = 0;
             sumy   = 0.0e0;
           }
          }
  
          granschmit (znorm, y);                       // ortonormalização por gram-schmidt
  
          if (t > trans){
            for (k = 0; k < NN; k++)
              if (znorm[k] > 0.e0)
                lyap_sum[k] += log(znorm[k]);
          } // end if of the trans 
  
          #ifdef BREAK
            if(ext_tumor == 1) ext++;
            if(ext % ntx0 == 0) break;
          #endif
          
      }  // end loop while
  
      fprintf (out_ly, "%18.12f %18.12f ", r3, r2);  
      for (k = 0; k < NN; k++){
        lyap[k] = lyap_sum[k] / (t - trans);
        fprintf (out_ly, "%18.12f ", lyap[k]);  // salva o espectro de expoentes de lyapunov
      }
      fprintf (out_ly, " \n");
    }   //end loop in r2

    fprintf (out_ly, " \n");
  }   //end loop in r3

  fclose (out_ly);
  return 0;
}
