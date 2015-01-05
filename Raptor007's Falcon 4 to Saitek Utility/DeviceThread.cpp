#include "DeviceThread.h"
#include "Clock.h"

DeviceThread::DeviceThread( DeviceInstance *instance, FalconThread ^master_thread )
{
	Instance = instance;
	MasterThread = master_thread;
	
	SleepMs = 120;
	if( instance->Config )
		SleepMs = instance->Config->SleepMs;
	
	FD = master_thread->FD;
	Tex = master_thread->Tex;
	TexCopy = nullptr;
}

void DeviceThread::Code( void )
{
	MasterThread->ChildThreads ++;
	Instance->Begin();
	
	Clock run_timer;
	double start_ms = 0.;
	
	while( MasterThread->Running )
	{
		start_ms = run_timer.ElapsedMilliseconds();
		
		if( MasterThread->FalconRunning )
		{
			FD = MasterThread->FD;
			if( (Instance->Config) && (Instance->Config->NeedsTex()) && (Tex != MasterThread->Tex) )
			{
				if( MasterThread->TexLock.WaitOne() )
				{
					Tex = MasterThread->Tex;
					delete TexCopy;
					TexCopy = Tex ? gcnew System::Drawing::Bitmap(Tex) : nullptr;
					MasterThread->TexLock.ReleaseMutex();
				}
			}
		}
		
		if( MasterThread->FalconRunning || (! MasterThread->Config.WaitForFalcon) )
		{
			if( MasterThread->DoDeviceUpdates )
				Instance->Update( FD, TexCopy, run_timer.ElapsedSeconds() );
			
			if( Instance->Config )
				SleepMs = Instance->Config->SleepMs;
			
			System::Threading::Thread::Sleep( System::Math::Max( 1, SleepMs - (int)( run_timer.ElapsedMilliseconds() - start_ms) ) );
		}
		else
			System::Threading::Thread::Sleep( 1000 );
	}
	
	Instance->End();
	MasterThread->ChildThreads --;
}
