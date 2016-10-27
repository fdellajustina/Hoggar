# ************************************************************************
#  FERNANDA J. DELLAJUSTINA | EMAIL: fernandadellajustina@gmail.com
#      UFPR, DEPARTAMENTO DE FÍSICA, CURITIBA-PR, BRASIL
#
#  GnuPlot script | 29-07-2016 14:11:12
#
# ************************************************************************
unset key
set tics out
set size 1,0.5
#set xtics 500

set term png size 1200,1000 crop
#set term postscript portrait enhanced color "Times-Roman" 12

set out "bts-x-v0.48.png"
#set out "bts-x5.eps"
set xlabel "t"
set ylabel "x" rotate by 0
plot "bts-v0.48.dat" i 0 u 1:2 w l

set out "bts-y-v0.48.png"
#set out "bts-y5.eps"
set xlabel "t"
set ylabel "y" rotate by 0
plot [][] "bts-v0.48.dat" i 0 u 1:3 w l

set out "bts-z-v0.48.png"
#set out "bts-z5.eps"
set xlabel "t"
set ylabel "z" rotate by 0
plot "bts-v0.48.dat" i 0 u 1:4 w l

set out "bts-q-v0.48.png"
#set out "bts-q5.eps"
set xlabel "t"
set ylabel "q" rotate by 0
plot [][] "bts-v0.48.dat" i 0 u 1:5 w l

set out "bts-phi-v0.48.png"
#set out "bts-q5.eps"
set xlabel "t"
set ylabel "phi" rotate by 0
plot [:200][] "bts-v0.48.dat" i 0 u 1:6 w l

#set term postscript portrait enhanced color "Times-Roman" 04
set title "x_0 = 0.3,y_0 = 4.0, z_0 = 0.8, q_0 = 0, a_{14} = 10^{-1}, a_{22} = 10^{-2}, a_{32} = 10^{-10}, d_4 = 0.5 e \phi = 5"
set size 0.32,0.16
set view 110,45,1
set ticslevel 0.0
set xtics 0.5
set ytics 0.5
set out "bts-real-space-v0.48.png"
#set out "bts-real-space5.eps"
set xlabel "x"
set ylabel "y"
set zlabel "z"
splot [][:1.2][] "bts-v0.48.dat" i 0 u 2:3:4 w l#p pt 7 ps 0.3
