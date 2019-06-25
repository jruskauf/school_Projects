#include /bin/bash

rm ~/.mtpaint 2>/dev/null

mtpaint &

xte 'mousemove 50 20'
sleep 1
xte 'mousedown 1'
xte 'mousemove 300 300'
xte 'mouseup 1'
xte 'mousemove 100 180'
xte 'mouseclick 1'
xte 'mousermove 0 180'
xte 'mouseclick 1'
xte 'mousemove 300 300'
xte 'mousedown 1'
xte 'mousemove 150 150'
xte 'mouseup 1'    

xte 'mousemove 20 110'
xte 'mouseclick 1'

./circle-3.sh
./dstry-3.sh

exit
