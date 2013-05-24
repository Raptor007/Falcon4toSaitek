#include "stdafx.h"
#include "FalconOutput.h"
#include <cmath>

#ifndef M_PI_F
#define M_PI_F 3.14159265358979323846f
#endif
#define TO_DEG(x) ((x) * 180.f / M_PI_F)
#define TO_RAD(x) ((x) * M_PI_F / 180.f)


FalconOutput::FalconOutput( void )
{
	TextTypes[ "altitude" ] = TextType::Altitude;
	TextTypes[ "nozzle" ] = TextType::Nozzle;
	TextTypes[ "rpm" ] = TextType::RPM;
	TextTypes[ "fuel" ] = TextType::Fuel;
	TextTypes[ "ded_line_1" ] = TextType::DEDLine1;
	TextTypes[ "ded_line_2" ] = TextType::DEDLine2;
	TextTypes[ "ded_line_3" ] = TextType::DEDLine3;
	TextTypes[ "ded_line_4" ] = TextType::DEDLine4;
	TextTypes[ "ded_line_5" ] = TextType::DEDLine5;
	TextTypes[ "run_time" ] = TextType::RunTime;

	ImageTypes[ "attitude" ] = ImageType::Attitude;
	ImageTypes[ "gear" ] = ImageType::Gear;
	ImageTypes[ "ils" ] = ImageType::ILS;
	ImageTypes[ "simple_rwr" ] = ImageType::SimpleRWR;
	ImageTypes[ "throttle" ] = ImageType::Throttle;
	ImageTypes[ "warning" ] = ImageType::Warning;
	ImageTypes[ "pitch_trim" ] = ImageType::PitchTrim;
	ImageTypes[ "roll_trim" ] = ImageType::RollTrim;
	ImageTypes[ "yaw_trim" ] = ImageType::YawTrim;
	ImageTypes[ "screen_copy" ] = ImageType::ScreenCopy;
	ImageTypes[ "screen_center" ] = ImageType::ScreenCenter;
	ImageTypes[ "screen_center_zoomed" ] = ImageType::ScreenCenterZoomed;
	ImageTypes[ "screen_cursor" ] = ImageType::ScreenCursor;
	ImageTypes[ "screen_cursor_zoomed" ] = ImageType::ScreenCursorZoomed;

	Conditions[ "rwr_missile" ] = Condition::RWRMissile;
	Conditions[ "rwr_lock" ] = Condition::RWRLock;
	Conditions[ "rwr_lethal" ] = Condition::RWRLethal;
	Conditions[ "rwr_contact" ] = Condition::RWRContact;
	Conditions[ "caution_master" ] = Condition::CautionMaster;
	Conditions[ "caution_altitude" ] = Condition::CautionAltitude;
	Conditions[ "caution_stores_config" ] = Condition::CautionStoresConfig;
	Conditions[ "caution_ecm" ] = Condition::CautionECM;
	Conditions[ "caution_fuel" ] = Condition::CautionFuel;
	Conditions[ "caution_oil" ] = Condition::CautionOil;
	Conditions[ "caution_engine_fault" ] = Condition::CautionEngineFault;
	Conditions[ "caution_avionics" ] = Condition::CautionAvionics;
	Conditions[ "caution_flcs" ] = Condition::CautionFLCS;
	Conditions[ "ecm" ] = Condition::ECM;
	Conditions[ "afterburner" ] = Condition::Afterburner;
	Conditions[ "airbrake" ] = Condition::AirBrake;
	Conditions[ "airbrake_33" ] = Condition::AirBrake33;
	Conditions[ "airbrake_66" ] = Condition::AirBrake66;
	Conditions[ "airbrake_99" ] = Condition::AirBrake99;
	Conditions[ "gear_down" ] = Condition::GearDown;
	Conditions[ "gear_up" ] = Condition::GearUp;
	Conditions[ "gear_moving" ] = Condition::GearMoving;
	Conditions[ "aoa_above" ] = Condition::AOAAbove;
	Conditions[ "aoa_below" ] = Condition::AOABelow;
	Conditions[ "aoa_on" ] = Condition::AOAOn;
	Conditions[ "gear_down_aoa_above" ] = Condition::GearDownAOAAbove;
	Conditions[ "gear_down_aoa_below" ] = Condition::GearDownAOABelow;
	Conditions[ "gear_down_aoa_on" ] = Condition::GearDownAOAOn;
	Conditions[ "bad_attitude" ] = Condition::BadAttitude;
	Conditions[ "chaff_low" ] = Condition::ChaffLow;
	Conditions[ "chaff_empty" ] = Condition::ChaffEmpty;
	Conditions[ "flare_low" ] = Condition::FlareLow;
	Conditions[ "flare_empty" ] = Condition::FlareEmpty;
	Conditions[ "fuel_low" ] = Condition::FuelLow;
	Conditions[ "fuel_critical" ] = Condition::FuelCritical;
	Conditions[ "fuel_empty" ] = Condition::FuelEmpty;
	Conditions[ "speed_lt350" ] = Condition::SpeedLT350;
	Conditions[ "speed_lt300" ] = Condition::SpeedLT300;
	Conditions[ "speed_lt250" ] = Condition::SpeedLT250;
	Conditions[ "speed_gt450" ] = Condition::SpeedGT450;
	Conditions[ "speed_gt500" ] = Condition::SpeedGT500;
	Conditions[ "speed_gt550" ] = Condition::SpeedGT550;
	Conditions[ "bad_speed" ] = Condition::BadSpeed;

	FalconSilhouette = gcnew cli::array<System::Drawing::PointF>( 15 );
	FalconSilhouette[  0 ].X =  0.00f;
	FalconSilhouette[  0 ].Y = -1.00f;
	FalconSilhouette[  1 ].X =  0.25f;
	FalconSilhouette[  1 ].Y = -0.05f;
	FalconSilhouette[  2 ].X =  0.75f;
	FalconSilhouette[  2 ].Y =  0.35f;
	FalconSilhouette[  3 ].X =  0.75f;
	FalconSilhouette[  3 ].Y =  0.50f;
	FalconSilhouette[  4 ].X =  0.20f;
	FalconSilhouette[  4 ].Y =  0.50f;
	FalconSilhouette[  5 ].X =  0.20f;
	FalconSilhouette[  5 ].Y =  0.75f;
	FalconSilhouette[  6 ].X =  0.35f;
	FalconSilhouette[  6 ].Y =  0.90f;
	FalconSilhouette[  7 ].X =  0.35f;
	FalconSilhouette[  7 ].Y =  1.00f;
	FalconSilhouette[  8 ].X = -0.35f;
	FalconSilhouette[  8 ].Y =  1.00f;
	FalconSilhouette[  9 ].X = -0.35f;
	FalconSilhouette[  9 ].Y =  0.90f;
	FalconSilhouette[ 10 ].X = -0.20f;
	FalconSilhouette[ 10 ].Y =  0.75f;
	FalconSilhouette[ 11 ].X = -0.20f;
	FalconSilhouette[ 11 ].Y =  0.50f;
	FalconSilhouette[ 12 ].X = -0.75f;
	FalconSilhouette[ 12 ].Y =  0.50f;
	FalconSilhouette[ 13 ].X = -0.75f;
	FalconSilhouette[ 13 ].Y =  0.35f;
	FalconSilhouette[ 14 ].X = -0.25f;
	FalconSilhouette[ 14 ].Y = -0.05f;
	ScalePoints( FalconSilhouette, 0.5, 0.5, 0.5, 0.5 );
}


