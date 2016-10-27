# ************************************************************************ 
#  FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com 
#  UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL 
##  GnuPlot script | 27/10/2016 
## ************************************************************************
unset key

set tics out
set size sq
set grid

tx0        = 100
epst       = 0.01
phi_max    = 12
phi_min    = 0

frames     = 200
frame      = 0
dphi       = (phi_max-phi_min)/frames 

set term gif animate delay 40 opt size 1200,1200
set out 'anim-v0.49.gif'

call 'anim-frames-v0.49.gnu'
