/*****************************************************************************************
* FILENAME :        prjsettings.h          
*
* DESCRIPTION :
*       Header file to define project specific settings
*
* PUBLIC FUNCTIONS :
*       N/A
*
* NOTES :
*
* Copyright (c) [2017] [Stephan Wink]
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
vAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*****************************************************************************************/
#ifndef PRJSETTINGS_H
#define PRJSETTINGS_H

/****************************************************************************************/
/* Imported header files: */

/****************************************************************************************/
/* Global constant defines: */
#define FW_IDENTIFIER             "00003FW" // Firmware identification
#define FW_VERSION                "002"     // Firmware Version
#define FW_DESCRIPTION            "WEMOS RELAY"

#define MQTT_SUB_TOGGLE           "/simple_relay/toggle" // command message for toggle command
#define MQTT_SUB_BUTTON           "/simple_relay/switch" // command message for button commands
#define MQTT_PUB_LIGHT_STATE      "/simple_relay/status" //state of relais
#define MQTT_PAYLOAD_CMD_ON       "ON"
#define MQTT_PAYLOAD_CMD_OFF      "OFF"

// used pins
//#define BUTTON_INPUT_PIN          0  // D3
#define SIMPLE_LIGHT_PIN          5 // D1
#define LED_PIN                   SIMPLE_LIGHT_PIN

// unused pins
#define UNUSED_12                 12 // D6
#define UNUSED_13                 13 // D7
#define UNUSED_14                 14 // D5
#define UNUSED_4                  4  // D2
#define UNUSED_16                 16 // D0
#define UNUSED_2                  2  // D4
#define UNUSED_15                 15 // D8

#define SERIAL_DEBUG

/****************************************************************************************/
/* Global function like macro defines (to be avoided): */

/****************************************************************************************/
/* Global type definitions (enum, struct, union): */

/****************************************************************************************/
/* Global data allusions (allows type checking, definition in c file): */

/****************************************************************************************/
/* Global function prototypes: */

#endif /* PRJSETTINGS_H */
/****************************************************************************************/
