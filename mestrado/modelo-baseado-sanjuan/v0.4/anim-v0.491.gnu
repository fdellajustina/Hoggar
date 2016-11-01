# ************************************************************************ 
#  FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com 
#  UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL 
##  GnuPlot script | 31/10/2016 
## ************************************************************************
unset key

set tics out
set size 2,1
set grid

tx0        =  100.000
epst       =    0.010
phi_max    =   20.000
phi_min    =   10.000
td2_max    =   20.000
td2_min    =   10.000

x_max    =    1.000
x_min    =    0.000
y_max    =    1.000
y_min    =    0.000
z_max    =    1.000
z_min    =    0.000

frames     = 50
frame      = 0
dphi       = (phi_max-phi_min)/frames 
dtd2       = (td2_max-td2_min)/frames 

dx         = (x_max-x_min)/frames 
dy         = (y_max-y_min)/frames 
dz         = (z_max-z_min)/frames 

set term gif animate delay 40 opt size 1500,1200
set out 'anim-v0.491.gif'

call 'anim-frames-v0.491.gnu'
