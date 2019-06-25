#!/bin/bash
###
### catweek.sh - an eoce script to determine the current week based on
###              provided options
###
###       usage: catweek.sh [DATESTRING] [OPTION...]
###
###     options:
### DATESTRING - a valid YYYYMMDD date string
###   fullname - display full name of week (week1, break2, etc.)
###   lastweek - identify the previous week
###   nextweek - identify the next week
###   nobreaks - only transact in regular weeks, not breaks
###  start=DAY - calculate weeks based on DAY (default: wednesday)
###    verbose - increase script verbosity
###       help - display this help and exit
###
###        NOTE: Whole week (5+ day) breaks are considered break weeks.
###              and do not increment or constitute a unique semester week.
###
### exit values:
###          0 - success (something valid reported)
###          1 - prior to the current semester
###          2 - after the current semester
###          3 - invalid date for processing
###
##############################################################################

##############################################################################
##
## Declare variables
##
SEMESTER=$(cat /usr/local/etc/semester)         # Obtain current semester
WEEK_START=11                                   # STARTDAY of semester week
START_DAY="thursday"
SEMESTER_START=14                               # SUNDAY of semester start
SEMESTER_END=132                                # SATURDAY of finals week
EARLY_ALERTS=35
WARNING_GRADES=70
DROP_DATE=84
STARTWEEK=3
ENDWEEK=19
BREAK[0]=16
BREAK[1]=16
BREAK[2]=49                                     # SUNDAY through
BREAK[3]=55                                     # SATURDAY
BREAK[4]=91
BREAK[5]=97
BREAKLIST="16 16 49 55 91 97"                   # First, last day pairs
BREAKWEEK[1]="49 50 51 52 53 54 55"             # No trailing spaces
BREAKWEEK[2]="91 92 93 94 95 96 97"             # No trailing spaces
BREAKDAYS="16 ${BREAKWEEK[1]} ${BREAKWEEK[2]}"  # Literally each day

YEAR=`date | cut -b 25-29`
MONTHNAME=`date | cut -d " " -f2`
if [ $MONTHNAME == "January" ]
then
	MONTH=01
elif [ $MONTHNAME == "February" ]
then
	MONTH=02
elif [ $MONTHNAME == "March" ]
then
	MONTH=03
elif [ $MONTHNAME == "April" ]
then
	MONTH=04
elif [ $MONTHNAME == "May" ]
then
	MONTH=05
elif [ $MONTHNAME == "June" ]
then
	MONTH=06
elif [ $MONTHNAME == "July" ]
then
	MONTH=07
elif [ $MONTHNAME == "August" ]
then
	MONTH=08
elif [ $MONTHNAME == "September" ]
then
	MONTH=09
elif [ $MONTHNAME == "October" ]
then
	MONTH=10
elif [ $MONTHNAME == "November" ]
then
	MONTH=11
elif [ $MONTHNAME == "December" ]
then
	MONTH=12
fi
DAY=`date | cut -b 9-10 | tr " " "0"`
DAYNAME=`date | cut -b -3`
SETDATE=$YEAR$MONTH$DAY
SETWEEK=""
SETDAY=$WEEK_START
SETNAME="week"
VAR=0
input=$SETDATE
function checkdate(){
if [ $input -lt 20180114 ]
then
	exit 1
elif [ $input -gt 20180512 ]
then
	exit 2
elif [ $input -ge 2018011n
			SETWEEK=13
		elif [ $input -ge 20180401 ] && [ $input -le 20180407 ]
		then
			SETWEEK=14
		elif [ $input -ge 20180408 ] && [ $input -le 20180414 ]
		then
			SETWEEK=15
		elif [ $input -ge 20180415 ] && [ $input -le 20180421 ]
		then
			SETWEEK=16
		elif [ $input -ge 20180422 ] && [ $input -le 20180428 ]
		then
			SETWEEK=17
		elif [ $input -ge 20180429 ] && [ $input -le 20180430 ]
		then
			SETWEEK=18
		elif [ $input -ge 20180501 ] && [ $input -le 20180505 ]
		then
			SETWEEK=18
		elif [ $input -ge 20180506 ] && [ $input -le 20180512 ]
		then
			SETWEEK=19
		fi
4 ] && [ $input -le 20180120 ]
then
	SETWEEK=3
elif [ $input -ge 20180121 ] && [ $input -le 20180127 ]
then
	SETWEEK=4
elif [ $input -ge 20180128 ] && [ $input -le 20180131 ]
then
	SETWEEK=5
elif [ $input -ge 20180201 ] && [ $input -le 20180203 ]
then
	SETWEEK=5
elif [ $input -ge 20180204 ] && [ $input -le 20180210 ]
then
	SETWEEK=6
elif [ $input -ge 20180211 ] && [ $input -le 20180217 ]	
then
	SETWEEK=7
elif [ $input -ge 20180218 ] && [ $input -le 20180224 ]
then
	SETWEEK=8
elif [ $input -ge 20180225 ] && [ $input -le 20180231 ]
then
	SETWEEK=9
elif [ $input -ge 20180301 ] && [ $input -le 20180303 ]
then
	SETWEEK=9
elif [ $input -ge 20180304 ] && [ $input -le 20180310 ]
then
	SETWEEK=10
elif [ $input -ge 20180311 ] && [ $input -le 20180317 ]
then
	SETWEEK=11
elif [ $input -ge 20180318 ] && [ $input -le 20180324 ]
then
	SETWEEK=12
elif [ $input -ge 20180325 ] && [ $input -le 20180331 ]
then
	SETWEEK=13
elif [ $input -ge 20180401 ] && [ $input -le 20180407 ]
then
	SETWEEK=14
elif [ $input -ge 20180408 ] && [ $input -le 20180414 ]
then
	SETWEEK=15
elif [ $input -ge 20180415 ] && [ $input -le 20180421 ]
then
	SETWEEK=16
elif [ $input -ge 20180422 ] && [ $input -le 20180428 ]
then
	SETWEEK=17
elif [ $input -ge 20180429 ] && [ $input -le 20180430 ]
then
	SETWEEK=18
elif [ $input -ge 20180501 ] && [ $input -le 20180505 ]
then
	SETWEEK=18
elif [ $input -ge 20180506 ] && [ $input -le 20180512 ]
then
	SETWEEK=19
else
	exit 3
fi

}

