#include <stdio.h>
#include <stdlib.h>

//Setting up all the function prototypes and the data they need to run
int insert (int value, int count, int size, int array[]);
int append (int value, int count, int size, int array[]);
int obtain (int count, int size, int array[]);
void display(int count, int array[]);
void menu ();

int main ()
{
	//Setting up variables for use, initializing an empty array of 20 
	//elements to use as well.
	int input;
	int value;
	int count;
	int array[20];
	int size;
	
	//An external Do...While loop that detects whether the input is a valid
	//number of 1-6, and if it is 7 or above it kicks you out.
	do{
		//initial menu and ask for input that will be shown after every
		//iteration of the Do...While loop.
		menu();
		scanf("%d", &input);
		
		//Responsible for building a list if input in the menu is 0.
		if (input == 0){

			count=0;
			
			//Populates the list with the values inputted until it
			//detects an entry of -1, which caps the very end of
			//the list.
			do{	
				value = 0;
				fprintf(stderr, "enter value (-1 to finish): ");
				fscanf(stdin, "%d", &value);
				array[count]=value;
				count++;
			}while(value != -1);
			
			//Sets the size of the array to how many times count
			//was iterated, very important.
			size=count;
		
		//Responsible for displaying the list forward 0-size
		}else if (input == 1){

			count=0;
			
			//For each iteration of the loop, it prints out one
			//value at a time, and is also responsible for whether
			//there will be an arrow after the value or not
			while (count < size){
					if (count > 0 && count <= size){
						fprintf(stdout, " -> ");
					}
					display(count, array);
					count++;
			}
			
			//resets the buffer so menu appears correctly
			printf("\n");
		
		//Responsible for displaying list backwards size-0
		}else if (input == 2){
		
			count=size-1;
			
			//same as printing the list out forward, except with
			//different arguments and count iterations to allow
			//for proper printing of the list in reverse
			while (count > -1){

					if (count > -1 && count < size-1){
						fprintf(stdout, " -> ");
					} 

					display(count, array);
					count--;
			}
			
			//resets buffer so menu appears correctly
			printf("\n");

		//Responsible for inserting into the array before a value
		}else if (input == 3){
			
			//prompt for inputs and assignment of inputs
			fprintf(stderr, "Enter index to insert before: ");
			fscanf(stdin, "%d", &count);
			fprintf(stderr, "Enter value to insert into list: ");
			fscanf(stdin, "%d", &value);
			
			//sets the new array size on the return value of the
			//function
			size = insert(value, count, size, array);
		
		//Responsible for appending into an array after a value
		}else if (input == 4){

			//prompt for inputs and assignment of input
			fprintf(stderr, "Enter index to append after: ");
			fscanf(stdin, "%d", &count);
			fprintf(stderr, "Enter value to append into list: ");
			fscanf(stdin, "%d", &value);
			
			//sets the new array size on the return value of the
			//function
			size = append(value, count, size, array);

		//Responsible for obtaining a value from a list and then 
		//removing the obtained value
		}else if (input == 5){
	
			fprintf(stderr, "Enter index to obtain: ");
			fscanf(stdin, "%d", &count);
			value = obtain(count, size, array);
			fprintf(stdout, "The value you obtained is: %d", value);
			printf("\n");
			size--;

		//Used to nuke the entire array with -1.  Leave nothing alive.
		}else if (input == 6){

			count=0;
			value=-1;
			size=0;

			while (count<20){
				array[count]=value;
				count++;
			}

		}

	}while(input < 7);

	return(0);

}

//Menu function that is used to print out the menu each time it is called.
void menu(){

	fprintf(stderr, "\n===ael0===\n");
	fprintf(stderr, "0. build list\n");
	fprintf(stderr, "1. display list forward\n");
	fprintf(stderr, "2. display list backward\n");
	fprintf(stderr, "3. insert into list\n");
	fprintf(stderr, "4. append into list\n");
	fprintf(stderr, "5. obtain from list\n");
	fprintf(stderr, "6. clear list\n");
	fprintf(stderr, "7. quit\n");
	fprintf(stderr, ">>> ");

}

//Function responsible for appending after a value
int append (int value, int count, int size, int array[]){
	
	//If you enter an element to append after while there is an empty array
	//you will instead insert the value into the first array element with a
	//-1 attached to signify the end of the list
	if ((count == 0 || count != 0)&& size == 0){

		array[0]=value;
		array[1]=-1;
		size=2;

	//This shunts everything after the element you want to append behind to
	//the right, so the value inserts into an empty element and doesn't
	//overwrite any values. Then size iterates up by one to account for the
	//new value in the array.
	} else if (count >= 0 && size != 0){

		int tick;

		for (tick=size; tick > count; tick--){
			array[tick+1]=array[tick];
		}

		array[count+1]=value;
		size++;
		
	}
	
	//returns the new size of the array
	return(size);

}

//Function responsible for inserting before a value
int insert (int value, int count, int size, int array[]){

	//If you enter an element to append after while there is an empty array
	//you will instead insert the value into the first array element with a
	//-1 attached to signify the end of the list
	if ((count == 0 || count != 0) && size == 0){

		array[0]=value;
		array[1]=-1;
		size=2;

	//This shunts everything after the element you want to insert before to
	//the right, so the value inserts into an empty element and doesn't
	//overwrite any values. Then size iterates up by one to account for the
	//new value in the array.
	} else if (count >= 0 && size != 0){

		int tick;

		for (tick=size; tick >= count; tick--){
			array[tick+1]=array[tick];
		}

		array[count]=value;
		size++;

	}

	//returns the new size of the array
	return(size);
}

//Function that displays the specified element and array value that element
//addresses
void display (int count, int array[]){
	fprintf(stdout, "[%d] %d", count, array[count]);
}

//This function is responsible for obtaining a value and then removing it from
//the array and shifting all values accordingly.
int obtain (int count, int size, int array[]){

	int value = array[count];

	for (count=count; count < size; count++){
		array[count]=array[count+1];
	}

	return(value);

}
