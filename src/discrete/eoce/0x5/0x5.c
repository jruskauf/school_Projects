#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
    //My idea with this program was to calculate out the total possible number
    //of anagrams, and then have a function in which i would put the array
    //holding the word, and using the total number of unique combinations
    //as a cap to a recursively called program, generate each and every
    //unique anagram for the letters of the word.  While i wasn't able
    //to create said function, i was at least able to create something which
    //attempts to calculate the total number of unique anagrams from a word.
    //while this only does it for one word, if i was to do it for multiple
    //words i'd put it all in an outer loop which handles iterating through
    //each seperate argument, calculating out and printing out the anagrams
    //for each seperate word, and then calculating how many unique orderings
    //of the words there were through using the same recursively called program
    //with the addresses of the strings held within an array.
    
    //Here we check if there is more than one argument, because any less and the
    //program won't work.
    if(argc < 2){
	fprintf(stderr, "ERROR! Not enough argumenst!\n");
	exit(1);
    }

    //creating the array and mallocing out the proper amount of memory for the
    //word.
    char *word = NULL;
    word = (char *)malloc(sizeof(char) * strlen(argv[1]));
    word = argv[1];

    int Letter = 0;
    int check  = 0;
    int count  = 1;
    int uniq   = strlen(word);
    int dupe   = 1;
    int iter   = 0;
    int checkl = 0;
    //This loop handles the counting of duplicate letters.  I found that for 
    //every duplicate letter pairs present, you have !dupe less combinations.
    //for beet, with !2 repeating letters, you have 12 combinations, where bats
    //with !1 repeating letters (each letter can count as a repeat of itself,
    //we're only counting pairs mind you) the number of possible combinations
    //is 24.
    Letter = word[iter];
    while(iter < strlen(word)){
	Letter = word[iter];
	checkl = 0;
	count = iter+1;
	while(count < strlen(word)){
	    check = word[count];
	    //printf("%d %d\n", Letter, check);
	    if (Letter == check){
	       checkl = 1;
	    }
	    count++;
        }
	if(checkl == 1){
	    dupe++;
	}
	iter++;
    }	


    //This handles the calculation of the number of anagrams.  The calculation
    //for the number of a unique combination of something is !letters/!dupe.
    //This means if there are 4 letters and 2 duplicate letters, we have
    //4*3*2*1/2*1, which is equal to 12 unique combinations
    int divisor = 1;
    int dividend = 1;

    while(uniq != 0){
	dividend = dividend * (uniq);
	//printf("%d ", dividend);
	uniq--;
    }
    //printf("\n");

    while(dupe != 0){
	divisor = divisor * (dupe);
	//printf("%d ", divisor);
	dupe--;
    }
    //printf("\n");

    printf("# of Anagrams possible of %s: %d\n", word, dividend/divisor);
    
    return(0);
}
