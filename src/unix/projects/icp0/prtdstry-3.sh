#include /bin/bash
#
#
#Circle destroyer
#
#Joshua Ruskauff
###############################################################################

xte 'mousemove 20 110'
xte 'mouseclick 1'
 
for angle in {0..90}
do
	xte 'mousemove 40 205'
	xte 'mouseclick 1'
	xte 'mousemove 570 685'
	xte 'mousedown 1'
	radians=`echo "scale=4; $angle * 0.0174532925" | bc`
	x=`echo "scale=4; (200 * c($radians))" | bc -l | cut -d "." -f1`
	y=`echo "scale=4; (200 * s($radians))" | bc -l`
	
	check="-"	
	
	if [ "$x" == "$check" ] || [ -z $x ]
	then
		x=0
	elif [ $x -lt 1 ] && [ $x -gt 1 ]
       	then
		x=1
	fi

	xte "mousermove ${x}"
	xte "mousermove 0 ${y}"
	xte 'mousemove 570 685'
	let x=$x*-1
	xte "mousermove ${x}"
	xte "mousermove 0 ${y}"
	xte 'mousemove 570 685'
	xte "mousermove ${x}"
	xte "mousermove 0 -${y}"	
	xte 'mousemove 570 685'
	let x=$x*-1
	xte "mousermove ${x}"
	xte "mousermove 0 -${y}"
	xte 'mousemove 570 685'

	xte 'mouseup 1'

done

exit
