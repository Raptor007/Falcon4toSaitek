#include "DeviceThread.h"
#include "Clock.h"

DeviceThread::DeviceThread( DeviceInstance *instance, FalconThread ^master_thread )
{
	Instance = instance;
	MasterThread = master_thread;
	FD = master_thread->FD;
	SleepMs = 1000;
	if( instance->Config )
		SleepMs = instance->Config->SleepMs;
}

void DeviceThread::Code( void )
{
	MasterThread->ChildThreads ++;
	Instance->Begin();

	Clock run_timer;
	while( MasterThread->Running )
	{
		if( MasterThread->FalconRunning )
		{
			try
			{
				MasterThread->FDLock.AcquireReaderLock( 100 );
				if( MasterThread->FDLock.IsReaderLockHeld )
				{
					FD = MasterThread->FD;
					Tex = MasterThread->Tex;
					
					MasterThread->FDLock.ReleaseLock();
				}
			}
			catch( ... ){}
		}

		if( MasterThread->FalconRunning || (! MasterThread->Config.WaitForFalcon) )
		{
			if( MasterThread->DoDeviceUpdates )
				Instance->Update( MasterThread->FD, MasterThread->Tex, run_timer.ElapsedSeconds() );
			System::Threading::Thread::Sleep( SleepMs );
		}
		else
			System::Threading::Thread::Sleep( 1000 );
	}

	Instance->End();
	MasterThread->ChildThreads --;
}
