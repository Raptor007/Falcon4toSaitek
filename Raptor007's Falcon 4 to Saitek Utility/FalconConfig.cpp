#include "FalconConfig.h"

#include <cstdio>
#include <fstream>
#include "Str.h"
#include "Saitek.h"


FalconConfig::FalconConfig( void )
{
	FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
	WaitForFalcon = false;
	AutoLaunch = false;
	FalconParameters[ F4SharedMem::FalconDataFormats::AlliedForce ] = "-g5";
}


void FalconConfig::Load( void )
{
	std::ifstream config_file( "settings.cfg" );
	if( ! config_file.good() )
		return;
	
	while( config_file.good() )
	{
		char line[ 1024 ] = "";
		config_file.getline( line, 1023 );
		
		std::list<std::string> cmd_tokens = Str::ParseCommand( line );
		
		try
		{
			while( cmd_tokens.size() )
			{
				// Pull all data relevant to one command.
				std::vector<std::string> cmd_vec;
				while( cmd_tokens.size() && (cmd_tokens.front() != ";") )
				{
					cmd_vec.push_back( cmd_tokens.front() );
					cmd_tokens.pop_front();
				}
				if( cmd_tokens.size() && (cmd_tokens.front() == ";") )
					cmd_tokens.pop_front();
				
				// Execute one command.
				if( cmd_vec.size() )
				{
					if( (cmd_vec[0] == "min_version") && (cmd_tokens.size() >= 2) )
					{
						float min_version = atof( cmd_vec[1].c_str() );
						if( (min_version - 0.0001f) > Saitek::Version )
						{
							// FIXME: Be more descriptive.
							System::Windows::Forms::MessageBox::Show( "Couldn't load: settings.cfg", "Couldn't Load Settings", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error );
							break;
						}
					}
					else
						LoadLine( cmd_vec );
				}
			}
		}
		catch( ... ){}
	}
	
	config_file.close();
}