checkdate;

for this in $@
do
	if [ $this == "start=monday"  ]
	then
		if [ $DAYNAME = "Sun" ]
		then
			let SETWEEK=$SETWEEK-1
		fi
	elif [ $this == "nextweek" ]
	then
		VAR=1
	elif [ $this == "lastweek" ]
	then
		VAR=-1
	elif [ $this == "fullname" ]
	then
	
		if [ $SETDATE == 20180116 ]
		then
			SETNAME="break"
		elif [ $SETDATE -ge 20180219 ] && [ $SETDATE -le 20180224 ]
		then
			SETNAME="break"
		elif [ $SETDATE -ge 20180402 ] && [ $SETDATE -le 20180407 ]
		then
			SETNAME="break"
		else
			SETNAME="week"
		fi
	elif [ $this == "nobreaks" ]
	then
		let SETDATE=$SETDATE-1
		checkdate;
		let SETWEEK=$SETWEEK-2
	elif [ $this == "help" ]
	then
		echo "
### catweek.sh - an eoce script to determine the current week based on
###              provided options
###
###       usage: catweek.sh [DATESTRING] [OPTION...]
###
###     options:
### DATESTRING - a valid YYYYMMDD date string
###   fullname - display full name of week (week1, break2, etc.)
###   lastweek - identify the previous week
###   nextweek - identify the next week
###   nobreaks - only transact in regular weeks, not breaks
###  start=DAY - calculate weeks based on DAY (default: wednesday)
###    verbose - increase script verbosity
###       help - display this help and exit
###
###        NOTE: Whole week (5+ day) breaks are considered break weeks.
###              and do not increment or constitute a unique semester week.
###
### exit values:
###          0 - success (something valid reported)
###          1 - prior to the current semester
###          2 - after the current semester
###          3 - invalid date for processing
"
	else
		input=`echo $this | egrep -vie [a-z]`
		if [ -z $input ]
		then
			exit 3
		elif [ $input -lt 20180114 ]
		then
			exit 1
		elif [ $input -gt 20180512 ]
		then
			exit 2
		elif [ $input -ge 20180114 ] && [ $input -le 20180120 ]
		then
			SETWEEK=3
		elif [ $input -ge 20180121 ] && [ $input -le 20180127 ]
		then
			SETWEEK=4
		elif [ $input -ge 20180128 ] && [ $input -le 20180131 ]
		then
			SETWEEK=5
		elif [ $input -ge 20180201 ] && [ $input -le 20180203 ]
		then
			SETWEEK=5
		elif [ $input -ge 20180204 ] && [ $input -le 20180210 ]
		then
			SETWEEK=6
		elif [ $input -ge 20180211 ] && [ $input -le 20180217 ]
		then
			SETWEEK=7
		elif [ $input -ge 20180218 ] && [ $input -le 20180224 ]
		then
			SETWEEK=8
		elif [ $input -ge 20180225 ] && [ $input -le 20180231 ]
		then
			SETWEEK=9
		elif [ $input -ge 20180301 ] && [ $input -le 20180303 ]
		then
			SETWEEK=9
		elif [ $input -ge 20180304 ] && [ $input -le 20180310 ]
		then
			SETWEEK=10
		elif [ $input -ge 20180311 ] && [ $input -le 20180317 ]
		then
			SETWEEK=11
		elif [ $input -ge 20180318 ] && [ $input -le 20180324 ]
		then
			SETWEEK=12
		elif [ $input -ge 20180325 ] && [ $input -le 20180331 ]
		then
			SETWEEK=13
		elif [ $input -ge 20180401 ] && [ $input -le 20180407 ]
		then
			SETWEEK=14
		elif [ $input -ge 20180408 ] && [ $input -le 20180414 ]
		then
			SETWEEK=15
		elif [ $input -ge 20180415 ] && [ $input -le 20180421 ]
		then
			SETWEEK=16
		elif [ $input -ge 20180422 ] && [ $input -le 20180428 ]
		then
			SETWEEK=17
		elif [ $input -ge 20180429 ] && [ $input -le 20180430 ]
		then
			SETWEEK=18
		elif [ $input -ge 20180501 ] && [ $input -le 20180505 ]
		then
			SETWEEK=18
		elif [ $input -ge 20180506 ] && [ $input -le 20180512 ]
		then
			SETWEEK=19
		fi

	
	fi
done

let SETECHO=$SETWEEK+$VAR
echo $SETNAME$SETECHO
exit 0
