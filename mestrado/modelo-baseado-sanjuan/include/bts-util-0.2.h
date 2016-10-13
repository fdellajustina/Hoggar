// ess-util-0.0.h - Modified by FJD in 29/07/2016 13:49:53 - Implementação de bibliotecas.

void make_header (FILE *o);
// #############################################################################
// inicializão do sistema
void init (double *y, double *lyap_sum) {
  int i;
  // Escolha da inicialização
  switch (tipo) {
  case 0:                                                 // Saddle with two positive eigenvalues
    y[0] = 1.5e0;                                        // x
    y[1] = 4.0e0;                                        // y
    y[2] = 0.8e0;                                        // z
    y[3] = 0.0e0;
    break;
  case 1:                                                 // Saddle with two negative eigenvalues (only normal cells)
    y[0] = 0.208333e0;                                        // x
    y[1] = 6.41667e0;                                        // y
    y[2] = 0.2e0;                                        // z
    y[3] = 0.0e0;
    break;
  }                                                       // end switch

  for (i = N; i < NN; i++)
    y[i] = 0.e0;                                          // zera o bloco da base vetorial

  for (i = 0; i < N; i++) {
    y[N * (i + 1) + i] = 1.e0;                            // inicialização dos vetores da base
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
  fprintf (o, "#        N  = %20d\n", N);
  fprintf (o, "#        NN = %20d\n", NN);
  fprintf (o, "#\n");
  fprintf (o, "#      TIPO = %20d\n", tipo);
  fprintf (o, "#\n");
  fprintf (o, "#       a12 = %10.5e\n", a12);
  fprintf (o, "#       a13 = %10.5e\n", a13);
  fprintf (o, "#       a14 = %10.5e\n", a14);
  fprintf (o, "#       a21 = %10.5e\n", a21);
  fprintf (o, "#       a22 = %10.5e\n", a22);
  fprintf (o, "#       a31 = %10.5e\n", a31);
  fprintf (o, "#       a32 = %10.5e\n", a32);
  fprintf (o, "#        r2 = %10.5e\n", r2);
  fprintf (o, "#        r3 = %10.5e\n", r3);
  fprintf (o, "#        d3 = %10.5e\n", d3);
  fprintf (o, "#        d4 = %10.5e\n", d4);
  fprintf (o, "#        k3 = %10.5e\n", k3);
  fprintf (o, "#\n");
  fprintf (o, "#        nx = %5d\n", nx);
  fprintf (o, "#        ny = %5d\n", ny);
  fprintf (o, "#      xmin = %10.5e\n", ymin);
  fprintf (o, "#      xmax = %10.5e\n", xmax);
  fprintf (o, "#      ymin = %10.5e\n", ymin);
  fprintf (o, "#      ymax = %10.5e\n", ymax);
  fprintf (o, "#\n");
  fprintf (o, "#      tmax = %10.5e\n", tmax);
  fprintf (o, "#     trans = %10.5e\n", trans);
  fprintf (o, "#         h = %10.5e\n", h);
  fprintf (o, "#       tol = %10.5e\n", tol);
  fprintf (o, "#\n");
}                                                      // end for function make_header(FILE *o)

// ##################################################################################################
// function that ortonormaliza the basis for the calculation of the Lyapunov exponent
void granschmit (double *znorm, double *y) {
  int         j, k, l;
  double      gsk3[N];

  znorm[0] = 0.e0;                               // normaliza o primeiro vetor
  for (j = 1; j <= N; j++)
    znorm[0] += pow (y[N * j], 2);

  znorm[0] = sqrt (znorm[0]);
  for (j = 1; j <= N; j++)
    y[N * j] = y[N * j] / znorm[0];

  for (j = 2; j <= N; j++) {
    for (k = 1; k <= j - 1; k++) {
      gsk3[k - 1] = 0.e0;
      for (l = 1; l <= N; l++) {
        gsk3[k - 1] = gsk3[k - 1] + y[N * l + j - 1] * y[N * l + k - 1];
      }
    }

    for (k = 1; k <= N; k++) {                // constroi um novo vetor
      for (l = 0; l < j - 1; l++) {
        y[N * k + j - 1] = y[N * k + j - 1] - gsk3[l] * y[N * k + l];
      }
    }

    znorm[j - 1] = 0.e0;                         // calcula os vetores normais
    for (k = 1; k <= N; k++) {
      znorm[j - 1] = znorm[j - 1] + pow (y[N * k + j - 1], 2);
    }

    znorm[j - 1] = sqrt (znorm[j - 1]);
    for (k = 1; k <= N; k++) {                // normaliza o novo vetor
      y[N * k + j - 1] = y[N * k + j - 1] / znorm[j - 1];
    }
  }
}                                                // end for function granschmit (double *znorm, double *y)

// DEQUANT
double dequant (int i, int min, int max, double xmin, double xmax) {
  return (xmin + (xmax - xmin) * (double) (i - min) / (double) (max - min));
}
