# Gnuplot script file for plotting data in file "force.dat"
# This file is called   force.p
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set autoscale
set xrange [0:0.36]
set yrange [0:60]
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Backlog of the system"
set xlabel "Slot"
set ylabel "Backlogged nodes"
set term pngcairo
set output "graphs/delays.png"
#set key 0.01,100
p "simulatedDelayOutput.txt" u 1:2 t 'Simulated' w points, "theoreticalDelayOutput.txt" u 1:2 t 'Theoretical' w lines