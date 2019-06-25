#!/bin/bash  
#
#
#gfo0: The Grade-Figure-outer-er
#
#Joshua Ruskauff
#
###############################################################################
# Variables #
#############

TEMP=$(mktemp -p /tmp status.XXX.out)	#This sets up the random TEMP file if no first line argument is given
FILE=$1		#This sets a variable to the first command line argument

###############################################################################

#This sets up the initial file and grabs what i need.  Doing it this way i ran into a problem with one of the required objectives
#The objective which required you to check the total of the porject and the grand total against the detailed status pull.
#I tried going back and rewriting this with a different grep statement(s) and i was unable to pull everything cleanly.  I would always
#be leaving out one or two things, and i wasn't able to find a way to fix it.  Perhaps it is my unfamiliarity with egrep and its usage,
#or perhaps there is some other problem.  If i find a solution i will make sure to add it in.
getStat(){
	status unix  > ${FILE}
	cat ${FILE} | egrep -e ":.*:" > trim
}

#The next three functions are to get the project names and totals, journal names and totals, and the participation names and totals. 
#Originally, i wanted to have a single overarching function in which i was able to do this, but as i went through the project i realized
#it would either be an impossiblity or an overly complicated programming solution.  So i opted instead to split up my original single
#function into three seperate.
#(I found reverse egrepping to be very helpful in isolating the portions of Status i wanted.)
getPRJCTS(){
	cat trim | egrep -ve "week.*" -e "break.*" -e "extra" > temp
	cat temp | egrep -ve "wcp.*" -e "moar" > PRJCTS	
	rm -f temp
}

getJRNALS(){
	cat trim | egrep -e "week.*" -e "break.*" -e "extra" > JRNALS
}

getPRTCPT(){
	cat trim | egrep -e "wcp.*" -e "moar" > PRTCPT
}

#This function handles getting the number totals from the above functions, whether they've been split up into different sections or not
#This gave me a bit of trouble because the grepped output had an initial 5 space tab, and it through me off for awhile before i was
#able to catch it and thus remove it from the NUM file.  I had another small snag on how to get the output file to read into the function,
#but i realized after some tinkering i could assign the content of an output file such as PRTCPT to a variable, and then feed that into the
#function so i didn't have to split it up into three different functions.
getNum(){
	cat ${INPUT} | cut -d ":" -f 1 --output-delimiter=' ' > temp
	cat temp | cut -b 5- > NUM
	rm -f temp
}

#This retrieves the name of the projects from the PRJCTS file and outputs it into its own file to be used in the table.  Didn't need to have any
#other frills, and it's only in a function because it looks cleaner in my opinion.  I realize that it's an extra step, but it helps declutter
#the bottom portion for me.
getName(){
	cat PRJCTS | cut -d ":" -f 2 --output-delimiter=' ' > PRJNAME
}

#This retrieves the total from whatever has been assigned to the INPUT variable.  This can be used for the big, overall total, or the smaller 
#section by section totals (Example: The "GRand Total" of Journals, Participation, and Projects versus just the total for projects)
getTtl(){
	paste -sd+ ${INPUT} | bc > TOTAL
	TOTAL=`cat TOTAL`
}

#This handles the denominator of the fraction, so quite literally it is computing the "out of" portion of the fraction.  Again, this can be
#done for portions of status or the whole depending upon the INPUT
outOf(){
	cat ${INPUT} | cut -d " " -f9 > temp
	cat temp | cut -d "/" -f2 > temp2
	cat temp2 | cut -d ")" -f1 > OUTOF
	rm -f temp temp2		
}

#This prints out each of the numbers for the Projects.  It takes each line in the INPUT variable and processes it so it goes from a fraction
#out of a variable number into a percentile value.  It also handles the formatting for the line, including the current USER who is running the file
prntNmbr(){
	nmbr=1
	printf "%-10s" "${USER}:"
	while [ $nmbr -lt `cat ${INPUT} | wc -l` ]
	do
		OUTOF="`cat OUTOF | head -$nmbr | tail -1`"
		LINE="`cat  ${INPUT} | head -$nmbr | tail -1`"
		LINE=`echo "scale=4;($LINE/$OUTOF)*100" | bc | cut -b -2`
		printf "%-5s" "$LINE"
		let nmbr=$nmbr+1
	done
	printf "%-4s" "`cat ${INPUT} | tail -1`"
}	

#This prints out all the names of the projects.  It again takes the INPUT variable and takes it apart line by line, printing out the names in the 
#required format.  It also handles the front format with the class (Set as UNIX as only i'm using it.  If i wanted it to be changeable, i'd set a variable
#for CLASS so it can be changed to something like cprog) and the end format with the bonus and grade total template.
prntName(){
	name=1
	printf "%-10s" "UNIX"
	while [ $name -lt `cat ${INPUT} | wc -l` ]
	do
		LINE="`cat ${INPUT} | head -$name | tail -1`"
		printf "%-5s" "$LINE"
		let name=$name+1
	done
	printf "%s\n" "bns prjct+ptcpn+jrnal= result"
}

