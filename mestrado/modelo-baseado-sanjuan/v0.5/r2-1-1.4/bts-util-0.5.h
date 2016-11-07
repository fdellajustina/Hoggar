void make_header (FILE *o);
// #############################################################################
// inicializão do sistema
void init (double *y, double *lyap_sum) {
  int i;
  // Escolha da inicialização
    y[0] = 0.2e0;                                 // x
    y[1] = 0.9e0;                                 // y
    y[2] = 0.5e0;                                 // z
    y[3] = phiMax;                                // q

  for (i = NN; i < NVARS; i++)
    y[i] = 0.e0;                                          // zera o bloco da base vetorial

  for (i = 0; i < NN; i++) {
    y[NN * (i + 1) + i] = 1.e0;                            // inicialização dos vetores da base
    lyap_sum[i] = 0.e0;                                   // zera os somatórios lyapunovs
  }

} // init

// #############################################################################
// Make the header of the archives with variables of the system
void make_header (FILE * o) {
  fprintf (o, "# GROWTH TUMOR SIMULATION bts-%s.c (%s)\n", vers_id, date_id);
  fprintf (o, "# 2016 (C) %s\n", auth1_id);
  fprintf (o, "#          %s\n", dept1_id);
  fprintf (o, "#          %s\n", host1_id);
  fprintf (o, "#\n");
  fprintf (o, "#        NN = %20d\n", NN);
  fprintf (o, "#\n");
  fprintf (o, "#       a12 = %10.5e\n", a12);
  fprintf (o, "#       a13 = %10.5e\n", a13);
  fprintf (o, "#       a21 = %10.5e\n", a21);
  fprintf (o, "#       a31 = %10.5e\n", a31);
  fprintf (o, "#        r2 = %10.5e\n", r2);
  fprintf (o, "#        r3 = %10.5e\n", r3);
  fprintf (o, "#        d3 = %10.5e\n", d3);
  fprintf (o, "#        k3 = %10.5e\n", k3);
  fprintf (o, "#\n");
  fprintf (o, "#      nphi = %5d\n", nphi);
  fprintf (o, "#      ntd2 = %5d\n", ntd2);
  fprintf (o, "#   phi_min = %10.5f\n", phi_min);
  fprintf (o, "#   phi_max = %10.5f\n", phi_max);
  fprintf (o, "#   td2_min = %10.5f\n", td2_min);
  fprintf (o, "#   td2_max = %10.5f\n", td2_max);
  fprintf (o, "#\n");
  fprintf (o, "#    phiMax = %10.5f\n", phiMax);
  fprintf (o, "#\n");
  fprintf (o, "#       td1 = %10.5f\n", td1);
  fprintf (o, "#       td2 = %10.5f\n", td2);
  fprintf (o, "#       eps = %10.5f\n", eps);
  fprintf (o, "#      epst = %10.5f\n", epst);
  fprintf (o, "#      tx0  = %10.5f\n", tx0);
  fprintf (o, "#      ntx0 = %d\n", ntx0);
  fprintf (o, "#\n");
  fprintf (o, "#      tmax = %10.5f\n", tmax);
  fprintf (o, "#         h = %10.5f\n", h);
  fprintf (o, "#       tol = %10.5e\n", tol);
  fprintf (o, "#\n");
  #ifdef BREAK
    fprintf (o, "#     BREAK DEFINED\n");              // Break após ntx0 tempos
  #endif
  fprintf (o, "#\n");
}                                                      // end for function make_header(FILE *o)

// DEQUANT
double dequant (int i, int min, int max, double xmin, double xmax) {
  return (xmin + (xmax - xmin) * (double) (i - min) / (double) (max - min));
}

