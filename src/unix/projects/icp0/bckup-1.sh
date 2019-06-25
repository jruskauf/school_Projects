#include /bin/bash
#
#Mouse Mover
#
#Joshua Ruskauff
#
#
###############################################################################
i
#This grabs the screen info regarding the width and height and sets them both to 
#their respective variables.  Especially useful when drawing squares/rectangles.
#Need to mess with assigning variables for different shapes (triangles, diamonds,
#rhombus, etc...
xwininfo -root -stats > temp
cat temp | egrep -e "Width:" -e "Height:" > info
WIDTH=`cat info | head -1 | cut -d ":" -f2`
HEIGHT=`cat info | tail -1 | cut -d ":" -f2`

#This puts the cursor in the upper left corner of the screen as an arbitrary
#starting point.  Then the next four loops handle the "arbitrary movements
#of the mouse.  Thise takes the mouse in a rough backward 6 shape.  Loops
#here are useful to get the slow, controlled movement, as you can tell it to
#go to consecutive points in a straight line rather than jump to a singular point.
#Mousermove isn't the best for this, as its relative.  If put in a loop your mouse
#will accelerate exponentially.  While this is funny, it is not a controlled
#movement across the screen.
xte 'mousemove 0 0'

going=0
while [ $going -le 500 ]
do
	xte "mousemove $going $going"
	going=$(($going+1))
done

going=500
while [ $going -le 1000 ]
do
	xte "mousemove 500 $going"
	going=$(($going+1))
done

going=500
while [ $going -le 1000 ]
do
	xte "mousemove $going 1000"
	going=$(($going+1))
done

going=1000
while [ $going -ge 0 ]
do
	xte "mousemove $going $going"
	going=$(($going-1))
done


#These next four loops  handle the mouse movement around the screen.  By having
#the height and width pre-set with the screen info, it'll move around the border
#of any screen in a slow, controlled movement.  I tried putting these loops in a
#function called "rectangle" so i could use it for the square as well, but that
#wasn't working, as i had to reverse the movement in which the square was drawn.
going=0
while [ $going -le $WIDTH ]
do
	xte "mousemove $going 0"
	going=$(($going+1))
done

going=0
while [ $going -le $HEIGHT ]
do
	xte "mousemove $WIDTH $going"
	going=$(($going+1))
done

going=$WIDTH
while [ $going -ge 0 ]
do
	xte "mousemove $going $HEIGHT"
	going=$(($going-1))
done

going=$HEIGHT
while [ $going -ge 0 ]
do
	xte "mousemove 0 $going"
	going=$(($going-1))
done


#This sets up the width and height of the square before drawing it out in the
#opposite direction of the rectangle drawn around the border.
WIDTH=500
HEIGHT=500
going=0
while [ $going -le $HEIGHT ]
do
	xte "mousemove 0 $going"
	going=$(($going+1))
done

going=0
while [ $going -le $WIDTH ]
do
	xte "mousemove $going $HEIGHT"
	going=$(($going+1))
done

going=$HEIGHT
while [ $going -ge 0 ]
do
	xte "mousemove $WIDTH $going"
	going=$(($going-1))
done

going=$WIDTH
while [ $going -ge 0 ]
do
	xte "mousemove $going 0"
	going=$(($going-1))
done


exit
