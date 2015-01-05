#pragma once
class DrawingToolbox;

#include "PlatformSpecific.h"
#include <msclr\auto_gcroot.h>


class DrawingToolbox
{
public:
	gcroot<System::Drawing::Bitmap^> Horizon;
	
	DrawingToolbox( void );
	DrawingToolbox( const DrawingToolbox &other );
	~DrawingToolbox();
	
	System::Drawing::Brush ^GetBrush( System::Drawing::Color color );
	System::Drawing::Pen ^GetPen( System::Drawing::Color color );
	System::Drawing::Font ^GetFont( System::Drawing::FontFamily ^family = System::Drawing::FontFamily::GenericMonospace, int size = 12, System::Drawing::FontStyle style = System::Drawing::FontStyle::Regular );
	
	void UpdateHorizon( F4SharedMem::FlightData ^fd );
	
private:
	msclr::auto_gcroot<System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Brush^ >^> Brushes;
	msclr::auto_gcroot<System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Pen^ >^> Pens;
	msclr::auto_gcroot<System::Collections::Generic::Dictionary< int, System::Drawing::Font^ >^> Fonts;
	
	gcroot<System::Drawing::Graphics^> HorizonGfx;
	gcroot<array<System::Drawing::Point>^> HorizonPoints;

	int GetFontID( System::Drawing::FontFamily ^family, int size, System::Drawing::FontStyle style );
};
