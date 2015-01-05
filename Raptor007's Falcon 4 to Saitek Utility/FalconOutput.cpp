#include "FalconOutput.h"
#include "Math2D.h"
#include "Num.h"
#include "Saitek.h"
#include <cmath>

#ifndef M_PI_F
#define M_PI_F 3.14159265358979323846f
#endif
#define TO_DEG(x) ((x) * 180.f / M_PI_F)
#define TO_RAD(x) ((x) * M_PI_F / 180.f)

using namespace System::Windows::Forms;
using namespace System::Drawing;


FalconOutput::FalconOutput( void )
{
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
	Conditions[ "on_ground" ] = Condition::OnGround;
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
	Conditions[ "bad_speed" ] = Condition::SpeedBad;
	
	TextTypes[ "altitude" ] = TextType::Altitude;
	TextTypes[ "altitude_time" ] = TextType::AltitudeTime;
	TextTypes[ "indicated_knots" ] = TextType::IndicatedKnots;
	TextTypes[ "indicated_fps" ] = TextType::IndicatedFPS;
	TextTypes[ "indicated_mph" ] = TextType::IndicatedMPH;
	TextTypes[ "true_knots" ] = TextType::TrueKnots;
	TextTypes[ "true_fps" ] = TextType::TrueFPS;
	TextTypes[ "true_mph" ] = TextType::TrueMPH;
	TextTypes[ "ground_knots" ] = TextType::GroundKnots;
	TextTypes[ "ground_fps" ] = TextType::GroundFPS;
	TextTypes[ "ground_mph" ] = TextType::GroundMPH;
	TextTypes[ "mach" ] = TextType::Mach;
	TextTypes[ "g_forces" ] = TextType::GForces;
	TextTypes[ "heading" ] = TextType::Heading;
	TextTypes[ "heading_ground" ] = TextType::HeadingGround;
	TextTypes[ "heading_air" ] = TextType::HeadingAir;
	TextTypes[ "heading_diff" ] = TextType::HeadingDiff;
	TextTypes[ "wind_dir" ] = TextType::WindDir;
	TextTypes[ "wind_knots" ] = TextType::WindKnots;
	TextTypes[ "wind_fps" ] = TextType::WindFPS;
	TextTypes[ "wind_mph" ] = TextType::WindMPH;
	TextTypes[ "tailwind_knots" ] = TextType::TailwindKnots;
	TextTypes[ "tailwind_fps" ] = TextType::TailwindFPS;
	TextTypes[ "tailwind_mph" ] = TextType::TailwindMPH;
	TextTypes[ "crosswind_knots" ] = TextType::CrosswindKnots;
	TextTypes[ "crosswind_fps" ] = TextType::CrosswindFPS;
	TextTypes[ "crosswind_mph" ] = TextType::CrosswindMPH;
	TextTypes[ "wind_heading_effect" ] = TextType::WindHeadingEffect;
	TextTypes[ "yaw" ] = TextType::Yaw;
	TextTypes[ "beta" ] = TextType::Beta;
	TextTypes[ "yaw_trim" ] = TextType::YawTrim;
	TextTypes[ "climb_angle" ] = TextType::ClimbAngle;
	TextTypes[ "pitch" ] = TextType::Pitch;
	TextTypes[ "aoa" ] = TextType::AOA;
	TextTypes[ "pitch_trim" ] = TextType::PitchTrim;
	TextTypes[ "roll" ] = TextType::Roll;
	TextTypes[ "roll_trim" ] = TextType::RollTrim;
	TextTypes[ "airbrake" ] = TextType::Airbrake;
	TextTypes[ "gear" ] = TextType::Gear;
	TextTypes[ "aoai" ] = TextType::AOAI;
	TextTypes[ "rpm" ] = TextType::RPM;
	TextTypes[ "nozzle" ] = TextType::Nozzle;
	TextTypes[ "fuel_total" ] = TextType::FuelTotal;
	TextTypes[ "fuel_internal" ] = TextType::FuelInternal;
	TextTypes[ "fuel_external" ] = TextType::FuelExternal;
	TextTypes[ "fuel_epu" ] = TextType::FuelEPU;
	TextTypes[ "fuel_flow" ] = TextType::FuelFlow;
	TextTypes[ "fuel_time" ] = TextType::FuelTime;
	TextTypes[ "fuel_dist" ] = TextType::FuelDist;
	TextTypes[ "chaff" ] = TextType::Chaff;
	TextTypes[ "flares" ] = TextType::Flares;
	TextTypes[ "caution_master" ] = TextType::CautionMaster;
	TextTypes[ "rwr_heading" ] = TextType::RWRHeading;
	TextTypes[ "rwr_lethality" ] = TextType::RWRLethality;
	TextTypes[ "steerpoint" ] = TextType::Steerpoint;
	TextTypes[ "horizon_1" ] = TextType::Horizon1;
	TextTypes[ "horizon_2" ] = TextType::Horizon2;
	TextTypes[ "horizon_3" ] = TextType::Horizon3;
	TextTypes[ "ded_line_1" ] = TextType::DEDLine1;
	TextTypes[ "ded_line_2" ] = TextType::DEDLine2;
	TextTypes[ "ded_line_3" ] = TextType::DEDLine3;
	TextTypes[ "ded_line_4" ] = TextType::DEDLine4;
	TextTypes[ "ded_line_5" ] = TextType::DEDLine5;
	TextTypes[ "pfl_line_1" ] = TextType::PFLLine1;
	TextTypes[ "pfl_line_2" ] = TextType::PFLLine2;
	TextTypes[ "pfl_line_3" ] = TextType::PFLLine3;
	TextTypes[ "pfl_line_4" ] = TextType::PFLLine4;
	TextTypes[ "pfl_line_5" ] = TextType::PFLLine5;
	TextTypes[ "light_bits_1_1" ] = TextType::LightBits1_1;
	TextTypes[ "light_bits_1_2" ] = TextType::LightBits1_2;
	TextTypes[ "light_bits_2_1" ] = TextType::LightBits2_1;
	TextTypes[ "light_bits_2_2" ] = TextType::LightBits2_1;
	TextTypes[ "light_bits_3_1" ] = TextType::LightBits3_1;
	TextTypes[ "light_bits_3_2" ] = TextType::LightBits3_2;
	TextTypes[ "hsi_bits_1" ] = TextType::HsiBits1;
	TextTypes[ "hsi_bits_2" ] = TextType::HsiBits2;
	TextTypes[ "run_time" ] = TextType::RunTime;
	TextTypes[ "tex_w" ] = TextType::TexW;
	TextTypes[ "tex_h" ] = TextType::TexH;
	
	ImageTypes[ "attitude" ] = ImageType::Attitude;
	ImageTypes[ "gear" ] = ImageType::Gear;
	ImageTypes[ "airbrake" ] = ImageType::Airbrake;
	ImageTypes[ "ils" ] = ImageType::ILS;
	ImageTypes[ "rwr_simple" ] = ImageType::RWRSimple;
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
	ImageTypes[ "tex" ] = ImageType::Tex;
	ImageTypes[ "tex_mfd1" ] = ImageType::TexMFD1;
	ImageTypes[ "tex_mfd2" ] = ImageType::TexMFD2;
	ImageTypes[ "tex_rwr" ] = ImageType::TexRWR;
	ImageTypes[ "tex_ded" ] = ImageType::TexDED;
	ImageTypes[ "tex_hud" ] = ImageType::TexHUD;
	ImageTypes[ "tex_hmcs" ] = ImageType::TexHMCS;
	ImageTypes[ "gauge_azimuth" ] = ImageType::GaugeAzimuth;
	
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


FalconOutput::~FalconOutput()
{
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
		
		case Condition::OnGround:
			return ( (fd->lightBits & (int)F4SharedMem::Headers::LightBits::WOW) || ((fd->lightBits3 & (int)F4SharedMem::Headers::Bms4LightBits3::OnGround) && (Saitek::MainThread->Config.FalconType == F4SharedMem::FalconDataFormats::BMS4)) );
		
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
		case Condition::SpeedBad:
			return ( (fd->kias < 350.0f) || (fd->kias > 450.0f) );
	}
	
	return false;
}


