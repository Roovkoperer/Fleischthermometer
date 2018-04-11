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

//int i32arrMittelwert[2];                    //Mittelwert der Messfühler
//int i32RetMittelwert = 0;                   //Rueckgabewert Mittelwert Funktion
//int i32AktMittelwert = 0;                   //Aktueller Wert für den Gleitendenmittelwert
int i32arrThreshAlarm[] =  {0,0,0,0};       //Schwelle fuer Temperturalarm
//int i32Blynk_lasttime = 0;                  //Zeit seit dem die Funtion aufgerufen wurde
//int i32Blynk_mtbs = 1000;                   //Meantime zwischen den Aufrufen
//int i32Alarm01 = 0;                         //Temperaturalarm an/aus
//int i32AlarmVal01 = 0;                      //Temperaturschwelle fuer Alarm 01

/*
char auth[] = "a7b0a1414afb4a01939f633053000aa6"; //Autentification Key for Blynk

// Initialize Telegram BOT
#define BOTtoken "399277797:AAF10-L9gVbbZYWq9AUXrkJgX2GRMYVsFD4"
#define BOTname "Dr. Smoker"
#define BOTusername "Mr_Smoker_Bot"
//#define BOTtoken "399277797:AAF10-L9gVbbZYWq9AUXrkJgX2GRMYVsFD4"

//#define BOTname "Grillbot"
//#define BOTusername "Eilsenbot"
//#define BOTtoken "592983149:AAFhKcWoX1MxkiDXU-kxWPhcK2yub7yPBYs"
*/

TelegramBOT bot(BOTtoken, BOTname, BOTusername);

/***
 __        _____ _____ ___   ____       _   _   _                 
 \ \      / /_ _|  ___|_ _| / ___|  ___| |_| |_(_)_ __   __ _ ___ 
  \ \ /\ / / | || |_   | |  \___ \ / _ \ __| __| | '_ \ / _` / __|
   \ V  V /  | ||  _|  | |   ___) |  __/ |_| |_| | | | | (_| \__ \
    \_/\_/  |___|_|   |___| |____/ \___|\__|\__|_|_| |_|\__, |___/
                                                        |___/     
***/
WiFiClient client;
//WiFiClientSecure client;

/***
  _____ _     _             ____                   _      ____       _   _   _                 
 |_   _| |__ (_)_ __   __ _/ ___| _ __   ___  __ _| | __ / ___|  ___| |_| |_(_)_ __   __ _ ___ 
   | | | '_ \| | '_ \ / _` \___ \| '_ \ / _ \/ _` | |/ / \___ \ / _ \ __| __| | '_ \ / _` / __|
   | | | | | | | | | | (_| |___) | |_) |  __/ (_| |   <   ___) |  __/ |_| |_| | | | | (_| \__ \
   |_| |_| |_|_|_| |_|\__, |____/| .__/ \___|\__,_|_|\_\ |____/ \___|\__|\__|_|_| |_|\__, |___/
                      |___/      |_|                                                 |___/     

const int channelID = 327919;                   // Channel ID
//String writeAPIKey = "MGNOBEO54HZSQ0JW";      // write API key for your ThingSpeak Channel
const char * writeAPIKey = "MGNOBEO54HZSQ0JW";  // write API key for your ThingSpeak Channel
const char *server = "api.thingspeak.com";      // Serveradresse
//const int postingInterval = 20 * 1000;        // post data every 20 seconds
***/

/*** ADC Adresse einstellen ***/
Adafruit_ADS1115 ads1115(0x48); 


//UniversalTelegramBot bot(BOTtoken, client);



/********************************************
 * EchoMessages - function to Echo messages *
 ********************************************/
//void Bot_EchoMessages() {
//
//  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
//    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
//  }
//  bot.message[0][0] = "";   // All messages have been replied - reset new messages
//}

/*
BLYNK_WRITE(V10){
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V10 Slider value is: ");
  Serial.println(pinValue);
  i32AlarmVal01 = pinValue; 
}

BLYNK_WRITE(V11){
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V11 Button value is: ");
  Serial.println(pinValue);
  i32Alarm01 = pinValue;
}
*/

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
 
//  SPIFFS.begin();

/*** Feste WLAN adresse*/
//  const char* ssid = "Das Asozialenetzwerk"; // your wireless network name (SSID)
//  const char* password = "frAuke&Denn1s#Kaut1?96"; // your Wi-Fi network password
 // const char* ssid = "Monopole Free WiFi"; // your wireless network name (SSID)
  //const char* password = "ILOVEMONOPOLE"; // your Wi-Fi network password
//  const char* ssid = "BKA Ueberwachungsvan WLAN #334"; // your wireless network name (SSID)
//  const char* password = "60003377208519488322&Dennis"; // your Wi-Fi network password
  //const char* ssid = "Adam"; // your wireless network name (SSID)
  //const char* password = "Knispel1703..,-"; // your Wi-Fi network password
   
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



    /*** Mit Blynk verbinden um die App nutzen zu können***
  Blynk.config(auth);  // in place of Blynk.begin(auth, ssid, pass);
  Blynk.connect(10000);  // timeout set to 10 seconds and then continue without Blynk
  while (Blynk.connected() == false) {
    Serial.println("Waiting for Blynk server");
  }
  
  Serial.println("Connected to Blynk server");
*/
  bot.begin();                                  // launch Bot functionalities  
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
/*
  __  __                          
 |  \/  | ___  ___ ___  ___ _ __  
 | |\/| |/ _ \/ __/ __|/ _ \ '_ \ 
 | |  | |  __/\__ \__ \  __/ | | |
 |_|  |_|\___||___/___/\___|_| |_|
                                  
*/
  if (millis() > i32Messen_lasttime + i32Messen_mtbs)  {
    i32RetMessen = CallMessen();          //Aufruf des Unterprogramms
    //i32RetMittelwert = CallMittelwert(0); //Aufruf des Gleitendenmittelwertes für Fühler 1
    //i32RetMittelwert = CallMittelwert(1); //Aufruf des Gleitendenmittelwertes für Fühler 2
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



/*
  ____  _             _    
 | __ )| |_   _ _ __ | | __
 |  _ \| | | | | '_ \| |/ /
 | |_) | | |_| | | | |   < 
 |____/|_|\__, |_| |_|_|\_\
          |___/            

  Blynk.run();
  Blynk.virtualWrite(V0, i32arrTemperatur_adc[0]);
  Blynk.virtualWrite(V2, rssi);
*/

  // wait and then post again
 // delay(100);

/*
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
    //bot.sendMessage("312155541", "Alarm Alarm!!!", "");
     
    /*
    Serial.println("DRIN");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) {
        bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }


    */

//    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
//    Bot_EchoMessages();   // reply to message with Echo

    
    i32Tele_lasttime = millis();
  }



}