void FalconConfig::LoadLine( std::vector<std::string> cmd_tokens )
{
	if( ! cmd_tokens.size() )
		return;
	
	std::string cmd = cmd_tokens[ 0 ];
	
	if( (cmd == "path") && (cmd_tokens.size() >= 3) )
	{
		std::string falcon = cmd_tokens[ 1 ];
		F4SharedMem::FalconDataFormats falcon_type = F4SharedMem::FalconDataFormats::AlliedForce;
		std::string path = cmd_tokens[ 2 ];
		
		if( falcon == "alliedforce" )
			falcon_type = F4SharedMem::FalconDataFormats::AlliedForce;
		else if( falcon == "bms2" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS2;
		else if( falcon == "bms3" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS3;
		else if( falcon == "bms4" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS4;
		else if( falcon == "openfalcon" )
			falcon_type = F4SharedMem::FalconDataFormats::OpenFalcon;
		else if( falcon == "freefalcon5" )
			falcon_type = F4SharedMem::FalconDataFormats::FreeFalcon5;
		
		FalconPaths[ falcon_type ] = gcnew System::String( path.c_str() );
	}
	else if( (cmd == "param") && (cmd_tokens.size() >= 3) )
	{
		std::string falcon = cmd_tokens[ 1 ];
		F4SharedMem::FalconDataFormats falcon_type = F4SharedMem::FalconDataFormats::AlliedForce;
		std::string parameters = cmd_tokens[ 2 ];
		
		if( falcon == "alliedforce" )
			falcon_type = F4SharedMem::FalconDataFormats::AlliedForce;
		else if( falcon == "bms2" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS2;
		else if( falcon == "bms3" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS3;
		else if( falcon == "bms4" )
			falcon_type = F4SharedMem::FalconDataFormats::BMS4;
		else if( falcon == "openfalcon" )
			falcon_type = F4SharedMem::FalconDataFormats::OpenFalcon;
		else if( falcon == "freefalcon5" )
			falcon_type = F4SharedMem::FalconDataFormats::FreeFalcon5;
		
		FalconParameters[ falcon_type ] = gcnew System::String( parameters.c_str() );
	}
	else if( (cmd == "falcon") && (cmd_tokens.size() >= 2) )
	{
		std::string falcon = cmd_tokens[ 1 ];
		
		if( falcon == "alliedforce" )
			FalconType = F4SharedMem::FalconDataFormats::AlliedForce;
		else if( falcon == "bms2" )
			FalconType = F4SharedMem::FalconDataFormats::BMS2;
		else if( falcon == "bms3" )
			FalconType = F4SharedMem::FalconDataFormats::BMS3;
		else if( falcon == "bms4" )
			FalconType = F4SharedMem::FalconDataFormats::BMS4;
		else if( falcon == "openfalcon" )
			FalconType = F4SharedMem::FalconDataFormats::OpenFalcon;
		else if( falcon == "freefalcon5" )
			FalconType = F4SharedMem::FalconDataFormats::FreeFalcon5;
	}
	else if( (cmd == "wait") && (cmd_tokens.size() >= 2) )
	{
		std::string wait = cmd_tokens[ 1 ];
		
		if( wait == "true" )
			WaitForFalcon = true;
		else if( wait == "false" )
			WaitForFalcon = false;
	}
	else if( (cmd == "autolaunch") && (cmd_tokens.size() >= 2) )
	{
		std::string autolaunch = cmd_tokens[ 1 ];
		
		if( autolaunch == "true" )
			AutoLaunch = true;
		else if( autolaunch == "false" )
			AutoLaunch = false;
	}
	else if( (cmd == "config") && (cmd_tokens.size() >= 3) )
	{
		System::String ^guid_str = gcnew System::String( cmd_tokens[ 1 ].c_str() );
		System::String ^config_name = gcnew System::String( cmd_tokens[ 2 ].c_str() );
		
		if( ! StartupConfigs.ContainsKey( guid_str ) )
			StartupConfigs[ guid_str ] = gcnew System::Collections::Generic::List<System::String^>;
		
		StartupConfigs[ guid_str ]->Add( config_name );
	}
}


void FalconConfig::Save( void )
{
	FILE *config_file = fopen( "settings.cfg", "wt" );
	if( ! config_file )
	{
		System::Windows::Forms::MessageBox::Show( "Couldn't save: settings.cfg", "Couldn't Save Settings", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error );
		return;
	}
	
	fprintf( config_file, "// Raptor007's Falcon 4 to Saitek Utility\n\n" );
	fprintf( config_file, "min_version 2.0\n" );
	fprintf( config_file, "version %.1f\n\n", Saitek::Version );
	
	if( FalconType == F4SharedMem::FalconDataFormats::AlliedForce )
		fprintf( config_file, "falcon alliedforce\n\n" );
	else if( FalconType == F4SharedMem::FalconDataFormats::BMS2 )
		fprintf( config_file, "falcon bms2\n\n" );
	else if( FalconType == F4SharedMem::FalconDataFormats::BMS3 )
		fprintf( config_file, "falcon bms3\n\n" );
	else if( FalconType == F4SharedMem::FalconDataFormats::BMS4 )
		fprintf( config_file, "falcon bms4\n\n" );
	else if( FalconType == F4SharedMem::FalconDataFormats::OpenFalcon )
		fprintf( config_file, "falcon openfalcon\n\n" );
	else if( FalconType == F4SharedMem::FalconDataFormats::FreeFalcon5 )
		fprintf( config_file, "falcon freefalcon5\n\n" );
	
	if( WaitForFalcon )
		fprintf( config_file, "wait true\n" );
	else
		fprintf( config_file, "wait false\n" );
	
	if( AutoLaunch )
		fprintf( config_file, "autolaunch true\n\n" );
	else
		fprintf( config_file, "autolaunch false\n\n" );
	
	System::Collections::Generic::Dictionary< F4SharedMem::FalconDataFormats, System::String^ >::Enumerator ^iter = FalconPaths.GetEnumerator();
	while( iter->MoveNext() )
	{
		F4SharedMem::FalconDataFormats falcon_type = iter->Current.Key;
		const char *falcon_type_string = NULL;
		
		if( falcon_type == F4SharedMem::FalconDataFormats::AlliedForce )
			falcon_type_string = "alliedforce";
		else if( falcon_type == F4SharedMem::FalconDataFormats::BMS2 )
			falcon_type_string = "bms2";
		else if( falcon_type == F4SharedMem::FalconDataFormats::BMS3 )
			falcon_type_string = "bms3";
		else if( falcon_type == F4SharedMem::FalconDataFormats::BMS4 )
			falcon_type_string = "bms4";
		else if( falcon_type == F4SharedMem::FalconDataFormats::OpenFalcon )
			falcon_type_string = "openfalcon";
		else if( falcon_type == F4SharedMem::FalconDataFormats::FreeFalcon5 )
			falcon_type_string = "freefalcon5";
		
		if( falcon_type_string )
		{
			char *falcon_path = (char*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( iter->Current.Value ).ToPointer();
			fprintf( config_file, "path %s \"%s\"\n", falcon_type_string, falcon_path );
			System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( falcon_path ) );
			
			try
			{
				char *falcon_params = (char*) System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( FalconParameters[falcon_type] ).ToPointer();
				fprintf( config_file, "param %s \"%s\"\n", falcon_type_string, falcon_params );
				System::Runtime::InteropServices::Marshal::FreeHGlobal( System::IntPtr( falcon_params ) );
			}
			catch( ... ){}
			
			fprintf( config_file, "\n" );
		}
	}
	
	for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
	{
		if( (*inst_iter)->Config )
			fprintf( config_file, "config %s \"%s\"\n", (*inst_iter)->GuidString().c_str(), (*inst_iter)->Config->Name.c_str() );
		else
			fprintf( config_file, "config %s \"\"\n", (*inst_iter)->GuidString().c_str() );
	}
	
	fclose( config_file );
	config_file = NULL;
}
