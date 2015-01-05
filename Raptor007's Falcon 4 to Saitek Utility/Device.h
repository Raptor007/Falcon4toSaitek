#pragma once
class Device;
class DeviceConfig;
class DeviceInstance;
class LEDLook;
class LEDCondition;
class LED;

#include <string>
#include <vector>
#include <map>
#include <set>
#include "DirectOutputImpl.h"

namespace Raptor007sFalcon4toSaitekUtility
{
	ref class MainForm;
}


class Device
{
public:
	GUID Guid;

	Device( GUID guid );
	virtual ~Device();

	virtual const char *TypeString( void );
	std::string GuidString( void );
};


class DeviceConfig : public Device
{
public:
	std::string Name;
	int SleepMs;
	std::map<std::string,std::string> KeyBinds;
	
	DeviceConfig( GUID guid );
	virtual ~DeviceConfig();
	
	virtual void Clear( void );
	void Load( void );
	void Save( void );
	void LoadLine( char *line );
	virtual void LoadLine( std::vector<std::string> cmd_tokens );
	virtual void SaveLines( FILE *config_file );
	
	virtual void ShowEditWindow( void );
	
	virtual bool NeedsTex( void );
};


class DeviceInstance : public Device
{
public:
	void *SaitekDevice;
	DeviceConfig *Config;
	int SelectedPage;
	DWORD Buttons;
	std::map< int, std::map<int,bool> > LEDState;
	std::set<int> PagesNeedRefresh;
	
	DeviceInstance( void *saitek_device, DeviceConfig *config, GUID guid );
	virtual ~DeviceInstance();
	
	virtual void Begin( void );
	virtual void End( void );
	
	virtual void Update( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, double dt );
	virtual void SetLED( int page_num, int led, bool value, bool force = false );
	
	void ChangeButtons( DWORD buttons );
	virtual void ChangedButton( DWORD button, bool state );
	
	virtual void RegisterCallbacks( void );
	virtual void UnregisterCallbacks( void );
};


class LEDLook
{
public:
	char Color;
	double BlinkRate;

	LEDLook( void );
	virtual ~LEDLook();
};

class LEDCondition
{
public:
	int Type;
	LEDLook Look;

	LEDCondition( int type, char color, double blink_rate );
	virtual ~LEDCondition();
};

class LED
{
public:
	int IndexR, IndexG;
	LEDLook DefaultLook;
	std::vector<LEDCondition*> Conditions;

	LED( void );
	virtual ~LED();

	void SetIndices( int index_r, int index_g );
	void ApplyLook( F4SharedMem::FlightData ^fd, double total_time, DeviceInstance *instance, int page_num, bool force_update = false );
	void ApplyLook( LEDLook *look, double total_time, DeviceInstance *instance, int page_num, bool force_update = false );
};

namespace LEDColor
{
	enum
	{
		Off,
		On,
		Red,
		Yellow,
		Green
	};
}
