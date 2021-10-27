
plot "E.dat" using (log(abs($1))):(log(abs($6))) t "Euler data"
replot "EC.dat" using (log(abs($1))):(log(abs($6))) t "Euler Cromer data"
replot "PC.dat" using (log(abs($1))):(log(abs($6))) t "Mid Point data"
replot "LF.dat" using (log(abs($1))):(log(abs($6))) t "Leap Frog data"
replot "V.dat" using (log(abs($1))):(log(abs($6))) t "Verlet data"

set grid

q_E = 1
m_E = 1

q_EC = 1
m_EC = 1

q_PC = 1
m_PC = 1

q_LF = 1
m_LF = 1

q_V=1
m_V=1

f_E(x) = m_E * x + q_E
f_EC(x) = m_EC * x + q_EC
f_PC(x) = m_PC * x + q_PC
f_LF(x) = m_LF * x + q_LF
f_V(x) = m_V * x + q_V

set fit quiet
set fit logfile '/dev/null'

fit f_E(x) "E.dat" using (log(abs($1))):(log(abs($6)))  via q_E, m_E
fit f_EC(x) "EC.dat" using (log(abs($1))):(log(abs($6)))  via q_EC, m_EC
fit f_PC(x) "PC.dat" using (log(abs($1))):(log(abs($6)))  via q_PC, m_PC
fit f_LF(x) "LF.dat" using (log(abs($1))):(log(abs($6)))  via q_LF, m_LF
fit f_V(x) "V.dat" using (log(abs($1))):(log(abs($6)))  via q_V, m_V

set yrange [-20:-2]
set xrange [GPVAL_X_MIN:GPVAL_X_MAX]

set key bottom right

replot  (m_E * x + q_E) t 'Best Fit Euler'
replot  (m_EC * x + q_EC) t 'Best Fit Euler-Cromer'
replot  (m_PC * x + q_PC) t 'Best Fit Mid-Point'
replot  (m_LF * x + q_LF) t 'Best Fit Leap-Frog'
replot  (m_V * x + q_V) t 'Best Fit Verlet'



set xlabel "dt"
set ylabel "{/Symbol D}E/\E_0" enhance
set title "Renormalized error Vs dt for the various algorithms"

replot
