#include "Saitek.h"
#include <cstdio>
#include <cstdlib>
#include <map>
#include <fstream>
#include <dirent.h>
#include "FalconOutput.h"
#include "Device.h"
#include "X52Pro.h"
#include "FIP.h"

namespace Saitek
{
	float Version = 2.1f;
	
	FalconOutput Output;
	
	CDirectOutput DO;
	bool Initialized = false;
	
	std::vector<DeviceInstance*> Instances;
	msclr::auto_gcroot<System::Threading::Mutex^> InstancesLock = gcnew System::Threading::Mutex( false );
	bool InstancesChanged;
	
	std::map<std::string, DeviceConfig*> Configs;
	bool ConfigsChanged;
	
	msclr::auto_gcroot<FalconThread^> MainThread = gcnew FalconThread();
	
	std::map<std::string,WORD> KeyMap;
}


void Saitek::InitKeyMap( void )
{
	if( ! KeyMap.size() )
	{
		KeyMap[ "esc" ] = 1;
		KeyMap[ "1" ] = 2;
		KeyMap[ "2" ] = 3;
		KeyMap[ "3" ] = 4;
		KeyMap[ "4" ] = 5;
		KeyMap[ "5" ] = 6;
		KeyMap[ "6" ] = 7;
		KeyMap[ "7" ] = 8;
		KeyMap[ "8" ] = 9;
		KeyMap[ "9" ] = 10;
		KeyMap[ "0" ] = 11;
		KeyMap[ "minus" ] = 12;
		KeyMap[ "equals" ] = 13;
		KeyMap[ "backspace" ] = 14;
		KeyMap[ "tab" ] = 15;
		KeyMap[ "q" ] = 16;
		KeyMap[ "w" ] = 17;
		KeyMap[ "e" ] = 18;
		KeyMap[ "r" ] = 19;
		KeyMap[ "t" ] = 20;
		KeyMap[ "y" ] = 21;
		KeyMap[ "u" ] = 22;
		KeyMap[ "i" ] = 23;
		KeyMap[ "o" ] = 24;
		KeyMap[ "p" ] = 25;
		KeyMap[ "left_bracket" ] = 26;
		KeyMap[ "right_bracket" ] = 27;
		KeyMap[ "enter" ] = 28;
		KeyMap[ "ctrl" ] = 29;
		KeyMap[ "a" ] = 30;
		KeyMap[ "s" ] = 31;
		KeyMap[ "d" ] = 32;
		KeyMap[ "f" ] = 33;
		KeyMap[ "g" ] = 34;
		KeyMap[ "h" ] = 35;
		KeyMap[ "j" ] = 36;
		KeyMap[ "k" ] = 37;
		KeyMap[ "l" ] = 38;
		KeyMap[ "semicolon" ] = 39;
		KeyMap[ "quote" ] = 40;
		KeyMap[ "tilde" ] = 41;
		KeyMap[ "shift" ] = 42;
		KeyMap[ "backslash" ] = 43;
		KeyMap[ "z" ] = 44;
		KeyMap[ "x" ] = 45;
		KeyMap[ "c" ] = 46;
		KeyMap[ "v" ] = 47;
		KeyMap[ "b" ] = 48;
		KeyMap[ "n" ] = 49;
		KeyMap[ "m" ] = 50;
		KeyMap[ "comma" ] = 51;
		KeyMap[ "period" ] = 52;
		KeyMap[ "slash" ] = 53;
		KeyMap[ "right_shift" ] = 54;
		KeyMap[ "num_star" ] = 55;
		KeyMap[ "alt" ] = 56;
		KeyMap[ "left_menu" ] = 56;
		KeyMap[ "space" ] = 57;
		KeyMap[ "capslock" ] = 58;
		KeyMap[ "f1" ] = 59;
		KeyMap[ "f2" ] = 60;
		KeyMap[ "f3" ] = 61;
		KeyMap[ "f4" ] = 62;
		KeyMap[ "f5" ] = 63;
		KeyMap[ "f6" ] = 64;
		KeyMap[ "f7" ] = 65;
		KeyMap[ "f8" ] = 66;
		KeyMap[ "f9" ] = 67;
		KeyMap[ "f10" ] = 68;
		KeyMap[ "numlock" ] = 69;
		KeyMap[ "scroll_lock" ] = 70;
		KeyMap[ "num_7" ] = 71;
		KeyMap[ "num_8" ] = 72;
		KeyMap[ "num_9" ] = 73;
		KeyMap[ "num_minus" ] = 74;
		KeyMap[ "num_4" ] = 75;
		KeyMap[ "num_5" ] = 76;
		KeyMap[ "num_6" ] = 77;
		KeyMap[ "num_plus" ] = 78;
		KeyMap[ "num_1" ] = 79;
		KeyMap[ "num_2" ] = 80;
		KeyMap[ "num_3" ] = 81;
		KeyMap[ "num_0" ] = 82;
		KeyMap[ "num_period" ] = 83;
		KeyMap[ "oem102" ] = 86;
		KeyMap[ "f11" ] = 87;
		KeyMap[ "f12" ] = 88;
		KeyMap[ "f13" ] = 100;
		KeyMap[ "f14" ] = 101;
		KeyMap[ "f15" ] = 102;
		KeyMap[ "kana" ] = 112;
		KeyMap[ "abnt_c1" ] = 115;
		KeyMap[ "convert" ] = 121;
		KeyMap[ "no_convert" ] = 123;
		KeyMap[ "yen" ] = 125;
		KeyMap[ "abnt_c2" ] = 126;
		KeyMap[ "num_equals" ] = 141;
		KeyMap[ "track_prev" ] = 144;
		KeyMap[ "at" ] = 145;
		KeyMap[ "colon" ] = 146;
		KeyMap[ "underline" ] = 147;
		KeyMap[ "kanji" ] = 148;
		KeyMap[ "stop" ] = 149;
		KeyMap[ "ax" ] = 150;
		KeyMap[ "unlabeled" ] = 151;
		KeyMap[ "track_next" ] = 153;
		KeyMap[ "num_enter" ] = 156;
		KeyMap[ "right_ctrl" ] = 157;
		KeyMap[ "mute" ] = 160;
		KeyMap[ "calculator" ] = 161;
		KeyMap[ "play_pause" ] = 162;
		KeyMap[ "media_stop" ] = 164;
		KeyMap[ "volume_down" ] = 174;
		KeyMap[ "volume_up" ] = 176;
		KeyMap[ "web_home" ] = 178;
		KeyMap[ "num_comma" ] = 179;
		KeyMap[ "num_slash" ] = 181;
		KeyMap[ "print_screen" ] = 183;
		KeyMap[ "right_alt" ] = 184;
		KeyMap[ "menu" ] = 184;
		KeyMap[ "pause" ] = 197;
		KeyMap[ "home" ] = 199;
		KeyMap[ "up" ] = 200;
		KeyMap[ "pgup" ] = 201;
		KeyMap[ "left" ] = 203;
		KeyMap[ "right" ] = 205;
		KeyMap[ "end" ] = 207;
		KeyMap[ "down" ] = 208;
		KeyMap[ "pgdn" ] = 209;
		KeyMap[ "ins" ] = 210;
		KeyMap[ "del" ] = 211;
		KeyMap[ "win" ] = 219;
		KeyMap[ "right_win" ] = 220;
		KeyMap[ "apps" ] = 221;
		KeyMap[ "power" ] = 222;
		KeyMap[ "sleep" ] = 223;
		KeyMap[ "wake" ] = 227;
		KeyMap[ "web_search" ] = 229;
		KeyMap[ "web_favorites" ] = 230;
		KeyMap[ "web_refresh" ] = 231;
		KeyMap[ "web_stop" ] = 232;
		KeyMap[ "web_forward" ] = 233;
		KeyMap[ "web_back" ] = 234;
		KeyMap[ "my_computer" ] = 235;
		KeyMap[ "mail" ] = 236;
		KeyMap[ "media_select" ] = 237;
	}
}


