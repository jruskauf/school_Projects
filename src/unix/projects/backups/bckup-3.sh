#include /bin/bash

rm ~/.mtpaint 2>/dev/null

mtpaint &

xte 'mousemove 50 20'
sleep 1
xte 'mousedown 1'
xte 'mousemove 300 300'
xte 'mouseup 1'
xte 'mousemove 40 60'
xte 'mouseclick 1'
xte 'mousermove 0 180'
xte 'mouseclick 1'
xte 'mousemove 300 300'
xte 'mousedown 1'
xte 'mousemove 150 150'
xte 'mouseup 1'

xte 'mousemove 20 110'
xte 'mouseclick 1'
#xte 'mousemove 410 80'
#xte 'mouseclick 1'
#xte 'mousemove 380 230'
#xte 'mouseclick 1'

for angle in {0..90}
do
	if [ $angle -lt 10 ]
	then
		check="1"
	elif [ $angle -lt 100 ]
	then	
		check="2"
	else 
		check="3"
	fi

	if [ `echo $angle | cut -b $check` = 0 ]
	then
		color=215	
	elif [ `echo $angle | cut -b $check` = 1 ]
	then
		color=230
	elif [ `echo $angle | cut -b $check` = 2 ]
	then
		color=248
	elif [ `echo $angle | cut -b $check` = 3 ]
	then
		color=282
	elif [ `echo $angle | cut -b $check` = 4 ]
	then
		color=295
	elif [ `echo $angle | cut -b $check` = 5 ]
	then
		color=315
	elif [ `echo $angle | cut -b $check` = 6 ]
	then
		color=215
	elif [ `echo $angle | cut -b $check` = 7 ]
	then
		color=248
	elif [ `echo $angle | cut -b $check` = 8 ]
	then
		color=295
	elif [ `echo $angle | cut -b $check` = 9 ]
	then
		color=315
	fi

	xte "mousemove 45 $color"
	xte 'mouseclick 1'
	xte 'mousemove 570 685'
	xte 'mousedown 1'
	radians=`echo "scale=4; $angle * 0.0174532925" | bc`
	x=`echo "scale=4; (200 * c($angle))" | bc -l | cut -d "." -f1`
	y=`echo "scale=4; (200 * s($radians))" | bc -l`
	
	check="-"	
	
	if [ "$x" == "$check" ] || [ -z $x ]
	then
		x=0
	elif [ $x -lt 1 ] && [ $x -gt 1 ]
       	then
		x=1
	fi

	xte "mousermove 0 ${y}"
	xte "mousermove ${x} 0"
	xte 'mousemove 570 685'
	xte "mousermove 0 ${y}"
	let x=$x*-1
	xte "mousermove ${x}"
	xte 'mousemove 570 685'
	xte "mousermove 0 -${y}"	
	xte "mousermove ${x} 0"
	xte 'mousemove 570 685'
	xte "mousermove 0 -${y}"
	let x=$x*-1
	xte "mousermove ${x} 0"
	xte 'mousemove 570 685'

	xte 'mouseup 1'

	echo "X: $x"
	echo "Y: $y"
	echo " "
done
