/*
 *  Clock.cpp
 */

#include "stdafx.h"
#include "Clock.h"
#include <cmath>


Clock::Clock( void )
{
	TimeVal.tv_sec = 0;
	TimeVal.tv_usec = 0;
	Reset();
}


Clock::Clock( const Clock &c )
{
	TimeVal.tv_sec = c.TimeVal.tv_sec;
	TimeVal.tv_usec = c.TimeVal.tv_usec;
}


void Clock::Reset( void )
{
	gettimeofday( &TimeVal, NULL );
}

double Clock::ElapsedSeconds( void )
{
	struct timeval current_time;
	gettimeofday( &current_time, NULL );
	
	return ((double)( current_time.tv_sec - TimeVal.tv_sec )) + ((double)( current_time.tv_usec - TimeVal.tv_usec )) / 1000000.0;
}


double Clock::ElapsedMilliseconds( void )
{
	struct timeval current_time;
	gettimeofday( &current_time, NULL );
	
	return ((double)( current_time.tv_sec - TimeVal.tv_sec )) * 1000.0 + ((double)( current_time.tv_usec - TimeVal.tv_usec )) / 1000.0;
}


double Clock::ElapsedMicroseconds( void )
{
	struct timeval current_time;
	gettimeofday( &current_time, NULL );
	
	return ((double)( current_time.tv_sec - TimeVal.tv_sec )) * 1000000.0 + ((double)( current_time.tv_usec - TimeVal.tv_usec ));
}


void Clock::operator+=( double rhs )
{
	double dsec_f = 0;
	long dusec = (long)( modf( rhs, &dsec_f ) + 0.5 );
	long dsec = (long)( dsec_f + 0.5 );
	TimeVal.tv_sec += dsec;
	TimeVal.tv_usec += dusec;
	if( TimeVal.tv_usec >= 1000000 )
	{
		TimeVal.tv_sec += TimeVal.tv_usec / 1000000;
		TimeVal.tv_usec %= 1000000;
	}
}


void Clock::operator-=( double rhs )
{
	operator+=( rhs );
}
