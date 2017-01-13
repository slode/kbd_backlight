# kbd_backlight
Controls the keyboard backlight on Linux for Asus Zenbook UX330CA

Options:

-i Increment
  
-d Decrement

-l <num>

  Set the level to <num> - must be between 0 and 3

To install, run:
# root needs to own this
chown root:root /bin/kbd_backlight
# Set suid bit to run as root.
chmod a+xs /bin/kbd_backlight
