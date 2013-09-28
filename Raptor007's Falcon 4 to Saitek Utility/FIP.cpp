#include "FIP.h"
#include <cstdlib>
#include <cmath>
#include "Saitek.h"
#include "FalconOutput.h"


FIPInstance::FIPInstance( void *saitek_device, FIPConfig *config ) : DeviceInstance( saitek_device, config, DeviceType_Fip )
{
	SelectedPage = 0;
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

void FIPInstance::Update( F4SharedMem::FlightData ^fd, double total_time )
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
			(*layer_iter)->Draw( fd, gfx, total_time );
	}

	// Draw button labels.
	Brush ^label_brush = gcnew SolidBrush( Color::LightGray );
	Brush ^selected_label_brush = gcnew SolidBrush( Color::White );
	Font ^label_font = gcnew Font( FontFamily::GenericSansSerif, 10.f, FontStyle::Regular );
	Font ^selected_label_font = gcnew Font( FontFamily::GenericSansSerif, 10.f, FontStyle::Bold );
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
		gfx->DrawString( gcnew System::String( page->Label.c_str() ), font, brush, 4.f, 3.f + page_num * 43 );

		// Set LED status based on each page.
		if( page_num < 6 )
		{
			page->LED.SetIndices( page_num + 1, -1 );
			page->LED.ApplyLook( fd, total_time, SaitekDevice, 0 );
		}
	}

	// Set other LEDs.
	Saitek::DO.SetLed( SaitekDevice, 0, 0, true );
	for( int led = Config->Pages.size() + 1; led <= 6; led ++ )
		Saitek::DO.SetLed( SaitekDevice, 0, led, false );

	// Update the FIP image display.
	Saitek::DO.SetImage( SaitekDevice, 0, 0, 320*240*3, Bmp.GetBuffer() );
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
	for( std::vector<FIPPage*>::iterator page_iter = Pages.begin(); page_iter != Pages.end(); page_iter ++ )
	{
		delete *page_iter;
		*page_iter = NULL;
	}
	
	Pages.clear();
}

void FIPConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
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
		
		System::Drawing::Font ^font = gcnew System::Drawing::Font( System::Drawing::FontFamily::GenericMonospace, 12.f, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel );
		System::Drawing::Brush ^brush = gcnew System::Drawing::SolidBrush( System::Drawing::Color::White );
		Pages[ screen ]->Layers.push_back( new FIPText( text, x, y, font, brush ) );
	}
}

void FIPConfig::SaveLines( FILE *config_file )
{
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
		
		fprintf( config_file, "\n" );
	}
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

void FIPImage::Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time )
{
	Saitek::Output.DrawImage( fd, Type, total_time, X, Y, W, H, gfx );
}


FIPText::FIPText( int type, int x, int y, System::Drawing::Font ^font, System::Drawing::Brush ^brush )
{
	Class = FIPLayerClass::Text;
	Type = type;
	X = x;
	Y = y;
	TextFont = font;
	TextBrush = brush;
}

FIPText::~FIPText()
{
}

void FIPText::Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time )
{
	Saitek::Output.DrawText( fd, Type, total_time, X, Y, gfx, TextFont.get(), TextBrush.get() );
}
