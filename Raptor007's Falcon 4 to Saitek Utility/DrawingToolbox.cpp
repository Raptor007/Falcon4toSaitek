#pragma once

#include "DrawingToolbox.h"
#include <cmath>
#include "Num.h"


DrawingToolbox::DrawingToolbox( void )
{
	Brushes = gcnew System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Brush^ >();
	Pens = gcnew System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Pen^ >();
	Fonts = gcnew System::Collections::Generic::Dictionary< int, System::Drawing::Font^ >();
	
	Horizon = gcnew System::Drawing::Bitmap( 16, 3, System::Drawing::Imaging::PixelFormat::Format16bppRgb565 );
	HorizonGfx = System::Drawing::Graphics::FromImage( Horizon );
	HorizonPoints = gcnew array<System::Drawing::Point>( 3 );
}


DrawingToolbox::DrawingToolbox( const DrawingToolbox &other )
{
	Brushes = gcnew System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Brush^ >();
	Pens = gcnew System::Collections::Generic::Dictionary< System::Drawing::Color, System::Drawing::Pen^ >();
	Fonts = gcnew System::Collections::Generic::Dictionary< int, System::Drawing::Font^ >();
	
	Horizon = gcnew System::Drawing::Bitmap( 16, 3, System::Drawing::Imaging::PixelFormat::Format16bppRgb565 );
	HorizonGfx = System::Drawing::Graphics::FromImage( Horizon );
	HorizonPoints = gcnew array<System::Drawing::Point>( 3 );
}


DrawingToolbox::~DrawingToolbox()
{
	// FIXME
}


System::Drawing::Brush ^DrawingToolbox::GetBrush( System::Drawing::Color color )
{
	if( ! Brushes->ContainsKey(color) )
		Brushes->Add( color, gcnew System::Drawing::SolidBrush(color) );
	
	return Brushes.get()[ color ];
}

System::Drawing::Pen ^DrawingToolbox::GetPen( System::Drawing::Color color )
{
	if( ! Pens->ContainsKey(color) )
		Pens->Add( color, gcnew System::Drawing::Pen(color) );
	
	return Pens.get()[ color ];
}

System::Drawing::Font ^DrawingToolbox::GetFont( System::Drawing::FontFamily ^family, int size, System::Drawing::FontStyle style )
{
	int font_id = GetFontID( family, size, style );
	
	if( ! Fonts->ContainsKey(font_id) )
		Fonts->Add( font_id, gcnew System::Drawing::Font( family, (float) size, style, System::Drawing::GraphicsUnit::Pixel ) );
	
	return Fonts.get()[ font_id ];
}


void DrawingToolbox::UpdateHorizon( F4SharedMem::FlightData ^fd )
{
	// Set up the artificial horizon bitmap.
	System::Drawing::Color horizonEmpty = System::Drawing::Color::Red;
	System::Drawing::Pen ^horizonPen = GetPen( System::Drawing::Color::Green );
	System::Drawing::Brush ^horizonBrush = GetBrush( System::Drawing::Color::Blue );
	double charAspectRatio = 6.0/9.0;
	
	// Draw the artificial horizon to a bitmap in memory.
	double rightX = cos( fd->roll );
	double rightY = sin( fd->roll );
	double downX = cos( fd->roll - M_PI/2. );
	double downY = sin( fd->roll - M_PI/2. );
	double pitchX = downX * (Num::RadToDeg(fd->pitch) - 7.0) / 5.0;
	double pitchY = downY * (Num::RadToDeg(fd->pitch) - 7.0) / 5.0;
	HorizonPoints[ 0 ].X = (int)( rightX * 100.0 + 7.5 + pitchX );
	HorizonPoints[ 0 ].Y = (int)( rightY * 100.0*charAspectRatio + 1.0 + pitchY*charAspectRatio );
	HorizonPoints[ 1 ].X = (int)( rightX * -100.0 + 7.5 + pitchX );
	HorizonPoints[ 1 ].Y = (int)( rightY * -100.0*charAspectRatio + 1.0 + pitchY*charAspectRatio );
	HorizonPoints[ 2 ].X = (int)( downX * 100.0 + 7.5 + pitchX );
	HorizonPoints[ 2 ].Y = (int)( downY * 100.0*charAspectRatio + 1.0 + pitchY*charAspectRatio );
	HorizonGfx->Clear( horizonEmpty );
	HorizonGfx->FillPolygon( horizonBrush, HorizonPoints, System::Drawing::Drawing2D::FillMode::Alternate );
	HorizonGfx->DrawLine( horizonPen, HorizonPoints[ 0 ].X, HorizonPoints[ 0 ].Y, HorizonPoints[ 1 ].X , HorizonPoints[ 1 ].Y );
}


int DrawingToolbox::GetFontID( System::Drawing::FontFamily ^family, int size, System::Drawing::FontStyle style )
{
	int hash = size * 16;
	
	if( family != System::Drawing::FontFamily::GenericMonospace )
		hash += 8;
	
	if( style == System::Drawing::FontStyle::Bold )
		hash += 1;
	else if( style == System::Drawing::FontStyle::Italic )
		hash += 2;
	else if( style == System::Drawing::FontStyle::Underline )
		hash += 3;
	else if( style == System::Drawing::FontStyle::Strikeout )
		hash += 4;
	
	return hash;
}