void FalconOutput::FormatText( F4SharedMem::FlightData ^fd, int type, double total_time, void *device, wchar_t *buffer, int size )
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
		case TextType::AltitudeTime:
			if( fd->zDot > 0.0f )
				swprintf_s( buffer, size, L"MSL 0: %.0fs", fd->z * -1.0f / fd->zDot );
			else
				swprintf_s( buffer, size, L"" );
		break;
		
		case TextType::IndicatedKnots:
			swprintf_s( buffer, size, L"IAS: %.0f", fd->kias );
		break;
		case TextType::IndicatedFPS:
			swprintf_s( buffer, size, L"IAS: %.0f", fd->kias * 1.68780986 );
		break;
		case TextType::IndicatedMPH:
			swprintf_s( buffer, size, L"IAS: %.0f", fd->kias * 1.15077945 );
		break;
		case TextType::TrueKnots:
			swprintf_s( buffer, size, L"TAS: %.0f", fd->vt * 0.592483801 );
		break;
		case TextType::TrueFPS:
			swprintf_s( buffer, size, L"TAS: %.0f", fd->vt );
		break;
		case TextType::TrueMPH:
			swprintf_s( buffer, size, L"TAS: %.0f", fd->vt * 0.681818182 );
		break;
		case TextType::GroundKnots:
			swprintf_s( buffer, size, L"GS: %.0f", Math2D::Length( fd->xDot, fd->yDot ) * 0.592483801 );
		break;
		case TextType::GroundFPS:
			swprintf_s( buffer, size, L"GS: %.0f", Math2D::Length( fd->xDot, fd->yDot ) );
		break;
		case TextType::GroundMPH:
			swprintf_s( buffer, size, L"GS: %.0f", Math2D::Length( fd->xDot, fd->yDot ) * 0.681818182 );
		break;
		
		case TextType::Mach:
			swprintf_s( buffer, size, L"Mach: %.0f", fd->mach );
		break;
		case TextType::GForces:
			swprintf_s( buffer, size, L"G-Forces: %.1f", fd->gs );
		break;
		
		case TextType::Heading:
			swprintf_s( buffer, size, L"Heading: %03i", (int)(fd->currentHeading + 0.5f) );
		break;
		case TextType::HeadingGround:
			swprintf_s( buffer, size, L"Gnd Heading: %03i", (int)(Num::RadToDeg( atan2(fd->yDot,fd->xDot) ) + 360.5f)%360 );
		break;
		case TextType::HeadingAir:
			swprintf_s( buffer, size, L"Dir in Air: %03i", (int)(Num::RadToDeg(DirInAir(fd)) + 360.5f)%360 );
		break;
		case TextType::HeadingDiff:
			swprintf_s( buffer, size, L"Dir Diff: %03i", (int)(Num::RadToDeg( DirInAir(fd) - fd->yaw ) + 360.5f)%360 );
		break;
		
		case TextType::WindDir:
			swprintf_s( buffer, size, L"WindDir: %03i", (int)(Num::RadToDeg( (float)atan2( fd->yDot - (float)sin(DirInAir(fd)) * fd->vt * (float)cos(fd->gamma), fd->xDot - (float)cos(DirInAir(fd)) * fd->vt * (float)cos(fd->gamma) ) ) + 360.5f)%360 );
		break;
		case TextType::WindKnots:
			swprintf_s( buffer, size, L"WindSpd: %.0f", ( cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) ) * 0.592483801 );
		break;
		case TextType::WindFPS:
			swprintf_s( buffer, size, L"WindSpd: %.0f", cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) );
		break;
		case TextType::WindMPH:
			swprintf_s( buffer, size, L"WindSpd: %.0f", ( cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) ) * 0.681818182 );
		break;
		case TextType::TailwindKnots:
			swprintf_s( buffer, size, L"Twind: %.0f", ( cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) ) * 0.592483801 );
		break;
		case TextType::TailwindFPS:
			swprintf_s( buffer, size, L"Twind: %.0f", cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) );
		break;
		case TextType::TailwindMPH:
			swprintf_s( buffer, size, L"Twind: %.0f", ( cos( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) - fd->vt * (float)cos(fd->gamma) ) * 0.681818182 );
		break;
		case TextType::CrosswindKnots:
			swprintf_s( buffer, size, L"Xwind: %.0f", ( sin( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) ) * 0.592483801 );
		break;
		case TextType::CrosswindFPS:
			swprintf_s( buffer, size, L"Xwind: %.0f", sin( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) );
		break;
		case TextType::CrosswindMPH:
			swprintf_s( buffer, size, L"Xwind: %.0f", ( sin( (float)atan2(fd->yDot,fd->xDot) - DirInAir(fd) ) * Math2D::Length( fd->xDot, fd->yDot ) ) * 0.681818182 );
		break;
		case TextType::WindHeadingEffect:
			swprintf_s( buffer, size, L"Wind Offset: %03i", (int)(Num::RadToDeg(fd->windOffset)) );
		break;
		
		case TextType::Yaw:
			swprintf_s( buffer, size, L"Yaw: %03i", (int)(Num::RadToDeg(fd->yaw) + 360.5f)%360 );
		break;
		case TextType::Beta:
			swprintf_s( buffer, size, L"Beta: %.0f", fd->beta );
		break;
		case TextType::YawTrim:
			swprintf_s( buffer, size, L"Yaw Trim: %.0f%%", fd->TrimYaw * 200.0f );
		break;
		case TextType::ClimbAngle:
			swprintf_s( buffer, size, L"Climb Angle: %.0f", Num::RadToDeg(fd->gamma) );
		break;
		case TextType::Pitch:
			swprintf_s( buffer, size, L"Pitch: %.0f", Num::RadToDeg(fd->pitch) );
		break;
		case TextType::AOA:
			swprintf_s( buffer, size, L"AOA: %.0f", fd->alpha );
		break;
		case TextType::PitchTrim:
			swprintf_s( buffer, size, L"Pitch Trim: %.0f%%", fd->TrimPitch * 200.0f );
		break;
		case TextType::Roll:
			swprintf_s( buffer, size, L"Roll: %.0f", Num::RadToDeg(fd->roll) );
		break;
		case TextType::RollTrim:
			swprintf_s( buffer, size, L"Roll Trim: %.0f%%", fd->TrimRoll * 200.0f );
		break;
		
		case TextType::Airbrake:
			swprintf_s( buffer, size, L"Brake: %.0f%%", fd->speedBrake * 100.0f );
		break;
		case TextType::Gear:
		{
			const wchar_t *gear = L"Moving...";
			if( fd->gearPos < 0.01f )
				gear = L"UP";
			else if( fd->gearPos > 0.99f )
				gear = L"DOWN";
			swprintf_s( buffer, size, L"Gear: %s", gear );
		}
		break;
		case TextType::AOAI:
		{
			const wchar_t *aoai = L"";
			if( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAAbove )
				aoai = L"|/ ABOVE";
			else if( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOABelow )
				aoai = L"/| BELOW";
			else if( fd->lightBits & (int)F4SharedMem::Headers::LightBits::AOAOn )
				aoai = L"() ON";
			swprintf_s( buffer, size, L"AOAI: %s", aoai );
		}
		break;
		
		case TextType::RPM:
			swprintf_s( buffer, size, L"RPM: %.0f%%", fd->rpm );
		break;
		case TextType::Nozzle:
			swprintf_s( buffer, size, L"Nozzle: %.0f%%", (Saitek::MainThread->Config.FalconType == F4SharedMem::FalconDataFormats::AlliedForce) ? fd->nozzlePos : (fd->nozzlePos * 100.) );
		break;
		
		case TextType::FuelTotal:
			swprintf_s( buffer, size, L"Fuel: %.0f", fd->total );
		break;
		case TextType::FuelInternal:
			swprintf_s( buffer, size, L"Fuel Int: %.0f", fd->internalFuel );
		break;
		case TextType::FuelExternal:
			swprintf_s( buffer, size, L"Fuel Ext: %.0f", fd->externalFuel );
		break;
		case TextType::FuelEPU:
			swprintf_s( buffer, size, L"Fuel EPU: %.0f%%", fd->epuFuel );
		break;
		case TextType::FuelFlow:
			swprintf_s( buffer, size, L"Fuel Flow: %.0f", fd->fuelFlow );
		break;
		case TextType::FuelTime:
		{
			if( fd->fuelFlow > 0.0f )
			{
				float fuel_minutes = fd->total / (fd->fuelFlow / 60.0f);
				int fuel_hours = (fuel_minutes + 0.5f) / 60;
				fuel_minutes -= fuel_hours * 60;
				swprintf_s( buffer, size, L"Fuel Time: %i:%02.0f", fuel_hours, fuel_minutes );
			}
		}
		break;
		case TextType::FuelDist:
		{
			if( fd->fuelFlow > 0.0f )
				swprintf_s( buffer, size, L"Fuel Dist: %.0fmi", ( Math2D::Length( fd->xDot, fd->yDot ) / 5280.0f ) * fd->total / (fd->fuelFlow / (60.0f*60.0f)) );
		}
		break;
		
		case TextType::Chaff:
			swprintf_s( buffer, size, L"Chaff: %.0f", ((fd->ChaffCount > 0.f) ? fd->ChaffCount : 0.f) );
		break;
		case TextType::Flares:
			swprintf_s( buffer, size, L"Flare: %.0f", ((fd->FlareCount > 0.f) ? fd->FlareCount : 0.f) );
		break;
		
		case TextType::CautionMaster:
			swprintf_s( buffer, size, (fd->lightBits & (int)F4SharedMem::Headers::LightBits::MasterCaution) ? L"CAUTION" : L"" );
		break;
		
		case TextType::RWRHeading:
		{
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
			{
				if( fd->selected[i] )
					swprintf_s( buffer, size, L"Threat: %03i", ((int)(Num::RadToDeg(fd->bearing[i]) + 360.5f))%360 );
			}
		}
		break;
		case TextType::RWRLethality:
		{
			for( int i = 0; i < fd->RwrObjectCount; i ++ )
			{
				if( fd->selected[i] )
					swprintf_s( buffer, size, L"Lethality: %.2f", fd->lethality[i] );
			}
		}
		break;
		
		case TextType::Steerpoint:
			swprintf_s( buffer, size, L"Steerpoint: %03i", (int)(fd->bearingToBeacon + 0.5f) );
		break;
		
		case TextType::Horizon1:
		{
			// FIXME: Should this happen here?
			DrawTools[device].UpdateHorizon( fd );
			
			// Draw horizon line 1.
			wchar_t disp[3]=L"#.";
			for( int i = 0; i < 16; i ++ )
			{
				float hue = DrawTools[device].Horizon->GetPixel(i,2).GetHue();
				if(fabs( hue - Color::Green.GetHue() ) < 110.0)
					buffer[i] = disp[0];
				else if(fabs( hue - Color::Blue.GetHue() ) < 110.0)
					buffer[i] = disp[1];
				else buffer[i] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::Horizon2:
		{
			// Draw horizon line 2.
			wchar_t disp[3]=L"#.";
			for( int i = 0; i < 16; i ++ )
			{
				float hue = DrawTools[device].Horizon->GetPixel(i,1).GetHue();
				if(fabs( hue - Color::Green.GetHue() ) < 110.0)
					buffer[i] = disp[0];
				else if(fabs( hue - Color::Blue.GetHue() ) < 110.0)
					buffer[i] = disp[1];
				else buffer[i] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::Horizon3:
		{
			// Draw horizon line 3.
			wchar_t disp[3]=L"#.";
			for( int i = 0; i < 16; i ++ )
			{
				float hue = DrawTools[device].Horizon->GetPixel(i,0).GetHue();
				if(fabs( hue - Color::Green.GetHue() ) < 110.0)
					buffer[i] = disp[0];
				else if(fabs( hue - Color::Blue.GetHue() ) < 110.0)
					buffer[i] = disp[1];
				else buffer[i] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		
		case TextType::DEDLine1:
			if( fd->DEDLines && (fd->DEDLines->Length >= 1) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->DEDLines[ 0 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine2:
			if( fd->DEDLines && (fd->DEDLines->Length >= 2) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->DEDLines[ 1 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine3:
			if( fd->DEDLines && (fd->DEDLines->Length >= 3) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->DEDLines[ 2 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine4:
			if( fd->DEDLines && (fd->DEDLines->Length >= 4) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->DEDLines[ 3 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::DEDLine5:
			if( fd->DEDLines && (fd->DEDLines->Length >= 5) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->DEDLines[ 4 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		
		case TextType::PFLLine1:
			if( fd->PFLLines && (fd->PFLLines->Length >= 1) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->PFLLines[ 0 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::PFLLine2:
			if( fd->PFLLines && (fd->PFLLines->Length >= 2) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->PFLLines[ 1 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::PFLLine3:
			if( fd->PFLLines && (fd->PFLLines->Length >= 3) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->PFLLines[ 2 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::PFLLine4:
			if( fd->PFLLines && (fd->PFLLines->Length >= 4) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->PFLLines[ 3 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		case TextType::PFLLine5:
			if( fd->PFLLines && (fd->PFLLines->Length >= 5) )
			{
				System::String ^str = System::Text::RegularExpressions::Regex::Replace( fd->PFLLines[ 4 ]->Trim(), "\\s+", " " );
				pin_ptr<const wchar_t> wch = PtrToStringChars( str );
				swprintf_s( buffer, size, L"%ls", wch );
			}
			else
				swprintf_s( buffer, size, L"" );
		break;
		
		case TextType::LightBits1_1:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << i;
				if( fd->lightBits & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::LightBits1_2:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << (i + 16);
				if( fd->lightBits & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::LightBits2_1:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << i;
				if( fd->lightBits2 & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::LightBits2_2:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << (i + 16);
				if( fd->lightBits2 & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::LightBits3_1:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << i;
				if( fd->lightBits3 & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::LightBits3_2:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << (i + 16);
				if( fd->lightBits3 & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::HsiBits1:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << i;
				if( fd->hsiBits & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		case TextType::HsiBits2:
		{
			for( int i = 0; i < 16; i ++ )
			{
				int test = 1 << (i + 16);
				if( fd->hsiBits & test )
					buffer[ i ] = L'*';
				else
					buffer[ i ] = L' ';
			}
			swprintf_s( buffer+16, size-16, L"" );
		}
		break;
		
		case TextType::RunTime:
			swprintf_s( buffer, size, L"RunTime: %.2f sec", total_time );
		break;
		
		case TextType::TexW:
			swprintf_s( buffer, size, L"TexW: %i", Saitek::MainThread->Tex ? Saitek::MainThread->Tex->Width : 0 );
		break;
		case TextType::TexH:
			swprintf_s( buffer, size, L"TexH: %i", Saitek::MainThread->Tex ? Saitek::MainThread->Tex->Height : 0 );
		break;
		
		default:
			swprintf_s( buffer, size, L"" );
	}
}


void FalconOutput::DrawText( F4SharedMem::FlightData ^fd, int type, double total_time, void *device, int x, int y, System::Drawing::Graphics ^gfx, System::Drawing::Font ^font, System::Drawing::Brush ^brush )
{
	wchar_t buffer[ 1024 ];
	FormatText( fd, type, total_time, device, buffer, 1024 );
	
	System::String ^str = gcnew System::String( buffer );
	gfx->DrawString( str, font, brush, (float)( x ), (float)( y ) );
	delete str;
}


void FalconOutput::DrawImage( F4SharedMem::FlightData ^fd, System::Drawing::Bitmap ^tex, int type, double total_time, void *device, int x, int y, int w, int h, System::Drawing::Graphics ^gfx )
{
	bool active_sec = (fmod( total_time, 2. ) > 1.);
	bool active_half_sec = (fmod( total_time, 1. ) > 0.5);
	bool active_quarter_sec = (fmod( total_time, 0.5 ) > 0.25);
	bool active_eighth_sec = (fmod( total_time, 0.25 ) > 0.125);
	
	using namespace System::Drawing;
	
	Brush ^black_brush = DrawTools[device].GetBrush( Color::Black );
	Brush ^red_brush = DrawTools[device].GetBrush( Color::Red );
	Brush ^green_brush = DrawTools[device].GetBrush( Color::Green );
	Brush ^blue_brush = DrawTools[device].GetBrush( Color::Blue );
	Brush ^yellow_brush = DrawTools[device].GetBrush( Color::Yellow );
	Brush ^magenta_brush = DrawTools[device].GetBrush( Color::Magenta );
	Brush ^grey_brush = DrawTools[device].GetBrush( Color::Gray );
	Brush ^brown_brush = DrawTools[device].GetBrush( Color::Brown );
	
	Pen ^white_pen = DrawTools[device].GetPen( Color::White );
	Pen ^green_pen = DrawTools[device].GetPen( Color::Green );
	Pen ^orange_pen = DrawTools[device].GetPen( Color::Orange );
	Pen ^grey_pen = DrawTools[device].GetPen( Color::Gray );
	
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
			delete gfx->Clip;
			gfx->Clip = gcnew Region( clip_path );
			delete clip_path;
			
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
			delete sky_points;
			delete gfx->Clip;
			gfx->Clip = gcnew Region( System::Drawing::Rectangle( 0, 0, 320, 240 ) );

			// Draw inner border.
			gfx->DrawEllipse( white_pen, x + w/8.f, y + h/8.f, w*3.f/4.f, h*3.f/4.f );

			// Draw fixed markings.
			gfx->DrawLine( orange_pen, x + w*3.f/16.f, y + h/2.f, x + w*7.f/16.f, y + h/2.f );
			gfx->DrawLine( orange_pen, x + w*9.f/16.f, y + h/2.f, x + w*13.f/16.f, y + h/2.f );
			gfx->DrawLine( orange_pen, x + w/2.f, y + h/8.f, x + w/2.f, y + h/4.f );
		}
		break;

		case ImageType::RWRSimple:
		{
			// Draw our plane's silhouette.
			cli::array<System::Drawing::PointF> ^silhouette = gcnew cli::array<System::Drawing::PointF>( FalconSilhouette->Length );
			for( int i = 0; i < FalconSilhouette->Length; i ++ )
			{
				silhouette[ i ].X = FalconSilhouette[ i ].X;
				silhouette[ i ].Y = FalconSilhouette[ i ].Y;
			}
			ScalePoints( silhouette, x + w/4.f, y + h/4.f, w/2.f, h/2.f );
			gfx->FillPolygon( green_brush, silhouette );
			UndoScalePoints( silhouette, x + w/4.f, y + h/4.f, w/2.f, h/2.f );
			delete silhouette;

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
			float nozzle_h = fd->nozzlePos * h / ((Saitek::MainThread->Config.FalconType == F4SharedMem::FalconDataFormats::AlliedForce) ? 200. : 2.);
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

		case ImageType::Airbrake:
		{
			gfx->DrawPie( grey_pen, x-w, y, w*2, h, 270, 180 );
			gfx->FillPie( red_brush, (float)(x-w), (float)y, (float)(w*2), (float)h, fd->speedBrake * -90.f, fd->speedBrake * 180.f );
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
				Graphics ^tmp_gfx = Graphics::FromImage( tmp_bmp );
				
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
		
		case ImageType::Tex:
		{
			try
			{
				gfx->DrawImage( tex, x, y, w, h );
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexMFD1:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(750,750,450,450), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexMFD2:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(750,290,450,450), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexRWR:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(964,0,236,236), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexDED:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(570,150,380,130), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexHUD:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(0,0,560,560), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		case ImageType::TexHMCS:
		{
			try
			{
				System::Drawing::Bitmap ^region = tex->Clone( System::Drawing::Rectangle(0,630,570,570), System::Drawing::Imaging::PixelFormat::Format32bppArgb );
				gfx->DrawImage( region, x, y, w, h );
				delete region;
			}
			catch( ... ){}
		}
		break;
		
		// FIXME
		case ImageType::GaugeAzimuth:
		{
			try
			{
				/*
				LightningGauges::Renderers::F16AzimuthIndicator ^gauge = gcnew LightningGauges::Renderers::F16AzimuthIndicator();
				gauge->InstrumentState->MagneticHeadingDegrees = fd->headingState;
				gauge->InstrumentState->RollDegrees = fd->roll;
				gauge->Render( gfx, System::Drawing::Rectangle(x,y,w,h) );
				delete gauge;
				*/
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


float FalconOutput::DirInAir( F4SharedMem::FlightData ^fd )
{
	// Returns radians.
	
	if( (float) cos(fd->gamma) )
		return fd->yaw + ( Num::DegToRad(fd->beta) * cos(fd->roll) - Num::DegToRad(fd->alpha) * sin(fd->roll) ) / cos(fd->gamma);
	else
		return fd->yaw;
}
