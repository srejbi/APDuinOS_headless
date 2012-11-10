/* APDuinOS Headless
 * Copyright (C) 2012 by György Schreiber
 *
 * This Application is built on top of the APDuinOS Library
 *
 * This Application is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the APDuinOS Headless application.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * This is basically a wrapper around the application implemented in
 * the APDuinOS library. It only takes your desired Serial baudrate,
 * the rest should be configured automatically from filesystem on SD.
 *
 * If you try to build a display enabled custom version, here is where
 * display-specific stuff should be implemented.
 *
 * Callbacks for display will be re-enabled soon...
 * Also possibility will be given to peek in the debug log
 * (contains printables).
 *
 */

// Do not remove the include below
#include "apduinos-headless.h"


#ifndef __AVR_ATmega2560__
#error "currently only runs on the mega2560"
#endif

/* App specific defines, constants, declarations */
//#include "apd_prototype.h"         // use prototype stuff

// globals
APDuino *pAPD;                       // APDuino object pointer

// timers
unsigned int uIdleDuration=60000;    // how long of no local inactivity to consider device idle

int firstrun = 1 ;
/***********************************************************************************************
  setup
***********************************************************************************************/
void setup(void) {
  delay(500);                   // delay to allow powerup (seems to help w/ some shields)

  // Serial is set up in APDuino. best is to start up with APDuino instance creation
  Serial.print( freeMemory(), DEC); SerPrintP(" RAM free.\n");		// print ram for debug
  if (NULL != (pAPD = new APDuino(57600))) {
  	pAPD->setup_with_storage(4,SPI_HALF_SPEED);					// set up Time, SD, Ethernet, load SA,CA,RA
  } else {
      SerPrintP("APDuino init failed. Sources...\n");
      return;
  }
  // this is for debugging how much ram is consumed
  Serial.print( freeMemory(), DEC); SerPrintP(" RAM free.\n");

  if (pAPD->bConfigured() && pAPD->storage_ready()) {	// check APDuino app state and system state (sd)
  	SerPrintP("Ready.\n");
  } else {
  	if (pAPD->storage_ready()) {		// APDuino will be running in Service Mode
			SerPrintP("\nAPDuino unconfigured.\nWill loop core.\n");		// you should find the IP
			// (should display in the APDuino Online account as a link, or printed in the Serial/Debug log)
			// eg. http://192.168.0.21/claimdevice -> should take you to APDuino Online
			// follow the link to register device, it should come up under your devices
			// then configure and push config. (provision)
			// than refresh the device root uri (eg. http://192.168.0.21) and you should have
			// a web gui to your device, ready for further tweaking via configuration
			//
			// If that's not enough, you should attempt to add your mods via this file.
			// Good luck!
  	} else {
  		SerPrintP("Fix EtherShield/SD reader.\n");
  		while (true) ;
  	}
  }

  pAPD->start_idling(uIdleDuration);     // idle ui (can shut down lcd based on idling)
  pAPD->unidle_device();                // we're not idle at startup
  delay(300);

  // any more setup steps of your liking...

  SerPrintP("APP:SET.\n\n\n");
  delay(100);
}

// the loop
void loop(void) {

  if (pAPD) { pAPD->loop(); }	// make sure to loop APDuino; it will loop core & configured/enabled app services

  // now do whatever you want (extras)
  // if you want it to work,
  //   remember: while you're out in the main loop & not in pAPD->loop()
  //   your sensors & controls & rules & other operations are not being performed
  //   as this is all a single thread.
  //   so write quick (and safe) code, that DOES NOT WASTE TIME : no delays > 1-2ms OVERALL,
  //   try to keep the entire stuff within ~50ms (use timers/metros/flags to execute code you really have to)
  // else
  //   feel free to do whatever
  // except
  //   blaiming me :-)
}

