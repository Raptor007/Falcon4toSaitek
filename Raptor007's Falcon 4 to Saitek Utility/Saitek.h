#pragma once

#include <msclr\auto_gcroot.h>
#include <vector>
#include <map>
#include <string>
#include "FalconOutput.h"
#include "DirectOutputImpl.h"
#include "Device.h"
#include "FalconThread.h"

namespace Saitek
{
	extern FalconOutput Output;
	
	extern CDirectOutput DO;
	extern bool Initialized;
	
	extern std::vector<DeviceInstance*> Instances;
	extern msclr::auto_gcroot<System::Threading::Mutex^> InstancesLock;
	extern bool InstancesChanged;
	
	extern std::map<std::string, DeviceConfig*> Configs;
	
	extern msclr::auto_gcroot<FalconThread^> MainThread;
	
	
	void GenerateDefaults( void );
	void LoadConfigs( void );
	void SaveConfigs( void );
	void Initialize( void );
	void Deinitialize( void );
	void __stdcall EnumerateCallback( void *device, void *ctxt );
	void __stdcall DeviceChange( void *device, bool added, void *ctxt );
	void __stdcall PageChange( void *device, DWORD page_num, bool active, void *instance_ptr );
	void __stdcall SoftButtonChange( void *device, DWORD buttons, void *instance_ptr );
	
	void RestartService( void );
}
