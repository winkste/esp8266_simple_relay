/*****************************************************************************************
* FILENAME :        relay.c          
*
* DESCRIPTION :
*       File to support simple wemos relay shield
*
* PUBLIC FUNCTIONS :
* boolean relay_ProcessPublishRequests(void)
* void relay_CallbackMqtt(char* p_topic, String p_payload) 
* void relay_InitializePins(void)
* void relay_ToggleSimpleLight(void)
* void relay_Reconnect() 
*
*
* NOTES :
*       
*       The relay implements simple MQTT relay switch with the following
*       command set:
*         MQTT_SUB_TOGGLE           "/simple_relay/toggle" // command message for toggle command
*         MQTT_SUB_BUTTON           "/simple_relay/switch" // command message for button commands
*         MQTT_PUB_LIGHT_STATE      "/simple_relay/status" //state of relais
*       
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
* 
* AUTHOR :    Stephan Wink        START DATE :    01.10.2017
*
*
* REF NO  VERSION DATE    WHO     DETAIL
* 000       16.10         SWI     migration from template      
* 001       05.11         SWI     migrated from template
* 002       11.11         SWI     add generic command subscription
*
*****************************************************************************************/

/*****************************************************************************************
 * Include Interfaces
*****************************************************************************************/
#include <ESP8266WiFi.h>
#include "WiFiManager.h" // local modified version          
#include <PubSubClient.h>
#include <EEPROM.h>
#include "gensettings.h"

#include "prjsettings.h"

/*****************************************************************************************
 * Local constant defines
*****************************************************************************************/

/*****************************************************************************************
 * Local function like makros 
*****************************************************************************************/

/*****************************************************************************************
 * Local type definitions (enum, struct, union):
*****************************************************************************************/

/*****************************************************************************************
 * Global data definitions (unlimited visibility, to be avoided):
*****************************************************************************************/

/****************************************************************************************/
/* Local function prototypes (always use static to limit visibility): 
*****************************************************************************************/
static void TurnRelayOff(void);
static void TurnRelayOn(void);
static void setSimpleLight(void);

/*****************************************************************************************
 * Local data definitions:
 * (always use static: limit visibility, const: read only, volatile: non-optimizable) 
*****************************************************************************************/
static boolean              simpleLightState_bolst = false;
static boolean              publishState_bolst = true;

/*****************************************************************************************
* Global functions (unlimited visibility): 
*****************************************************************************************/

/**---------------------------------------------------------------------------------------
 * @brief     This function processes the publish requests and is called cyclic.   
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    This function returns 'true' if the function processing was successful.
 *             In all other cases it returns 'false'.
*//*-----------------------------------------------------------------------------------*/
boolean relay_ProcessPublishRequests(void)
{
  String tPayload;
  boolean ret = false;

  if(true == publishState_bolst)
  {
    Serial.print("[mqtt] publish requested state: ");
    Serial.print(MQTT_PUB_LIGHT_STATE);
    Serial.print("  :  ");
    if(true == simpleLightState_bolst)
    {
      ret = client_sts.publish(build_topic(MQTT_PUB_LIGHT_STATE), MQTT_PAYLOAD_CMD_ON, true);
      Serial.println(MQTT_PAYLOAD_CMD_ON);
    }
    else
    {
      ret = client_sts.publish(build_topic(MQTT_PUB_LIGHT_STATE), MQTT_PAYLOAD_CMD_OFF, true); 
      Serial.println(MQTT_PAYLOAD_CMD_OFF); 
    } 
    if(ret)
    {
      publishState_bolst = false;     
    }
  }
 
  return ret;  
}

