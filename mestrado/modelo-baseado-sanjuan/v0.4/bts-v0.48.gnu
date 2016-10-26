# ************************************************************************
#  FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
#      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL
#
#  GnuPlot script | 26-10-2016 14:11:12
#
# ************************************************************************
unset key
set tics out

set term gif animate delay 20
set out "bts-v0.48.gif"

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.09

set multiplot layout 2,2 columnsfirst title "{/:Bold=15 V0.48 Melhoramento da aplicação de phi}" \
              margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_GAP

na=5
do for[frame=0:na]{
    #*********************************
    #set format y "%.1f"
    #set key box opaque
    set ylabel "x" rotate by 0
    plot "bts-v0.48.dat" i frame u 1:2 w l

    #*********************************
    set xlabel "t"
    set ylabel "y" rotate by 0
    plot [][] "bts-v0.48.dat" i frame u 1:3 w l

    #*********************************
    unset xlabel
    set ylabel "z" rotate by 0
    plot "bts-v0.48.dat" i frame u 1:4 w l

    #*********************************
    set xlabel "t"
    set ylabel "q" rotate by 0
    plot [][] "bts-v0.48.dat" i frame u 1:5 w l

}

unset multiplot
