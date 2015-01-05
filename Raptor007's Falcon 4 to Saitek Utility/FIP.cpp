#include "FIP.h"
#include <cstdlib>
#include <cmath>
#include "Saitek.h"
#include "FalconOutput.h"
#include "Str.h"
#include <windows.h>


FIPInstance::FIPInstance( void *saitek_device, FIPConfig *config ) : DeviceInstance( saitek_device, config, DeviceType_Fip )
{
}

FIPInstance::~FIPInstance()
{
}

const char *FIPInstance::TypeString( void )
{
	return "FIP";
}

void FIPInstance::Begin( void )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	FIPConfig *Config = (FIPConfig *) this->Config;
	
	Saitek::DO.AddPage( SaitekDevice, 0, NULL, FLAG_SET_AS_ACTIVE );
	Saitek::DO.SetImage( SaitekDevice, 0, 0, 0, NULL );
	
	for( int led = 0; led < 7; led ++ )
	{
		Saitek::DO.SetLed( SaitekDevice, 0, led, 1 );
		Saitek::DO.SetLed( SaitekDevice, 0, led, 0 );
		LEDState[ 0 ][ led ] = false;
	}
	
	RegisterCallbacks();
}

void FIPInstance::End( void )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	FIPConfig *Config = (FIPConfig *) this->Config;

	Saitek::DO.SetImage( SaitekDevice, 0, 0, 0, NULL );
	Saitek::DO.RemovePage( SaitekDevice, 0 );

	UnregisterCallbacks();
}

void FIPInstance::Update( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, double total_time )
{
	if(!( SaitekDevice && Config && Saitek::Initialized ))
		return;
	FIPConfig *Config = (FIPConfig *) this->Config;
	
	using namespace System::Drawing;
	Graphics ^gfx = Bmp.GetGraphics();
	gfx->Clear( Color::Black );
	
	// Draw the currently-selected page.
	if( (SelectedPage >= 0) && (SelectedPage < (int) Config->Pages.size()) )
	{
		FIPPage *page = Config->Pages.at( SelectedPage );

		// Draw all layers.
		for( std::vector<FIPLayer*>::iterator layer_iter = page->Layers.begin(); layer_iter != page->Layers.end(); layer_iter ++ )
			(*layer_iter)->Draw( fd, tex, gfx, total_time, SaitekDevice );
	}
	
	// Draw button labels.
	Brush ^label_brush = Saitek::Output.DrawTools[SaitekDevice].GetBrush( Color::LightGray );
	Brush ^selected_label_brush = Saitek::Output.DrawTools[SaitekDevice].GetBrush( Color::White );
	Font ^label_font = Saitek::Output.DrawTools[SaitekDevice].GetFont( FontFamily::GenericSansSerif, 11, FontStyle::Regular );
	Font ^selected_label_font = Saitek::Output.DrawTools[SaitekDevice].GetFont( FontFamily::GenericSansSerif, 11, FontStyle::Bold );
	for( size_t page_num = 0; page_num < Config->Pages.size(); page_num ++ )
	{
		FIPPage *page = Config->Pages.at( page_num );
		Brush ^brush = label_brush;
		Font ^font = label_font;
		if( page_num == SelectedPage )
		{
			brush = selected_label_brush;
			font = selected_label_font;
		}
		gfx->DrawString( gcnew System::String( page->Label.c_str() ), font, brush, 2.f, 3.f + page_num * 44 );

		// Set LED status based on each page.
		if( page_num < 6 )
		{
			page->LED.SetIndices( page_num + 1, -1 );
			page->LED.ApplyLook( fd, total_time, this, 0 );
		}
	}
	
	// Set other LEDs.
	for( int led = Config->Pages.size() + 1; led <= 6; led ++ )
		SetLED( 0, led, false );
	
	// Update the FIP image display.
	Saitek::DO.SetImage( SaitekDevice, 0, 0, 320*240*3, Bmp.GetBuffer() );
}

