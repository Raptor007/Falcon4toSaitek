#include "stdafx.h"
#include "Device.h"
#include <cmath>
#include <fstream>
#include "Saitek.h"
#include "Str.h"


Device::Device( GUID guid )
{
	Guid = guid;
}

const char *Device::TypeString( void )
{
	return "Unknown";
}

std::string Device::GuidString( void )
{
	char guid_string[ 128 ] = "";
	sprintf_s( guid_string, 128, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", Guid.Data1, Guid.Data2, Guid.Data3, Guid.Data4[ 0 ], Guid.Data4[ 1 ], Guid.Data4[ 2 ], Guid.Data4[ 3 ], Guid.Data4[ 4 ], Guid.Data4[ 5 ], Guid.Data4[ 6 ], Guid.Data4[ 7 ] );
	return std::string( guid_string );
}


DeviceConfig::DeviceConfig( GUID guid ) : Device( guid )
{
	Name = "Untitled";
	SleepMs = 1000;
}

void DeviceConfig::Load( void )
{
	std::string filename = std::string("Configs\\") + Name + std::string(".cfg");
	std::ifstream config_file( filename.c_str() );
	if( ! config_file.good() )
	{
		System::Windows::Forms::MessageBox::Show( "Couldn't load: " + gcnew String(filename.c_str()), "Couldn't Load Settings", MessageBoxButtons::OK, MessageBoxIcon::Error );
		return;
	}

	while( config_file.good() )
	{
		char line[ 1024 ] = "";
		config_file.getline( line, 1023 );
		LoadLine( line );
	}

	config_file.close();
}

void DeviceConfig::Save( void )
{
	std::string filename = std::string("Configs\\") + Name + std::string(".cfg");
	FILE *config_file = fopen( filename.c_str(), "wt" );
	if( ! config_file )
	{
		System::Windows::Forms::MessageBox::Show( "Couldn't save: " + gcnew String(filename.c_str()), "Couldn't Save Settings", MessageBoxButtons::OK, MessageBoxIcon::Error );
		return;
	}

	fprintf( config_file, "// Raptor007's Falcon 4 to Saitek Utility\n\n" );
	fprintf( config_file, "min_version 2.0\n" );
	fprintf( config_file, "version 2.0\n\n" );
	fprintf( config_file, "// %s\n", TypeString() );
	fprintf( config_file, "device %s\n\n", GuidString().c_str() );

	SaveLines( config_file );

	fclose( config_file );
	config_file = NULL;
}

void DeviceConfig::LoadLine( char *line )
{
	std::list<std::string> cmd_tokens = Str::ParseCommand( line );
	
	try
	{
		while( cmd_tokens.size() )
		{
			// Pull all data relevant to one command.
			std::vector<std::string> cmd_vec;
			while( cmd_tokens.size() && (cmd_tokens.front() != ";") )
			{
				cmd_vec.push_back( cmd_tokens.front() );
				cmd_tokens.pop_front();
			}
			if( cmd_tokens.size() && (cmd_tokens.front() == ";") )
				cmd_tokens.pop_front();
			
			// Execute one command.
			if( cmd_vec.size() )
				LoadLine( cmd_vec );
		}
	}
	catch( ... ){}
}

void DeviceConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
}

void DeviceConfig::SaveLines( FILE *config_file )
{
}

void DeviceConfig::ShowEditWindow( Raptor007sFalcon4toSaitekUtility::MainForm ^main_form )
{
}


DeviceInstance::DeviceInstance( void *saitek_device, DeviceConfig *config, GUID guid ) : Device( guid )
{
	SaitekDevice = saitek_device;
	Config = config;
}

void DeviceInstance::Begin( void ){}
void DeviceInstance::End( void ){}
void DeviceInstance::Update( F4SharedMem::FlightData ^fd, double total_time ){}

void DeviceInstance::RegisterCallbacks( void )
{
	Saitek::DO.RegisterSoftButtonCallback( SaitekDevice, &(Saitek::SoftButtonChange), this );
}

void DeviceInstance::UnregisterCallbacks( void )
{
	Saitek::DO.RegisterSoftButtonCallback( SaitekDevice, NULL, this );
}


LEDLook::LEDLook( void )
{
	Color = LEDColor::On;
	BlinkRate = 0.;
}

LEDCondition::LEDCondition( int type, char color, double blink_rate )
{
	Type = type;
	Look.Color = color;
	Look.BlinkRate = blink_rate;
}

LED::LED( void )
{
	IndexR = -1;
	IndexG = -1;
}

void LED::SetIndices( int index_r, int index_g )
{
	IndexR = index_r;
	IndexG = index_g;
}

void LED::ApplyLook( F4SharedMem::FlightData ^fd, double total_time, void *device, int page_num )
{
	LEDLook *look = &(DefaultLook);

	for( std::vector<LEDCondition*>::iterator cond_iter = Conditions.begin(); cond_iter != Conditions.end(); cond_iter ++ )
	{
		if( Saitek::Output.CheckCondition( fd, (*cond_iter)->Type, total_time ) )
		{
			look = &((*cond_iter)->Look);
			break;
		}
	}

	ApplyLook( look, total_time, device, page_num );
}

void LED::ApplyLook( LEDLook *look, double total_time, void *device, int page_num )
{
	double blink_wait = look->BlinkRate ? (1. / look->BlinkRate) : 0.;
	
	if( IndexR >= 0 )
	{
		bool active = ( (look->Color == LEDColor::On) || (look->Color == LEDColor::Red) || (look->Color == LEDColor::Yellow) );
		if( active && blink_wait && (fmod( total_time, blink_wait * 2. ) < blink_wait) )
			active = false;

		Saitek::DO.SetLed( device, page_num, IndexR, active );
	}

	if( IndexG >= 0 )
	{
		bool active = ( (look->Color == LEDColor::On) || (look->Color == LEDColor::Green) || (look->Color == LEDColor::Yellow) );
		if( active && blink_wait && (fmod( total_time, blink_wait * 2. ) < blink_wait) )
			active = false;

		Saitek::DO.SetLed( device, page_num, IndexG, active );
	}
}
