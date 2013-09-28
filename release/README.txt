=====================================================
|      Raptor007's Falcon 4 to Saitek Utility       |
|             Version 2.0 (2013-09-28)              |
|                                                   |
|             http://www.raptor007.com/             |
| http://www.saitekforum.com/showthread.php?t=16028 |
|                 blair@datapro.net                 |
=====================================================


This program was written by Raptor007 (Blair Sherman).  Email me or find my thread on
saitekforums.com if you find a bug or would like additional features.  I have plans
for additional features, so keep watching for updated versions.

This program would be nothing without the F4SharedMemory library, by Lightning of
viperpits.org.  Thanks for the excellent work!

Special thanks to Darkcloud of saitekforum.com for pointing me in the right direction.


INSTALLATION
------------
First you'll need to install the Saitek X52 Pro drivers, FIP drivers, and SST
programming software (in that order).  These files are available from saitek.com:
  http://www.saitek.com/uk/down/drivers.php

You might also need to install the Microsoft Visual C++ 2008 runtime:
  http://www.microsoft.com/downloads/en/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf

Windows XP users may need to install Microsoft .NET Framework 2.0:
  http://www.microsoft.com/en-us/download/details.aspx?id=1639

Other than that, there's really nothing to do besides unzip the archive, which I
assume you've already done to read this file.  Now you can place the "Raptor007's
Falcon 4 to Saitek Utility" folder wherever you'd like it to be.  (I usually place
it inside the "Lead Pursuit" folder, but this is not required.)

Keep everything together in that folder!  If F4SharedMem.dll is removed, this
utility will NOT function.


GETTING STARTED
---------------
Default configurations for X52 Pro and FIP are provided, so the easiest way to get
started is to simply select your flavor of Falcon 4 from the drop-down, click Start,
and then go play Falcon 4.


USING AUTO-LAUNCH
-----------------
You can use this utility to launch Falcon 4 by checking the "Automatically Start
Falcon" checkbox.  Click the "Browse..." button to select the Falcon 4 executable
for the selected flavor of Falcon 4 (such as "FalconAF.exe" for Allied Force).

As of v2.0 of this utility, it will individually remember each Falcon type's path,
so you can easily switch between Falcon types without having to re-select your exe.


CUSTOMIZING
-----------
You can customize your output configurations by either editing the defaults or
creating your own from scratch.  Right now these are only editable as text files,
but I've made all the info somewhat human-readable.  I recommend using the sample
config files as an example to learn the format.

If you ever need to restore default configs, simply quit and erase everything in
the Configs folder.  The next time you launch this utility, it will create new
default configurations.

When adding images to the FIP, the first 2 numbers after the image type specify
the top-left corner (x y).  The last 2 numbers specify the size (w h).

When adding text to the FIP, the 2 numbers specify the top-left corner (x y).

When defining LED states for the X52 Pro buttons or FIP pages, the number at the
end specifies the blink rate.  0 means solid, 2 means slow blink, 4 means medium
blink, 8 means fast blink.  You can also experiment with other blink speeds.

Names of LEDs:
  fire
  a
  b
  hat2
  t1
  t3
  t5
  d
  e
  clutch
  throttle

LED colors for A/B/Hat2/T1/T3/T5/D/E/Clutch:
  green
  yellow
  red
  off

LED colors for Fire/Throttle:
  on
  off

Conditions for LEDs:
  rwr_missile
  rwr_lock
  rwr_lethal
  rwr_contact
  caution_master
  caution_altitude
  caution_stores_config
  caution_ecm
  caution_fuel
  caution_oil
  caution_engine_fault
  caution_avionics
  caution_flcs
  ecm
  afterburner
  airbrake
  airbrake_33
  airbrake_66
  airbrake_99
  gear_down
  gear_up
  gear_moving
  aoa_above
  aoa_below
  aoa_on
  gear_down_aoa_above
  gear_down_aoa_below
  gear_down_aoa_on
  bad_attitude
  chaff_low
  chaff_empty
  flare_low
  flare_empty
  fuel_low
  fuel_critical
  fuel_empty
  speed_lt350
  speed_lt300
  speed_lt250
  speed_gt450
  speed_gt500
  speed_gt550
  bad_speed

Text for MFD/FIP:
  altitude
  altitude_time
  indicated_knots
  indicated_fps
  indicated_mph
  true_knots
  true_fps
  true_mph
  ground_knots
  ground_fps
  ground_mph
  mach
  g_forces
  heading
  heading_ground
  heading_air
  heading_diff
  wind_dir
  wind_knots
  wind_fps
  wind_mph
  tailwind_knots
  tailwind_fps
  tailwind_mph
  crosswind_knots
  crosswind_fps
  crosswind_mph
  wind_heading_effect
  yaw
  beta
  yaw_trim
  climb_angle
  pitch
  aoa
  pitch_trim
  roll
  roll_trim
  airbrake
  gear
  aoai
  rpm
  nozzle
  fuel_total
  fuel_internal
  fuel_external
  fuel_epu
  fuel_flow
  fuel_time
  fuel_dist
  chaff
  flares
  caution_master
  rwr_heading
  rwr_lethality
  steerpoint
  horizon_1
  horizon_2
  horizon_3
  ded_line_1
  ded_line_2
  ded_line_3
  ded_line_4
  ded_line_5
  pfl_line_1
  pfl_line_2
  pfl_line_3
  pfl_line_4
  pfl_line_5
  light_bits_1_1
  light_bits_1_2
  light_bits_2_1
  light_bits_2_2
  light_bits_3_1
  light_bits_3_2
  hsi_bits_1
  hsi_bits_2
  run_time

Images for FIP:
  attitude
  gear
  airbrake
  ils
  rwr_simple
  throttle
  warning
  pitch_trim
  roll_trim
  yaw_trim
  screen_copy
  screen_center
  screen_center_zoomed
  screen_cursor
  screen_cursor_zoomed


TROUBLESHOOTING
---------------
If you get no lights or MFD activity after clicking Start and opening Falcon 4, you
probably need to restart the Saitek DirectOutput service.  To do this, quit Falcon 4
and click the "Restart DirectOutput" button at the bottom of the settings window.  It
should work properly the next time you start it.

If you get an error about DirectOutput not found or the list of devices is empty, you
may need to reinstall the Saitek drivers.  This version of my utility is designed to
work with Saitek DirectOutput 6.6, so you will probably need to install FIP drivers
even if you only have an X52 Pro.

If Falcon 4 freezes when you launch it, hit Stop, check the "Wait for Falcon" box,
then hit Start and try again.


PLANNED IMPROVEMENTS
--------------------
* Use F4TexSharedMem to copy textures directly to the FIP from BMS4.
* New FIP images:
 - Full-featured RWR.
 - Damage report.
 - Map with bullseye, if possible.
* Nice GUI mode for editing configs.
* Ability to read v1.x config files for X52 Pro.


CHANGES: v2.0 (2013-09-28)
--------------------------
* Rewritten from scratch, because the old code was a messy kludge.
* Supports X52 Pro and FIP, including multiple FIPs.
* Requires DirectOutput version 6.6 or newer (included with FIP drivers).
* Updated to VC++ 2008 runtime version 9.0.30729.1, and included the DLLs.
* Now multi-threaded, so the UI remains functional after starting it.
* All threads are currently run at Normal priority; this may change if users
  with single-core CPUs report issues.
* Customization is now achieved through text config files with human-readable
  variable names.
* Allows easily switching between configuration files.
* Added support for FreeFalcon5 format.
* Fixed display of nozzle position in BMS4 (scaled x100).

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
