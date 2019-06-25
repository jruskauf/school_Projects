#include /bin/bash

for angle in {0..90}
do
	if [ $angle -le 10 ]
	then
		xte 'mousemove 45 407'
		xte 'mouseclick 1'
	elif [ $angle -le 20 ]
	then
		xte 'mousemove 45 390'
		xte 'mouseclick 1'


	elif [ $angle -le 30 ]
	then
		xte 'mousemove 45 378'
		xte 'mouseclick 1'
	elif [ $angle -le 40 ]
	then
		xte 'mousemove 45 359'
		xte 'mouseclick 1'
	elif [ $angle -le 50 ]
	then
		xte 'mousemove 45 346'
		xte 'mouseclick 1'
	elif [ $angle -le 60 ]
	then
		xte 'mousemove 45 330'
		xte 'mouseclick 1'
	elif [ $angle -le 90 ]
	then
		xte 'mousemove 45 312'
		xte 'mouseclick 1'

	fi

	xte "mousemove 45 "
	xte 'mouseclick 1'
	xte 'mousemove 562 693'

	radians=`echo "scale=4; $angle * 0.0174532925" | bc`
	x=`echo "scale=4; (100 * c($radians))" | bc -l | cut -d "." -f1`
	y=`echo "scale=4; (100 * s($radians))" | bc -l`
	
	check="-"	
	
	if [ "$x" == "$check" ] || [ -z $x ]
	then
		x=0
	elif [ $x -lt 1 ] && [ $x -gt 1 ]
       	then
		x=1
	fi


	xte "mousermove 0 -${y}"
	xte 'mousedown 1'
	xte "mousermove ${x}"
	xte 'mouseup 1'
	xte 'mousemove 562 693'
	xte "mousermove 0 -${y}"
	xte 'mousedown 1'
	let x=$x*-1
	xte "mousermove ${x}"
	xte 'mouseup 1'
	xte 'mousemove 562 693'

done

exit
