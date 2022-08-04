#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int main( void )
{
    char buffer[1024], *p;
    long num_long;
    int  num_int;

    //prompt user for input
    printf( "Enter a number: " );

    //get one line of input from input stream
    if ( fgets( buffer, sizeof buffer, stdin ) == NULL )
    {
        fprintf( stderr, "Unrecoverable error reading from input!\n" );
        exit( EXIT_FAILURE );
    }

    //make sure that entire line was read in (i.e. that
    //the buffer was not too small)
    if ( strchr( buffer, '\n' ) == NULL )
    {
        printf( "Line input was too long!\n" );
        exit( EXIT_FAILURE );
    }

    //attempt to convert string to number
    errno = 0;
    num_long = strtol( buffer, &p, 10 );
    if ( p == buffer )
    {
        printf( "Error converting string to number\n" );
        exit( EXIT_FAILURE );
    }

    //make sure that no range error occurred
    if ( errno == ERANGE || num_long < INT_MIN || num_long > INT_MAX )
    {
        printf( "Range error!\n" );
        exit( EXIT_FAILURE );
    }

    //range is ok, so we can convert to int
    num_int = (int)num_long;

    //make sure that remainder of line contains only whitespace,
    //so that input such as "6sdfh4q" gets rejected
    for ( ; *p != '\0'; p++ )
    {
        if ( !isspace( (unsigned char)*p ) )
        {
            printf( "Unexpected input encountered!\n" );
            exit( EXIT_FAILURE );
        }
    }

    //number was successfully converted, so we print it
    printf( "You entered the following valid number: %d\n", num_int );
}