std::string FalconOutput::GetName( std::map< std::string, int > *map, int type )
{
	for( std::map< std::string, int >::iterator iter = map->begin(); iter != map->end(); iter ++ )
		if( iter->second == type )
			return iter->first;
	
	return "unknown";
}

int FalconOutput::GetType( std::map< std::string, int > *map, std::string name )
{
	std::map< std::string, int >::iterator iter = map->find( name );
	if( iter != map->end() )
		return iter->second;
	
	return 0;
}


int FalconOutput::GetTextType( std::string name )
{
	return GetType( &TextTypes, name );
}

int FalconOutput::GetImageType( std::string name )
{
	return GetType( &ImageTypes, name );
}

int FalconOutput::GetCondition( std::string name )
{
	return GetType( &Conditions, name );
}

std::string FalconOutput::GetTextName( int type )
{
	return GetName( &TextTypes, type );
}

std::string FalconOutput::GetImageName( int type )
{
	return GetName( &ImageTypes, type );
}

std::string FalconOutput::GetConditionName( int type )
{
	return GetName( &Conditions, type );
}


bool FalconOutput::CheckCondition( F4SharedMem::FlightData ^fd, int type, double total_time )
{
	switch( type )
	{
		case Condition::RWRMissile:
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
				if( fd->missileLaunch[ i ] || fd->missileActivity[ i ] )
					return true;
			return false;
		case Condition::RWRLock:
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
				if( fd->lethality[ i ] >= 1.f )
					return true;
			return false;
		case Condition::RWRLethal:
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
				if( fd->lethality[ i ] >= 0.5f )
					return true;
			return false;
		case Condition::RWRContact:
			return ( fd->RwrObjectCount > 0 );
		
		case Condition::CautionMaster:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::MasterCaution );
		case Condition::CautionAltitude:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::ALT );
		case Condition::CautionStoresConfig:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::CONFIG );
		case Condition::CautionECM:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::ECM );
		case Condition::CautionFuel:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::FuelLow );
		case Condition::CautionOil:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::OIL );
		case Condition::CautionEngineFault:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::EngineFault );
		case Condition::CautionAvionics:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::Avionics );
		case Condition::CautionFLCS:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::FltControlSys );
		
		case Condition::ECM:
			return ( fd->lightBits2 & (int)F4SharedMem::Headers::LightBits2::EcmPwr );
		
		case Condition::Afterburner:
			return ( fd->nozzlePos > 0.2f );
		
		case Condition::AirBrake:
			return ( fd->speedBrake >= 0.01f );
		case Condition::AirBrake33:
			return ( fd->speedBrake > 0.333f );
		case Condition::AirBrake66:
			 return ( fd->speedBrake >= 0.667f );
		case Condition::AirBrake99:
			return ( fd->speedBrake > 0.99f );
		
		case Condition::GearDown:
			return ( fd->gearPos > 0.99f );
		case Condition::GearUp:
			return ( fd->gearPos < 0.01f );
		case Condition::GearMoving:
			return ( (fd->gearPos >= 0.01f) && (fd->gearPos <= 0.99f) );
		
		case Condition::AOAAbove:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAAbove );
		case Condition::AOABelow:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOABelow );
		case Condition::AOAOn:
			return ( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAOn );
		
		case Condition::GearDownAOAAbove:
			return ( (fd->gearPos > 0.99f) && (fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAAbove) );
		case Condition::GearDownAOABelow:
			return ( (fd->gearPos > 0.99f) && (fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOABelow) );
		case Condition::GearDownAOAOn:
			return ( (fd->gearPos > 0.99f) && (fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAOn) );
		
		case Condition::BadAttitude:
			return ( TO_DEG(fd->pitch) < -20 );
		
		case Condition::ChaffLow:
			return ( fd->ChaffCount <= 10.5f );
		case Condition::ChaffEmpty:
			return ( fd->ChaffCount < 0.5f );
		case Condition::FlareLow:
			return ( fd->FlareCount <= 10.5f );
		case Condition::FlareEmpty:
			return ( fd->FlareCount < 0.5f );
		
		case Condition::FuelLow:
			return ( fd->total <= 1600.5f );
		case Condition::FuelCritical:
			return ( fd->total <= 800.5f );
		case Condition::FuelEmpty:
			return ( fd->total < 0.5f );
		
		case Condition::SpeedLT350:
			return ( fd->kias < 350.0f );
		case Condition::SpeedLT300:
			return ( fd->kias < 300.0f );
		case Condition::SpeedLT250:
			return ( fd->kias < 250.0f );
		case Condition::SpeedGT450:
			return ( fd->kias > 450.0f );
		case Condition::SpeedGT500:
			return ( fd->kias > 500.0f );
		case Condition::SpeedGT550:
			return ( fd->kias > 550.0f );
		case Condition::BadSpeed:
			return ( (fd->kias < 350.0f) || (fd->kias > 450.0f) );
		
		default:
			return false;
	}
}


