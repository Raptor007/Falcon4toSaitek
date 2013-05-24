/*
 *  gettimeofday.h
 */

#ifndef GETTIMEOFDAY_H
#define GETTIMEOFDAY_H

#include <time.h>
#ifdef WIN32
#include <winsock.h>
#endif


struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};


int gettimeofday(struct timeval *tv, struct timezone *tz);


#endif
