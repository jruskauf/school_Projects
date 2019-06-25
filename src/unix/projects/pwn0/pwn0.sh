#!/bin/bash  
#
#unix
#
#pwn0
#
#Joshua Ruskauff
#
########################################################################################################
# Variables #		Sets up several variable which are used in the program.
#############

array=(2 8 10 16)		#array for the default 4 bases
count=0				#count for any while loops i might use.
one=$1				#sets one to $1
two=$2				#sets two t $2
itter=1				#sets initial itteration to 1

########################################################################################################
# Value generator Functions #		These set up the values of the data table in ascending/descending order, and with variable base values and itteration.
#############################

upNum(){

	range=`expr $range + $strt`							#initializes range
	count=`expr $count + $strt`							#initializes count
	
	while [ $count -le $range ]							#Loops while count is less than range
	do
			
		for h in `echo ${array[@]}`						#Loops for the number of values in the array
		do	
			printf "%9s |" "`echo "obase=$h;$count" | bc 2>/dev/null`" 	#print out each row of values with custom base and count, send any echos to the void
		done

		printf "\n"								#newline
		
		count=`expr $count + $itter`						#itterate count based on itter
		
		if [ $count -gt 255 ]; then						#stops if the count goes above 255
			exit
		fi
	
	done
	exit
}

downNum(){

	range=`expr $range \* -1 + $strt`						#initializes range
	count=`expr $count + $strt`							#initializes count
	
	while [ $count -le $range ]							#Loops while count is less than range
	do
		
		for h in `echo ${array[@]}`						#Loops for the number of values in the array
		do			
			printf "%9s |" "`echo "obase=$h;$range" | bc 2>/dev/null` " 	#print out each row of values with custom base and count, send any echos to the void
		done
		
		printf "\n"								#newline

		if [ $range -gt 255 ]; then						#stops if the range goes above 255
			exit
		fi

		range=`expr $range - $itter`						#itterates range based on itter
		
	done
	exit
}

########################################################################################################
# Create the Header function#		This function lets the header for the data table be created, and works in junction with sans# and with#
#############################

header(){
	
	for num in `echo ${array[@]}`		#Loop to print out the Base names/columns
	do
		printf "%7s%2s |" "Base" "$num"	#Print statement accesses the elements of the array for the bases
	done

	printf "\n"				#newline at the end of the row

	for div in `echo ${array[@]}`		#Loop to print out the border between Base names and values
	do
		printf "%s" "----------+"	#the divider!
	done

	printf "\n"				#newline at the end of the row
}

#######################################################################################################
# Kill a base #		This allows for sans# to remove any of the default bases
###############

for nope in $@						#loop for however many arguments there are
	do
		if [[ $nope == sans** ]]; then		#check if the argument references sans#
			temp=`echo $nope | cut -c 5-`	#set temp to the # value of sans
		
			if [ $temp -eq 2 ]; then	#checks if temp is equal to 2
				array[0]=" "		#sets element 0 to a blank space
			elif [ $temp -eq 8 ]; then	#checks if temp is equal to 8
				array[1]=" "		#sets element 1 to a blank space
			elif [ $temp -eq 10 ]; then	#checks if temp is equal to 10
				array[2]=" "		#sets element 2 to a blank space
			elif [ $temp -eq 16 ]; then	#checks if temp is equal to 16
				array[3]=" "		#sets element 3 to a blank space
			fi
	
		fi
	done

########################################################################################################
# sans# argument checks #		A series of checks on sans# if it falls in the place of arg1 and arg2
#########################

if [[ $1 == sans** ]]; then		#checks to see if $1 references by#
	range=15			#sets the default range to 15
	strt=0				#sets starting value to 0						
	header;				#calls on the funciton header
	upNum;				#calls on the function upNum
	exit
fi

if [[ $2 == sans** ]]; then		#checks to see if $2 references by#
	range=15			#sets the default range to 15
	strt=$one			#sets starting value to $one					
	header;				#calls on the function header
	upNum;				#calls on the function upNum
	exit
fi


########################################################################################################
# Include more base #		This allows for the use of with# in including more than the default bases.
#####################

