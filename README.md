# kbd_backlight
Controls the keyboard backlight on Linux

Options:

-e

  Enable, set to 100%
  
-d

  Disable, set to 0%

-l <num>

  Set the level to <num> - must be between 0 and 100

This is hardcoded to use /sys/class/leds/kbd_backlight/brightness.  If
your system does not use this file for backlight control, then this
program isn't for you.

To install, run:
# root needs to own this
chown root:root /bin/kbd_backlight
# Set suid bit to run as root.
chmod a+xs /bin/kbd_backlight
