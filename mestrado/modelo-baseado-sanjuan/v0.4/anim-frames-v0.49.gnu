# ************************************************************************
#  FERNANDA JAIARA DELLAJUSTINA, E-MAIL: fernandadellajustina@gmail.com 
#  UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL 
#
#  GnuPlot script | 27/10/2016 
#
# ************************************************************************

s = sprintf('{/:Bold=18 tx0=%6.2f epst=%6.2f phiMax = %6.2f}', tx0, epst, dphi*frame) 
print frame
set multiplot title s font ',14'
#*********************************
set xtics 100 
set ytics 0.2 
set origin 0.0,0.0 
set size 0.48,0.48 
set ylabel 'z' rotate by 0 
plot [0:400][0:1] 'bts-v0.49.dat' i frame u 1:4 w l lw 2 lc -1 
#********************************* 
set origin 0.0,0.5 
set size 0.48,0.48 
unset xlabel 
set ylabel 'x' rotate by 0 
plot [0:400][-0.1:1.1] 'bts-v0.49.dat' i frame u 1:2 w l lw 2 lc -1 
#********************************* 
set origin 0.5,0.5 
set size 0.48,0.48 
set xlabel 't' 
set ylabel 'y' rotate by 0 
plot [0:400][-0.1:1.1] 'bts-v0.49.dat' i frame u 1:3 w l lw 2 lc -1 
#********************************* 
set origin 0.5,0.0 
set size 0.48,0.48 
set xtics 100 
set ytics 20 
set xlabel 't' 
set ylabel 'q' rotate by 0 
plot [][0:70] 'bts-v0.49.dat' i frame u 1:5 w l lw 2 lc -1 
# Small plot  ******************** 
set origin 0.67,0.27 
set size 0.3,0.20 
set ytics 10 
set xlabel 't' 
set ylabel 'phi' rotate by 0 
plot [0:400][0:21] 'bts-v0.49.dat' i frame u 1:6 w l lw 2 lc -1 
unset multiplot
frame = frame + 1 

if(frame<frames) reread 
