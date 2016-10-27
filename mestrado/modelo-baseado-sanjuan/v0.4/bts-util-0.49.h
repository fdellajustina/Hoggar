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
  fprintf (o, "#       tol = %10.5f\n", tol);
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

  fprintf(o,"s = sprintf('{/:Bold=18 tx0=%%6.2f epst=%%6.2f phiMax = %%6.2f}', tx0, epst, dphi*frame) \n");
  fprintf(o,"print frame\n");

  fprintf(o,"set multiplot title s font ',14'\n");

  fprintf(o,"#*********************************\n");
  fprintf(o,"set xtics 100 \n");
  fprintf(o,"set ytics 0.2 \n");
  fprintf(o,"set origin 0.0,0.0 \n");
  fprintf(o,"set size 0.48,0.48 \n");
  fprintf(o,"set ylabel 'z' rotate by 0 \n");
  fprintf(o,"plot [0:400][0:1] 'bts-%s.dat' i frame u 1:4 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"#********************************* \n");
  fprintf(o,"set origin 0.0,0.5 \n");
  fprintf(o,"set size 0.48,0.48 \n");
  fprintf(o,"unset xlabel \n");
  fprintf(o,"set ylabel 'x' rotate by 0 \n");
  fprintf(o,"plot [0:400][-0.1:1.1] 'bts-%s.dat' i frame u 1:2 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"#********************************* \n");
  fprintf(o,"set origin 0.5,0.5 \n");
  fprintf(o,"set size 0.48,0.48 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'y' rotate by 0 \n");
  fprintf(o,"plot [0:400][-0.1:1.1] 'bts-%s.dat' i frame u 1:3 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"#********************************* \n");
  fprintf(o,"set origin 0.5,0.0 \n");
  fprintf(o,"set size 0.48,0.48 \n");

  fprintf(o,"set xtics 100 \n");
  fprintf(o,"set ytics 20 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'q' rotate by 0 \n");
  fprintf(o,"plot [][0:70] 'bts-%s.dat' i frame u 1:5 w l lw 2 lc -1 \n", vers_id);

  fprintf(o,"# Small plot  ******************** \n");
  fprintf(o,"set origin 0.67,0.27 \n");
  fprintf(o,"set size 0.3,0.20 \n");
  fprintf(o,"set ytics 10 \n");
  fprintf(o,"set xlabel 't' \n");
  fprintf(o,"set ylabel 'phi' rotate by 0 \n");
  fprintf(o,"plot [0:400][0:21] 'bts-%s.dat' i frame u 1:6 w l lw 2 lc -1 \n", vers_id);

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
  fprintf(o,"set size sq\n");
  fprintf(o,"set grid\n");
  fprintf(o,"\n");
  fprintf(o,"tx0        = %g\n", tx0);
  fprintf(o,"epst       = %g\n", epst);
  fprintf(o,"phi_max    = %g\n", phi_max);
  fprintf(o,"phi_min    = %g\n", phi_min);
  fprintf(o,"\n");
  fprintf(o,"frames     = %d\n", nphi);
  fprintf(o,"frame      = 0\n");
  fprintf(o,"dphi       = (phi_max-phi_min)/frames \n");
  fprintf(o,"\n");
  fprintf(o,"set term gif animate delay 40 opt size 1200,1200\n");
  fprintf(o,"set out 'anim-%s.gif'\n", vers_id);
  fprintf(o,"\n");
  fprintf(o,"call 'anim-frames-%s.gnu'\n", vers_id);
  fclose(o);

  make_gnu_frames();

}
