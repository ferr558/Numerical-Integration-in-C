plot "Verlet.dat"  index 0 using 2:3 w l t "dt=0.01"
replot "Verlet.dat"  index 1 using 2:3 w l t "dt=0.02"
replot "Verlet.dat" index 2 using 2:3 w l t "dt=0.03"
replot "Verlet.dat" index 3 using 2:3 w l t "dt=0.04"
set grid
set autoscale
set key left
set xlabel 'x'
set ylabel 'v'
set title 'Verlet Phase Space'
replot
