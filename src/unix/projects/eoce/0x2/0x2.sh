#include /bin/bash
array=(2 8 10 16)
start=0
step=1
stop=15

for base in ${array[@]}
do
	printf "%7s%2s |" "base" "$base"
done

printf '\n'

for base in ${array[@]}
do
	printf "%s" "----------+"
done

printf "\n"
one=`echo $1 | egrep -vie [a-z]`
two=`echo $2 | egrep -vie [a-z]`

if [ -z $one ]
then
	start=0
elif [ $one -lt 0 ]
then
	let step=$step*-1
	let start=$one*-1
elif [ $one -ge 0 ]
then
	start=$one
	if [ $start -gt 255 ] 
	then
		start=255
		stop=255
	elif [ $start -lt 0 ]
	then
		start=0
	fi
fi

if [ -z $two ]
then
	stop=15
elif [ $two -lt 0 ]
then
	let stop=$two*-1
	let step=$step/-1
elif [ $two -ge 0 ]
then
	stop=$two
	if [ $stop -gt 255 ] 
	then
		stop=255
	elif [ $stop -lt 0 ]
	then
		stop=0
	fi
fi

for value in `seq $start $step $stop`
do
	for base in ${array[@]}
	do
		printf "%9s |" "`echo "obase=$base;$value" | bc 2>/dev/null`"
	done
	printf "\n"
done

for this in $@
do
	if [ $this == "help" ]
	then
		echo "
pwn0.sh - render a number table in the specified bases,
                displaying from starting value to ending value.

      behavior: by default, bases 2, 8, 10, and 16 will be
                displayed, in a range of 0 to 15 (inclusive).

          note: valid bases range from 2-16, and values should
                not go negative nor exceed 255. If a starting
                value but no ending value is given, assume an
                ending value +15 away (or capped by 255).

         usage: pwn0.sh [start#] [end#] [OPTION]...

       options:
           $1 - if a positive decimal value, override the
                starting value (0)
           $2 - if a positive decimal value, override the
                ending value (15)

 other options:
          by# - iterate through values by # (default: 1)
        with# - include base # in the list of bases to display
        sans# - remove base # in the list of bases to display
         help - display script usage and exit
		 "
	fi
done

exit 0
