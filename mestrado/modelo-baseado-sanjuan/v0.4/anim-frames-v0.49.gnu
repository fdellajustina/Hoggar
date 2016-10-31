# ************************************************************************
#  FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com
#  UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL
#
#  GnuPlot script | 27/10/2016
#
# ************************************************************************

s = sprintf('{/:Bold=18 tx0=%6.2f epst=%6.2f phiMax = %6.2f td2 = %6.2f}', tx0, epst, dphi*frame, dtd2*frame)
print frame
set multiplot title s font ',14'

#*********************************
set xtics 100
set ytics 0.2
set origin 0.35,0.0
set size 0.65,0.3
set ylabel 'z' rotate by 0
plot [0:400][0:1.2] 'bts-v0.49.dat' i frame u 1:4 w l lw 2 lc -1

#*********************************
set origin 0.35,0.32
set size 0.65,0.3
unset xlabel
set ylabel 'x' rotate by 0
plot [0:400][-0.1:1.1] 'bts-v0.49.dat' i frame u 1:2 w l lw 2 lc -1

#*********************************
set origin 0.35,0.62
set size 0.65,0.3
set xlabel 't'
set ylabel 'y' rotate by 0
plot [0:400][-0.1:1.1] 'bts-v0.49.dat' i frame u 1:3 w l lw 2 lc -1

#*********************************
set origin 0.0,0.1
set size 0.35,0.3
set xtics 100
set ytics 20
set xlabel 't'
set ylabel 'q' rotate by 0
plot [0:400][0:70] 'bts-v0.49.dat' i frame u 1:5 w l lw 2 lc -1
# Small plot  ********************
set origin 0.0,0.6
set size 0.35,0.3
set ytics 10
set xlabel 't'
set ylabel 'phi' rotate by 0
plot [0:400][0:  30.0] 'bts-v0.49.dat' i frame u 1:6 w l lw 2 lc -1
unset multiplot
frame = frame + 1

if(frame<frames) reread
