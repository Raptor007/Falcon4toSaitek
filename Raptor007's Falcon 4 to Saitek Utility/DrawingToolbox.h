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
	
	void UpdateHorizon( F4SharedMem::FlightData ^fd );
	
private:
	msclr::auto_gcroot<System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Brush^ >^> Brushes;
	msclr::auto_gcroot<System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Pen^ >^> Pens;
	
	gcroot<System::Drawing::Graphics^> HorizonGfx;
	gcroot<array<System::Drawing::Point>^> HorizonPoints;
};
