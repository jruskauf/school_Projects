#!/bin/bash -x
#
# Execute this with some quantity of arguments:
#   ./0x0 4 37 16 23 11 8 29 0 32 2 43 5.2 1 3.14 19
#
###############################################################################

function evaluate()
{
    value=${1}
    sleep  "${1}" && printf "${1} "
}

for item in ${*}; do
    evaluate "${item}" & 
done
wait
echo

exit 0


#Q1: The $*/${*} variable lets the loop iterate through every argument passed
#    through the command line.  The $* special variable reads the command 
#    line arguments as a string, so it can pass real numbers, integers, and 
#    different bases such as hexidecimal values (0x0 for example).
#
#Q2: The "&" after calling on the evaluate function means it runs in the 
#    background.  This allows for the program to "sort" the arguments correctly.
#    Without the "&", the script still runs, but will not correctly sort the
#    arguments out from lowest to highest numerical value.  It will simply 
#    iterate through every argument as it's fed into the script, and will print
#    it out in order of how it was entered.
#
#Q3: The script is taking each command line argument and sorting it out in the 
#    final string that's printed out incrimentally.
#
#Q4: The script is run with several command line arguments.  For every argument
#    present the loop will run with the value of every argument, which is stored
#    in the variable "item".  Then the function "evaluate" is called with the 
#    variable ${item} as an input, while also being run in the background with
#    the use of "&".  The value of ${1} is assigned to the variable of 
#    "value", and then the value is used as a delay in the "sleep" command.  
#    Then, after the delay, ${1} will be printed out.  This effectively sorts 
#    the values of the arguments from lowest to highest.
