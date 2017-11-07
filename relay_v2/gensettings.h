/*****************************************************************************************
* FILENAME :        gensettings.h          
*
* DESCRIPTION :
*       Header file to define general/template settings
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
#ifndef GENSETTINGS_H
#define GENSETTINGS_H

/****************************************************************************************/
/* Imported header files: */

/****************************************************************************************/
/* Global constant defines: */
#define CONFIG_SSID               "OPEN_ESP_CONFIG_AP2" // SSID of the configuration mode
#define MAX_AP_TIME               300 // restart eps after 300 sec in config mode

//#define MSG_BUFFER_SIZE           60  // mqtt messages max char size
#define MQTT_DEFAULT_DEVICE       "devXX" // default room device 

#define MQTT_PUB_FW_IDENT         "/generic/fwident" //firmware identification
#define MQTT_PUB_FW_VERSION       "/generic/fwversion" //firmware version
#define MQTT_PUB_FW_DESC          "/generic/desc" //firmware description
#define MQTT_SUB_COMMAND          "/generic/cmd" // command message for generic commands
#define MQTT_CLIENT               MQTT_DEFAULT_DEVICE // just a name used to talk to MQTT broker
#define MQTT_PAYLOAD_CMD_INFO     "INFO"
#define MQTT_PAYLOAD_CMD_SETUP    "SETUP"
#define PUBLISH_TIME_OFFSET       200     // ms timeout between two publishes

#define BUTTON_INPUT_PIN          0  // D3
#define BUTTON_TIMEOUT            1500  // max 1500ms timeout between each button press to count up (start of config)
#define BUTTON_DEBOUNCE           400  // ms debouncing for the botton

/****************************************************************************************/
/* Global function like macro defines (to be avoided): */

/****************************************************************************************/
/* Global type definitions (enum, struct, union): */
// Buffer to hold data from the WiFi manager for mqtt login
typedef struct mqttData_tag{ //80 byte
  char login[16];
  char pw[16];
  char dev_short[6];
  char cap[2]; // capability
  char server_ip[16];
  char server_port[6];
}mqttData_t;

/****************************************************************************************/
/* Global data allusions (allows type checking, definition in c file): */

/****************************************************************************************/
/* Global function prototypes: */

#endif /* GENSETTINGS_H */
/****************************************************************************************/
