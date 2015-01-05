============================================
|  Raptor007's Falcon 4 to Saitek Utility  |
|         Version 2.2 (2015-01-04)         |
|                                          |
|         http://www.raptor007.com/        |
|             blair@datapro.net            |
============================================


This program was written by Raptor007 (Blair Sherman).  Email me if you find a
bug or if you think of something else you'd like this utility to do.  I already
have some plans for additional features, so keep watching for updated versions.

This program would be nothing without the F4SharedMemory library, by Lightning
of viperpits.org.  Thanks for the excellent work!

Special thanks to Darkcloud of saitekforum.com for pointing me in the right
direction.


INSTALLATION
------------
First you'll need to install some Saitek drivers that give you DirectOutput 6.6
or newer.  At this time, I recommend the latest 7.0.34.109 drivers for all your
Saitek devices (X52 Pro and FIP):
  ftp://ftp.saitek.com/pub/software/full/

You might also need to install the Microsoft Visual C++ 2008 runtime:
  http://www.microsoft.com/downloads/en/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf

Windows XP users may need to install Microsoft .NET Framework 2.0:
  http://www.microsoft.com/en-us/download/details.aspx?id=1639

Other than that, there's really nothing to do besides unzip the archive, which
I assume you've already done to read this file.  Now you can place the
"Raptor007's Falcon 4 to Saitek Utility" folder wherever you'd like it to be.
(I usually place it inside the "Lead Pursuit" folder, but that's not required.)

Keep everything together in that folder!  If F4SharedMem.dll is removed, this
utility will NOT function.  It probably won't work without F4TexSharedMem.dll
either.


SETTING UP SHARED TEXTURES
--------------------------
To get shared textures from BMS4, you'll need to install Lightning's MFD
Extractor, available here:
  https://www.assembla.com/code/lightningstools/subversion/nodes/213/releases/End%20User%20Applications

Once you've got it installed and running, right-click its tray icon and pick
"Options..." to bring up the options window.  Then select the "Performance"
tab, click "Falcon BMS Advanced Options...", and check the "Enable exporting
of 3D cockpit instrument images to shared memory" checkbox.

Unfortunately, the MFD Extractor does not support Allied Force textures.


GETTING STARTED
---------------
Default configurations for X52 Pro and FIP are provided, so the easiest way to
get started is to simply select your flavor of Falcon 4 from the drop-down,
click Start, and then go play Falcon 4.


USING AUTO-LAUNCH
-----------------
You can use this utility to launch Falcon 4 by checking the "Automatically
Start Falcon" checkbox.  Click the "Browse..." button to select the Falcon 4
executable for the selected flavor of Falcon 4 (such as "FalconAF.exe" for
Allied Force).

As of v2.0 of this utility, it will individually remember each Falcon type's
path, so you can easily switch between Falcon types without having to re-select
your exe.


CUSTOMIZING
-----------
You can customize your output configurations by either editing the defaults or
creating your own from scratch.  Right now these are only editable as text
files, but I've made all the info somewhat human-readable.  I recommend using
the sample config files as an example to learn the format.

If you ever need to restore default configs, simply quit and erase everything
in the Configs folder.  The next time you launch this utility, it will create
new default configurations.

When adding images to the FIP, the first 2 numbers after the image type specify
the top-left corner (x y).  The last 2 numbers specify the size (w h).

When adding text to the FIP, the 2 numbers specify the top-left corner (x y).

When defining LED states for the X52 Pro buttons or FIP pages, the number at
the end specifies the blink rate.  0 means solid, 2 means slow blink, 4 means
medium blink, 8 means fast blink.  You can also experiment with other blink
speeds.

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
  on_ground
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
  tex_w
  tex_h

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
  tex
  tex_mfd1
  tex_mfd2
  tex_rwr
  tex_ded
  tex_hud
  tex_hmcs


BINDING KEYS TO BUTTONS
-----------------------
When you make a new config, button presses on the FIP will change output pages,
and rotating the dials has no effect.  But you can customize these by adding
"bind" statements in your config files!

The default configurations are set up so the dials will work with BMS4's
default keyboard layout.  I recommend observing how they look before trying to
create your own from scratch.

FIP example: Bind the left dial to the A and B keys:
  bind "left_minus" "a"
  bind "left_plus" "b"

You can simulate multiple keys pressed in a row using spaces to separate them.

X52 Pro example: Bind the wheel up to type "hello" and down to "world":
  bind "up" "h e l l o"
  bind "down" "w o r l d"

NOTE: The list of keys must be enclosed in quotes!

It's also possible to create two different events for button press and release
using the + and - prefixes before the button name.  You can also use these
prefixes before key names to simulate holding down these keys.

FIP example: Bind the S6 button to hold ctrl-E for eject:
  bind "+s6" "+ctrl +e"
  bind "-s6" "-e -ctrl"

NOTE: If you bind a command to a soft-button on the FIP, that button will no
longer change pages!  But you can bind page changes on the FIP with the
at-sign (@) and page number, like so:
  bind "s6" "@6"

It's also possible to bind events per-page, which overrides the global bind
while that page is active.

FIP example:
  screen 1 bind "left_minus" "a"
  screen 1 bind "left_plus" "b"

X52 Pro example:
  mfd 1 bind "up" "a"
  mfd 1 bind "down" "b"

FIP button names:
  s1
  s2
  s3
  s4
  s5
  s6
  left_minus
  left_plus
  right_minus
  right_plus

X52 Pro button names (right wheel only):
  up
  down
  click

Key scancode names:
  esc
  1
  2
  3
  4
  5
  6
  7
  8
  9
  0
  minus
  equals
  backspace
  tab
  q
  w
  e
  r
  t
  y
  u
  i
  o
  p
  left_bracket
  right_bracket
  enter
  ctrl
  a
  s
  d
  f
  g
  h
  j
  k
  l
  semicolon
  quote
  tilde
  shift
  backslash
  z
  x
  c
  v
  b
  n
  m
  comma
  period
  slash
  right_shift
  num_star
  alt
  left_menu
  space
  capslock
  f1
  f2
  f3
  f4
  f5
  f6
  f7
  f8
  f9
  f10
  numlock
  scroll_lock
  num_7
  num_8
  num_9
  num_minus
  num_4
  num_5
  num_6
  num_plus
  num_1
  num_2
  num_3
  num_0
  num_period
  oem102
  f11
  f12
  f13
  f14
  f15
  kana
  abnt_c1
  convert
  no_convert
  yen
  abnt_c2
  num_equals
  track_prev
  at
  colon
  underline
  kanji
  stop
  ax
  unlabeled
  track_next
  num_enter
  right_ctrl
  mute
  calculator
  play_pause
  media_stop
  volume_down
  volume_up
  web_home
  num_comma
  num_slash
  print_screen
  right_alt
  menu
  pause
  home
  up
  pgup
  left
  right
  end
  down
  pgdn
  ins
  del
  win
  right_win
  apps
  power
  sleep
  wake
  web_search
  web_favorites
  web_refresh
  web_stop
  web_forward
  web_back
  my_computer
  mail
  media_select

Or you can use raw numeric scancodes by prefixing the decimal number with a
pound sign (#) like so:
  bind "s1" "#30"

The raw values for these keys come from Microsoft's DirectInput documentation,
but many of them do not behave as I'd expect.  Your mileage may vary.


TROUBLESHOOTING
---------------
If your device list is missing items, you're probably missing some drivers.
Uninstall all existing copies of Saitek DirectOutput, then install the latest
Saitek drivers for your hardware.

If you're sure you've properly installed all drivers and your device still
isn't showing up, try moving it to a different USB port.

If you get no lights or MFD activity after clicking Start and opening Falcon 4,
you may need to restart the Saitek DirectOutput service.  To do this, click the
"Restart DirectOutput" button at the bottom of the settings window.  It should
work properly the next time you click Start.

If Falcon 4 freezes when you launch it, hit Stop, check the "Wait for Falcon"
box, then hit Start and try again.

If the X52 Pro MFD starts out dim, simply roll the left wheel (page select) up,
then back down.  This seems to be caused by a bug in Saitek's 7.x.x.x drivers.

If you alt-tab out of Falcon 4, it will probably stop updating the shared
textures (this is definitely true in BMS4).  You will have to quit and re-open
Falcon 4 to fix the shared textures.


CHANGES: v2.2 (2015-01-04)
--------------------------
* Shared textures on FIP shouldn't go black or hang anymore.
* Reduced X52 Pro MFD glitches by no longer sending data that is the same as
  what is currently being displayed.
* Fixed some potential crashes, especially when using lots of devices.
* Combined BMS3 / OpenFalcon into one option because they use the same format.
* Tweaked default configurations to better match what I use while flying.

CHANGES: v2.1 (2013-10-12)
--------------------------
* Added the ability to read shared textures using Lightning's F4TexSharedMem.
* Updated default FIP config to utilize some shared textures when available.
* Can now bind device button presses to simulated keyboard presses.
* Added new default configs for FIP MFD emulation (with MFD Extractor).
* Added keybinds for BMS4 to all default configs.
* Remembers your device's selected configs.
* Added on_ground condition for LEDs.
* Tweaked text display of fuel time remaining.
* Implemented ctrl-A shortcut in config editor for select-all.
* Vastly improved memory management.
* Fixed a potential crash when applying config changes while it's running.

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