void Saitek::GenerateDefaults( void )
{
	{
		X52ProConfig *config = new X52ProConfig();
		config->Name = "Falcon 4 Joystick";
		Saitek::Configs[ config->Name ] = config;
		
		config->KeyBinds[ "up" ] = "+alt p -alt";
		config->KeyBinds[ "down" ] = "+shift slash -shift";
		config->KeyBinds[ "+click" ] = "+k";
		config->KeyBinds[ "-click" ] = "-k";
		
		config->LEDs[ X52ProLEDNum::Fire ].Conditions.push_back( new LEDCondition( Condition::CautionStoresConfig, LEDColor::On, 2 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::CautionAltitude, LEDColor::Yellow, 8 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::OnGround, LEDColor::Green, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::Off, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::BadAttitude, LEDColor::Yellow, 2 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::CautionAltitude, LEDColor::Yellow, 8 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::OnGround, LEDColor::Green, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::Off, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::BadAttitude, LEDColor::Yellow, 2 ) );
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRLethal, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::GearDown, LEDColor::Green, 0 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::SpeedLT250, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::SpeedLT300, LEDColor::Red, 4 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::SpeedLT350, LEDColor::Red, 2 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::SpeedGT450, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::E ].Conditions.push_back( new LEDCondition( Condition::ChaffEmpty, LEDColor::Red, 2 ) );
		config->LEDs[ X52ProLEDNum::E ].Conditions.push_back( new LEDCondition( Condition::FlareEmpty, LEDColor::Red, 2 ) );
		config->LEDs[ X52ProLEDNum::E ].Conditions.push_back( new LEDCondition( Condition::ChaffLow, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::E ].Conditions.push_back( new LEDCondition( Condition::FlareLow, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::Clutch ].Conditions.push_back( new LEDCondition( Condition::CautionECM, LEDColor::Red, 2 ) );
		config->LEDs[ X52ProLEDNum::Clutch ].Conditions.push_back( new LEDCondition( Condition::ECM, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake99, LEDColor::Green, 8 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake66, LEDColor::Green, 4 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake33, LEDColor::Green, 3 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake, LEDColor::Green, 2 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::OnGround, LEDColor::Green, 0 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::GearDown, LEDColor::Green, 2 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::GearMoving, LEDColor::Green, 8 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T5 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T5 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::Throttle ].Conditions.push_back( new LEDCondition( Condition::FuelEmpty, LEDColor::Off, 0 ) );
		config->LEDs[ X52ProLEDNum::Throttle ].Conditions.push_back( new LEDCondition( Condition::FuelCritical, LEDColor::On, 8 ) );
		config->LEDs[ X52ProLEDNum::Throttle ].Conditions.push_back( new LEDCondition( Condition::FuelLow, LEDColor::On, 4 ) );
		
		X52ProPage *rpm_page = new X52ProPage();
		config->Pages.push_back( rpm_page );
		rpm_page->Texts[ 0 ] = TextType::RPM;
		rpm_page->Texts[ 1 ] = TextType::Nozzle;
		rpm_page->Texts[ 2 ] = TextType::FuelTime;
		
		X52ProPage *heading_page = new X52ProPage();
		config->Pages.push_back( heading_page );
		heading_page->Texts[ 0 ] = TextType::Heading;
		heading_page->Texts[ 1 ] = TextType::Steerpoint;
		heading_page->Texts[ 2 ] = TextType::RWRHeading;
		
		X52ProPage *air_page = new X52ProPage();
		config->Pages.push_back( air_page );
		air_page->Texts[ 0 ] = TextType::IndicatedKnots;
		air_page->Texts[ 1 ] = TextType::GForces;
		air_page->Texts[ 2 ] = TextType::Altitude;
		
		X52ProPage *supply_page = new X52ProPage();
		config->Pages.push_back( supply_page );
		supply_page->Texts[ 0 ] = TextType::FuelExternal;
		supply_page->Texts[ 1 ] = TextType::Chaff;
		supply_page->Texts[ 2 ] = TextType::Flares;
		
		X52ProPage *ded_page = new X52ProPage();
		config->Pages.push_back( ded_page );
		ded_page->Texts[ 0 ] = TextType::DEDLine1;
		ded_page->Texts[ 1 ] = TextType::DEDLine3;
		ded_page->Texts[ 2 ] = TextType::DEDLine5;
		
		X52ProPage *horizon_page = new X52ProPage();
		config->Pages.push_back( horizon_page );
		horizon_page->Texts[ 0 ] = TextType::Horizon1;
		horizon_page->Texts[ 1 ] = TextType::Horizon2;
		horizon_page->Texts[ 2 ] = TextType::Horizon3;
		
		X52ProPage *trim_page = new X52ProPage();
		config->Pages.push_back( trim_page );
		trim_page->Texts[ 0 ] = TextType::PitchTrim;
		trim_page->Texts[ 1 ] = TextType::YawTrim;
		trim_page->Texts[ 2 ] = TextType::RollTrim;
	}

	{
		FIPConfig *config = new FIPConfig();
		config->Name = "Falcon 4 FIP";
		Saitek::Configs[ config->Name ] = config;
		
		config->KeyBinds[ "left_minus" ] = "+shift z -shift";
		config->KeyBinds[ "left_plus" ] = "+shift x -shift";
		config->KeyBinds[ "right_minus" ] = "+ctrl m -ctrl";
		config->KeyBinds[ "right_plus" ] = "+shift m -shift";
		
		FIPPage *status_page = new FIPPage( "Multi" );
		config->Pages.push_back( status_page );
		status_page->Layers.push_back( new FIPImage( ImageType::Attitude, 70, 10, 130, 130 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::RWRSimple, 95, 150, 80, 80 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Gear, 183, 205, 10, 10 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Gear, 175, 220, 10, 10 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Gear, 191, 220, 10, 10 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Airbrake, 70, 200, 20, 30 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::PitchTrim, 210, 10, 36, 75 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::RollTrim, 240, 10, 70, 35 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::YawTrim, 240, 50, 70, 35 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Throttle, 210, 100, 100, 130 ) );
		System::Drawing::Font ^status_font = gcnew System::Drawing::Font( System::Drawing::FontFamily::GenericMonospace, 12.f, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel );
		System::Drawing::Brush ^white_brush = gcnew System::Drawing::SolidBrush( System::Drawing::Color::White );
		status_page->Layers.push_back( new FIPText( TextType::Nozzle, 212, 102, status_font, white_brush ) );
		status_page->Layers.push_back( new FIPText( TextType::RPM, 212, 167, status_font, white_brush ) );
		
		FIPPage *attitude_page = new FIPPage( "Attitude" );
		config->Pages.push_back( attitude_page );
		attitude_page->Layers.push_back( new FIPImage( ImageType::Attitude, 80, 10, 220, 220 ) );
		attitude_page->Layers.push_back( new FIPImage( ImageType::RWRSimple, 270, 190, 47, 47 ) );
		attitude_page->LED.Conditions.push_back( new LEDCondition( Condition::BadAttitude, LEDColor::On, 4 ) );
		
		FIPPage *rwr_page = new FIPPage( "RWR" );
		config->Pages.push_back( rwr_page );
		rwr_page->Layers.push_back( new FIPImage( ImageType::RWRSimple, 80, 10, 220, 220 ) );
		rwr_page->Layers.push_back( new FIPImage( ImageType::TexRWR, 79, 9, 222, 222 ) );
		rwr_page->Layers.push_back( new FIPImage( ImageType::Attitude, 270, 190, 47, 47 ) );
		rwr_page->LED.Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::On, 8 ) );
		rwr_page->LED.Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::On, 2 ) );
		
		FIPPage *ils_page = new FIPPage( "ILS" );
		config->Pages.push_back( ils_page );
		ils_page->Layers.push_back( new FIPImage( ImageType::ILS, 80, 10, 220, 220 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Attitude, 270, 190, 47, 47 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 285, 3, 15, 15 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 270, 35, 15, 15 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 302, 35, 15, 15 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Airbrake, 70, 190, 25, 47 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::OnGround, LEDColor::On, 0 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearMoving, LEDColor::On, 8 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::On, 4 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::On, 4 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDown, LEDColor::On, 2 ) );
		
		FIPPage *mfd1_page = new FIPPage( "MFD1" );
		config->Pages.push_back( mfd1_page );
		mfd1_page->Layers.push_back( new FIPImage( ImageType::TexMFD1, 80, 0, 240, 240 ) );
		
		FIPPage *mfd2_page = new FIPPage( "MFD2" );
		config->Pages.push_back( mfd2_page );
		mfd2_page->Layers.push_back( new FIPImage( ImageType::TexMFD2, 80, 0, 240, 240 ) );
	}
	
	{
		FIPConfig *config = new FIPConfig();
		config->Name = "MFD Extractor Left";
		Saitek::Configs[ config->Name ] = config;
		
		FIPPage *mfd_page = new FIPPage( "" );
		config->Pages.push_back( mfd_page );
		mfd_page->LED.DefaultLook.Color = LEDColor::Off;
		mfd_page->Layers.push_back( new FIPImage( ImageType::TexMFD1, 20, 0, 240, 240 ) );
		mfd_page->KeyBinds[ "s1" ] = "+ctrl +alt num_0 -alt -ctrl";
		mfd_page->KeyBinds[ "s2" ] = "+ctrl +alt num_9 -alt -ctrl";
		mfd_page->KeyBinds[ "s3" ] = "+ctrl +alt num_8 -alt -ctrl";
		mfd_page->KeyBinds[ "s4" ] = "+ctrl +alt num_7 -alt -ctrl";
		mfd_page->KeyBinds[ "s5" ] = "+ctrl +alt num_6 -alt -ctrl";
		mfd_page->KeyBinds[ "s6" ] = "+ctrl +alt num_5 -alt -ctrl";
		mfd_page->KeyBinds[ "left_minus" ] = "+ctrl +alt num_4 -alt -ctrl";
		mfd_page->KeyBinds[ "left_plus" ] = "+ctrl +alt num_3 -alt -ctrl";
		mfd_page->KeyBinds[ "right_minus" ] = "+ctrl +alt num_2 -alt -ctrl";
		mfd_page->KeyBinds[ "right_plus" ] = "+ctrl +alt num_1 -alt -ctrl";
	}
	
	{
		FIPConfig *config = new FIPConfig();
		config->Name = "MFD Extractor Right";
		Saitek::Configs[ config->Name ] = config;
		
		FIPPage *mfd_page = new FIPPage( "" );
		config->Pages.push_back( mfd_page );
		mfd_page->LED.DefaultLook.Color = LEDColor::Off;
		mfd_page->Layers.push_back( new FIPImage( ImageType::TexMFD2, 20, 0, 240, 240 ) );
		mfd_page->KeyBinds[ "s1" ] = "+shift +alt num_0 -alt -shift";
		mfd_page->KeyBinds[ "s2" ] = "+shift +alt num_9 -alt -shift";
		mfd_page->KeyBinds[ "s3" ] = "+shift +alt num_8 -alt -shift";
		mfd_page->KeyBinds[ "s4" ] = "+shift +alt num_7 -alt -shift";
		mfd_page->KeyBinds[ "s5" ] = "+shift +alt num_6 -alt -shift";
		mfd_page->KeyBinds[ "s6" ] = "+shift +alt num_5 -alt -shift";
		mfd_page->KeyBinds[ "left_minus" ] = "+shift +alt num_4 -alt -shift";
		mfd_page->KeyBinds[ "left_plus" ] = "+shift +alt num_3 -alt -shift";
		mfd_page->KeyBinds[ "right_minus" ] = "+shift +alt num_2 -alt -shift";
		mfd_page->KeyBinds[ "right_plus" ] = "+shift +alt num_1 -alt -shift";
	}
	
	{
		FIPConfig *config = new FIPConfig();
		config->Name = "Screen FIP";
		Saitek::Configs[ config->Name ] = config;
		
		FIPPage *screen_page = new FIPPage( "" );
		config->Pages.push_back( screen_page );
		screen_page->Layers.push_back( new FIPImage( ImageType::ScreenCopy, 0, 0, 320, 240 ) );
		
		FIPPage *center1_page = new FIPPage( "" );
		config->Pages.push_back( center1_page );
		center1_page->Layers.push_back( new FIPImage( ImageType::ScreenCenter, 0, 0, 320, 240 ) );
		
		FIPPage *center2_page = new FIPPage( "" );
		config->Pages.push_back( center2_page );
		center2_page->Layers.push_back( new FIPImage( ImageType::ScreenCenterZoomed, 0, 0, 320, 240 ) );
		
		FIPPage *cursor1_page = new FIPPage( "" );
		config->Pages.push_back( cursor1_page );
		cursor1_page->Layers.push_back( new FIPImage( ImageType::ScreenCursor, 0, 0, 320, 240 ) );
		
		FIPPage *cursor2_page = new FIPPage( "" );
		config->Pages.push_back( cursor2_page );
		cursor2_page->Layers.push_back( new FIPImage( ImageType::ScreenCursorZoomed, 0, 0, 320, 240 ) );
		
		FIPPage *tex_page = new FIPPage( "" );
		config->Pages.push_back( tex_page );
		tex_page->Layers.push_back( new FIPImage( ImageType::Tex, 0, 0, 320, 240 ) );
		tex_page->LED.DefaultLook.Color = LEDColor::Off;
		tex_page->LED.Conditions.push_back( new LEDCondition( Condition::RWRContact, LEDColor::On, 0 ) );
	}
}