#This prints out the correctly sized border based on how many projects there are.  It includes a static beginning and end border as those are the two portions
#which do not change, no matter how many projects there are.
prntBrdr(){
	brdr=0
	printf "%s" "========="
	while [ $brdr -lt `cat ${INPUT} | wc -l` ]
	do
		printf "%s" "====="
		let brdr=$brdr+1
	done
	printf "%s\n" "============================"
}

#This calculates the total points accumilated.  This is again variable dependent upon input, as it can create total point values for portions of status or the whole
#This was a later function added in when i realized it was present in four different locations.
calcGrd(){
	getNum;
	outOf;
	INPUT="NUM"
	getTtl;
	OUTOF=`paste -sd+ OUTOF | bc`
	TOTAL=`cat TOTAL`
}

#This statement handles the creation of the STATUS cache.  Dependent upon whether there is a argument present or not, it will either create a TEMP file, or it will
#send the STATUS cache to a specified file.  The one problem i had with this was handling invalid input, the main thing being more than 1 argument.  I tried to 
#send the error output to /dev/null, but no matter where i placed it within this statement, i was unable to get it to run quietly if there was invalid input.
#Is there something i'm missing with how 2> /dev/null works withing a statement?

if [ -z ${FILE} ]; then

	FILE=${TEMP} 

elif [ $# -gt 1 ]; then	
	
	echo "Please enter only a single filename"	
	exit

else
	touch ${FILE}
fi

#Setting up the initial status cache after the cache file has been created.
getStat;

#This creates the initial JRNALS file as well as calculating the grade for that portion.  An if statement is used to cap off the total number
#of points at 17 if the bonus points did bring it over 17 total points.  Assigns the output to JRNLGRD for later use.
#the same principle goes for the next two functions, with the only different being projects that did not include a specified "cap" within
#the instructions.
getJRNALS;
INPUT="JRNALS"
calcGrd;
JNLGRD=`echo "scale=2;($TOTAL/$OUTOF)*13" | bc | cut -b -2`
if [ $JNLGRD -gt 17 ]; then
	JRNLGRD=17
fi

getPRTCPT;
INPUT="PRTCPT"
calcGrd;
PCPGRD=`echo "scale=2;($TOTAL/$OUTOF)*13" | bc | cut -b -2`
if [ $PCPGRD -gt 16 ]; then
	PCPGRD=16
fi


getPRJCTS;
INPUT="PRJCTS"
calcGrd;
PRJGRD=`echo "scale=2;($TOTAL/$OUTOF)*52" | bc | cut -b -2`

#This portion handles the creation of most of the table.  While it is a bit "messy" in that i'm using a whole bunch of different inputs, it was easier in the 
#long run for me to make as much of the code modular as i could.  Meaning INPUT became something i was setting up manually to have a simplar function run, instead
#of creating specified functions for everything that i needed.
INPUT="PRJCTS"
getNum;
getName;
prntBrdr;
INPUT="PRJNAME"
prntName;
prntBrdr;
INPUT="PRJCTS"
outOf;
INPUT="NUM"
prntNmbr;
getTtl;

#This handles the overall grade, comprised of Journals, Participation, and Projects.  This is put into a nice big percentile number so its easier to comprehend
#in the final table, even though it could easily be changed to create a point total instead of a percentile.
INPUT="trim"
calcGrd;
BIGGRD=`echo "scale=2;($TOTAL/$OUTOF)*100" | bc | cut -b -2`

#This statement creates the letter grade after calculating the overall grade.  Likely one of the reasons the big grade was made into a percentile, instead of
#a grand point total.  So far i've only got to bump myself up to 4 points to get an A-.  Hopefully i'll get there!
if [ $BIGGRD -ge 100 ]; then
	LTRGRD="A"
elif [ $BIGGRD -ge 94 ]; then
	LTRGRD="A-"
elif [ $BIGGRD -ge 88 ]; then
	LTRGRD="B+"
elif [ $BIGGRD -ge 82 ]; then
	LTRGRD="B"
elif [ $BIGGRD -ge 76 ]; then
	LTRGRD="B-"
elif [ $BIGGRD -ge 70 ]; then
	LTRGRD="C+"
elif [ $BIGGRD -ge 64 ]; then
	LTRGRD="C"
elif [ $BIGGRD -ge 58 ]; then
	LTRGRD="D"
elif [ $BIGGRD -ge 0 ]; then
	LTRGRD="F"
fi

#This is the last bit of the table.  This handles the final grade culmination, AKA the bottom right of the table.  This prints out the last bit of information
#before bottoming it off with another border.
printf "%s%7s%3s\n" "${PRJGRD}/52+${PCPGRD}/13+${JNLGRD}/13=" "${BIGGRD}/100" "${LTRGRD}"
INPUT="PRJCTS"
getNum;
INPUT="NUM"
prntBrdr;

#This is just to remove all the files that are used in the program.  Nothing fancy, though a problem could come from erasing the ${FILE}.  There was no specification
#within the instructions to keep a specified FILE, but if someone did want to keep that cached data for other uses, this would pose a problem.
rm -f ${FILE} NUM PRJ* trim OUTOF JRNALS PRTCPT TOTAL
