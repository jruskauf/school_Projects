#include /bin/bash

xte 'mousemove 20 110'
xte 'mouseclick 1'
xte 'mousemove 556 693'
xte "mousemove 45 857"
xte 'mouseclick 1'

xpos1=325
xpos2=-325
ypos1=1

triangle=0
while [ $triangle -le 190 ]
do

	if [ $triangle -ge 20 ]
	then
		let xpos1=$xpos1-2
		let xpos2=$xpos2+2
		let ypos1=$ypos1-1
	fi
	
	if [ $triangle -eq 180 ]
	then
		xte 'mousemove 45 313'
		xte 'mouseclick 1'
	fi

	let ypos1=$ypos1+1*$triangle
	xte 'mousemove 562 693'
	xte 'mousedown 1'
	xte "mousermove ${xpos1} ${ypos1}"
	xte 'mousemove 562 693'
	xte "mousermove ${xpos2} ${ypos1}"
	xte 'mouseup 1'
	xte 'mousemove 562 693'
	let triangle=$triangle+1
done

triangle=0
xte "mousemove 45 857"
xte 'mouseclick 1'

while [ $triangle -le 90 ]
do
	radians=`echo "scale=4; $triangle * 0.0174532925" | bc`
	ypos2=`echo "scale=4; (-240 * c($radians))" | bc -l | cut -d "." -f1`	
	
	
	check="-"	
	
	if [ "$ypos2" == "$check" ] || [ -z $ypos2 ]
	then
		ypos2=0
	elif [ $ypos2 -lt 1 ] && [ $ypos2 -gt 1 ]
       	then
		ypos2=1
	fi
	
	if [ $triangle -le 90 ]
	then

		let ypos2=933+$ypos2
		xte "mousemove 237 $ypos2"
		xte 'mousedown 1'
		xte "mousemove 887 $ypos2"
		xte 'mouseup 1'
	
	fi

	let triangle=$triangle+5
done


exit
