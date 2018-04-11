#include "includes.h"
#include "PSW.h"

int i32RetMessen = 0;                       //Rueckgabewert Messen Funktion
int i32Messen_lasttime = 0;                 //Zeit seit dem die Funtion aufgerufen wurde
int i32Messen_mtbs = 1000;                  //Meantime zwischen den Aufrufen
int i32TS_lasttime = 0;                     //Zeit seit dem die Funtion aufgerufen wurde
int i32TS_mtbs = 20 * 1000;                 //Poste alle 20 sec
int i32RetTS = 200;                           //Rueckgabewert ThingSpeak Funktion
int i32arrTemperatur_adc[] = {0,0,0,0};     //Temperaturwerte ausgelesen aus Temperaturtabelle
int Temperatur_adc0;                        //Gemittelte Temperaturwerte
int Temperatur_adc1;                        //Gemittelte Temperaturwerte
int Temperatur_adc2;                        //Gemittelte Temperaturwerte
int Temperatur_adc3;                        //Gemittelte Temperaturwerte
int i32Tele_lasttime;                       //Zeit seit dem die Funtion aufgerufen wurde
int i32Tele_mtbs = 10000;                   //Meantime zwischen den Aufrufen
int i32RetTele = 0;                         //Rueckgabewert Telegram Funktion
int i32UpdateIntervall = 0;                 //Wie oft soll die Temperatur an Telegramm gesendet werden 0=aus
int i32IdChat = 0;                          //Chat ID zwischen dir und dem SmokerBot
int i32TeleAktTemp_lasttime = 0;            //Zeit seit dem die Funtion aufgerufen wurde
int i32arrThreshAlarm[] =  {0,0,0,0};       //Schwelle fuer Temperturalarm


/***
  ____       _   _   _                 
 / ___|  ___| |_| |_(_)_ __   __ _ ___ 
 \___ \ / _ \ __| __| | '_ \ / _` / __|
  ___) |  __/ |_| |_| | | | | (_| \__ \
 |____/ \___|\__|\__|_|_| |_|\__, |___/
                             |___/     
***/
TelegramBOT bot(BOTtoken, BOTname, BOTusername);
WiFiClient client;
/*** ADC Adresse einstellen ***/
Adafruit_ADS1115 ads1115(0x48); 


/***
  ____       _               
 / ___|  ___| |_ _   _ _ __  
 \___ \ / _ \ __| | | | '_ \ 
  ___) |  __/ |_| |_| | |_) |
 |____/ \___|\__|\__,_| .__/ 
                      |_|    
***/
void setup() {
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  /*** Serielleschnittstelle starten ***/
  Serial.begin(115200); 

  /*** Automatisch wird der Wlan Zugang geladen, falls dieser nicht verfügbar ist 
       mach der Wemos selbst einen Hotspot auf wo man das neue Wlan eintragen kann***
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(true);
  wifiManager.autoConnect("BlackPearl");
  Serial.println("You're connected to the network");
 */

  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("WLAN ERROR");
  }
  Serial.println("WLAN Connected");

  /*** ADC 1115 starten ***/
  ads1115.begin();
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!

  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV (default)
  ads1115.setGain(GAIN_ONE);           // 1x gain   +/- 4.096V  1 bit = 0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.0078125mV

  /*** Connect to ThingSpeak ***/
  ThingSpeak.begin(client);

  /***** launch Bot functionalities */
  bot.begin();
}



/***
  __  __       _         _                      
 |  \/  | __ _(_)_ __   | |    ___   ___  _ __  
 | |\/| |/ _` | | '_ \  | |   / _ \ / _ \| '_ \ 
 | |  | | (_| | | | | | | |__| (_) | (_) | |_) |
 |_|  |_|\__,_|_|_| |_| |_____\___/ \___/| .__/ 
                                         |_|    

***/
void loop() {
  // Measure Signal Strength (RSSI) of Wi-Fi connection
  long rssi = WiFi.RSSI();
  //wdt_reset();
  
/***
  __  __                          
 |  \/  | ___  ___ ___  ___ _ __  
 | |\/| |/ _ \/ __/ __|/ _ \ '_ \ 
 | |  | |  __/\__ \__ \  __/ | | |
 |_|  |_|\___||___/___/\___|_| |_|
                                  
*/
  if (millis() > i32Messen_lasttime + i32Messen_mtbs)  {
    i32RetMessen = CallMessen();          //Aufruf des Unterprogramms
    i32Messen_lasttime = millis();        //Setzen des aktuellen Zeitpunktes
  }


/*
  _____ _     _             ____                   _    
 |_   _| |__ (_)_ __   __ _/ ___| _ __   ___  __ _| | __
   | | | '_ \| | '_ \ / _` \___ \| '_ \ / _ \/ _` | |/ /
   | | | | | | | | | | (_| |___) | |_) |  __/ (_| |   < 
   |_| |_| |_|_|_| |_|\__, |____/| .__/ \___|\__,_|_|\_\
                      |___/      |_|                    
 */
  if (millis() > i32TS_lasttime + i32TS_mtbs || i32RetTS != 200)  {
    Serial.print("i32RetTS Value: ");
    Serial.println(i32RetTS);
    i32RetTS = CallThingSpeak();
    i32TS_lasttime = millis();
    Serial.print("i32RetTS Value nach: ");
    Serial.println(i32RetTS);
  }


/***
  _____    _                                
 |_   _|__| | ___  __ _ _ __ __ _ _ __ ___  
   | |/ _ \ |/ _ \/ _` | '__/ _` | '_ ` _ \ 
   | |  __/ |  __/ (_| | | | (_| | | | | | |
   |_|\___|_|\___|\__, |_|  \__,_|_| |_| |_|
                  |___/                     
*/
  //wdt_reset();
  if (millis() > i32Tele_lasttime + i32Tele_mtbs || i32RetTele != 1)  {
     
    bot.getUpdates(bot.message[0][1]);                      // launch API GetUpdates up to xxx message
    i32RetTele = CallTelegram();
    i32Tele_lasttime = millis();
  }


}
