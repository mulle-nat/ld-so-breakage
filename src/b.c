#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e.h"


//
// b is a small objc runtime
// it allocates memory via e
// it gets configured by c
//
extern void  c_init( void);


struct method
{
   char   *sel;
   void   (*imp)( void);
};


struct methodtable
{
   struct method   *methods;
   unsigned int    n;
   unsigned int    size;
};

struct methodtable  *table;


static void   b_atexit( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "-- run b_atexit\n");
   e_allocator.free( table);
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}



// b is like mulle-objc-runtime
// c is like startup
void   b_init( int param)
{
   static int   once;

   fprintf( stderr, "-> %s %d (%d)\n", __PRETTY_FUNCTION__, param, once);
   if( ! once)
   {
      once = 1;

      atexit( b_atexit);

      table          = e_allocator.calloc( 1, sizeof( struct method) * param + sizeof( struct methodtable));
      table->methods = (struct method *) (table + 1);
      fprintf( stderr, "-- install b_atexit\n");
   }
   fprintf( stderr, "<- %s %d (%d)\n", __PRETTY_FUNCTION__, param, once);
}



void   b_register( char *s, void (*f)( void))
{
   fprintf( stderr, "-> %s \"%s\"\n", __PRETTY_FUNCTION__, s);

   c_init();

   table->methods[ table->n].sel = s;
   table->methods[ table->n].imp = f;
   ++table->n;
   fprintf( stderr, "<- %s \"%s\"\n", __PRETTY_FUNCTION__, s);
}


void   b_call( char *s)
{
   struct method   *p;
   struct method   *sentinel;

   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);

   c_init();

   p        = table->methods;
   sentinel = &p[ table->n];
   while( p < sentinel)
   {
      if( ! strcmp( p->sel, s))
      {
         (*p->imp)();
         break;
      }
      ++p;
   }
   if( p == sentinel)
      abort();

   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}


#ifdef DESTRUCTOR

__attribute__((destructor))
static void  destructor_b( void)
{
   fprintf( stderr, "-> %s\n", __PRETTY_FUNCTION__);
   fprintf( stderr, "-- run destructor_b\n");
   fprintf( stderr, "<- %s\n", __PRETTY_FUNCTION__);
}

#endif
