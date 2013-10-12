#include "X52Pro.h"
#include "Saitek.h"
#include "FalconOutput.h"
#include "X52ProConfigForm.h"
#include "Str.h"
#include <fstream>


X52ProInstance::X52ProInstance( void *saitek_device, X52ProConfig *config ) : DeviceInstance( saitek_device, config, DeviceType_X52Pro )
{
	SelectedPage = 0;
}

X52ProInstance::~X52ProInstance()
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
	
	size_t page_count = Config->Pages.size();
	if( ! page_count )
		page_count = 1;
	
	for( size_t page_num = 0; page_num < page_count; page_num ++ )
	{
		DWORD flags = 0;
		if( page_num == SelectedPage )
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

void X52ProInstance::Update( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, double total_time )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	X52ProConfig *Config = (X52ProConfig *) this->Config;
	
	size_t page_count = Config->Pages.size();
	if( ! page_count )
		page_count = 1;
	
	for( size_t page_num = 0; page_num < page_count; page_num ++ )
	{
		for( int led = 0; led < 11; led ++ )
			Config->LEDs[ led ].ApplyLook( fd, total_time, SaitekDevice, page_num );

		if( page_num < Config->Pages.size() )
		{
			X52ProPage *page = Config->Pages[ page_num ];
			for( int line = 0; line < 3; line ++ )
			{
				wchar_t buffer[ 32 ] = L"";
				memset( buffer, 0, 32*sizeof(wchar_t) );
				Saitek::Output.FormatText( fd, page->Texts[ line ], total_time, SaitekDevice, buffer, 32 );
				Saitek::DO.SetString( SaitekDevice, page_num, line, wcslen(buffer), buffer );
			}
		}
		else
		{
			for( int line = 0; line < 3; line ++ )
				Saitek::DO.SetString( SaitekDevice, page_num, line, wcslen(L""), L"" );
		}
	}
}

void X52ProInstance::ChangedButton( DWORD button, bool state )
{
	std::string button_name;
	if( button == SoftButton_Select )
		button_name = "click";
	else if( button == SoftButton_Down )
		button_name = "down";
	else if( button == SoftButton_Up )
		button_name = "up";
	
	// Determine the binds to search for.
	std::vector<std::string> button_names;
	if( button_name.length() )
	{
		if( state )
		{
			button_names.push_back( button_name );
			button_names.push_back( std::string("+") + button_name );
		}
		else
			button_names.push_back( std::string("-") + button_name );
	}
	
	// Loop through all button events to see if any are bound to key events.
	for( std::vector<std::string>::iterator name_iter = button_names.begin(); name_iter != button_names.end(); name_iter ++ )
	{
		std::string bind;
		
		// See if this button is bound for this page.
		std::map<std::string,std::string>::iterator bind_find = ((X52ProConfig*)Config)->Pages[SelectedPage]->KeyBinds.find( *name_iter );
		if( bind_find != ((X52ProConfig*)Config)->Pages[SelectedPage]->KeyBinds.end() )
			bind = bind_find->second;
		else
		{
			// See if this button is bound for this device.
			std::map<std::string,std::string>::iterator bind_find = Config->KeyBinds.find( *name_iter );
			if( bind_find != Config->KeyBinds.end() )
				bind = bind_find->second;
		}
		
		if( bind.length() )
		{
			// Split to a vector of strings, one per key event.
			std::vector<std::string> binds = Str::SplitToVector( bind.c_str(), " " );
			for( std::vector<std::string>::iterator bind_iter = binds.begin(); bind_iter != binds.end(); bind_iter ++ )
			{
				// Determine if this is a hold/release event or a quick press.
				char bind_prefix = (*bind_iter)[ 0 ];
				if( (bind_prefix != '+') && (bind_prefix != '-') )
					bind_prefix = 0;
				
				// Get the keyname.
				std::string bind = (bind_prefix ? (*bind_iter).substr(1) : *bind_iter);
				
				// Determine the key's scancode.
				WORD scancode = 0;
				if( bind[ 0 ] == '#' )
				{
					// Use raw numeric value as scancode.
					scancode = atoi( bind.substr(1).c_str() );
				}
				else
				{
					// Look up the scancode in the keymap.
					std::map<std::string,WORD>::iterator key_find = Saitek::KeyMap.find(bind);
					if( key_find != Saitek::KeyMap.end() )
						scancode = key_find->second;
				}
				
				// If we have a valid scancode, send the key events.
				if( scancode )
				{
					// This structure will be used to create the keyboard input event.
					INPUT ip;
					
					// Set up a generic keyboard event.
					ip.type = INPUT_KEYBOARD;
					ip.ki.wVk = 0;
					ip.ki.wScan = 0;
					ip.ki.time = 0;
					ip.ki.dwExtraInfo = 0;
					
					// Get the scancode.
					ip.ki.wScan = scancode;
					
					if( bind_prefix != '-' )
					{
						// Press the key.
						ip.ki.dwFlags = KEYEVENTF_SCANCODE;
						SendInput( 1, &ip, sizeof(INPUT) );
					}
					
					if( bind_prefix != '+' )
					{
						// Release the key.
						ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
						SendInput( 1, &ip, sizeof(INPUT) );
					}
				}
			}
		}
	}
}

void X52ProInstance::RegisterCallbacks( void )
{
	DeviceInstance::RegisterCallbacks();
	Saitek::DO.RegisterPageCallback( SaitekDevice, &(Saitek::PageChange), this );
}

