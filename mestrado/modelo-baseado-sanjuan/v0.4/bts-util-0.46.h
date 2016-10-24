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
  fprintf (o, "#   phi_min = %10.5e\n", phi_min);
  fprintf (o, "#   phi_max = %10.5e\n", phi_max);
  fprintf (o, "#   td2_min = %10.5e\n", td2_min);
  fprintf (o, "#   td2_max = %10.5e\n", td2_max);
  fprintf (o, "#\n");
  fprintf (o, "#       td1 = %10.5e\n", td1);
  fprintf (o, "#       td2 = %10.5e\n", td2);
  fprintf (o, "#       eps = %10.5e\n", eps);
  fprintf (o, "#      epst = %10.5e\n", epst);
  fprintf (o, "#      ntx0 = %d\n", ntx0);
  fprintf (o, "#   freqQui = %d\n", freqQui);
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

void apli_qui(double phi0, double t){
  double phi1;
  //if(td1 < 1.0e-5) phi = phi0;
  //else{
    //if(t1 < td1){
      //t1 += h;
      //phi = phi0;

      //if(fabs(t1 - td1) < eps){
        //t1 = 2.0e0*td1;
        //t2 = 0.0e0;
      //}
    //}
    //else{
      //t2 += h;
      //phi = 0.0e0;
      //if(fabs(t2 - td2) < eps){
         //t1 = 0.0e0;
         //dt1 = 0.0e0;
      //}
    //}
  //}


  if(td1 < 1.0e-5) phi = phi0;
  else{
    if(t1 < td1){
      t1 += h;
      if(dt1 < td1_3){
        phi=exp(Gamma*dt1);
        dt1+=h;
      }
      else{
        phi1 = phi;
        //printf("phi1= %4.1f\n", phi1);

        if((dt1 > td1_3) && (dt1 < 2.0e0*td1_3)){
          //phi = phi1;
          dt1+=h;
        }
        else{
          if((dt1 > 2.0e0*td1_3) && (dt1 < 3.0e0*td1_3)){
            phi=phi1exp(-Gamma*fabs(dt1-2.0e0*td1_3));
            dt1+=h;
          }
        }
      }

      if(fabs(t1 - td1) < eps){
        //t1 = 2.0e0*td1;
        t2 = 0.0e0;
      }
    }
    else{
      t2 += h;
      phi = 0.0e0;
      if(fabs(t2 - td2) < eps){
         t1 = 0.0e0;
         dt1 = 0.0e0;
      }
    }
  }

  //printf("t1= %4.1f t2= %4.1f dt1= %4.1f phi= %4.1f\n",t1, t2, dt1, phi);

}
