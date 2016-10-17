set pm3d corners2color c1 map

unset key
set tics out
#set grid front lc -1
set xlabel "d4"
set ylabel "phi0"

###################################################################################
stat 'optimal-phid4.dat' u 3
min= STATS_min
max= STATS_max

z=-min/(max-min)

set cbrange [min:max]

#paleta gray-rainbow, z é o valor do zero mapeado no intervalo unitário
R(x)=(x<=0.625) ? 2.5-4.*x: ((x<=0.875) ? 4*x-2.5: 1.)
G(x)=1.-4.*(2*x-1.5)**2.
B(x)=4.*x*(1.-x)
map(x,xmin,xmax,a,b)=1.*a+1.*(b-a)*(x-xmin)/(xmax-xmin)

set palette mode RGB functions (gray < z ? 0.0 + gray/z/5: R(map(gray,z,1.,0.5,1.))),\
                               (gray < z ? 0.0 + gray/z/5: G(map(gray,z,1.,0.5,1.))),\
                               (gray < z ? 0.0 + gray/z/5: B(map(gray,z,1.,0.5,1.)))

###################################################################################

#set cbrange [0:16]
#set pal rgb 33,13,10

#set term post eps enhanced color "Symbol-Times-Italic" 20
#set term postscript portrait enhanced color "Symbol-Times-Italic" 20
#set out "optimal-q.eps"

set term png size 1200,1000
set out "optimal-phid4.png"

splot "optimal-phid4.dat" u 2:1:3
