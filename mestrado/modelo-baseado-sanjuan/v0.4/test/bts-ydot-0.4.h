// ************************************************************
// função com as derivadas de primeira ordem a ser integradas
// ydot[0] = dx/dt ---> y[0] = x(t)
// ydot[1] = dy/dt ---> y[1] = y(t)
// ydot[2] = dz/dt ---> y[2] = z(t)
// ************************************************************
// Sistema normalizado de equações
void derivs (int *nn, double *t, double *y, double *ydot) {
 ydot[0] = y[0]*(1.0e0-y[0]) - a12*y[0]*y[1] - a13*y[0]*y[2] - a14*y[0]*y[3];
 ydot[1] = r2*y[1]*(1.0e0-y[1]) - a21*y[0]*y[1] - a22*y[1]*y[3];
 ydot[2] = r3*y[2]*y[0]/(y[0] + k3) - a31*y[2]*y[0] - d3*y[2] - a32*y[2]*y[3];
 ydot[3] = phi - d4*y[3];
}  // end for function derivs(int *nn, double *t, double *y, double *ydot)
