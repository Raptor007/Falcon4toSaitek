#pragma once
class FalconOutput;

#include <msclr\auto_gcroot.h>
#include <string>
#include <map>
#include <tchar.h>

class FalconOutput
{
public:
	FalconOutput( void );
	
	int GetTextType( std::string name );
	int GetImageType( std::string name );
	int GetCondition( std::string name );
	std::string GetTextName( int type );
	std::string GetImageName( int type );
	std::string GetConditionName( int type );
	
	bool CheckCondition( F4SharedMem::FlightData ^fd, int type, double total_time );
	void FormatText( F4SharedMem::FlightData ^fd, int type, double total_time, wchar_t *buffer, int size = 1024 );
	void DrawText( F4SharedMem::FlightData ^fd, int type, double total_time, int x, int y, System::Drawing::Graphics ^gfx, System::Drawing::Font ^font, System::Drawing::Brush ^brush );
	void DrawImage( F4SharedMem::FlightData ^fd, int type, double total_time, int x, int y, int w, int h, System::Drawing::Graphics ^gfx );
	void ScalePoints( cli::array<System::Drawing::PointF> ^points, float x, float y, float w, float h );
	void UndoScalePoints( cli::array<System::Drawing::PointF> ^points, float x, float y, float w, float h );
	
	float DirInAir( F4SharedMem::FlightData ^fd );
	
private:
	std::map< std::string, int > TextTypes;
	std::map< std::string, int > ImageTypes;
	std::map< std::string, int > Conditions;
	std::string GetName( std::map< std::string, int > *map, int type );
	int GetType( std::map< std::string, int > *map, std::string name );

	gcroot<cli::array<System::Drawing::PointF>^> FalconSilhouette;
};

namespace Condition
{
	enum
	{
		Nothing = 0,
		
		RWRMissile,
		RWRLock,
		RWRLethal,
		RWRContact,
		
		CautionMaster,
		CautionAltitude,
		CautionStoresConfig,
		CautionECM,
		CautionFuel,
		CautionOil,
		CautionEngineFault,
		CautionAvionics,
		CautionFLCS,
		
		ECM,
		
		Afterburner,
		
		AirBrake,
		AirBrake33,
		AirBrake66,
		AirBrake99,
		
		GearDown,
		GearUp,
		GearMoving,
		AOAAbove,
		AOABelow,
		AOAOn,
		GearDownAOAAbove,
		GearDownAOABelow,
		GearDownAOAOn,
		
		BadAttitude,

		ChaffLow,
		ChaffEmpty,
		FlareLow,
		FlareEmpty,

		FuelLow,
		FuelCritical,
		FuelEmpty,

		SpeedLT350,
		SpeedLT300,
		SpeedLT250,
		SpeedGT450,
		SpeedGT500,
		SpeedGT550,
		SpeedBad
	};
}

namespace TextType
{
	enum
	{
		Nothing = 0,
		
		Altitude,
		AltitudeTime,
		
		IndicatedKnots,
		IndicatedFPS,
		IndicatedMPH,
		TrueKnots,
		TrueFPS,
		TrueMPH,
		GroundKnots,
		GroundFPS,
		GroundMPH,
		
		Mach,
		GForces,
		
		Heading,
		HeadingGround,
		HeadingAir,
		HeadingDiff,
		
		WindDir,
		WindKnots,
		WindFPS,
		WindMPH,
		TailwindKnots,
		TailwindFPS,
		TailwindMPH,
		CrosswindKnots,
		CrosswindFPS,
		CrosswindMPH,
		WindHeadingEffect,
		
		Yaw,
		Beta,
		YawTrim,
		ClimbAngle,
		Pitch,
		AOA,
		PitchTrim,
		Roll,
		RollTrim,
		
		Airbrake,
		Gear,
		AOAI,
		
		RPM,
		Nozzle,
		
		FuelTotal,
		FuelInternal,
		FuelExternal,
		FuelEPU,
		FuelFlow,
		FuelTime,
		FuelDist,
		
		Chaff,
		Flares,
		
		CautionMaster,
		
		RWRHeading,
		RWRLethality,
		Steerpoint,
		
		Horizon1,
		Horizon2,
		Horizon3,
		
		DEDLine1,
		DEDLine2,
		DEDLine3,
		DEDLine4,
		DEDLine5,
		
		PFLLine1,
		PFLLine2,
		PFLLine3,
		PFLLine4,
		PFLLine5,
		
		LightBits1_1,
		LightBits1_2,
		LightBits2_1,
		LightBits2_2,
		LightBits3_1,
		LightBits3_2,
		HsiBits1,
		HsiBits2,
		
		RunTime
	};
}

namespace ImageType
{
	enum
	{
		Nothing = 0,

		Attitude,
		Gear,
		Airbrake,
		ILS,
		RWRSimple,
		Throttle,
		Warning,

		PitchTrim,
		RollTrim,
		YawTrim,

		ScreenCopy,
		ScreenCenter,
		ScreenCenterZoomed,
		ScreenCursor,
		ScreenCursorZoomed
	};
}
