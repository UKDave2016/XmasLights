# XmasLights

PIC16F676 used to flash 4 LEDS, with a mode button

In the main loop we check for RA2 going high, debounce it with a delay timer, change the mode, and then wait for the button to be released.

It's trivial, but added a nice display to one of our xmas ornaments!
