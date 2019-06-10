#include <stdio.h>
#include <stdlib.h>


extern void   b_call( char *s);


int  main( void)
{
   b_call( "d");
   fprintf( stderr, "exit\n");
   exit( 0);
}
