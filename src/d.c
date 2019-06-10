#include <stdio.h>
#include <stdlib.h>
#include "b.h"


//
// d is like any random objc class
// it registers a method "d" in the runtime, nothing more
//
static void  d( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}


__attribute__((constructor))
static void  constructor_d( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   b_register( "d", d);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}
