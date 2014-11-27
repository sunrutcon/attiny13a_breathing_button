attiny13a_breathing_button
==========================
Breathing leds with attiny13a and button connected on reset pin.
Button is used to turn on and off attiny13.
Every time button is pressed microcontroller is reseted and toggles internal state that is written in eeprom.
First state runs breathing, and second puts microcontroller in power down mode. 
While in power down mode microcontroller can be tunred on by pressing reset button.
