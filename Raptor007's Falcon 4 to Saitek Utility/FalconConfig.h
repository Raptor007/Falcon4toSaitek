#pragma once

ref class FalconConfig
{
public:
	F4SharedMem::FalconDataFormats FalconType;
	bool WaitForFalcon;
	bool AutoLaunch;
	System::String ^FalconPath;
	System::String ^FalconParameters;
	
	FalconConfig( void );
};
