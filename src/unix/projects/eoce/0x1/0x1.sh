#include /bin/bash -x
#
#Initial Address(hex): 0x1ced3
#initial Length(octal): 130
################################################################################
#This sets up the initial address for the TOC that's located in the ram dump.
#Then, it uses dd to pull the section of bytes specified by the hex and octal
#values.  After it does that, it snips off the ends and places it in a new file,
#removing the old and unneeded file.
initaddrs=`echo "1ced3" | ./hextodec`
initlngth=`echo "130" | ./octtodec`
dd if=memdump.ram of=dirtymemes bs=1 skip=$initaddrs count=$initlngth
cat dirtymemes | tr ";-" "\n" | head -6 | tail -4 > cleanmemes
rm -f temp dirtymemes

#This loop handles the retrieval of the parts, grabbing each part before cutting
#away the octal and hex values.  It then passes these values to modified C 
#programs that process hex and octal into decimal.  Again, dd is used to pull a 
#specific number of bytes from a certain line in the ram dump, putting each of 
#these grabs into a seperate file.
for meme in {1..3}
do
	cat cleanmemes | egrep -e "part$meme" > cleanmeme-$meme
	cat cleanmeme-$meme | cut -b 9- | cut -d "," -f1 > cleanmeme-$meme.hex
	cat cleanmeme-$meme | cut -b 7- | cut -d "," -f2 > cleanmeme-$meme.oct
	ADDRS=`cat cleanmeme-$meme.hex | ./hextodec`
	LNGTH=`cat cleanmeme-$meme.oct | ./octtodec`
	dd if=memdump.ram of=tidememe-$meme bs=1 skip=$ADDRS count=$LNGTH
	
done

rm -f cleanmeme* temp

#This processes part 1 and 2 which needed extra processing, as they were either
#encoded or archived.
cat tidememe-2 | uudecode -o temp
cat temp > tidememe-2
xzcat tidememe-1 > temp
cat temp > tidememe-1

rm -f temp bleachmeme

#This loop handles creating the complete data file to be used.
for meme in {1..3}
do
	cat tidememe-$meme >> bleachmeme
done
#This handles the creation and sizing of the PNG file, giving birth to the 
#best of palindrome memes
rletopnm bleachmeme > temp
pnmscale 2 temp > temp.ppm
pnmtopng temp.ppm > meme0531.png

rm -f temp* tidememe-* bleachmeme

exit 0