void FIPInstance::ChangedButton( DWORD button, bool state )
{
	std::string button_name;
	int goto_page = -1;
	bool skip_release_event = false;
	
	if( button == SoftButton_1 )
	{
		button_name = "s1";
		if( state ){ goto_page = 0; skip_release_event = true; }
	}
	else if( button == SoftButton_2 )
	{
		button_name = "s2";
		if( state ){ goto_page = 1; skip_release_event = true; }
	}
	else if( button == SoftButton_3 )
	{
		button_name = "s3";
		if( state ){ goto_page = 2; skip_release_event = true; }
	}
	else if( button == SoftButton_4 )
	{
		button_name = "s4";
		if( state ){ goto_page = 3; skip_release_event = true; }
	}
	else if( button == SoftButton_5 )
	{
		button_name = "s5";
		if( state ){ goto_page = 4; skip_release_event = true; }
	}
	else if( button == SoftButton_6 )
	{
		button_name = "s6";
		if( state ){ goto_page = 5; skip_release_event = true; }
	}
	else if( button == SoftButton_Right )
		button_name = "left_minus";
	else if( button == SoftButton_Left )
		button_name = "left_plus";
	else if( button == SoftButton_Down )
		button_name = "right_minus";
	else if( button == SoftButton_Up )
		button_name = "right_plus";
	
	// Initially assume the button event will be a page change.
	bool found_bind = false;
	
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
		bool bind_found = false;
		
		// See if this button is bound for this page.
		std::map<std::string,std::string>::iterator bind_find = ((FIPConfig*)Config)->Pages[SelectedPage]->KeyBinds.find( *name_iter );
		if( bind_find != ((FIPConfig*)Config)->Pages[SelectedPage]->KeyBinds.end() )
		{
			bind = bind_find->second;
			bind_found = true;
		}
		else
		{
			// See if this button is bound for this device.
			bind_find = Config->KeyBinds.find( *name_iter );
			if( bind_find != Config->KeyBinds.end() )
			{
				bind = bind_find->second;
				bind_found = true;
			}
		}
		
		if( bind_found )
		{
			// If this button is bound to key events, don't change pages.
			goto_page = -1;
			
			// If we do anything with +button, don't ignore -button, even if the page changes.
			if( (*name_iter)[ 0 ] == '+' )
				skip_release_event = false;
			
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
				else if( bind[ 0 ] == '@' )
				{
					// Go to the page specified.
					goto_page = atoi( bind.substr(1).c_str() ) - 1;
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
	
	if( goto_page >= 0 )
	{
		int prev_page = SelectedPage;
		
		SetPage( goto_page );
		
		// If we changed pages, we might want to ignore the button-up event that follows.
		if( skip_release_event && (SelectedPage != prev_page) )
			Buttons ^= button;
	}
}

void FIPInstance::SetPage( int page )
{
	if( Config && ( page < (int) ((FIPConfig*)( Config ))->Pages.size() ) )
		SelectedPage = page;
}


FIPConfig::FIPConfig( void ) : DeviceConfig( DeviceType_Fip )
{
	Name = "My FIP Config";
	SleepMs = 10;
}

FIPConfig::~FIPConfig()
{
	Clear();
}

const char *FIPConfig::TypeString( void )
{
	return "FIP";
}

void FIPConfig::Clear( void )
{
	DeviceConfig::Clear();
	
	for( std::vector<FIPPage*>::iterator page_iter = Pages.begin(); page_iter != Pages.end(); page_iter ++ )
	{
		delete *page_iter;
		*page_iter = NULL;
	}
	
	Pages.clear();
}

void FIPConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
	DeviceConfig::LoadLine( cmd_tokens );
	
	if( cmd_tokens.size() < 3 )
		return;
	if( cmd_tokens[ 0 ] != "screen" )
		return;
	
	int screen = atoi( cmd_tokens[ 1 ].c_str() ) - 1;
	if( screen < 0 )
		return;
	
	std::string cmd = cmd_tokens[ 2 ];
	
	while( (int) Pages.size() <= screen )
		Pages.push_back( new FIPPage("") );
	
	if( (cmd == "label") && (cmd_tokens.size() >= 4) )
	{
		Pages[ screen ]->Label = cmd_tokens[ 3 ];
	}
	else if( (cmd == "led") && (cmd_tokens.size() >= 6) )
	{
		std::string condition_name = cmd_tokens[ 3 ];
		int condition = Saitek::Output.GetCondition( condition_name );
		std::string color_name = cmd_tokens[ 4 ];
		int color = LEDColor::Off;
		double blink_rate = atof( cmd_tokens[ 5 ].c_str() );
		
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
			Pages[ screen ]->LED.DefaultLook.Color = color;
			Pages[ screen ]->LED.DefaultLook.BlinkRate = blink_rate;
		}
		else
			Pages[ screen ]->LED.Conditions.push_back( new LEDCondition( condition, color, blink_rate ) );
	}
	else if( (cmd == "image") && (cmd_tokens.size() >= 8) )
	{
		int image = Saitek::Output.GetImageType( cmd_tokens[ 3 ] );
		int x = atoi( cmd_tokens[ 4 ].c_str() );
		int y = atoi( cmd_tokens[ 5 ].c_str() );
		int w = atoi( cmd_tokens[ 6 ].c_str() );
		int h = atoi( cmd_tokens[ 7 ].c_str() );
		
		Pages[ screen ]->Layers.push_back( new FIPImage( image, x, y, w, h ) );
	}
	else if( (cmd == "text") && (cmd_tokens.size() >= 6) )
	{
		// FIXME: Allow variable fonts.
		
		int text = Saitek::Output.GetTextType( cmd_tokens[ 3 ] );
		int x = atoi( cmd_tokens[ 4 ].c_str() );
		int y = atoi( cmd_tokens[ 5 ].c_str() );
		
		Pages[ screen ]->Layers.push_back( new FIPText( text, x, y ) );
	}
	else if( (cmd == "bind") && (cmd_tokens.size() >= 5) )
	{
		Pages[ screen ]->KeyBinds[ cmd_tokens[3] ] = cmd_tokens[ 4 ];
	}
}

