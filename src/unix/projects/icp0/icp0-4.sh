#include /bin/bash

#removes the file that initializes mtpaint settings and starts it up in the 
#background.
rm ~/.mtpaint 2>/dev/null

mtpaint &

#This is copied from icp0-3.sh and initializes mtpaint to the same setup as
#that program.
xte 'mousemove 50 20'
sleep 1
xte 'mousedown 1'
xte 'mousemove 300 300'
xte 'mouseup 1'
xte 'mousemove 75 125'
xte 'mouseclick 1'
xte 'mousermove 0 180'
xte 'mouseclick 1'
xte 'mousemove 300 300'
xte 'mousedown 1'
xte 'mousemove 150 150'
xte 'mouseup 1'    

xte 'mousemove 20 110'
xte 'mouseclick 1'

#I chose to create different files to help organize code and keep this file from
#looking like a scrap yard of code.  It also simplifies variables usage in these
#programs.

#grid.sh sets up the foreground grid.  I have always liked the 80's aesthetic
#art that has flooded the internet in the last few years, so i wanted to try
#and recreate the pattern with a road down the middle.  To creat the lateral
#lines i first tried to create an exponentially increasing Y coordinate, but
#in trying to implement it i ran into problems with how mtpaint functions, as
#well as the numbers growing too quickly.  In order to try and get the same
#effect, i decided to try and use the Y coordinate calculation for a circle.
#thankfully, this printed out the desired effect, even if i had to mess around
#with how it pritned out.  The diagonal lines fading into the middle point of
#the picture were trickier.  In short, i needed to create an arc that printed
#out lines set apart a certain distance.  However, an unintended effect of the
#lines converging in the middle happened to let my create a solid-ish road
#with a white center line without having to print out anything else.
./grid.sh

#This program handles the creation of the "sun" rising above the horizon.  This
#came from the other program i created called "blink".  This prints out a circle
#with only the horizontal lines visible.  So by taking the circle program i 
#wrote for blink and having it print out only the upper half of the circle in
#the desired colors.  I had also planned to use a modified blink program in
#order to create a faded "background" behind the sun.
./sun.sh

exit
