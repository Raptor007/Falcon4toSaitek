#include "stdafx.h"
#include "FalconConfig.h"


FalconConfig::FalconConfig( void )
{
	FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
	WaitForFalcon = false;
	AutoLaunch = false;
	FalconPath = "";
	FalconParameters = "-g5";
}
