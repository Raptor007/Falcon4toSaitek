#include "stdafx.h"
#include "X52Pro.h"
#include "Saitek.h"
#include "FalconOutput.h"
#include "X52ProConfigForm.h"
#include <fstream>


X52ProInstance::X52ProInstance( void *saitek_device, X52ProConfig *config ) : DeviceInstance( saitek_device, config, DeviceType_X52Pro )
{
}

const char *X52ProInstance::TypeString( void )
{
	return "X52 Pro";
}

void X52ProInstance::Begin( void )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	X52ProConfig *Config = (X52ProConfig *) this->Config;

	for( int page_num = 0; page_num < Config->Pages.size(); page_num ++ )
	{
		DWORD flags = 0;
		if( page_num == 0 )
			flags = FLAG_SET_AS_ACTIVE;
		Saitek::DO.AddPage( SaitekDevice, page_num, NULL, flags );

		for( int led = 0; led < 20; led ++ )
		{
			Saitek::DO.SetLed( SaitekDevice, page_num, led, 1 );
			Saitek::DO.SetLed( SaitekDevice, page_num, led, 0 );
		}
	}

	RegisterCallbacks();
}

void X52ProInstance::End( void )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	X52ProConfig *Config = (X52ProConfig *) this->Config;

	for( int page_num = Config->Pages.size() - 1; page_num >= 0; page_num -- )
		Saitek::DO.RemovePage( SaitekDevice, page_num );
	
	UnregisterCallbacks();
}

void X52ProInstance::Update( F4SharedMem::FlightData ^fd, double total_time )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	X52ProConfig *Config = (X52ProConfig *) this->Config;

	for( int page_num = 0; page_num < Config->Pages.size(); page_num ++ )
	{
		for( int led = 0; led < 11; led ++ )
			Config->LEDs[ led ].ApplyLook( fd, total_time, SaitekDevice, page_num );

		X52ProPage *page = Config->Pages.at( page_num );
		for( int line = 0; line < 3; line ++ )
		{
			wchar_t buffer[ 32 ] = L"";
			memset( buffer, 0, 32*sizeof(wchar_t) );
			Saitek::Output.FormatText( fd, page->Texts[ line ], total_time, buffer, 32 );
			Saitek::DO.SetString( SaitekDevice, page_num, line, wcslen(buffer), buffer );
		}
	}
}


X52ProConfig::X52ProConfig( void ) : DeviceConfig( DeviceType_X52Pro )
{
	Initialize();
}


X52ProConfig::X52ProConfig( std::string config_name ) : DeviceConfig( DeviceType_X52Pro )
{
	Initialize();
	Name = config_name;
	Load();
}


const char *X52ProConfig::TypeString( void )
{
	return "X52 Pro";
}


void X52ProConfig::Initialize( void )
{
	LEDs[ X52ProLEDNum::Fire ].SetIndices( X52ProLEDID::Fire, X52ProLEDID::Unused );
	LEDs[ X52ProLEDNum::A ].SetIndices( X52ProLEDID::ARed, X52ProLEDID::AGreen );
	LEDs[ X52ProLEDNum::B ].SetIndices( X52ProLEDID::BRed, X52ProLEDID::BGreen );
	LEDs[ X52ProLEDNum::Hat2 ].SetIndices( X52ProLEDID::Hat2Red, X52ProLEDID::Hat2Green );
	LEDs[ X52ProLEDNum::T1 ].SetIndices( X52ProLEDID::T1Red, X52ProLEDID::T1Green );
	LEDs[ X52ProLEDNum::T3 ].SetIndices( X52ProLEDID::T3Red, X52ProLEDID::T3Green );
	LEDs[ X52ProLEDNum::T5 ].SetIndices( X52ProLEDID::T5Red, X52ProLEDID::T5Green );
	LEDs[ X52ProLEDNum::D ].SetIndices( X52ProLEDID::DRed, X52ProLEDID::DGreen );
	LEDs[ X52ProLEDNum::E ].SetIndices( X52ProLEDID::ERed, X52ProLEDID::EGreen );
	LEDs[ X52ProLEDNum::Clutch ].SetIndices( X52ProLEDID::ClutchRed, X52ProLEDID::ClutchGreen );
	LEDs[ X52ProLEDNum::Throttle ].SetIndices( X52ProLEDID::Throttle, X52ProLEDID::Unused );

	SetDefaults();
}


