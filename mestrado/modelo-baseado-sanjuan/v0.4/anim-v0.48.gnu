# ************************************************************************
#  FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
#      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL
#
#  GnuPlot script | 26-10-2016 14:11:12
#
# ************************************************************************
unset key
set tics out

set term gif animate delay 60 opt size 1200,1200
set out "bts-v0.48.gif"

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.09

frames = 200
frame  = 0
dt=0.01
phi_max=12.0
phi_min=0.0
dphi=(phi_max-phi_min)/frames

call 'frame-v0.481.gnu'