void FalconOutput::FormatText( F4SharedMem::FlightData ^fd, int type, double total_time, wchar_t *buffer, int size )
{
	bool active_sec = fmod( total_time, 2. ) > 1.;
	bool active_half_sec = fmod( total_time, 1. ) > 0.5;
	bool active_quarter_sec = fmod( total_time, 0.5 ) > 0.25;
	bool active_eighth_sec = fmod( total_time, 0.25 ) > 0.125;

	switch( type )
	{
		case TextType::Altitude:
			swprintf_s( buffer, size, L"MSL: %.0f", fd->z * -1. );
		break;
		case TextType::Nozzle:
			swprintf_s( buffer, size, L"Nozzle: %.0f%%", fd->nozzlePos );
		break;
		case TextType::RPM:
			swprintf_s( buffer, size, L"RPM: %.0f%%", fd->rpm );
		break;
		case TextType::Fuel:
			swprintf_s( buffer, size, L"Fuel: %.0f", fd->total );
		break;
		case TextType::RunTime:
			swprintf_s( buffer, size, L"RunTime: %.2f sec", total_time );
		break;
		case TextType::DEDLine1:
			if( fd->DEDLines && (fd->DEDLines->Length >= 1) )
			{
				pin_ptr<const wchar_t> wch = PtrToStringChars( fd->DEDLines[ 0 ] );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine2:
			if( fd->DEDLines && (fd->DEDLines->Length >= 2) )
			{
				pin_ptr<const wchar_t> wch = PtrToStringChars( fd->DEDLines[ 1 ] );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine3:
			if( fd->DEDLines && (fd->DEDLines->Length >= 3) )
			{
				pin_ptr<const wchar_t> wch = PtrToStringChars( fd->DEDLines[ 2 ] );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine4:
			if( fd->DEDLines && (fd->DEDLines->Length >= 4) )
			{
				pin_ptr<const wchar_t> wch = PtrToStringChars( fd->DEDLines[ 3 ] );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine5:
			if( fd->DEDLines && (fd->DEDLines->Length >= 5) )
			{
				pin_ptr<const wchar_t> wch = PtrToStringChars( fd->DEDLines[ 4 ] );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		default:
			swprintf_s( buffer, size, L"" );
	}
}


void FalconOutput::DrawText( F4SharedMem::FlightData ^fd, int type, double total_time, int x, int y, System::Drawing::Graphics ^gfx, System::Drawing::Font ^font, System::Drawing::Brush ^brush )
{
	wchar_t buffer[ 1024 ];
	FormatText( fd, type, total_time, buffer, 1024 );
	gfx->DrawString( gcnew System::String( buffer ), font, brush, (float)( x ), (float)( y ) );
}


void FalconOutput::DrawImage( F4SharedMem::FlightData ^fd, int type, double total_time, int x, int y, int w, int h, System::Drawing::Graphics ^gfx )
{
	bool active_sec = (fmod( total_time, 2. ) > 1.);
	bool active_half_sec = (fmod( total_time, 1. ) > 0.5);
	bool active_quarter_sec = (fmod( total_time, 0.5 ) > 0.25);
	bool active_eighth_sec = (fmod( total_time, 0.25 ) > 0.125);

	using namespace System::Drawing;

	Brush ^black_brush = gcnew SolidBrush( Color::Black );
	Brush ^red_brush = gcnew SolidBrush( Color::Red );
	Brush ^green_brush = gcnew SolidBrush( Color::Green );
	Brush ^blue_brush = gcnew SolidBrush( Color::Blue );
	Brush ^yellow_brush = gcnew SolidBrush( Color::Yellow );
	Brush ^magenta_brush = gcnew SolidBrush( Color::Magenta );
	Brush ^grey_brush = gcnew SolidBrush( Color::Gray );
	Brush ^brown_brush = gcnew SolidBrush( Color::Brown );

	Pen ^white_pen = gcnew Pen( Color::White );
	Pen ^green_pen = gcnew Pen( Color::Green );
	Pen ^orange_pen = gcnew Pen( Color::Orange );
	Pen ^grey_pen = gcnew Pen( Color::Gray );

	switch( type )
	{
		case ImageType::Attitude:
		{
			// Draw roll indicator outside.
			gfx->FillEllipse( brown_brush, x, y, w, h );
			gfx->FillPie( blue_brush, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) + 180.f, 180.f );
			gfx->DrawEllipse( white_pen, x, y, w, h );

			// Draw markings on roll indicator.
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ), 180.f );
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) - 90.f, 180.f );
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) - 30.f, -90.f );
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) - 60.f, -90.f );
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) - 70.f, -30.f );
			gfx->DrawPie( white_pen, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( -1.f * fd->roll ) - 80.f, -30.f );

			// Clip drawing to the inner circle.
			Drawing2D::GraphicsPath ^clip_path = gcnew Drawing2D::GraphicsPath();
			clip_path->AddEllipse( x + w/8.f, y + h/8.f, w*3.f/4.f, h*3.f/4.f );
			gfx->Clip = gcnew Region( clip_path );

			// Draw attitude indicator inside.
			gfx->FillRectangle( brown_brush, x, y, w, h );
			cli::array<PointF> ^sky_points = gcnew cli::array<PointF>( 3 );
			sky_points[ 0 ].X = 100.f * cos( -1.f * fd->roll );
			sky_points[ 0 ].Y = 100.f * sin( -1.f * fd->roll );
			sky_points[ 1 ].X = -1.f * sky_points[ 0 ].X;
			sky_points[ 1 ].Y = -1.f * sky_points[ 0 ].Y;
			sky_points[ 2 ].X = 100.f * cos( -1.f * fd->roll - M_PI_F/2.f );
			sky_points[ 2 ].Y = 100.f * sin( -1.f * fd->roll - M_PI_F/2.f );
			float pitch_dx = sin( fd->roll ) / 80.f;
			float pitch_dy = cos( fd->roll ) / 80.f;
			ScalePoints( sky_points, pitch_dx * TO_DEG(fd->pitch), pitch_dy * TO_DEG(fd->pitch), 1.f, 1.f );
			ScalePoints( sky_points, x + w/2.f, y + h/2.f, (float) w, (float) h );
			gfx->FillPolygon( blue_brush, sky_points );
			UndoScalePoints( sky_points, x + w/2.f, y + h/2.f, (float) w, (float) h );

			// Draw a line for every 10 degrees.
			for( int degrees = -90; degrees <= 90; degrees += 10 )
			{
				ScalePoints( sky_points, degrees * pitch_dx, degrees * pitch_dy, 1.f, 1.f );
				ScalePoints( sky_points, x + w/2.f, y + h/2.f, (float) w, (float) h );
				gfx->DrawLine( white_pen, sky_points[ 0 ].X, sky_points[ 0 ].Y, sky_points[ 1 ].X, sky_points[ 1 ].Y );
				UndoScalePoints( sky_points, x + w/2.f, y + h/2.f, (float) w, (float) h );
				UndoScalePoints( sky_points, degrees * pitch_dx, degrees * pitch_dy, 1.f, 1.f );
			}
			
			// Restore full-image drawing.
			gfx->Clip = gcnew Region( Drawing::Rectangle( 0, 0, 320, 240 ) );

			// Draw inner border.
			gfx->DrawEllipse( white_pen, x + w/8.f, y + h/8.f, w*3.f/4.f, h*3.f/4.f );

			// Draw fixed markings.
			gfx->DrawLine( orange_pen, x + w*3.f/16.f, y + h/2.f, x + w*7.f/16.f, y + h/2.f );
			gfx->DrawLine( orange_pen, x + w*9.f/16.f, y + h/2.f, x + w*13.f/16.f, y + h/2.f );
			gfx->DrawLine( orange_pen, x + w/2.f, y + h/8.f, x + w/2.f, y + h/4.f );
		}
		break;
		case ImageType::SimpleRWR:
		{
			// Draw our plane's silhouette.
			ScalePoints( FalconSilhouette, x + w/4.f, y + h/4.f, w/2.f, h/2.f );
			gfx->FillPolygon( green_brush, FalconSilhouette );
			UndoScalePoints( FalconSilhouette, x + w/4.f, y + h/4.f, w/2.f, h/2.f );

			gfx->DrawEllipse( green_pen, x, y, w, h );

			// FIXME: Sort??
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
			{
				Brush ^contact_brush;
				if( active_quarter_sec && ( fd->missileLaunch[ i ] || fd->missileActivity[ i ] ) )
					contact_brush = magenta_brush;
				else if( fd->lethality[ i ] >= 1.f )
					contact_brush = red_brush;
				else if( fd->lethality[ i ] >= 0.5f )
					contact_brush = yellow_brush;
				else if( fd->lethality[ i ] > 0.f )
					contact_brush = blue_brush;
				else
					contact_brush = grey_brush;

				float width = 2.f;
				if( fd->lethality[ i ] > 0.f )
					width += fd->lethality[ i ] * 5.f;
				gfx->FillPie( contact_brush, (float)( x ), (float)( y ), (float)( w ), (float)( h ), TO_DEG( fd->bearing[ i ] ) - fd->currentHeading - width/2.f - 90.f, width );
			}
		}
		break;
		case ImageType::Throttle:
		{
			float rpm_h = fd->rpm * h / 200.f;
			gfx->FillRectangle( green_brush, (float)x, y+h - rpm_h, (float)w, rpm_h );
			float nozzle_h = fd->nozzlePos * h / 200.f;
			gfx->FillRectangle( red_brush, (float)x, y+h/2 - nozzle_h, (float)w, nozzle_h );
			gfx->DrawRectangle( grey_pen, x, y, w, h );
			gfx->DrawLine( grey_pen, x, y+h/2, x+w, y+h/2 );
		}
		break;
		case ImageType::PitchTrim:
		{
			gfx->DrawPie( grey_pen, x-w, y, w*2, h, 270, 180 );
			gfx->FillPie( yellow_brush, (float)(x-w), (float)y, (float)(w*2), (float)h, -1.f + fd->TrimPitch*180.f, 2.f );
		}
		break;
		case ImageType::RollTrim:
		{
			gfx->DrawPie( grey_pen, x, y-h, w, h*2, 0, 180 );
			gfx->FillPie( yellow_brush, (float)x, (float)(y-h), (float)w, (float)(h*2), 89.f - fd->TrimRoll*180.f, 2.f );
		}
		break;
		case ImageType::YawTrim:
		{
			gfx->DrawPie( grey_pen, x, y, w, h*2, 180, 180 );
			gfx->FillPie( yellow_brush, (float)x, (float)y, (float)w, (float)(h*2), 269.f - fd->TrimYaw*180.f, 2.f );
		}
		break;
		case ImageType::ILS:
		{
			float horizontal = (fd->AdiIlsHorPos + 1.f) / 2.f;
			float vertical = (fd->AdiIlsVerPos + 1.f) / 2.f;
			gfx->DrawLine( white_pen, (float)x, y + h*vertical, (float)(x+w), y + h*vertical );
			gfx->DrawLine( white_pen, x + w*horizontal, (float)y, x + w*horizontal, (float)(y+h) );
			
			gfx->DrawLine( orange_pen, x + w*.4f, y + h*.5f, x + w*.6f, y + h*.5f );
			gfx->DrawLine( orange_pen, x + w*.5f, y + h*.4f, x + w*.5f, y + h*.6f );
		}
		break;
		case ImageType::Gear:
		{
			Brush ^brush;
			if( fd->gearPos >= 1.f )
				brush = green_brush;
			else if( fd->gearPos > 0.f )
				brush = red_brush;
			else
				brush = black_brush;

			gfx->FillEllipse( brush, x, y, w, h );
			gfx->DrawEllipse( grey_pen, x, y, w, h );
		}
		break;
		case ImageType::ScreenCopy:
		{
			try
			{
				Bitmap ^tmp_bmp = gcnew Bitmap( Screen::PrimaryScreen->Bounds.Width, Screen::PrimaryScreen->Bounds.Height, Imaging::PixelFormat::Format24bppRgb );
				Graphics ^tmp_gfx = Graphics::FromImage( tmp_bmp );
				tmp_gfx->CopyFromScreen( Screen::PrimaryScreen->Bounds.X, Screen::PrimaryScreen->Bounds.Y, 0, 0, System::Drawing::Size( Screen::PrimaryScreen->Bounds.Width, Screen::PrimaryScreen->Bounds.Height ) );
				gfx->DrawImage( tmp_bmp, x, y, w, h );
				delete tmp_gfx;
				delete tmp_bmp;
			}
			catch( ... ){}
		}
		break;
		case ImageType::ScreenCenter:
		{
			try
			{
				gfx->CopyFromScreen( (Screen::PrimaryScreen->Bounds.Width - w) / 2 + Screen::PrimaryScreen->Bounds.X, (Screen::PrimaryScreen->Bounds.Height - h) / 2 + Screen::PrimaryScreen->Bounds.Y, x, y, System::Drawing::Size( w, h ) );
			}
			catch( ... ){}
		}
		break;
		case ImageType::ScreenCenterZoomed:
		{
			try
			{
				Bitmap ^tmp_bmp = gcnew Bitmap( w / 2, h / 2, Imaging::PixelFormat::Format24bppRgb );
				Graphics ^tmp_gfx = Graphics::FromImage( tmp_bmp );\

				tmp_gfx->CopyFromScreen( (Screen::PrimaryScreen->Bounds.Width - (w/2)) / 2 + Screen::PrimaryScreen->Bounds.X, (Screen::PrimaryScreen->Bounds.Height - (h/2)) / 2 + Screen::PrimaryScreen->Bounds.Y, x, y, System::Drawing::Size( w/2, h/2 ) );
				gfx->DrawImage( tmp_bmp, x, y, w, h );
				delete tmp_gfx;
				delete tmp_bmp;
			}
			catch( ... ){}
		}
		break;
		case ImageType::ScreenCursor:
		{
			try
			{
				int x1 = System::Windows::Forms::Cursor::Position.X - w/2;
				int y1 = System::Windows::Forms::Cursor::Position.Y - h/2;
				if( x1 < Screen::PrimaryScreen->Bounds.X ) x1 = Screen::PrimaryScreen->Bounds.X;
				if( y1 < Screen::PrimaryScreen->Bounds.Y ) y1 = Screen::PrimaryScreen->Bounds.Y;
				if( x1 + w > Screen::PrimaryScreen->Bounds.Width ) x1 = Screen::PrimaryScreen->Bounds.Width - w;
				if( y1 + h > Screen::PrimaryScreen->Bounds.Height ) y1 = Screen::PrimaryScreen->Bounds.Height - h;

				gfx->CopyFromScreen( x1, y1, x, y, System::Drawing::Size( w, h ) );
			}
			catch( ... ){}
		}
		break;
		case ImageType::ScreenCursorZoomed:
		{
			try
			{
				Bitmap ^tmp_bmp = gcnew Bitmap( w / 2, h / 2, Imaging::PixelFormat::Format24bppRgb );
				Graphics ^tmp_gfx = Graphics::FromImage( tmp_bmp );

				int x1 = System::Windows::Forms::Cursor::Position.X - w/4;
				int y1 = System::Windows::Forms::Cursor::Position.Y - h/4;
				if( x1 < Screen::PrimaryScreen->Bounds.X ) x1 = Screen::PrimaryScreen->Bounds.X;
				if( y1 < Screen::PrimaryScreen->Bounds.Y ) y1 = Screen::PrimaryScreen->Bounds.Y;
				if( x1 + w/2 > Screen::PrimaryScreen->Bounds.Width ) x1 = Screen::PrimaryScreen->Bounds.Width - w/2;
				if( y1 + h/2 > Screen::PrimaryScreen->Bounds.Height ) y1 = Screen::PrimaryScreen->Bounds.Height - h/2;

				tmp_gfx->CopyFromScreen( x1, y1, x, y, System::Drawing::Size( w/2, h/2 ) );
				gfx->DrawImage( tmp_bmp, x, y, w, h );
				delete tmp_gfx;
				delete tmp_bmp;
			}
			catch( ... ){}
		}
		break;
	}
}


void FalconOutput::ScalePoints( cli::array<System::Drawing::PointF> ^points, float x, float y, float w, float h )
{
	for( int i = 0; i < points->Length; i ++ )
	{
		points[ i ].X *= w;
		points[ i ].Y *= h;
		points[ i ].X += x;
		points[ i ].Y += y;
	}
}

void FalconOutput::UndoScalePoints( cli::array<System::Drawing::PointF> ^points, float x, float y, float w, float h )
{
	for( int i = 0; i < points->Length; i ++ )
	{
		points[ i ].X -= x;
		points[ i ].Y -= y;
		points[ i ].X /= w;
		points[ i ].Y /= h;
	}
}