void FIPConfig::SaveLines( FILE *config_file )
{
	DeviceConfig::SaveLines( config_file );
	
	for( size_t i = 0; i < Pages.size(); i ++ )
	{
		const char *color = "off";
		
		fprintf( config_file, "screen %i label \"%s\"\n", i + 1, Pages[ i ]->Label.c_str() );
		
		switch( Pages[ i ]->LED.DefaultLook.Color )
		{
			case LEDColor::Off:
				color = "off";
				break;
			case LEDColor::On:
				color = "on";
				break;
		}
		
		for( std::vector<LEDCondition*>::iterator cond_iter = Pages[ i ]->LED.Conditions.begin(); cond_iter != Pages[ i ]->LED.Conditions.end(); cond_iter ++ )
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
			}
			
			fprintf( config_file, "screen %i led %s %s %.0f\n", i + 1, condition.c_str(), color, (*cond_iter)->Look.BlinkRate );
		}
		
		fprintf( config_file, "screen %i led default %s %.0f\n", i + 1, color, Pages[ i ]->LED.DefaultLook.BlinkRate );
		
		for( std::vector<FIPLayer*>::iterator layer_iter = Pages[ i ]->Layers.begin(); layer_iter != Pages[ i ]->Layers.end(); layer_iter ++ )
		{
			switch( (*layer_iter)->Class )
			{
				case FIPLayerClass::Image:
				{
					FIPImage *image = (FIPImage*) *layer_iter;
					std::string type = Saitek::Output.GetImageName( image->Type );
					fprintf( config_file, "screen %i image %s %i %i %i %i\n", i + 1, type.c_str(), image->X, image->Y, image->W, image->H );
					break;
				}
				case FIPLayerClass::Text:
				{
					// FIXME: Allow variable fonts.
					
					FIPText *text = (FIPText*) *layer_iter;
					std::string type = Saitek::Output.GetTextName( text->Type );
					fprintf( config_file, "screen %i text %s %i %i\n", i + 1, type.c_str(), text->X, text->Y );
					break;
				}
			}
		}
		
		for( std::map<std::string,std::string>::iterator bind_iter = Pages[ i ]->KeyBinds.begin(); bind_iter != Pages[ i ]->KeyBinds.end(); bind_iter ++ )
			fprintf( config_file, "screen %i bind \"%s\" \"%s\"\n", i + 1, bind_iter->first.c_str(), bind_iter->second.c_str() );
		
		fprintf( config_file, "\n" );
	}
}

bool FIPConfig::NeedsTex( void )
{
	// FIXME: Only return true if the current view uses any shared texture data.
	return true;
}


FIPPage::FIPPage( std::string label )
{
	Label = label;
}

FIPPage::~FIPPage()
{
}


FIPLayer::FIPLayer( void )
{
	Class = FIPLayerClass::Unknown;
}

FIPLayer::~FIPLayer()
{
}


FIPImage::FIPImage( int type, int x, int y, int w, int h )
{
	Class = FIPLayerClass::Image;
	Type = type;
	X = x;
	Y = y;
	W = w;
	H = h;
}

FIPImage::~FIPImage()
{
}

void FIPImage::Draw( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, System::Drawing::Graphics ^gfx, double total_time, void *device )
{
	Saitek::Output.DrawImage( fd, tex, Type, total_time, device, X, Y, W, H, gfx );
}


FIPText::FIPText( int type, int x, int y )
{
	Class = FIPLayerClass::Text;
	Type = type;
	X = x;
	Y = y;
}

FIPText::~FIPText()
{
}

void FIPText::Draw( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, System::Drawing::Graphics ^gfx, double total_time, void *device )
{
	System::Drawing::Font ^font = Saitek::Output.DrawTools[device].GetFont( System::Drawing::FontFamily::GenericMonospace, 12, System::Drawing::FontStyle::Regular );
	System::Drawing::Brush ^brush = Saitek::Output.DrawTools[device].GetBrush( System::Drawing::Color::White );
	
	Saitek::Output.DrawText( fd, Type, total_time, device, X, Y, gfx, font, brush );
}
