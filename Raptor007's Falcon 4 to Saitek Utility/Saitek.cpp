#include "stdafx.h"
#include "Saitek.h"
#include <cstdio>
#include <cstdlib>
#include <map>
#include "FalconOutput.h"
#include "Device.h"
#include "X52Pro.h"
#include "FIP.h"

namespace Saitek
{
	FalconOutput Output;
	
	CDirectOutput DO;
	bool Initialized = false;
	
	std::vector<DeviceInstance*> Instances;
	msclr::auto_gcroot<System::Threading::Mutex^> InstancesLock = gcnew System::Threading::Mutex( false );
	bool InstancesChanged;
	
	std::map<std::string, DeviceConfig*> Configs;
	
	msclr::auto_gcroot<FalconThread^> MainThread = gcnew FalconThread();
}


void Saitek::GenerateDefaults( void )
{
	{
		X52ProConfig *config = new X52ProConfig();
		config->Name = "Falcon 4 Joystick";
		Saitek::Configs[ config->Name ] = config;
		
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::Hat2 ].Conditions.push_back( new LEDCondition( Condition::RWRLethal, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::A ].Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::Off, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::Red, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::B ].Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::Off, 0 ) );
		config->LEDs[ X52ProLEDNum::D ].Conditions.push_back( new LEDCondition( Condition::BadAttitude, LEDColor::Red, 4 ) );
		config->LEDs[ X52ProLEDNum::Clutch ].Conditions.push_back( new LEDCondition( Condition::ECM, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake99, LEDColor::Green, 8 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake66, LEDColor::Green, 4 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake33, LEDColor::Green, 3 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::AirBrake, LEDColor::Green, 2 ) );
		config->LEDs[ X52ProLEDNum::T1 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::GearDown, LEDColor::Green, 2 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::GearMoving, LEDColor::Green, 8 ) );
		config->LEDs[ X52ProLEDNum::T3 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		config->LEDs[ X52ProLEDNum::T5 ].Conditions.push_back( new LEDCondition( Condition::CautionOil, LEDColor::Red, 8 ) );
		config->LEDs[ X52ProLEDNum::T5 ].Conditions.push_back( new LEDCondition( Condition::CautionMaster, LEDColor::Yellow, 0 ) );
		
		X52ProPage *page1 = new X52ProPage();
		config->Pages.push_back( page1 );
		page1->Texts[ 0 ] = TextType::Altitude;
		page1->Texts[ 1 ] = TextType::RPM;
		page1->Texts[ 2 ] = TextType::Fuel;
		
		X52ProPage *page2 = new X52ProPage();
		config->Pages.push_back( page2 );
		page2->Texts[ 0 ] = TextType::DEDLine1;
		page2->Texts[ 1 ] = TextType::DEDLine2;
		page2->Texts[ 2 ] = TextType::DEDLine3;
		
		X52ProPage *page3 = new X52ProPage();
		config->Pages.push_back( page3 );
		page3->Texts[ 0 ] = TextType::DEDLine4;
		page3->Texts[ 1 ] = TextType::DEDLine5;
		page3->Texts[ 2 ] = TextType::RunTime;
	}

	{
		FIPConfig *config = new FIPConfig();
		config->Name = "Falcon 4 FIP";
		Saitek::Configs[ config->Name ] = config;
		
		FIPPage *status_page = new FIPPage( "Status" );
		config->Pages.push_back( status_page );
		status_page->Layers.push_back( new FIPImage( ImageType::RollTrim, 140, 10, 110, 50 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::YawTrim, 140, 70, 110, 50 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::PitchTrim, 260, 10, 50, 110 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Throttle, 140, 140, 110, 90 ) );
		System::Drawing::Font ^status_font = gcnew System::Drawing::Font( System::Drawing::FontFamily::GenericMonospace, 12.f, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel );
		System::Drawing::Brush ^white_brush = gcnew System::Drawing::SolidBrush( System::Drawing::Color::White );
		status_page->Layers.push_back( new FIPText( TextType::Nozzle, 143, 143, status_font, white_brush ) );
		status_page->Layers.push_back( new FIPText( TextType::RPM, 143, 188, status_font, white_brush ) );
		status_page->Layers.push_back( new FIPImage( ImageType::Attitude, 270, 137, 47, 47 ) );
		status_page->Layers.push_back( new FIPImage( ImageType::SimpleRWR, 270, 190, 47, 47 ) );
		
		FIPPage *attitude_page = new FIPPage( "Attitude" );
		config->Pages.push_back( attitude_page );
		attitude_page->Layers.push_back( new FIPImage( ImageType::Attitude, 80, 10, 220, 220 ) );
		attitude_page->Layers.push_back( new FIPImage( ImageType::SimpleRWR, 270, 190, 47, 47 ) );
		attitude_page->LED.Conditions.push_back( new LEDCondition( Condition::BadAttitude, LEDColor::On, 4 ) );
		
		FIPPage *rwr_page = new FIPPage( "Simple RWR" );
		config->Pages.push_back( rwr_page );
		rwr_page->Layers.push_back( new FIPImage( ImageType::SimpleRWR, 80, 10, 220, 220 ) );
		rwr_page->Layers.push_back( new FIPImage( ImageType::Attitude, 270, 190, 47, 47 ) );
		rwr_page->LED.Conditions.push_back( new LEDCondition( Condition::RWRMissile, LEDColor::On, 8 ) );
		rwr_page->LED.Conditions.push_back( new LEDCondition( Condition::RWRLock, LEDColor::On, 2 ) );
		
		FIPPage *ils_page = new FIPPage( "ILS" );
		config->Pages.push_back( ils_page );
		ils_page->Layers.push_back( new FIPImage( ImageType::ILS, 80, 10, 220, 220 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Attitude, 270, 190, 47, 47 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 287, 3, 11, 11 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 270, 39, 11, 11 ) );
		ils_page->Layers.push_back( new FIPImage( ImageType::Gear, 306, 39, 11, 11 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDownAOAAbove, LEDColor::On, 8 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDownAOABelow, LEDColor::On, 8 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearDown, LEDColor::On, 2 ) );
		ils_page->LED.Conditions.push_back( new LEDCondition( Condition::GearMoving, LEDColor::On, 4 ) );
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
	}
}


