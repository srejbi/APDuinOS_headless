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
 */

#ifndef apduinos-headless_H_
#define apduinos-headless_H_
#include <Arduino.h>
//add your includes for the project test here

#include "apd_utils.h"
#include "APDuino.h"
//#include "APDControl.h"

//#include "APDEvaluator.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project test here
#ifdef DEBUG
void sercom();
#endif
//Do not add code below this line
#endif /* apduinos-headless_H_ */
