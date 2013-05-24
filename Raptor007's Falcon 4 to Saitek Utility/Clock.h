/*
 *  Clock.h
 */

#ifndef CLOCK_H
#define CLOCK_H

#include "platforms.h"

#ifndef WIN32
#include <sys/time.h>
#else
#include <time.h>
#include "gettimeofday.h"
#endif


class Clock
{
public:
	struct timeval TimeVal;
	
	Clock( void );
	Clock( const Clock &c );
	
	void Reset( void );
	double ElapsedSeconds( void );
	double ElapsedMilliseconds( void );
	double ElapsedMicroseconds( void );

	void operator+=( double rhs );
	void operator-=( double rhs );
};


#endif
