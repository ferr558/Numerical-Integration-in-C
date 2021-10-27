This script includes numerical integration algorithms such as: Self-sufficient Verlet, Euler, Euler-Cromer, Leap-Frog and Central Point for an harmonic oscillator.

To execute this script it is necessary to have a file "passi.dat" containing the integration steps and a file "param.dat" that cointain the integration parameters in the following order: elastic constant, mass, initial position, initial speed and maximum integration time.

The operation of the program is briefly explained in the program itself, plus steps.dat and param.dat will be loaded to show how they must be organized.

To execute the "Automatic Plot" function it is necessary to have installed the gnuplot program, you will be provided with the code that will be used within gnuplot with the name "Fit.gnu".

You can see how at each integration I print the last 4 lines for each integration step on a different file. This is used to analyze the energy error related to the variation of the integration step through the "Fit.gnu" script that will be provided to you.

E_x_v.gnu, EC_x_v.gnu, V_x_v.gnu, LF_x_v.gnu, PC_x_v.gnu are files for plotting phase space of every algorythm.

This program works on linux systems, its functioning on windows is not guaranteed.
