#pragma once
ref class FalconThread;

#include "FalconConfig.h"

ref class FalconThread
{
public:
	FalconConfig Config;
	
	bool Running;
	int ChildThreads;
	
	bool FalconRunning;
	F4SharedMem::FlightData ^FD;
	System::Threading::ReaderWriterLock FDLock;
	
	FalconThread( void );
	void Code( void );
};
