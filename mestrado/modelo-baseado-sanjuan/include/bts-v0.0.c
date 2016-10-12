/*********************************************************************
 FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL

 versao 0.0               | 01.09.2016 20:37:48
 Integrando com o DVERK o sistema de equações que modela um crescimento
 tumoral, baseado "Avoiding healthy cells extinction in a cancer model",
 com adição de quimioterápico.

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

const char  vers_id[8]    = "v0.0";
const char  date_id[16]   = "01/09/2016";
const char  auth1_id[128] = "Fernanda Jaiara Dellajustina, e-mail: fernandadellajustina@gmail.com";
const char  dept1_id[128] = "Departamaneto de Física";
const char  host1_id[128] = "UFPR, Curitiba-PR, Brasil";

#include "bts-vars-0.0.h"                          // parametros/variaveis
#include "bts-util-0.0.h"                          // bibliotecas
#include "bts-ydot-0.0.h"                          // derivs function
#include "/home/fernanda/util/dverk.c"             // integrador
//#include "/home/fdellajustina/util/dverk.c"        // integrador

double      y[NN];

//  ---------------------------------------------------------------------
int main () {
  FILE *o=fopen("bts.dat","w");
  int         ind = 1, loop = 0, i = 0;
  double      t = 0.0e0, tout, w[NN * 9], c[24];

  make_header (stdout);
  make_header (o);

  init (y);

  // órbita
  while (t <= tmax) {
    if(loop % 10000 == 0) printf("%5.2f\n",t);
    if(loop % 1 == 0) fprintf(o,"%5.2f %12.6f %12.6f %12.6f %12.6f\n", t, y[0], y[1], y[2], y[3]);
    if(loop % 1000 == 0){
      if (i % 3 == 0) phi = 0.0e0;
      else            phi = 5.0e0;
      i++;
    }
    tout = t + h;
    dverk (&nn, &t, y, &tout, &tol, &ind, c, &nn, w);
    if (ind != 3) printf ("\nDVERK ERROR, IND=%d.\n\n", ind);
    loop++;
  }

 return 0;
}
