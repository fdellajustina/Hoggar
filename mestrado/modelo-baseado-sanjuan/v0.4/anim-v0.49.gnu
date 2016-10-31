# ************************************************************************ 
#  FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com 
#  UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL 
##  GnuPlot script | 27/10/2016 
## ************************************************************************
unset key

set tics out
set size 2,1
set grid

tx0        = 100
epst       = 0.01
phi_max    = 30
phi_min    = 20
td2_max    = 20
td2_min    = 0

frames     = 1
frame      = 0
dphi       = (phi_max-phi_min)/frames 
dtd2       = (td2_max-td2_min)/frames 

set term gif animate delay 40 opt size 1500,1200
set out 'anim-v0.49.gif'

call 'anim-frames-v0.49.gnu'
