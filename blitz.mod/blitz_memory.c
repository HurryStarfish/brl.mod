
#include "blitz.h"

#define SIZEALIGN 16
#define ALIGNMASK (SIZEALIGN-1)

//Allocates mem on 16 byte aligned boundary.
//
//Used by (some) GC routines to allocate large chunks, and GC mem needs to be on 16 byte boundary for
//mem bit flags system in ref couter/Mark Sibly GCs...
//
void *bbMemAlloc( size_t size ){
	void *p;
	
	//p=malloc( size );
	p=GC_MALLOC_ATOMIC_UNCOLLECTABLE( size );
	return p;
	
}

void bbMemFree( void *p ){
	if( p ) GC_free( p );
}

void *bbMemExtend( void *mem,size_t size,size_t new_size ){
	void *p;
	p=bbMemAlloc( new_size );
	bbMemCopy( p,mem,size );
	bbMemFree( mem );
	return p;
}

void bbMemClear( void *dst,size_t size ){
	memset( dst,0,size );
}

void bbMemCopy( void *dst,const void *src,size_t size ){
	memcpy( dst,src,size );
}

void bbMemMove( void *dst,const void *src,size_t size ){
	memmove( dst,src,size );
}
