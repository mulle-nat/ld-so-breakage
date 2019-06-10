#include <stdlib.h>


struct allocator
{
   void  *(*calloc)( size_t, size_t);
   void  (*free)( void *);
};


extern struct allocator  e_allocator;
