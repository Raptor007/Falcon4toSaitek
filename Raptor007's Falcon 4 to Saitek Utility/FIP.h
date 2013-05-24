#pragma once

class FIPInstance;
class FIPConfig;
class FIPPage;
class FIPLayer;
class FIPImage;
class FIPText;

#include <msclr\auto_gcroot.h>
#include <string>
#include <vector>
#include "Device.h"
#include "FIPBitmap.h"


namespace FIPLayerClass
{
	enum
	{
		Unknown = 0,
		Image,
		Text
	};
}


class FIPInstance : public DeviceInstance
{
public:
	FIPBitmap Bmp;
	int SelectedPage;
	
	FIPInstance( void *saitek_device, FIPConfig *config );
	
	const char *TypeString( void );
	
	void Begin( void );
	void End( void );
	
	void Update( F4SharedMem::FlightData ^fd, double total_time );
	
	void SetPage( int page );
};


class FIPConfig : public DeviceConfig
{
public:
	std::vector<FIPPage*> Pages;
	
	FIPConfig( void );
	
	const char *TypeString( void );
	
	void SaveLines( FILE *config_file );
};


class FIPPage
{
public:
	std::string Label;
	std::vector<FIPLayer*> Layers;
	LED LED;
	
	FIPPage( std::string label );
};


class FIPLayer
{
public:
	int Class;
	int Type;
	int X, Y;
	
	FIPLayer( void );
	virtual void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time ) = 0;
};


class FIPImage : public FIPLayer
{
public:
	int W, H;

	FIPImage( int type, int x, int y, int w, int h );
	void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time );
};


class FIPText : public FIPLayer
{
public:
	msclr::auto_gcroot<System::Drawing::Font^> TextFont;
	msclr::auto_gcroot<System::Drawing::Brush^> TextBrush;

	FIPText( int type, int x, int y, System::Drawing::Font ^font, System::Drawing::Brush ^brush );
	void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Graphics ^gfx, double total_time );
};
