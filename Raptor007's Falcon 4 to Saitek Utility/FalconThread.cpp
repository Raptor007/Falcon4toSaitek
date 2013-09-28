#include "FalconThread.h"
#include "DeviceThread.h"
#include "Saitek.h"
#include "Clock.h"


FalconThread::FalconThread( void )
{
	Running = false;
	ChildThreads = 0;
	FalconRunning = false;
}


void FalconThread::Code( void )
{
	Running = true;
	
	// Get set up to read data from Falcon, and grab some data before we spawn any device threads.
	F4SharedMem::Reader ^reader = gcnew F4SharedMem::Reader( Config.FalconType );
	if( reader->IsFalconRunning )
		FD = reader->GetCurrentData();
	else
		FD = gcnew F4SharedMem::FlightData();
	
	// If we've set it to auto-launch Falcon, do so now.
	if( Config.AutoLaunch && (Config.FalconPaths[ Config.FalconType ]->Length > 0) )
	{
		// Keep track of the working directory.
		System::String ^working_dir = System::Environment::CurrentDirectory;
		
		// Set the working directory for launching Falcon.
		int index = -1, temp_index = -1;
		while( (temp_index = Config.FalconPaths[ Config.FalconType ]->IndexOf( '\\', temp_index + 1 )) >= 0 )
			index = temp_index;
		if( index >= 0 )
			System::Environment::CurrentDirectory = Config.FalconPaths[ Config.FalconType ]->Substring( 0, index );
		
		// Launch Falcon.
		System::Diagnostics::Process ^falcon_process = System::Diagnostics::Process::Start( Config.FalconPaths[ Saitek::MainThread->Config.FalconType ], Config.FalconParameters[ Saitek::MainThread->Config.FalconType ] );
		
		// Restore the working directory.
		System::Environment::CurrentDirectory = working_dir;
		
		/*
		// Wait for Falcon 4 to finish loading before we continue.
		// NOTE: Disabled because not all types of Falcon support WaitForInputIdle!
		if( Config.WaitForFalcon )
			falcon_process->WaitForInputIdle();
		*/
	}
	
	// If we've set it to only run while Falcon is running, wait for Falcon to launch first.
	if( Config.WaitForFalcon )
	{
		// Don't spawn child threads until Falcon is opened.
		while( Running && (! reader->IsFalconRunning) )
			System::Threading::Thread::Sleep( 2000 );
	}
	
	// Make sure the condition we hit is Falcon being opened, not the Stop button.
	if( Running )
	{
		// If waiting, sleep a little longer so Falcon has time to finish launching.
		if( Config.WaitForFalcon )
			System::Threading::Thread::Sleep( 5000 );
		
		// Spawn one update thread per device.
		for( std::vector<DeviceInstance*>::iterator inst_iter = Saitek::Instances.begin(); inst_iter != Saitek::Instances.end(); inst_iter ++ )
		{
			DeviceThread ^device_thread = gcnew DeviceThread( *inst_iter, this );
			System::Threading::ThreadStart ^thread_start = gcnew System::Threading::ThreadStart( device_thread, &(DeviceThread::Code) );
			System::Threading::Thread ^thread = gcnew System::Threading::Thread( thread_start );
			thread->Start();
			//thread->Priority = System::Threading::ThreadPriority::AboveNormal;
		}
	}
	
	// Main thread loop.
	while( Running )
	{
		// Ask the reader if Falcon is running, and store it so the child threads will know.
		if( FalconRunning = reader->IsFalconRunning )
		{
			// We need try/catch in case AcquireWriterLock fails.
			try
			{
				// Make sure none of the device threads are currently using flight data.
				FDLock.AcquireWriterLock( 1000 );
				if( FDLock.IsWriterLockHeld )
				{
					// Update the flight data.
					FD = reader->GetCurrentData();
					FDLock.ReleaseLock();
				}
			}
			catch( ... ){}
			
			// Sleep a little if Falcon is running.
			System::Threading::Thread::Sleep( 100 );
		}
		else
			// Sleep a lot if Falcon is not running.
			System::Threading::Thread::Sleep( 2000 );
	}
	
	// Wait for child threads to finish before stopping execution.
	while( ChildThreads )
		System::Threading::Thread::Sleep( 500 );
}
