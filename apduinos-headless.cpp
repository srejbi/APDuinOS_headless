/* APDuinOS Headless
 * Copyright (C) 2012 by Gyorgy Schreiber
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
 */

// Do not remove the include below
#include "apduinos-headless.h"


#ifndef __AVR_ATmega2560__
#error "currently only runs on the mega2560"
#endif

/* App specific defines, constants, declarations */
//#include "apd_prototype.h"         // use prototype stuff
// global internals
char ts[] = "1970/01/01 00:00:00";   // string used for timestamp

APDuino *pAPD;                       // APDuino pointer

// timers
unsigned int uIdleDuration=60000;    // how long of no local inactivity to consider device idle

int firstrun = 1 ;
/***********************************************************************************************
  setup
***********************************************************************************************/
void setup(void) {
  delay(500);                   // delay to allow powerup (seems to help w/ some shields)

  // Serial is set up in APDuino. best is to start up with APDuino instance creation
  Serial.print( freeMemory(), DEC); SerPrintP(" RAM free.\n");
  if (NULL != (pAPD = new APDuino(57600))) {
  	pAPD->setup_with_storage(4,SPI_HALF_SPEED);					// set up Time, SD, Ethernet, load SA,CA,RA
  } else {
      SerPrintP("APDuino init failed. Recompile with #DEBUG.\n");
      return;
  }

  Serial.print( freeMemory(), DEC); SerPrintP(" RAM free.\n");

  if (pAPD->bConfigured() && pAPD->storage_ready()) {
  	SerPrintP("Ready.\n");
  } else {
  	if (pAPD->storage_ready()) {
			// APDuino will be running in Service Mode
			SerPrintP("\nAPDuino unconfigured. Configure and reset.\nWill loop core services.\n");
  	} else {
  		SerPrintP("Fix the EtherShield/SD reader.\n");
  		while (true) ;
  	}
  }

  pAPD->start_idling(uIdleDuration);     // idle ui (can shut down lcd based on idling)
  pAPD->unidle_device();                // we're not idle at startup
  delay(300);

  // this is moved to apduino
  SerPrintP("APP: SETUP DONE\n\n\n");
  delay(100);
}

// the loop
void loop(void) {

  if (pAPD) { pAPD->loop(); }	// make sure to loop papd

  // now do whatever you want.
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

