#pragma once

class X52ProInstance;
class X52ProConfig;
class X52ProPage;

#include "Device.h"
#include <vector>


namespace X52ProLEDNum
{
	enum
	{
		// Stick
		Fire = 0,
		A,
		B,
		Hat2,
		T1,
		T3,
		T5,

		// Throttle
		D,
		E,
		Clutch,
		Throttle,
		
		NUM
	};
}


namespace X52ProLEDID
{
	enum
	{
		Unused = -1,
		Fire = 0,
		ARed,
		AGreen,
		BRed,
		BGreen,
		DRed,
		DGreen,
		ERed,
		EGreen,
		T1Red,
		T1Green,
		T3Red,
		T3Green,
		T5Red,
		T5Green,
		Hat2Red,
		Hat2Green,
		ClutchRed,
		ClutchGreen,
		Throttle
	};
}


class X52ProInstance : public DeviceInstance
{
public:
	X52ProInstance( void *saitek_device, X52ProConfig *config );
	
	const char *TypeString( void );
	
	void Begin( void );
	void End( void );

	void Update( F4SharedMem::FlightData ^fd, double total_time );
};


class X52ProPage
{
public:
	int Texts[ 3 ];

	X52ProPage( void );
};


class X52ProConfig : public DeviceConfig
{
public:
	std::vector<X52ProPage*> Pages;
	LED LEDs[ X52ProLEDNum::NUM ];

	X52ProConfig( void );
	X52ProConfig( std::string config_name );
	
	const char *TypeString( void );
	
	void Initialize();
	void SetDefaults();
	void LoadLine( std::vector<std::string> cmd_tokens );
	void SaveLines( FILE *config_file );
	void ShowEditWindow( Raptor007sFalcon4toSaitekUtility::MainForm ^main_form );
};
