#set label 1 '(a)' at 0.9,0.06 front
#set label 2 '1' at 0.23,0.60 font "Symbol,8" front
#set label 3 '2' at 0.23,0.65 font "Symbol,8" front
#set label 4 '3' at 0.23,0.53 font "Symbol,8" front
#set label 5 '4' at 0.23,0.70 font "Symbol,8" front
#set label 6 '5' at 0.23,0.49 font "Symbol,8" front
#set label 7 '6' at 0.23,0.45 font "Symbol,8" front
#set label 8 '7' at 0.23,0.41 font "Symbol,8" front
#set label 9 '8' at 0.01,0.33 font "Symbol,8" front
#set label 10 '9' at 0.08,0.33 font "Symbol,8" front
set view map
set style data pm3d
set style function pm3d
set size square
unset key
#set grid
#set xtics 0.1
#set ytics 0.1
set xlabel '{/Symbol G}'
set ylabel '{/Symbol D}' rotate by 0
#set title "teste"
set tics out
#ZOOM1
set xrange [ 0.0 : 1.0 ] noreverse nowriteback
set yrange [ 0.0 : 1.0 ] noreverse nowriteback
set pm3d at b
#
set palette defined ( -0.03 "white", 0.0 "black", 0.025 "yellow", 0.05 "red")
#set palette defined ( -0.02 "white", 0.0 "black", 0.005 "yellow", 0.01 "red")
#
#set palette
set term post eps enhanced color "Symbol-Times-Italic" 20
set out 'zoom1.eps'
splot "zoom1bcm.dat" using 1:2:3 with image, "reta.dat" with l 
#with p pt 7 lt -1 lw 1