for more in $@								#loop for however many arguments there are
	do								
		if [[ $more == with** ]]; then				#check if the argument references with#
			temp=`echo $more | cut -c 5-`			#set temp to the # value of with
		
			if [ $temp -gt 2 ] && [ $temp -lt 8 ]; then	#checks if temp is between base 2 and 8
				array[0]+=" $temp"			#adds $temp to the right of element 0
			elif [ $temp -gt 8 ] && [ $temp -lt 10 ]; then	#checks if temp is between 8 and 10
				array[1]+=" $temp"			#adds $temp to the right of element 1
			elif [ $temp -gt 10 ] && [ $temp -lt 16 ]; then	#checks if temp is between 10 and 16
				array[2]+=" $temp"			#adds $temp to the right of element 2
			fi
	
		fi
	done

########################################################################################################
# with# argument checks #		A series of checks on with# if it falls in the place of arg1 and arg2
#######################

if [[ $1 == with** ]]; then		#checks to see if $1 references by#
	range=15			#sets the default range to 15
	strt=0				#sets starting value to 0						
	header;				#calls on the funciton header
	upNum;				#calls on the function upNum
	exit
fi

if [[ $2 == with** ]]; then		#checks to see if $2 references by#
	range=15			#sets the default range to 15
	strt=$one			#sets starting value to $one					
	header;				#calls on the function header
	upNum;				#calls on the function upNum
	exit
fi


########################################################################################################
# OH GOD HELP #			Provides a helpful echo if you so need it with the use of the help argument.
###############

for help in $@
do
	if [[ $help == help ]]; then					#checks to see if $help references help
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
	 "								#big cheeky echo statement for help
		exit	
	fi
done

########################################################################################################
# Set itter to by# #		This allows for the usage of by# in setting the itteration of the data table
####################

for bump in $@					#this loops for however many arguments are passed
do	
	if [[ $bump == by*** ]]; then		#checks if $x references by#
		itter=`echo $bump | cut -c 3-`	#If yes, assigns itter the # value of by#
	fi

done

########################################################################################################
# By# argument checks #		A series of checks on by# if it falls in the place of arg1 and arg2
#######################

if [[ $1 == by*** ]]; then		#checks to see if $1 references by#
	range=15			#sets the default range to 15
	strt=0				#sets starting value to 0						
	header;				#calls on the funciton header
	upNum;				#calls on the function upNum
	exit
fi

if [[ $2 == by*** ]]; then		#checks to see if $2 references by#
	range=15			#sets the default range to 15
	strt=$one			#sets starting value to $one					
	header;				#calls on the function header
	upNum;				#calls on the function upNum
	exit
fi

########################################################################################################
# Greater / Less Than #		Checks if the start and ending values are within the specified range of 0-255
#######################

if [ $1 -lt 0 ] 2>/dev/null; then		#checks if $1 is less than 0, outputs any echos ito /dev/null
	one=0					#sets one to 0
fi

if [ $2 -lt 0 ] 2>/dev/null; then		#checks if $2 is less than 0, outputs any echos ito /dev/null
	two=0					#sets two to 0
fi

if [ $1 -gt 255 ] 2>/dev/null; then		#checks if $1 is greater than 255, outputs any echos ito /dev/null
	one=255					#sets one to 255
fi

if [ $2 -gt 255 ] 2>/dev/null; then		#checks if $2 is greater than 255, outputs any echos ito /dev/null
	two=255					#sets two to 255
fi


########################################################################################################
# Lonely Boi #		If there is no start or end value present, this will produce the default data table
##############

if [ -z $one ]; then	#checks to see if the starting value for null and content
	range=15			#sets the default range to 15
	strt=0				#sets starting value to 0	
	header;				#calls on the function header
	upNum;				#calls on the function upNum
	exit
fi



########################################################################################################
# First int no second #		This produces the data table if the start variable is present, but nothing else is.
#######################

if [ $one -ge 0 ] && [ -z $two ] ; then		#checks $1 to see if its valid, and $2 for null and content
	range=15				#sets the default range to 15
	strt=$one				#sets starting value to the value of $1
	header;					#calls on the function header
	upNum;					#calls upon the function upNum
fi

########################################################################################################
# First and Second int #	This produces the data table if both start and end values are present
########################

if [ $one -ge 0 ] && [ $two -ge 0 ]; then		#checks to see if both args are greater than zero
	declare -i range				#declares range as an integer variable, allows for maths
	range=$two-$one					#declares range is the difference between $2 and $1
	if [ $one -gt $two ]; then			#checks to see if $1 is greater than $2
		strt=$two				#sets starting value to the value of $2
		header;					#calls on the function header
		downNum;				#calls upon downNum
	else
		strt=$one				#start is set to $1
		header;					#calls on the function header
		upNum;					#calls upon upNum
	fi
fi

exit 0
