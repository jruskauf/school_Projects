
set title 'jruskauf spring2018/unix'
set xlabel 'x'
set ylabel 'y'
set terminal png size 600,400

set grid
set key below center horizontal noreverse enhanced autotitle box dashtype solid
set tics out nomirror
set border 3 front linetype black linewidth 1.0 dashtype solid

set yrange [-10:110]
set ytic -10, 10, 110
set mytics 1

set style line 1 linewidth 2
set style line 2 linewidth 2
set style line 3 linewidth 2
set style line 4 linewidth 2
set style line 5 linewidth 5

plot 'gtf0.data' using 2:xticlabels(1) with lines linestyle 1 title 'lowscore',	'' using 3:xticlabels(1) with lines linestyle 2 title 'avgscore',	'' using 4:xticlabels(1) with lines linestyle 3 title 'median',	'' using 5:xticlabels(1) with lines linestyle 4 title 'hiscore',	'' using 6:xticlabels(1) with lines linestyle 5 title 'myscore'

