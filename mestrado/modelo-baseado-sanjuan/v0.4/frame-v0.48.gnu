# ************************************************************************
#  FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
#      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL
#
#  GnuPlot script | 26-10-2016 14:11:12
#
# ************************************************************************
s = sprintf("frame=%d", frame)
print s

set multiplot layout 2,2 columnsfirst title "{/:Bold=15 V0.48 Melhoramento da aplicação de phi}" \
              margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_GAP

#set format y "%.1f"
#set key box opaque
set ylabel "x" rotate by 0
plot [0:400][-0.1:1.1] "bts-v0.48.dat" i frame u 1:2 w l lw 2 lc -1

#*********************************
set xlabel "t"
set ylabel "y" rotate by 0
plot [0:400][-0.1:1.1] "bts-v0.48.dat" i frame u 1:3 w l lw 2 lc -1

#*********************************
unset xlabel
set ylabel "z" rotate by 0
plot [0:400][0:1] "bts-v0.48.dat" i frame u 1:4 w l lw 2 lc -1

#*********************************
set xlabel "t"
set ylabel "q" rotate by 0
plot [0:400][0:300] "bts-v0.48.dat" i frame u 1:5 w l lw 2 lc -1

#*********************************
set origin 0.9,0.9
set size 0.1,0.1
set xlabel "t"
set ylabel "phi" rotate by 0
plot [0:400][0:300] "bts-v0.48.dat" i frame u 1:6 w l lw 2 lc -1

frame = frame + 1

unset multiplot

if(frame<frames) reread
