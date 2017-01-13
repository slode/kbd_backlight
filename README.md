## kbd_backlight
Controls the keyboard backlight on Linux for Asus Zenbook UX330CA

Options:
```
  -i Increment
  -d Decrement
  -l <num> Set the level to <num> - must be between 0 and 3
```
#### Install
To install, run:
```bash
chown root:root /bin/kbd_backlight
chmod a+xs /bin/kbd_backlight
```

#### Usage
In **i3** set up the keyboard short-cuts like this
```bash
bindsym XF86KbdBrightnessUp exec "/bin/kbd_backlight -i"
bindsym XF86KbdBrightnessDown exec "/bin/kbd_backlight -d"
```
