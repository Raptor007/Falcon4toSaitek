#pragma once

class Device;
class DeviceConfig;
class DeviceInstance;
class LEDLook;
class LEDCondition;
class LED;

#include <string>
#include <vector>
#include "DirectOutputImpl.h"
#include "MainForm.h"


class Device
{
public:
	GUID Guid;

	Device( GUID guid );

	virtual const char *TypeString( void );
	std::string GuidString( void );
};


class DeviceConfig : public Device
{
public:
	std::string Name;
	int SleepMs;

	DeviceConfig( GUID guid );

	void Load( void );
	void Save( void );
	void LoadLine( char *line );
	virtual void LoadLine( std::vector<std::string> cmd_tokens );
	virtual void SaveLines( FILE *config_file );

	virtual void ShowEditWindow( Raptor007sFalcon4toSaitekUtility::MainForm ^main_form );
};


class DeviceInstance : public Device
{
public:
	void *SaitekDevice;
	DeviceConfig *Config;

	DeviceInstance( void *saitek_device, DeviceConfig *config, GUID guid );

	virtual void Begin( void );
	virtual void End( void );

	virtual void Update( F4SharedMem::FlightData ^fd, double dt );

	void RegisterCallbacks( void );
	void UnregisterCallbacks( void );
};


class LEDLook
{
public:
	char Color;
	double BlinkRate;

	LEDLook( void );
};

class LEDCondition
{
public:
	int Type;
	LEDLook Look;

	LEDCondition( int type, char color, double blink_rate );
};

class LED
{
public:
	int IndexR, IndexG;
	LEDLook DefaultLook;
	std::vector<LEDCondition*> Conditions;

	LED( void );
	void SetIndices( int index_r, int index_g );
	void ApplyLook( F4SharedMem::FlightData ^fd, double total_time, void *device, int page_num );
	void ApplyLook( LEDLook *look, double total_time, void *device, int page_num );
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