void Saitek::LoadConfigs( void )
{
	if( DIR *dir_p = opendir("Configs") )
	{
		while( struct dirent *dir_entry_p = readdir(dir_p) )
		{
			if( ! dir_entry_p->d_name )
				continue;
			if( dir_entry_p->d_name[ 0 ] == '.' )
				continue;
			
			int len = strlen(dir_entry_p->d_name);
			if( (len >= 4) && (strcmp( dir_entry_p->d_name + len - 4, ".cfg" ) == 0) )
			{
				std::string name( dir_entry_p->d_name, len - 4 );
				LoadConfig( name );
			}
		}
		
		closedir( dir_p );
	}
	
	if( ! Saitek::Configs.size() )
		GenerateDefaults();
	
	Saitek::MainThread->Config.Load();
	
	Saitek::ConfigsChanged = true;
}

void Saitek::LoadConfig( std::string name )
{
	std::string guid;
	
	std::string filename = std::string("Configs\\") + name + std::string(".cfg");
	std::ifstream config_file( filename.c_str() );
	if( ! config_file.good() )
	{
		System::Windows::Forms::MessageBox::Show( "Couldn't load: " + gcnew System::String(filename.c_str()), "Couldn't Load Settings", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error );
		return;
	}

	while( config_file.good() )
	{
		char line[ 1024 ] = "";
		config_file.getline( line, 1023 );
		
		if( strncmp( line, "device ", strlen("device ") ) == 0 )
		{
			guid = std::string( line + strlen("device ") );
			break;
		}
	}

	config_file.close();
	
	DeviceConfig *config = Saitek::NewConfig( guid );
	if( config )
	{
		config->Name = name;
		config->Load();
		Saitek::Configs[ name ] = config;
	}
}

