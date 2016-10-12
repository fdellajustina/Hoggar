// ess-util-0.0.h - Modified by FJD in 29/07/2016 13:49:53 - Implementação de bibliotecas.

void make_header (FILE *o);
// #############################################################################
// inicializão do sistema
void init (double *y) {
/*
Solução de pontos fixos gerados pelo Mathematica
{x -> -0.208333, y -> 1.41667, z -> 0., q -> 50.} ok (Negativas...!!! ALGO ERRADO...)
{x -> 0., y -> 0.583333, z -> 0., q -> 50.}, ok
{x -> 0.164091 - 0.369744 I, y -> -0.0730303 + 1.47898 I, z -> 0.310354 - 0.30812 I, q -> 50.}
{x -> 0.164091 - 0.369744 I, y -> 0., z -> 0.279924 + 0.30812 I, q -> 50.}
{x -> 0.164091 + 0.369744 I, y -> -0.0730303 - 1.47898 I, z -> 0.310354 + 0.30812 I, q -> 50.}
{x -> 0.164091 + 0.369744 I, y -> 0., z -> 0.279924 - 0.30812 I, q -> 50.}
{x -> 0.5, y -> 0., z -> 0., q -> 50.}
{x -> 0., y -> 0., z -> 0., q -> 50.}
*/

  // Escolha da inicialização
  switch (tipo) {
  case 0:                                                 // Saddle with two positive eigenvalues
    y[0] = 0.0e0;                                         // x
    y[1] = 0.0e0;                                         // y
    y[2] = 0.0e0;                                         // z
    y[3] = 50.0e0;
    break;
  case 1:                                                 // Saddle with two negative eigenvalues (only normal cells)
    y[0] = 0.0e0;                                         // x
    y[1] = 1.0e0;                                         // y
    y[2] = 0.0e0;                                         // z
    y[3] = 50.0e0;
    break;
  case 2:                                                 // Stable with eigenvalues small (only tumor cells)
    y[0] = 1.0e0;                                         // x
    y[1] = 0.0e0;                                         // y
    y[2] = 0.0e0;                                         // z
    y[3] = 50.0e0;
    break;
  case 3:                                                 // Saddle with two stable and one unestable direction
    y[0] = 0.5e0;                                        // x
    y[1] = 0.0e0;                                         // y
    y[2] = 0.0e0;                                        // z
    y[3] = 50.0e0;
    break;
  case 4:                                                 // Spiral stable
    y[0] = 1.5e0;                                        // x
    y[1] = 4.0e0;                                        // y
    y[2] = 0.8e0;                                        // z
    y[3] = 0.0e0;
    break;
  case 5:                                                 // ??
    y[0] = 0.208333e0;                                        // x
    y[1] = 6.41667e0;                                        // y
    y[2] = 0.2e0;                                        // z
    y[3] = 0.0e0;
    break;
  }                                                       // end switch
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
  fprintf (o, "#      TIPO = %20d\n", tipo);
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
  fprintf (o, "#      tmax = %10.5e\n", tmax);
  fprintf (o, "#         h = %10.5e\n", h);
  fprintf (o, "#       tol = %10.5e\n", tol);
  fprintf (o, "#\n");
}                                                      // end for function make_header(FILE *o)
