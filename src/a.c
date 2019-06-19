#include <stdio.h>
#include <stdlib.h>
#include "e.h"


// a is like mulle-testallocator
// it patches e

static size_t   total;


static void  *a_calloc( size_t n, size_t size)
{
   void   *p;

   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   total += n * size;
   p      = calloc( n, size);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
   return( p);
}


static void  a_free( void *p)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}



static void   a_atexit( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "-- run a_atexit\n");
//   fprintf( stderr, "total: %ld\n", total);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}


__attribute__((constructor))
static void  constructor_a( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   if( getenv( "USE_A"))
   {
      e_allocator.calloc = a_calloc;
      e_allocator.free   = a_free;
      fprintf( stderr, "-- install a_atexit\n");
      atexit( a_atexit);
   }
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}


#ifdef DESTRUCTOR

__attribute__((destructor))
static void  destructor_a( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "-- run destructor_a\n");
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}

#endif
