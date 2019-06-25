#include /bin/bash

for angle in {0..90}
do
#	if [ $angle -lt 10 ]
#	then
#		check="1"
#	elif [ $angle -lt 100 ]
#	then	
#		check="2"
#	else 
#		check="3"
#	fi
#
#	if [ `echo $angle | cut -b $check` = 0 ]
#	then
#		color=714	
#	elif [ `echo $angle | cut -b $check` = 1 ]
#	then
#		color=714
#	elif [ `echo $angle | cut -b $check` = 2 ]
#	then
#		color=714
#	elif [ `echo $angle | cut -b $check` = 3 ]
#	then
#		color=807
#	elif [ `echo $angle | cut -b $check` = 4 ]
#	then
#		color=807
#	elif [ `echo $angle | cut -b $check` = 5 ]
#	then
#		color=807
#	elif [ `echo $angle | cut -b $check` = 6 ]
#	then
#		color=905
#	elif [ `echo $angle | cut -b $check` = 7 ]
#	then
#		color=905
#	elif [ `echo $angle | cut -b $check` = 8 ]
#	then
#		color=905
#	elif [ `echo $angle | cut -b $check` = 9 ]
#	then
#		color=315
#	fi


	xte "mousemove 45  315"
	xte 'mouseclick 1'
	xte 'mousemove 570 685'

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

	xte 'mousedown 1'	
	xte "mousermove 0 ${y}"
	#xte 'mousedown 1'
	xte "mousermove ${x} 0"
	#xte 'mouseup 1'
	xte 'mousemove 570 685'
	xte "mousermove 0 ${y}"
	let x=$x*-1
	#xte 'mousedown 1'
	xte "mousermove ${x}"
	#xte 'mouseup 1'
	xte 'mousemove 570 685'
	xte "mousermove 0 -${y}"
	#xte 'mousedown 1'	
	xte "mousermove ${x} 0"
	#xte 'mouseup 1'
	xte 'mousemove 570 685'
	xte "mousermove 0 -${y}"
	let x=$x*-1
	#xte 'mousedown 1'
	xte "mousermove ${x} 0"
	#xte 'mouseup 1'
	xte 'mousemove 570 685'
	xte 'mouseup 1'

done

exit