void X52ProInstance::UnregisterCallbacks( void )
{
	DeviceInstance::UnregisterCallbacks();
	Saitek::DO.RegisterPageCallback( SaitekDevice, NULL, this );
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

X52ProConfig::~X52ProConfig()
{
	Clear();
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
	
	Name = "X52 Pro";
	
	Clear();
}


void X52ProConfig::Clear( void )
{
	DeviceConfig::Clear();
	
	SleepMs = 100;
	
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
	
	for( std::vector<X52ProPage*>::iterator page_iter = Pages.begin(); page_iter != Pages.end(); page_iter ++ )
	{
		delete *page_iter;
		*page_iter = NULL;
	}
	
	Pages.clear();
}


void X52ProConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
	DeviceConfig::LoadLine( cmd_tokens );
	
	if( ! cmd_tokens.size() )
		return;
	
	std::string cmd = cmd_tokens[ 0 ];
	
	if( (cmd == "led") && (cmd_tokens.size() >= 5) )
	{
		std::string name = cmd_tokens[ 1 ];
		int num = atoi( name.c_str() );
		std::string condition_name = cmd_tokens[ 2 ];
		int condition = Saitek::Output.GetCondition( condition_name );
		std::string color_name = cmd_tokens[ 3 ];
		int color = LEDColor::Off;
		double blink_rate = atof( cmd_tokens[ 4 ].c_str() );
		
		if( name == "fire" )
			num = X52ProLEDNum::Fire;
		else if( name == "a" )
			num = X52ProLEDNum::A;
		else if( name == "b" )
			num = X52ProLEDNum::B;
		else if( name == "hat2" )
			num = X52ProLEDNum::Hat2;
		else if( name == "t1" )
			num = X52ProLEDNum::T1;
		else if( name == "t3" )
			num = X52ProLEDNum::T3;
		else if( name == "t5" )
			num = X52ProLEDNum::T5;
		else if( name == "d" )
			num = X52ProLEDNum::D;
		else if( name == "e" )
			num = X52ProLEDNum::E;
		else if( name == "clutch" )
			num = X52ProLEDNum::Clutch;
		else if( name == "throttle" )
			num = X52ProLEDNum::Throttle;
		
		if( color_name == "green" )
			color = LEDColor::Green;
		else if( color_name == "yellow" )
			color = LEDColor::Yellow;
		else if( color_name == "red" )
			color = LEDColor::Red;
		else if( color_name == "on" )
			color = LEDColor::On;
		else if( color_name == "off" )
			color = LEDColor::Off;
		
		if( condition_name == "default" )
		{
			LEDs[ num ].DefaultLook.Color = color;
			LEDs[ num ].DefaultLook.BlinkRate = blink_rate;
		}
		else
			LEDs[ num ].Conditions.push_back( new LEDCondition( condition, color, blink_rate ) );
	}
	else if( (cmd == "mfd") && (cmd_tokens.size() >= 4) )
	{
		int page = atoi( cmd_tokens[ 1 ].c_str() ) - 1;
		
		while( (int) Pages.size() <= page )
			Pages.push_back( new X52ProPage() );
		
		if( (cmd_tokens[ 2 ] == "bind") && (cmd_tokens.size() >= 5) )
			Pages[ page ]->KeyBinds[ cmd_tokens[3] ] = cmd_tokens[ 4 ];
		else
		{
			int line = atoi( cmd_tokens[ 2 ].c_str() ) - 1;
			int text = Saitek::Output.GetTextType( cmd_tokens[ 3 ] );
			
			Pages[ page ]->Texts[ line ] = text;
		}
	}
}


void X52ProConfig::SaveLines( FILE *config_file )
{
	DeviceConfig::SaveLines( config_file );
	
	
	// Save LEDs.
	
	for( int i = 0; i < X52ProLEDNum::NUM; i ++ )
	{
		const char *led_name = "unknown", *color = "off";
		
		
		// Get LED name.
		
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
		
		
		// Save LED conditions.
		
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
		
		
		// Save default LED look.
		
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
		
		fprintf( config_file, "led %s default %s %.0f\n\n", led_name, color, LEDs[ i ].DefaultLook.BlinkRate );
	}
	
	
	// Save MFD pages.
	
	for( size_t i = 0; i < Pages.size(); i ++ )
	{
		for( int j = 0; j < 3; j ++ )
		{
			std::string text = Saitek::Output.GetTextName( Pages[ i ]->Texts[ j ] );
			
			fprintf( config_file, "mfd %i %i %s\n", i + 1, j + 1, text.c_str() );
		}
		
		for( std::map<std::string,std::string>::iterator bind_iter = Pages[ i ]->KeyBinds.begin(); bind_iter != Pages[ i ]->KeyBinds.end(); bind_iter ++ )
			fprintf( config_file, "mfd %i bind \"%s\" \"%s\"\n", i + 1, bind_iter->first.c_str(), bind_iter->second.c_str() );
		
		fprintf( config_file, "\n" );
	}
}

/*
void X52ProConfig::ShowEditWindow( void )
{
	Raptor007sFalcon4toSaitekUtility::X52ProConfigForm ^edit_window = gcnew Raptor007sFalcon4toSaitekUtility::X52ProConfigForm();
	edit_window->Show();
}
*/


X52ProPage::X52ProPage( void )
{
	for( int i = 0; i < 3; i ++ )
		Texts[ i ] = TextType::Nothing;
}

X52ProPage::~X52ProPage()
{
}
