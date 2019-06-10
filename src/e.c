#include <stdio.h>
#include "e.h"


// a is like mulle-allocator
static void  *e_calloc( size_t n, size_t size)
{
   void   *p;

   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   p      = calloc( n, size);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
   return( p);
}


static void  e_free( void *p)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   free( p);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}


struct allocator  e_allocator =
{
   e_calloc,
   e_free
};