//*************************************************************************
// Função responsável pela aplicação e dosagem de quimioterápico no sistema.
// O intervalo de aplicação de quimio td1 é dividido em 3 partes, das quais
// a dose de phi cresce exponencialmente com taxa Gamma no primeiro terço de
// tempo, no segundo terço a aplicaçãoé mantida constante em phiMax e no
// último terço a dose decai exponencialmente com a mesma taxa Gamma até 0.
// O fator subtraindo (-1) que surge nos intervalos de crescimento e
// decrescimento é devido que exp(0)=1 e portanto: exp(0) - 1 = 0.
void apli_qui(double phiMax, double t){
  if(td1 < 1.0e-5) phi = phiMax;        // aplicação contínua de quimio?
  else{
    if(t1 < td1){                       // período COM aplicação de quimio?
      t1 += h;

      if(dt1 < td1_3){
        phi=exp(Gamma*dt1)-1.0e0;
        dt1+=h;
      }
      else{
        if((dt1 > td1_3) && (dt1 < 2.0e0*td1_3)){
          dt1+=h;
        }
        else{
          if((dt1 > 2.0e0*td1_3) && (dt1 < 3.0e0*td1_3)){
            phi=phiMax*exp(-Gamma*fabs(dt1-2.0e0*td1_3))-1.0e0;
            dt1+=h;
          }
        }
      }

      if(fabs(t1 - td1) < eps) t2 = 0.0e0; // completou o período COM quimio?
    }
    else{                               // período SEM aplicação de quimio?
      t2 += h;
      phi = 0.0e0;
      if(fabs(t2 - td2) < eps){         // completou o período SEM quimio?
         t1 = 0.0e0;
         dt1 = 0.0e0;
      }
    }
  }

}

