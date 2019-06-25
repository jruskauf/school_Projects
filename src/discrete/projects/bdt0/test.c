#include <stdio.h>
int main ( int argc, char **argv ) {
    FILE *fp = fopen ( "in/sample0.txt", "r");
    char line[1024];
    char ch = getc ( fp );
    int index = 0;
    while ( ch != EOF ) {
        if ( ch != '\n'){
            line[index++] = ch;
        }else {
            line[index] = '\0';
            index = 0;

            printf ( "%s\n", line );
        }
        ch = getc ( fp );
    }


    fclose ( fp );

    return 0;
}