void X52ProConfig::SetDefaults( void )
{
	Name = "X52 Pro";
	SleepMs = 125;

	LEDs[ X52ProLEDNum::Fire ].DefaultLook.Color = LEDColor::On;
	LEDs[ X52ProLEDNum::Fire ].Conditions.clear();
	LEDs[ X52ProLEDNum::A ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::A ].Conditions.clear();
	LEDs[ X52ProLEDNum::B ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::B ].Conditions.clear();
	LEDs[ X52ProLEDNum::Hat2 ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::Hat2 ].Conditions.clear();
	LEDs[ X52ProLEDNum::T1 ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::T1 ].Conditions.clear();
	LEDs[ X52ProLEDNum::T3 ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::T3 ].Conditions.clear();
	LEDs[ X52ProLEDNum::T5 ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::T5 ].Conditions.clear();
	LEDs[ X52ProLEDNum::D ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::D ].Conditions.clear();
	LEDs[ X52ProLEDNum::E ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::E ].Conditions.clear();
	LEDs[ X52ProLEDNum::Clutch ].DefaultLook.Color = LEDColor::Green;
	LEDs[ X52ProLEDNum::Clutch ].Conditions.clear();
	LEDs[ X52ProLEDNum::Throttle ].DefaultLook.Color = LEDColor::On;
	LEDs[ X52ProLEDNum::Throttle ].Conditions.clear();

	Pages.clear();
}


void X52ProConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
	std::string cmd = cmd_tokens[ 0 ];
	
	if( cmd == "led" )
	{
		//
	}
}


void X52ProConfig::SaveLines( FILE *config_file )
{
	for( int i = 0; i < X52ProLEDNum::NUM; i ++ )
	{
		const char *led_name = "unknown", *color = "off";

		switch( i )
		{
			case X52ProLEDNum::Fire:
				led_name = "fire";
				break;
			case X52ProLEDNum::A:
				led_name = "a";
				break;
			case X52ProLEDNum::B:
				led_name = "b";
				break;
			case X52ProLEDNum::Hat2:
				led_name = "hat2";
				break;
			case X52ProLEDNum::T1:
				led_name = "t1";
				break;
			case X52ProLEDNum::T3:
				led_name = "t3";
				break;
			case X52ProLEDNum::T5:
				led_name = "t5";
				break;
			case X52ProLEDNum::D:
				led_name = "d";
				break;
			case X52ProLEDNum::E:
				led_name = "e";
				break;
			case X52ProLEDNum::Clutch:
				led_name = "clutch";
				break;
			case X52ProLEDNum::Throttle:
				led_name = "throttle";
				break;
		}

		switch( LEDs[ i ].DefaultLook.Color )
		{
			case LEDColor::Off:
				color = "off";
				break;
			case LEDColor::On:
				color = "on";
				break;
			case LEDColor::Green:
				color = "green";
				break;
			case LEDColor::Yellow:
				color = "yellow";
				break;
			case LEDColor::Red:
				color = "red";
				break;
		}
		
		for( std::vector<LEDCondition*>::iterator cond_iter = LEDs[ i ].Conditions.begin(); cond_iter != LEDs[ i ].Conditions.end(); cond_iter ++ )
		{
			std::string condition = Saitek::Output.GetConditionName( (*cond_iter)->Type );

			switch( (*cond_iter)->Look.Color )
			{
				case LEDColor::Off:
					color = "off";
					break;
				case LEDColor::On:
					color = "on";
					break;
				case LEDColor::Green:
					color = "green";
					break;
				case LEDColor::Yellow:
					color = "yellow";
					break;
				case LEDColor::Red:
					color = "red";
					break;
			}

			fprintf( config_file, "led %s %s %s %.0f\n", led_name, condition.c_str(), color, (*cond_iter)->Look.BlinkRate );
		}
		
		fprintf( config_file, "led %s default %s %.0f\n\n", led_name, color, LEDs[ i ].DefaultLook.BlinkRate );
	}

	for( int i = 0; i < Pages.size(); i ++ )
	{
		for( int j = 0; j < 3; j ++ )
		{
			std::string text = Saitek::Output.GetTextName( Pages[ i ]->Texts[ j ] );
			
			fprintf( config_file, "mfd %i %i %s\n", i + 1, j + 1, text.c_str() );
		}
		
		fprintf( config_file, "\n" );
	}
}


void X52ProConfig::ShowEditWindow( Raptor007sFalcon4toSaitekUtility::MainForm ^main_form )
{
	Raptor007sFalcon4toSaitekUtility::X52ProConfigForm ^edit_window = gcnew Raptor007sFalcon4toSaitekUtility::X52ProConfigForm();
	edit_window->Show();
}



X52ProPage::X52ProPage( void )
{
	for( int i = 0; i < 3; i ++ )
		Texts[ i ] = TextType::Nothing;
}