// gera o gnuplot script
void make_gnu_frames(){
  FILE *o;
  char file[256];
  sprintf(file,"anim-frames-%s.gnu", vers_id);
  o = fopen(file, "w");

  fprintf(o,"# ************************************************************************\n");
  fprintf(o,"#  %s \n", auth1_id);
  fprintf(o,"#  %s, %s \n", dept1_id, host1_id);
  fprintf(o,"#\n");
  fprintf(o,"#  GnuPlot script | %s \n", date_id);
  fprintf(o,"#\n");
  fprintf(o,"# ************************************************************************\n");
  fprintf(o,"\n");

  fprintf(o,"phi = dphi*frame\n");
  fprintf(o,"td2 = dtd2*frame\n");
  fprintf(o,"x   = dx*frame\n");
  fprintf(o,"y   = dy*frame\n");
  fprintf(o,"z   = dz*frame\n");
  fprintf(o,"s = sprintf('{/:Bold=18 tx0=%%6.2f epst=%%6.2f phiMax = %%6.2f td2 = %%6.2f x = %%6.2f y = %%6.2f z = %%6.2f}', tx0, epst, phi, td2, x, y, z) \n");
  fprintf(o,"print frame\n");

  fprintf(o,"set multiplot title s font ',14'\n");

  fprintf(o,"\n#*********************************\n");
  fprintf(o,"set xtics 100 \n");
  fprintf(o,"set ytics 0.2 \n");
  fprintf(o,"set origin 0.35,0.0 \n");
  fprintf(o,"set size 0.65,0.3 \n");
  fprintf(o,"set ylabel 'z' rotate by 0 \n");
  fprintf(o,"plot [0:400][0:1.2] 'bts-%s.dat' i frame u 1:4 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"\n#********************************* \n");
  fprintf(o,"set origin 0.35,0.32 \n");
  fprintf(o,"set size 0.65,0.3 \n");
  fprintf(o,"unset xlabel \n");
  fprintf(o,"set ylabel 'x' rotate by 0 \n");
  fprintf(o,"plot [0:400][-0.1:1.1] 'bts-%s.dat' i frame u 1:2 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"\n#********************************* \n");
  fprintf(o,"set origin 0.35,0.62 \n");
  fprintf(o,"set size 0.65,0.3 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'y' rotate by 0 \n");
  fprintf(o,"plot [0:400][-0.1:1.1] 'bts-%s.dat' i frame u 1:3 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"\n#********************************* \n");
  fprintf(o,"set origin 0.0,0.1 \n");
  fprintf(o,"set size 0.35,0.3 \n");

  fprintf(o,"set xtics 100 \n");
  fprintf(o,"set ytics 20 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'q' rotate by 0 \n");
  fprintf(o,"plot [0:400][0:70] 'bts-%s.dat' i frame u 1:5 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"# Small plot  ******************** \n");
  fprintf(o,"set origin 0.0,0.6 \n");
  fprintf(o,"set size 0.35,0.3 \n");
  fprintf(o,"set ytics 10 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'phi' rotate by 0 \n");
  fprintf(o,"plot [0:400][0:%6.1f] 'bts-%s.dat' i frame u 1:6 w l lw 2 lc -1 \n", phi_max, vers_id);

  fprintf(o,"unset multiplot\n");

  fprintf(o,"frame = frame + 1 \n");
  fprintf(o,"\n");
  fprintf(o,"if(frame<frames) reread \n");
  fclose(o);
}

// gera o gnuplot script
void make_gnu_anim(){
  char file[256];
  FILE *o;
  sprintf(file,"anim-%s.gnu", vers_id);
  o = fopen(file, "w");

  fprintf(o,"# ************************************************************************ \n");
  fprintf(o,"#  %s \n", auth1_id);
  fprintf(o,"#  %s, %s \n", dept1_id, host1_id);
  fprintf(o,"#");
  fprintf(o,"#  GnuPlot script | %s \n", date_id);
  fprintf(o,"#");
  fprintf(o,"# ************************************************************************");
  fprintf(o,"\n");

  fprintf(o,"unset key\n");
  fprintf(o,"\n");
  fprintf(o,"set tics out\n");
  fprintf(o,"set size 2,1\n");
  fprintf(o,"set grid\n");
  fprintf(o,"\n");
  fprintf(o,"tx0        = %8.3f\n", tx0);
  fprintf(o,"epst       = %8.3f\n", epst);
  fprintf(o,"phi_max    = %8.3f\n", phi_max);
  fprintf(o,"phi_min    = %8.3f\n", phi_min);
  fprintf(o,"td2_max    = %8.3f\n", td2_max);
  fprintf(o,"td2_min    = %8.3f\n", td2_min);
  fprintf(o,"\n");
  fprintf(o,"x_max    = %8.3f\n", x_max);
  fprintf(o,"x_min    = %8.3f\n", x_min);
  fprintf(o,"y_max    = %8.3f\n", y_max);
  fprintf(o,"y_min    = %8.3f\n", y_min);
  fprintf(o,"z_max    = %8.3f\n", z_max);
  fprintf(o,"z_min    = %8.3f\n", z_min);
  fprintf(o,"\n");
  fprintf(o,"frames     = %d\n", nx);
  fprintf(o,"frame      = 0\n");
  fprintf(o,"dphi       = (phi_max-phi_min)/frames \n");
  fprintf(o,"dtd2       = (td2_max-td2_min)/frames \n");
  fprintf(o,"\n");
  fprintf(o,"dx         = (x_max-x_min)/frames \n");
  fprintf(o,"dy         = (y_max-y_min)/frames \n");
  fprintf(o,"dz         = (z_max-z_min)/frames \n");
  fprintf(o,"\n");
  fprintf(o,"set term gif animate delay 40 opt size 1500,1200\n");
  fprintf(o,"set out 'anim-%s.gif'\n", vers_id);
  fprintf(o,"\n");
  fprintf(o,"call 'anim-frames-%s.gnu'\n", vers_id);
  fclose(o);

  make_gnu_frames();

}

// ##################################################################################################
// function that ortonormaliza the basis for the calculation of the Lyapunov exponent
void granschmit (double *znorm, double *y) {
  int         j, k, l;
  double      gsk3[NN];

  znorm[0] = 0.e0;                               // normaliza o primeiro vetor
  for (j = 1; j <= NN; j++)
    znorm[0] += pow (y[NN * j], 2);

  znorm[0] = sqrt (znorm[0]);
  for (j = 1; j <= NN; j++)
    y[NN * j] = y[NN * j] / znorm[0];

  for (j = 2; j <= NN; j++) {
    for (k = 1; k <= j - 1; k++) {
      gsk3[k - 1] = 0.e0;
      for (l = 1; l <= NN; l++) {
        gsk3[k - 1] = gsk3[k - 1] + y[NN * l + j - 1] * y[NN * l + k - 1];
      }
    }

    for (k = 1; k <= NN; k++) {                // constroi um novo vetor
      for (l = 0; l < j - 1; l++) {
        y[NN * k + j - 1] = y[NN * k + j - 1] - gsk3[l] * y[NN * k + l];
      }
    }

    znorm[j - 1] = 0.e0;                         // calcula os vetores normais
    for (k = 1; k <= NN; k++) {
      znorm[j - 1] = znorm[j - 1] + pow (y[NN * k + j - 1], 2);
    }

    znorm[j - 1] = sqrt (znorm[j - 1]);
    for (k = 1; k <= NN; k++) {                // normaliza o novo vetor
      y[NN * k + j - 1] = y[NN * k + j - 1] / znorm[j - 1];
    }
  }
}                                                // end for function granschmit (double *znorm, double *y)
