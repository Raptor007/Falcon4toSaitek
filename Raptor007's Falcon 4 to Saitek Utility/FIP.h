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
#include <map>
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
	
	FIPInstance( void *saitek_device, FIPConfig *config );
	virtual ~FIPInstance();
	
	const char *TypeString( void );
	
	void Begin( void );
	void End( void );
	
	void Update( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, double total_time );
	
	void ChangedButton( DWORD button, bool state );
	void SetPage( int page );
};


class FIPConfig : public DeviceConfig
{
public:
	std::vector<FIPPage*> Pages;
	
	FIPConfig( void );
	virtual ~FIPConfig();
	
	const char *TypeString( void );
	
	void Clear( void );
	void LoadLine( std::vector<std::string> cmd_tokens );
	void SaveLines( FILE *config_file );
	//void ShowEditWindow( Raptor007sFalcon4toSaitekUtility::MainForm ^main_form );
	
	bool NeedsTex( void );
};


class FIPPage
{
public:
	std::string Label;
	std::vector<FIPLayer*> Layers;
	LED LED;
	std::map<std::string, std::string> KeyBinds;
	
	FIPPage( std::string label );
	virtual ~FIPPage();
};


class FIPLayer
{
public:
	int Class;
	int Type;
	int X, Y;
	
	FIPLayer( void );
	virtual ~FIPLayer();

	virtual void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, System::Drawing::Graphics ^gfx, double total_time, void *device ) = 0;
};


class FIPImage : public FIPLayer
{
public:
	int W, H;

	FIPImage( int type, int x, int y, int w, int h );
	virtual ~FIPImage();

	void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, System::Drawing::Graphics ^gfx, double total_time, void *device );
};


class FIPText : public FIPLayer
{
public:
	msclr::auto_gcroot<System::Drawing::Font^> TextFont;
	msclr::auto_gcroot<System::Drawing::Brush^> TextBrush;

	FIPText( int type, int x, int y );
	virtual ~FIPText();

	void Draw( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, System::Drawing::Graphics ^gfx, double total_time, void *device );
};
