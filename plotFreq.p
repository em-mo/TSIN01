# Gnuplot script file for plotting data in file "force.dat"
# This file is called   force.p
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set autoscale
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Backlog of the system"
set xlabel "Number of backlogged nodes"
set ylabel "Probability"
set term pngcairo
set output "graphs/freq.png"
#set key 0.01,100
p "freq.txt" u 1:2 t '' w boxes