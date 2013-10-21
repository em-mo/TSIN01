# Gnuplot script file for plotting data in file "force.dat"
# This file is called   force.p
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set autoscale
set xrange [0:1000]
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Arrivals and departures"
set xlabel "Slot"
set ylabel "Packets"
set term pngcairo
set output graphs/arrivals.png
#set key 0.01,100
p "output.txt" u 1:4 t 'Arrivals' w lines, "output.txt" u 1:5 t 'Departues' w lines