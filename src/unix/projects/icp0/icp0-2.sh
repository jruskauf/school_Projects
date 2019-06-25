#include /bin/bash

rm ~/.mtpaint 2>/dev/null

mtpaint &

xte 'mousemove 50 20'
sleep 1
xte 'mousedown 1'
xte 'mousemove 300 300'
xte 'mouseup 1'
xte 'mousemove 45 65'
xte 'mouseclick 1'
xte 'mousermove 0 180'
xte 'mouseclick 1'
xte 'mousemove 300 300'
xte 'mousedown 1'
xte 'mousemove 150 150'
xte 'mouseup 1'

xte 'mousemove 600 600'
xte 'mousedown 1'
xte 'mousermove -100 100'
xte 'mouseup 1'
xte 'mousemove 490 110'
xte 'mouseclick 1'
xte 'mousemove 600 600'
xte 'mouseclick 3'
xte 'mousermove -25 25'
xte 'mousedown 1'
xte 'mousermove -50 50'
xte 'mouseup 1'
xte 'mousemove 45 265'
xte 'mouseclick 1'
xte 'mousemove 490 110'
xte 'mouseclick 1'
xte 'mousemove 600 600'
xte 'mouseclick 3'

exit

