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
  fprintf (o, "#      tmax = %10.5e\n", tmax);
  fprintf (o, "#         h = %10.5e\n", h);
  fprintf (o, "#       tol = %10.5e\n", tol);
  fprintf (o, "#\n");
}                                                      // end for function make_header(FILE *o)

// DEQUANT
double dequant (int i, int min, int max, double xmin, double xmax) {
  return (xmin + (xmax - xmin) * (double) (i - min) / (double) (max - min));
}