void Saitek::LoadConfigs( void )
{
	// FIXME
	GenerateDefaults();
}


void Saitek::SaveConfigs( void )
{
	for( std::map< std::string, DeviceConfig* >::iterator config_iter = Saitek::Configs.begin(); config_iter != Saitek::Configs.end(); config_iter ++ )
	{
		config_iter->second->Save();
	}
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
		// FIXME: Memory cleanup!
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
}

void __stdcall Saitek::SoftButtonChange( void *device, DWORD buttons, void *instance_ptr )
{
	DeviceInstance *instance = (DeviceInstance*) instance_ptr;
	if( instance->Guid == DeviceType_Fip )
	{
		if( buttons & SoftButton_1 )
			((FIPInstance*)( instance ))->SetPage( 0 );
		else if( buttons & SoftButton_2 )
			((FIPInstance*)( instance ))->SetPage( 1 );
		else if( buttons & SoftButton_3 )
			((FIPInstance*)( instance ))->SetPage( 2 );
		else if( buttons & SoftButton_4 )
			((FIPInstance*)( instance ))->SetPage( 3 );
		else if( buttons & SoftButton_5 )
			((FIPInstance*)( instance ))->SetPage( 4 );
		else if( buttons & SoftButton_6 )
			((FIPInstance*)( instance ))->SetPage( 5 );
	}
}


void Saitek::RestartService( void )
{
	Deinitialize();
	system( "net stop SaiDOutput" );
	system( "net start SaiDOutput" );
	Initialize();
}
