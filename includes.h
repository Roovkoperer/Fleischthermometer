

/***
 __        ___        _    _   _   _   _                _           
 \ \      / / |      / \  | \ | | | | | | ___  __ _  __| | ___ _ __ 
  \ \ /\ / /| |     / _ \ |  \| | | |_| |/ _ \/ _` |/ _` |/ _ \ '__|
   \ V  V / | |___ / ___ \| |\  | |  _  |  __/ (_| | (_| |  __/ |   
    \_/\_/  |_____/_/   \_\_| \_| |_| |_|\___|\__,_|\__,_|\___|_| 
***/
#include <ESP8266WiFi.h>
//#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

//#include "FS.h"

//#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
//#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
//#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

//#include <BlynkSimpleEsp8266.h>
//#include <ArduinoJson.h>




/***
     _    ____   ____   _   _                _           
    / \  |  _ \ / ___| | | | | ___  __ _  __| | ___ _ __ 
   / _ \ | | | | |     | |_| |/ _ \/ _` |/ _` |/ _ \ '__|
  / ___ \| |_| | |___  |  _  |  __/ (_| | (_| |  __/ |   
 /_/   \_\____/ \____| |_| |_|\___|\__,_|\__,_|\___|_| 
***/
#include <Wire.h>
#include <Adafruit_ADS1015.h>


/*
  _____ _     _             ____                   _      _   _                _           
 |_   _| |__ (_)_ __   __ _/ ___| _ __   ___  __ _| | __ | | | | ___  __ _  __| | ___ _ __ 
   | | | '_ \| | '_ \ / _` \___ \| '_ \ / _ \/ _` | |/ / | |_| |/ _ \/ _` |/ _` |/ _ \ '__|
   | | | | | | | | | | (_| |___) | |_) |  __/ (_| |   <  |  _  |  __/ (_| | (_| |  __/ |   
   |_| |_| |_|_|_| |_|\__, |____/| .__/ \___|\__,_|_|\_\ |_| |_|\___|\__,_|\__,_|\___|_|   
                      |___/      |_|                                                       
*/                      
#include <ThingSpeak.h>

int i32ArrTemperaturtabelle[] = {
  #include "Temperaturtabelle.h"
};



#include <ESP8266TelegramBOT.h>
//#include <UniversalTelegramBot.h>

