#include "stdafx.h"
#include "FIP.h"
#include <cstdlib>
#include <cmath>
#include "Saitek.h"
#include "FalconOutput.h"


FIPInstance::FIPInstance( void *saitek_device, FIPConfig *config ) : DeviceInstance( saitek_device, config, DeviceType_Fip )
{
	SelectedPage = 0;
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
	if( (SelectedPage >= 0) && (SelectedPage < Config->Pages.size()) )
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
	for( int page_num = 0; page_num < Config->Pages.size(); page_num ++ )
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
	if( Config && ( page < ((FIPConfig*)( Config ))->Pages.size() ) )
		SelectedPage = page;
}


FIPConfig::FIPConfig( void ) : DeviceConfig( DeviceType_Fip )
{
	Name = "My FIP Config";
	SleepMs = 10;
}

const char *FIPConfig::TypeString( void )
{
	return "FIP";
}

void FIPConfig::SaveLines( FILE *config_file )
{
	for( int i = 0; i < Pages.size(); i ++ )
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
		
		fprintf( config_file, "screen %i led default %s %.0f\n", i + 1, color, Pages[ i ]->LED.DefaultLook.BlinkRate );
		
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
					FIPText *text = (FIPText*) *layer_iter;
					std::string type = Saitek::Output.GetTextName( text->Type );
					fprintf( config_file, "screen %i text %s %i %i monospace 12 white\n", i + 1, type.c_str(), text->X, text->Y );
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


FIPLayer::FIPLayer( void )
{
	Class = FIPLayerClass::Unknown;
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

void FIPText::Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time )
{
	Saitek::Output.DrawText( fd, Type, total_time, X, Y, gfx, TextFont.get(), TextBrush.get() );
}