DeviceConfig *Saitek::NewConfig( std::string guid )
{
	if( guid == "29DAD506-F93B-4F20-85FA-1E02C04FAC17" )
		return new X52ProConfig();
	if( guid == "3E083CD8-6A37-4A58-80A8-3D6A2C07513E" )
		return new FIPConfig();
	return NULL;
}


void Saitek::SaveConfigs( void )
{
	for( std::map< std::string, DeviceConfig* >::iterator config_iter = Saitek::Configs.begin(); config_iter != Saitek::Configs.end(); config_iter ++ )
	{
		config_iter->second->Save();
	}
	
	Saitek::MainThread->Config.Save();
}


void Saitek::Initialize( void )
{
	using namespace System::Windows::Forms;

	if( ! Initialized )
	{
		HRESULT result = DO.Initialize( L"Raptor007's Falcon 4 to Saitek Utility" );
		if( SUCCEEDED(result) )
			Initialized = true;
		else
			MessageBox::Show( "Failed to initialize DirectOutput!\nTry reinstalling your Saitek device drivers.", "Saitek DirectOutput Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
	}

	if( Initialized )
	{
		if( ! Instances.size() )
		{
			// Find out what devices are attached.
			Saitek::DO.Enumerate( &(Saitek::EnumerateCallback), NULL );
		}

		// Configure the callback function for Saitek device add/remove.
		Saitek::DO.RegisterDeviceCallback( &(Saitek::DeviceChange), NULL );
	}
}

void Saitek::Deinitialize( void )
{
	if( Initialized )
	{
		for( std::vector<DeviceInstance*>::iterator inst_iter = Instances.begin(); inst_iter != Instances.end(); inst_iter ++ )
		{
			delete *inst_iter;
			*inst_iter = NULL;
		}
		Instances.clear();
		
		DO.Deinitialize();
		Initialized = false;
	}
}

void __stdcall Saitek::EnumerateCallback( void *device, void *ctxt )
{
	DeviceChange( device, true, ctxt );
}

void __stdcall Saitek::DeviceChange( void *device, bool added, void *ctxt )
{
	// See if the device was already in our list.
	std::vector<DeviceInstance*>::iterator found = Saitek::Instances.end();
	for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
		if( (*inst_iter)->SaitekDevice == device )
		{
			found = inst_iter;
			break;
		}

	if( added )
	{
		// Just added a DirectOutput device.

		if( found == Saitek::Instances.end() )
		{
			DeviceInstance *dev_inst = NULL;
			GUID guid;
			Saitek::DO.GetDeviceType( device, &guid );
			
			DeviceConfig *config = NULL;
			for( std::map<std::string,DeviceConfig*>::iterator cfg_iter = Saitek::Configs.begin(); cfg_iter != Saitek::Configs.end(); cfg_iter ++ )
			{
				if( cfg_iter->second->Guid == guid )
				{
					config = cfg_iter->second;
					break;
				}
			}
			
			if( guid == DeviceType_X52Pro )
				dev_inst = new X52ProInstance( device, (X52ProConfig*) config );
			else if( guid == DeviceType_Fip )
				dev_inst = new FIPInstance( device, (FIPConfig*) config );
			else
				dev_inst = new DeviceInstance( device, config, guid );
			
			Saitek::InstancesLock->WaitOne();
			Saitek::Instances.push_back( dev_inst );
			Saitek::InstancesChanged = true;
			Saitek::InstancesLock->ReleaseMutex();
		}
	}
	else if( found != Saitek::Instances.end() )
	{
		// Just removed a DirectOutput device.

		Saitek::InstancesLock->WaitOne();
		delete *found;
		Saitek::Instances.erase( found );
		Saitek::InstancesChanged = true;
		Saitek::InstancesLock->ReleaseMutex();
	}
}

void __stdcall Saitek::PageChange( void *device, DWORD page_num, bool active, void *instance_ptr )
{
	DeviceInstance *instance = (DeviceInstance*) instance_ptr;
	if( active && (instance->Guid == DeviceType_X52Pro) )
		((X52ProInstance*)instance)->SelectedPage = page_num;
}

void __stdcall Saitek::SoftButtonChange( void *device, DWORD buttons, void *instance_ptr )
{
	DeviceInstance *instance = (DeviceInstance*) instance_ptr;
	instance->ChangeButtons( buttons );
}


void Saitek::RestartService( void )
{
	Deinitialize();
	system( "net stop SaiDOutput" );
	system( "net start SaiDOutput" );
	Initialize();
}
