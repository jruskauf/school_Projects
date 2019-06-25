#include /bin/bash
#
#
#Circle/Square/Triangle stuff maker
#
#Joshua Ruskauff
###############################################################################

#This removes any mtpaint settings that are already on the machine and then
#starts up mtpaint in the background.  If mtpaint isn't running in the 
#background, then any xte commands wouldn't work correctly.
rm ~/.mtpaint 2>/dev/null

mtpaint &

#This section of commands handles the initial setup of mtpaint to the layout i
#like, a well as the required full screen for mtpaint.
xte 'mousemove 50 20'
sleep 1
xte 'mousedown 1'
xte 'mousemove 300 300'
xte 'mouseup 1'
#This may need to be changed, as for some odd reason my mtpaint seemed to 
#always start out at odd points if i happened to save a picture off of it.
#So this may or may not work correctly depending upon if mtpaint initializes in
#the correct position.
xte 'mousemove 40 70'
xte 'mouseclick 1'
xte 'mousermove 0 180'
xte 'mouseclick 1'
xte 'mousemove 300 300'
xte 'mousedown 1'
xte 'mousemove 150 150'
xte 'mouseup 1'

#This selects the drawing tool from the mtpaint toolbar
xte 'mousemove 20 110'
xte 'mouseclick 1'

#This function handles the creation of the circle.  For the process of creating
#the circle, i chose to calculate out the seperate X and Y coordinates.  This
#lets me create a circle with a variable radius, and if i so wished to create
#an elipse by modifying the output of the X or Y coordinate calculations.
#For this program i've done something different than what was required, as I
#created a patterned circle.  While it is not a "true" circle in the fact all
#X and Y coordinates are connected with a single "circle", it still appears the
#same in basic form.  I decided that the circle would look more interesting with
#all the triangles i used to get to the final X,Y coordinates for every point
#drawn out in different colors.  I first created a checking function to check
#the loop count, so i would then be able to check the right most digit in the
#count.  This was needed for the color swapping statement, which would swap the
#line color whenever the one's placed changed a digit.  Then the lines would
#be printed out.  I wanted the diagonal lines between the finished X,Y
#coordinates and the center to be on top, so i messed around with how the lines
#are printed out so they draw the Y coordinates, then the X coordinates, and 
#then return to the middle.  This produces the desired finished effect, while
#providing a neat little creation animation.  However, due to the constant 
#checks in the beginning of the loop, it bogs down the program.  In earlier
#iterations it sometimes took me more than a minute to draw the circle, but
#in this version i've been able to knock down the time to around 20 seconds
#after initial mtpaint setup.
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
	#changing $radians to $angle in either X or Y can produce interesting square
	#patterns, while changing both to $angle will draw out a different circle
	#pattern.
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

done

#unecho this if you want the final image to be zoomed in to 200% 
#xte 'mousemove 410 80'
#xte 'mouseclick 1'
#xte 'mousemove 380 230'
#xte 'mouseclick 1'

exit