/**---------------------------------------------------------------------------------------
 * @brief     This callback function processes incoming MQTT messages and is called by   
 *              the PubSub client
 * @author    winkste
 * @date      20 Okt. 2017
 * @param     p_topic     topic which was received
 * @param     p_payload   payload of the received MQTT message
 * @param     p_length    payload length
 * @return    This function returns 'true' if the function processing was successful.
 *             In all other cases it returns 'false'.
*//*-----------------------------------------------------------------------------------*/
void relay_CallbackMqtt(char* p_topic, String p_payload) 
{

  if (String(build_topic(MQTT_SUB_TOGGLE)).equals(p_topic)) 
  {
    relay_ToggleSimpleLight();
  }
  // execute command to switch on/off the light
  else if (String(build_topic(MQTT_SUB_BUTTON)).equals(p_topic)) 
  {
    // test if the payload is equal to "ON" or "OFF"
    if(0 == p_payload.indexOf(String(MQTT_PAYLOAD_CMD_ON))) 
    {
      simpleLightState_bolst = true;
      setSimpleLight();  
    }
    else if(0 == p_payload.indexOf(String(MQTT_PAYLOAD_CMD_OFF)))
    {
      simpleLightState_bolst = false;
      setSimpleLight();
    }
    else
    {
      Serial.print("[mqtt] unexpected command: "); 
      Serial.println(p_payload);
    }   
  }  
}

/**---------------------------------------------------------------------------------------
 * @brief     This initializes the used input and output pins
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    void
*//*-----------------------------------------------------------------------------------*/
void relay_InitializePins(void)
{
  pinMode(SIMPLE_LIGHT_PIN, OUTPUT);
  setSimpleLight();
}

/**---------------------------------------------------------------------------------------
 * @brief     This function toggles the relais
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    void
*//*-----------------------------------------------------------------------------------*/
void relay_ToggleSimpleLight(void)
{
  if(true == simpleLightState_bolst)
  {   
    TurnRelayOff();  
  }
  else
  {   
    TurnRelayOn();
  }
}

/**---------------------------------------------------------------------------------------
 * @brief     This function handles the connection to the MQTT broker. If connection can't
 *              be established after several attempts the WifiManager is called. If 
 *              connection is successfull, all needed subscriptions are done.
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    n/a
*//*-----------------------------------------------------------------------------------*/
void relay_Reconnect() 
{ 
  // ... and resubscribe
  client_sts.subscribe(build_topic(MQTT_SUB_TOGGLE));  // toggle sonoff button
  client_sts.loop();
  Serial.print("[mqtt] subscribed 1: ");
  Serial.println(MQTT_SUB_TOGGLE);
  client_sts.subscribe(build_topic(MQTT_SUB_BUTTON));  // change button state with payload
  client_sts.loop();
  Serial.print("[mqtt] subscribed 2: ");
  Serial.println(MQTT_SUB_BUTTON);
  client_sts.loop();
}

/****************************************************************************************/
/* Local functions (always use static to limit visibility): */
/****************************************************************************************/

/**---------------------------------------------------------------------------------------
 * @brief     This function turns the relay off
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    void
*//*-----------------------------------------------------------------------------------*/
static void TurnRelayOff(void)
{
  simpleLightState_bolst = false;
  digitalWrite(SIMPLE_LIGHT_PIN, LOW);
  Serial.println("relais state: OFF");
  Serial.println("request publish");
  publishState_bolst = true;
}

/**---------------------------------------------------------------------------------------
 * @brief     This function turns the relay on
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    void
*//*-----------------------------------------------------------------------------------*/
static void TurnRelayOn(void)
{
  simpleLightState_bolst = true;
  digitalWrite(SIMPLE_LIGHT_PIN, HIGH);
  Serial.println("Button state: ON");
  Serial.println("request publish");
  publishState_bolst = true;
}

/**---------------------------------------------------------------------------------------
 * @brief     This function sets the relay based on the state of the global variable
 *              simpleLightState_bolst
 * @author    winkste
 * @date      20 Okt. 2017
 * @return    n/a
*//*-----------------------------------------------------------------------------------*/
static void setSimpleLight(void)
{
  if(true == simpleLightState_bolst)
  {
    TurnRelayOn(); 
  }
  else
  {
    TurnRelayOff(); 
  }
}


/****************************************************************************************/
