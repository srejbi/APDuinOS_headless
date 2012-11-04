APDuinOS Headless Client
http://apduino.org

Copyright (C) György Schreiber 2012.

This software is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the software.  If not, see
<http://www.gnu.org/licenses/>.

This software relies on / incorporates other free software.
See CREDITS.TXT for more details.


Installation:
-------------

1) Go to http://arduino.cc and download Arduino-1.0 for your platform (Windows, Linux, MacOSX)
2) Install (extract) Arduino-1.0 to your PC
3) Connect your Arduino Mega 2560 to your PC, install drivers (if necessary)
4) make sure you can communicate with your Arduino using your PC (and the Arduino IDE, Serial console)
5) flash the apduinos-headless.hex to your Arduino using AVRDude:
   Assuming Arduino-1.0 is installed to "C:\arduino-1.0":
   C:\arduino-1.0\hardware\tools\avr\bin\avrdude -patmega2560 -cstk500v2 "-P\\.\COM3" -b115200 -Uflash:w:apduinos-headless.hex:a "-CC:\arduino-1.0\hardware\tools\avr\etc\avrdude.conf" 
6) go to http://apduino.com, register for an account if you don't have one
7) you should see a link to claim your device, if not, connect to your Arduino using the serial monitor and check logs
8) assuming you have claimed your device with success, proceed with configuring Networking, Logging, 
   Sensors, Controls, Rules and provision settings to your device
9) enjoy!

For more information, visit http://apduino.org.
To get the source code, register on http://apduino.org.
