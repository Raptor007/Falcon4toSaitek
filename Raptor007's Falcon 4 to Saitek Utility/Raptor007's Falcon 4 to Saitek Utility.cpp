// Raptor007's Falcon 4 to Saitek Utility.cpp : main project file.

#include "MainForm.h"
#include "Saitek.h"

using namespace Raptor007sFalcon4toSaitekUtility;

[STAThreadAttribute]
int main( array<System::String ^> ^args )
{
	// Enabling Windows XP visual effects before any controls are created.
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault( false ); 

	// Create the main window and run it.
	Application::Run( gcnew MainForm() );

	// Make sure we don't leave dangling threads.
	Saitek::MainThread->Running = false;

	return 0;
}
