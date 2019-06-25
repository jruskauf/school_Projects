#include <stdio.h>
#include <stdlib.h>

//Structs setting up the node and list calls
struct node {
    char info;
    struct node *right;
    struct node *left;
};
typedef struct node Node;

struct list {
    struct node *lead;
    struct node *last;
};
typedef struct list List;

//using functions for list functionality
List* mklist(List *newList);
Node* mknode(Node *newNode, char info);

int main(int argc, char *argv[]){
    if(argc < 2){
	fprintf(stderr, "ERROR! Must specify a valid file!\n");
	exit(1);
    }
    //File to read to as well as the lists we will be using
    FILE *open;
    List *Journal = NULL;
    List *Participation = NULL;
    List *Projects = NULL;
    Node *tmp1 = NULL;
    Node *tmp2 = NULL;
    Node *tmp3 = NULL;

    //making the lists
    Journal = mklist(Journal);
    Participation = mklist(Participation);
    Projects = mklist(Projects);

    tmp1 = mknode(tmp1, '0');
    tmp2 = mknode(tmp2, '0');
    tmp3 = mknode(tmp3, '0');
    Journal -> lead = tmp1;
    Journal -> last = tmp1;
    Participation -> lead = tmp2;
    Participation -> last = tmp2;
    Projects -> lead = tmp3;
    Projects -> last = tmp3;
    
    //opening the file to a variable and making sure the file is valid
    open = fopen(argv[1], "r");
    if(!open){
	fprintf(stderr, "ERROR! Invalid File!\n");
	exit(2);
    }

    //Here we read from the file, detecting when we hit each of the "sections"
    //by detecting when we hit a '-' and then identifying what one it is
    //with checking the number afterwords.  This then facilitates the reading
    //of bytes into each node.  I progammed myself into a corner, however.  I
    //should have been using strings rather than characters, as while reading
    //byte by byte is useful if you need to handle single characters, it means
    //i cannot work with numbers above a single digit easily.  So rather than
    //having used fgetc, i should have rather used fgets and read everything 
    //into an array.  Then, from that array, i should have read all non-
    //space/section values.  That way, i could have atoi'd the strings into
    //the nodes, allowing me to use numbers above 1.  After that its simple
    //arithmatic.  Add up all the values in a list, divide by the known max,
    //multiply by how much their max is worth in the total grade, and you
    //have each section's "true" grade.  Then add them all up, divide by the
    //total, times by 100, and then check it against the letter grades.
    int check = 0;
    char temp = fgetc(open);
    while(check != 4){
	if(temp == 45){
	    temp = fgetc(open);
	    if(temp == '1'){
		printf("Journal!\n");
		check = 1;
	    } else if (temp == '2'){
		printf("Participation!\n");
		check = 2;
	    } else if (temp == '3'){
		printf("Projects!\n");
		check = 3;
	    } else {
		printf("The End!\n");
		check = 4;
	    }
	} else {
	    if(check == 1 && temp != 32){
		tmp1 -> info = temp;
		printf("%c\n", tmp1 -> info);
	    } else if(check == 2 && temp != 32){
		tmp2 -> info = temp;
		printf("%c\n", tmp2 -> info);
	    } else if(check == 3 && temp != 32){
		tmp3 -> info = temp;
		printf("%c\n", tmp3 -> info);
	    } else {
	        printf("%c\n", temp);
	    }
	}
	temp = fgetc(open);
    }

    return(0);
}

List* mklist(List *newList){
    newList = (List *)malloc(sizeof(List));
    newList -> lead = NULL;
    newList -> last = NULL;
    return(newList);
}

Node* mknode(Node *newNode, char info){
    newNode = (Node *)malloc(sizeof(Node));
    newNode -> info = info;
    return(newNode);
}
