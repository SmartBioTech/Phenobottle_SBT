#!/usr/bin/gnuplot
#
# Plotting coordinate points

reset

# wxt
set terminal wxt size 2160,2160 enhanced font 'Verdana,10' persist
# png
#set output 'fluorescence.png'

# color definitions
set border linewidth 1.5
set style line 1 lc rgb '#0060ad' pt 7 ps 1.5 lt 1 lw 2 # --- blue

unset key

# Axes
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror out scale 0.75

# Grid
set style line 12 lc rgb'#808080' lt 0 lw 1
set grid back ls 12

set logscale x

set autoscale xmax
set xrange [0:]

set autoscale y

set xlabel "Time[ms]"
set ylabel "Relative intensity"

set samples 1000
plot 'fluorescence.data' pt 7 ps 0.3, 'fluorescence.data' smooth sbezier lw 3
