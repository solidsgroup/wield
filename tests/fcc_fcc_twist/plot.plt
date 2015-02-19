set multiplot layout 2,3 rowsfirst
A = 1400
unset key
set yrange [0:1300]
set title "100_100"
plot "100_100.out" using 1:(A*$2) with lines, "Wolf/100_100.dat" with linespoints 
set title "111_111"
plot "111_111.out" using 1:(A*$2) with lines, "Wolf/111_111.dat" with linespoints
set title "114_011"
plot "114_011.out" using 1:(A*$2) with lines, "Wolf/114_011.dat" with linespoints
set title "221_001"
plot "221_001.out" using 1:(A*$2) with lines, "Wolf/221_001.dat" with linespoints
set title "115_111"
plot "115_111.out" using 1:(A*$2) with lines, "Wolf/115_111.dat" with linespoints
set title "557_113"
plot "557_113.out" using 1:(A*$2) with lines, "Wolf/557_113.dat" with linespoints



