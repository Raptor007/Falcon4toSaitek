#pragma once
ref class DeviceThread;

#include "Device.h"
#include "FalconThread.h"

ref class DeviceThread
{
public:
	int SleepMs;
	F4SharedMem::FlightData ^FD;

	DeviceThread( DeviceInstance *instance, FalconThread ^master_thread );
	void Code( void );

private:
	DeviceInstance *Instance;
	FalconThread ^MasterThread;
};
