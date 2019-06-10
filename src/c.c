#include <stdio.h>
#include <stdlib.h>
#include "b.h"

// c configures b

extern void  b_init( int);


void  c_init( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   b_init( 1848);  // setup
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}

