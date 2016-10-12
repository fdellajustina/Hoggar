// ************************************************************
// função com as derivadas de primeira ordem a ser integradas
// ydot[0] = dx/dt ---> y[0] = x(t)
// ydot[1] = dy/dt ---> y[1] = y(t)
// ydot[2] = dz/dt ---> y[2] = z(t)
// ************************************************************

// matris jacobiana do sistema de Lorenz
void jacob (double *y, double J[N][N]) {
  // Atualiza a matriz jacobiana.
  J[0][0] = 1.0e0 - 2.0e0*y[0] - a12*y[1] - a13*y[2] - a14*y[3];
  J[1][0] = -a12*y[0];
  J[2][0] = -a13*y[0];
  J[3][0] = -a14*y[0];

  J[0][1] = -a21*y[1];
  J[1][1] = r2*(1.0e0-2.0e0*y[1]) - a21*y[0] - a22*y[3];
  J[2][1] = 0.0e0;
  J[3][1] = -a22*y[1];

  J[0][2] = (r3*y[2]/(y[0]+k3))*(1.0e0-y[0]/(y[0]+k3)) - a31*y[2];
  J[1][2] = 0.0e0;
  J[2][2] = r3*y[0]/(y[0]+k3) - a31*y[0] - d3 - a32*y[3];
  J[3][2] = -a32*y[2];

  J[0][3] = 0.0e0;
  J[1][3] = 0.0e0;
  J[2][3] = 0.0e0;
  J[3][3] = -d4;
}

// multiplicação de J pela base;
void multi_mat (double *y, double *ydot, double J[N][N]) {
  int i, j, k, A, D;

  jacob (y, J);                                                    // atualização da jacobiana

  //  multiplica as matrizes
  for (j = 0; j < N; j++) {
    for (i = 0; i < N; i++) {
      A = (i + 1) * N + j;                                         // ajusta elemento de vdot
      ydot[A] = 0.e0;                                              // zera vdot p/ somatorio
      for (k = 0; k < N; k++) {
        D = (k + 1) * N + j;                                       //  ajusta elemento de v
        ydot[A] += J[k][i] * y[D];
      }
    }
  }
}

// Sistema normalizado de equações
void derivs (int *nn, double *t, double *y, double *ydot) {
 ydot[0] = y[0]*(1.0e0-y[0]) - a12*y[0]*y[1] - a13*y[0]*y[2] - a14*y[0]*y[3];
 ydot[1] = r2*y[1]*(1.0e0-y[1]) - a21*y[0]*y[1] - a22*y[1]*y[3];
 ydot[2] = r3*y[2]*y[0]/(y[0] + k3) - a31*y[2]*y[0] - d3*y[2] - a32*y[2]*y[3];
 ydot[3] = phi - d4*y[3];

 // Atualiza a jacobinana e faz o loop como o produto de 2 matrizes
 multi_mat(y, ydot, J);

}  // end for function derivs(int *nn, double *t, double *y, double *ydot)
