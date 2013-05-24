==========================================
| Raptor007's Falcon 4 to Saitek Utility |
| Version 2.0 TEST BUILD 1 (2010-12-02)  |
|                                        |
| http://www.raptor007.com/              |
| blair@datapro.net                      |
==========================================


THIS IS AN UNFINISHED TEST VERSION!  PLEASE CHECK FOR UPDATES HERE:
  http://www.saitekforum.com/showthread.php?t=16028


This program was written by Raptor007 (Blair Sherman).  Email me or find my thread on
saitekforums.com if you find a bug or would like additional features.  I have plans
for additional features, so keep watching for updated versions.

This program would be nothing without the F4SharedMemory library, by Lightning of
viperpits.org.  Thanks for the excellent work!

Special thanks to Darkcloud of saitekforum.com for pointing me in the right direction.


INSTALLATION
------------
You'll need to have both the Saitek device drivers AND the SST programming software
installed.  These files are available from saitek.com here:
  http://www.saitek.com/uk/down/drivers.htm

You also need to install the Microsoft Visual C++ 2008 runtime:
  http://www.microsoft.com/downloads/en/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf

Other than that, there's really nothing to do besides unzip the archive, which I
assume you've already done to read this file.  Now you can place the "Raptor007's
Falcon 4 to Saitek Utility" folder wherever you'd like it to be.  (I usually place it
inside the "Lead Pursuit" folder, but this is not required.)

Keep everything together in that folder!  If F4SharedMem.dll is removed, this
utility will NOT function.


GETTING STARTED
---------------
To use this utility, simply open the exe and hit Start.  Then open Falcon 4 and enjoy!

This utility will stop responding once you hit Start; you'll have to open Falcon 4 to
wake up the program, then exit Falcon 4 to get it back to it's editable status.  In a
future verison, I may fix this with multi-threading.  Feel free to kill the task if
you need to, as it does not write to disk while running.


SETTING UP MFD PAGES
--------------------
Customization not yet implemented in v2.0.


SETTING UP LEDS
---------------
Customization not yet implemented in v2.0.


SETTING UP AUTO-LAUNCH
----------------------
Not yet implemented in v2.0.


TROUBLESHOOTING
---------------
If you get no lights or MFD activity after clicking Start and opening Falcon 4, you
probably need to restart the Saitek DirectOutput service.  To do this, quit Falcon 4
and click the "Restart DirectOutput" button at the bottom of the settings window.  It
should work properly the next time you start it.

If you get an error about DirectOutput not found or the list of devices is empty, you
may need to reinstall your Saitek device drivers and the SST programming software.

If Falcon 4 freezes when you launch it, hit Stop, check the "Wait for Falcon" box,
then hit Start and try again.


CHANGES: v2.0 TEST BUILD 1 (2010-12-02)
---------------------------------------
* Rewritten from scratch, because the old code was a messy kludge.
* Supports X52 Pro and FIP.
* Only supports Allied Force so far.
* Now multi-threaded; it was necessary for FIP performance.
* Internally supports better customization options; there is no UI for this yet.

CHANGES: v1.4 (2009-03-28)
--------------------------
* Added auto-launch feature, where the program starts Falcon 4 automatically when
  the Start button is clicked.
* Fixed an issue where the program would hog too many resources on a single-core
  CPU, preventing Falcon 4 from loading.  This fix only works when auto-launch is
  used to start Falcon 4!
* Added a button to restart the Saitek DirectOutput service.
* Updated to Lightning's F4SharedMemory v2.3.2.0.
* Updated to VC++ 2005 SP1 runtime version 8.0.50727.4053, and included the DLLs.
* Program runs at BelowNormal priority while waiting for the shared memory reader
  to recognize that Falcon 4 is ready.

CHANGES: v1.3 (2009-10-24)
--------------------------
* Added support for BMS3 and BMS4 formats.
* Changed minimum MFD pages to 1, because I can only control LEDs on my MFD pages.
* Now keeps track of all Saitek DirectOutput devices and lets you select one.
* Automatically selects X52 Pro if there are multiple Saitek DirectOutput devices.
* Many new MFD options, such as groundspeed, vector in air, and wind calculations.
* Fixed a minor bug that would cause it to jump to MFD page 1 unnecessarily when
  setting the number of MFD pages.
* Increased the height of some drop-down boxes to make them easier to use.

CHANGES: v1.2 (2009-04-13)
--------------------------
* Tweaked code to compile with Lightning's F4SharedMemory v2.0.0.0.  Hopefully this
  will improve OpenFalcon compatibility.
* Added an artificial horizon option for the MFD.
* No longer deinitializes DirectOutput when Falcon 4 exits.  Now you should not
  have to quit and reopen the utility for multiple Falcon 4 runs.
* Fixed the working directory bug; auto-save now works after manual load/save.
* Fixed a potential memory leak.
* Fixed a bug that would forget your selected MFD page if it was the last.
* Fixed a bug that would forget MFD labels sometimes.

CHANGES: v1.1 (2008-12-17)
--------------------------
* Rewrote LED code entirely, to allow multiple conditions and blinking lights.
* Added many more possible conditions for LEDs, like caution lights and RWR data.
* Added RWR and LightBit options for MFD.
* Removed "Engine Fire" conditions because I never could get it to work.
* Added save/load buttons for settings, so you can easily keep multiple setups.
* Implemented code to allow v1.1 to read settings from v1.0.
* The included settings.cfg has been updated for better MFD and LED utilization.

CHANGES: v1.0 (2008-10-31)
--------------------------
* Initial release.
