#include /bin/bash
#
#Graphing Trend Figures
#
#Joshua Ruskauff
################################################################################

#To start off i'm going to grab my status info directly from the unix.projects
#file in the info directory.  After i grab it,  reverse grep out the details
#and bonus, and then put that into a file named status.  Then i cat status out
#two times, grabbing the project names and then the project grade fractions.
#This way it makes it easier to compute them, as i only need to take the file
#apart line by line and run it through a bc computation to get the grade out of
#100 points.  Looking back at gfo0 helped me to remember how i could do this
#easily with the use of head -$variable | tails -1, as it isolates a single
#line while a loop iterates it.
cat ~/info/status/unix.projects | egrep -ve "\*" -ve "bonus" > status
cat status | cut -d ":" -f2 > names
cat status | cut -d "(" -f2 | tr -d ")" > numbers

nmbr=1
while [ $nmbr -le `cat numbers | wc -l` ]
do
	cat numbers | head -$nmbr | tail -1 > temp
	echo "scale=4; `cat temp`*100" | bc | cut -b -2 >> grade
	let nmbr=$nmbr+1
done

#Here I use a silent running curl to pull the html from the webpage into a file
#before i egrep out the 4 lines of values i need.  Then i isolate everything
#left of the first "." before running it through a loop that takes each line of
#data and seperates it, and then puts that in a seperate file while orienting it
#into a column.  In my original gtf0 file i also head headers for the project
#grades/names as wel as the class status data, but since i accidentally 
#rm -f * the entire directory (i had a minor case of serious brain damage)
#I had to restart from scratch at 10pm.
curl -s http://lab46.corning-cc.edu/haas/spring2018/unix/projects/status > temp
cat temp | egrep -e"lowscore" -e"avgscore" -e"median:" -e"hiscore" > gtf0.pull

cat gtf0.pull | cut -d "." -f1 | cut -d ":" -f2 > temp

nmbr=1
while [ $nmbr -le 4 ]
do
	cat temp | head -$nmbr | tail -1 | tr " " "\n" > temp.$nmbr
	cat temp.$nmbr | grep -v '^$' > data.$nmbr
	rm -f temp.$nmbr
	let nmbr=$nmbr+1
done

#This puts all the pertinent data into a gnuplot readable form, with the xtic
#labels in the first column, then hiscore, lowscore, acgscore, median, and 
#myscore in the following columns.  Then i clean up the directory by removing
#any files not needed anymore.
paste names data.{1..4} grade > gtf0.data 

rm -f temp grade names data.{1..4} pull status numbers gtf0.pull

#This sets up variables to change the user, designation of class, and the 
#semester.  Idk if this was needed or not, but i wanted to have it in there in
#case it was needed.  Then it set the title of the gnuplot as it's echoed into
#gtf0.gp.  The file is very similar to lines.gp, with the only differences 
#being i used xticlabels to set the xtics, then manually set the ytics, and
#then adding more lines to accomadate the data.
USER="`echo ${USER}`"
DESIG="unix"
SEMESTER="spring2018"
echo "
set title '$USER $SEMESTER/$DESIG'
set xlabel 'x'
set ylabel 'y'
set terminal png size 600,400

set grid
set key below center horizontal noreverse enhanced autotitle box dashtype solid
set tics out nomirror
set border 3 front linetype black linewidth 1.0 dashtype solid

set yrange [-10:110]
set ytic -10, 10, 110
set mytics 1

set style line 1 linewidth 2
set style line 2 linewidth 2
set style line 3 linewidth 2
set style line 4 linewidth 2
set style line 5 linewidth 5

plot 'gtf0.data' using 2:xticlabels(1) with lines linestyle 1 title 'lowscore',\
	'' using 3:xticlabels(1) with lines linestyle 2 title 'avgscore',\
	'' using 4:xticlabels(1) with lines linestyle 3 title 'median',\
	'' using 5:xticlabels(1) with lines linestyle 4 title 'hiscore',\
	'' using 6:xticlabels(1) with lines linestyle 5 title 'myscore'
" > gtf0.gp

#This places the png generated from gnuplot into the public html directory
#so i can now access the png through the lab46 site.  After that i remove any
#unneeded files yet again
gnuplot gtf0.gp > ~/src/unix/projects/gtf0/gtf0.png
cp gtf0.png ~/public_html/gtf0/
chmod 0604 ~/public_html/gtf0/gtf0.png

exit
