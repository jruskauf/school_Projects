#include <string.h>
#include <stdio.h>

int main (int argc, char **argv) {

   char *basename = NULL;
   char *pathname = NULL;
   char *sourcename = NULL;
   char filename[255];
   char *rlecap   = ".rle";
   //char str[80] = "~/src/data/projects/dcf1/in/sample0.txt";
   char *s = "/";
   char *token;
   char *whatiwant;
   

   basename = argv[1];
   pathname = argv[2];
   /* get the first token */
   token = strtok(basename, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( " %s\n", token );
   	sourcename = token; 
      token = strtok(NULL, s);
   }
   printf( " %s\n", sourcename );

   strcat (filename, pathname);
   strcat (filename, sourcename);
   strcat (filename, rlecap);

   printf("%s\n", filename);

   return(0);
}
