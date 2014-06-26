reset
intercept = -27.6383
multiplier= 5.4
#intercept = -24.1631 +.17
#multiplier= 9

set termoption dashed
set style line 1 lt 1 lc 1 lw 2
set style line 2 lt 3 lc 3 lw 2 pt 3
set multiplot layout 2,2;

set xlabel "Tilt Angle (degrees)"
set ylabel "Energy (J/m^2)"
set key box
set key width 3

set title "100 Tilt Axis"
#set output "BCC_100.png";
set xrange [0:90]    
set yrange [0:2]
plot "100.dat" using (90-$1):(multiplier*($2-intercept)) with lines ls 1 title "WIELD", "Shibuta_BCC_100.csv" with linespoints ls 2 title "MD"

set title "110 Tilt Axis"
#set output "BCC_110.png"
set xrange [0:180]
set yrange [-0.5:2]
plot "110.dat" using (180-$1):(multiplier*($2-intercept)) with lines ls 1 title "WIELD", "Shibuta_BCC_110.csv" with linespoints ls 2 title "MD"

set title "111 Tilt Axis"
#set output "BCC_111.png"
set xrange [0:60]
set yrange [0:2]
plot "111.dat" using 1:(multiplier*($2-intercept)) with lines ls 1 title "WIELD", "Shibuta_BCC_111.csv" with linespoints ls 2 title "MD"

set title "112 Tilt Axis"
#set output "BCC_112.png"
set xrange [0:105] 
plot "112.dat" using 1:(multiplier*($2-intercept)) with lines ls 1 title "WIELD", "Shibuta_BCC_112.csv" with linespoints ls 2 title "MD"

unset multiplot
#unset output
