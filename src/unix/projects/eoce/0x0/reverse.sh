#!/bin/bash
####################################################################
function evaluate()
{
    value="${1}"
    
#   The variable count is used to help reverse the process of the
#   "sorting" that the first script code does.  By having the 
#   variable "value" subtracted from 60, the highest value a number
#   can be in this case, it effectively reverses the delay.  Low
#   numbers will have a high delay, and higher numbers will have a
#   lower delay when "${count}" is used as the input for "sleep".

    count=`echo "60-${value}" | bc`
    sleep  "${count}" && printf "${1} "
}

for item in ${*}; do
    evaluate "${item}" &
done
wait
echo

exit 0

