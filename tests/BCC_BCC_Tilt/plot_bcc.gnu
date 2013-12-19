set termoption dashed
set style line 1 lt 1 lc 0 lw 2 
set style line 2 lt 3 lc 0 lw 2 pt 3
set multiplot layout 2,2;

set xlabel "Tilt Angle (degrees)"
set ylabel "Energy (J/m^2)"
set key box


set title "100 Tilt Axis"
set key ins vert bot
#set output "BCC_100.png";
set xrange [0:90]    
plot "bcc_bcc_tilt_100_cauchy.dat" using (90-$1):2  with lines ls 1 title "Theory", "Shibuta_BCC_100.csv" using (90-$1):2 with linespoints ls 2 title "MD"

set title "110 Tilt Axis"
#set output "BCC_110.png"
set xrange [0:180]
plot "bcc_bcc_tilt_110_cauchy.dat" using (180-$1):2 with lines ls 1 title "Theory", "Shibuta_BCC_110.csv" with linespoints ls 2 title "MD"

set title "111 Tilt Axis"
#set output "BCC_111.png"
set xrange [0:60]
plot "bcc_bcc_tilt_111_cauchy.dat" with lines ls 1 title "Theory", "Shibuta_BCC_111.csv" with linespoints ls 2 title "MD"

set title "112 Tilt Axis"
#set output "BCC_112.png"
set yrange [0:1.8]
set xrange [0:105]
plot "bcc_bcc_tilt_112_cauchy.dat" with lines ls 1 title "Theory", "Shibuta_BCC_112.csv" with linespoints ls 2 title "MD"

unset multiplot
#unset output