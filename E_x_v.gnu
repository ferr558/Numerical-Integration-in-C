plot "Eulero.dat" index 0 using 2:3 w l t "dt=0.01"
replot "Eulero.dat" index 1 using 2:3 w l t "dt=0.02"
replot "Eulero.dat" index 2 using 2:3 w l t "dt=0.03"
replot "Eulero.dat" index 3 using 2:3 w l t "dt=0.04"
set grid
set autoscale
set key left
set xlabel 'x'
set ylabel 'v'
set title 'Euler Phase Space'
replot
