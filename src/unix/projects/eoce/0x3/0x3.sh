#include /bin/bash

#Passphrase: Feb201999
#Deploy ssh-agent session and add the authorized_keys i have
eval `ssh-agent`
ssh-add 


#For every Pi-machine listed, ssh into it and then grab the necessary data.
#Then, print out the grabbed and processed data into an easily readable format
#which will be put into seperate files.
for pies in {48..56}
do
	#Set up variables that fetch wanted values from each Pi-Machine.
	
	
	
	ssh -A jruskauf@10.80.2.$pies 'printf "%s\n" "10.80.2.$pies" > pi.$pies.info; SPEED=`lscpu | egrep -e "CPU max MHz:" | tr -d " " | cut -d ":" -f2`; printf "CPU speed(MHz): %s\n" "$SPEED" >> pi.$pies.info; MMRY=`cat /proc/meminfo | egrep -e "MemTotal" | tr -d " " | cut -d ":" -f2`; printf "Memory: %s\n" "$MMRY"; >> pi.$pies.info; STORE=`df -H | egrep -e "/dev/root" | cut -b 14-20 `; printf "Storage(/): %s\n" "$STORE" >> pi.$pies.info; let TIME=`cat /proc/uptime | cut -d " " -f1 | cut -d "." -f1`/60; printf "Uptime(Minutes): %s\n\n" "$TIME" >> pi.$pies.info; mv pi.$pies.info ~/src/unix/projects/eoce/0x3/; df -H;'
done

exit 0
