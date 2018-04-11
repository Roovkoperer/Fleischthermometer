int CallThingSpeak(){
  
#define OK_SUCCESS              200     // OK / Success
#define ERR_BADAPIKEY           400     // Incorrect API key (or invalid ThingSpeak server address)
#define ERR_BADURL              404     // Incorrect API key (or invalid ThingSpeak server address)
#define ERR_OUT_OF_RANGE        -101    // Value is out of range or string is too long (> 255 bytes)
#define ERR_INVALID_FIELD_NUM   -201    // Invalid field number specified
#define ERR_SETFIELD_NOT_CALLED -210    // setField() was not called before writeFields()
#define ERR_CONNECT_FAILED      -301    // Failed to connect to ThingSpeak
#define ERR_UNEXPECTED_FAIL     -302    // Unexpected failure during write to ThingSpeak
#define ERR_BAD_RESPONSE        -303    // Unable to parse response
#define ERR_TIMEOUT             -304    // Timeout waiting for server to respond
#define ERR_NOT_INSERTED        -401    // Point was not inserted (most probable cause is the rate limit of once every 15 seconds)



  char server[] = "api.thingspeak.com";   // name address for addresse
  //char server[] = "api.sunrise-sunset.org",   // name address for addresse
//      c_Rueckgabe[500],
//      c_act_char,
//      ca_Internetdaten [15][50],
//      delimiter1[] = ",",
//      delimiter2[] = "T",
//      delimiter3[] = "+",
//      delimiter4[] = ":",
//      *ptr,
//      c_Helper1[20],
//      c_Helper2[20],
//      c_ctrl_String[20],
//      c_ctrl_Sunrise[] = "\"sunrise\":",
//      c_ctrl_Sunset[] = "\"sunset\":";

//  int i32_Nof_chars, 
//      i32_char_size, 
//      index = 0,
//      i32_Strlen = 0,
//      i32Counter = 0,
//      i32Stunde = 0,
//      i32Minute = 0,
//      i32Sekunde = 0;

  int i32RetWrt = 0;
//
/*
//  if (client.connect(server, 80)) {
//    Serial.println("ThingSpeak connected");
//    // Make a HTTP request:
//    //client.println("GET https://api.sunrise-sunset.org/json?lat=52.576709837129144&lng=9.42825973033905");            //Ergebnis formatiert
//    client.println("GET https://api.thingspeak.com/channels/327919/feeds.json?api_key=TJL6JTCMUEFDV25Y&results=2\n");  //Ergebnis unformatiert
//  } else {
//    // if you didn't get a connection to the server:
//    Serial.println("connection to sunrise server failed");
//    return -1;
//  }
//  Serial.println(client.connected());
//  i32_Nof_chars = 0;
//  while (client.connected()) {
//    i32_Nof_chars = i32_Nof_chars + 1;
//    c_act_char = client.read();
//    Serial.print(c_act_char);
//    c_Rueckgabe[index] = c_act_char;
//    index++;   
//  }
//Serial.println("xxx");
//Serial.println(i32_Nof_chars);
//
//
//Serial.println(client);
//
//  // Skip HTTP headers
//  char endOfHeaders[] = {":"};
////  if (!client.find(endOfHeaders)) {
////    Serial.println(F("Invalid response"));
////    return -1;
////  }
//
//  // Allocate JsonBuffer
//  // Use arduinojson.org/assistant to compute the capacity.
//  const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(11);
//  DynamicJsonBuffer jsonBuffer(capacity);
//
//  // Parse JSON object
//  JsonObject& root = jsonBuffer.parseObject(client);
//  if (!root.success()) {
//    Serial.println(F("Parsing failed!"));
//    return -1;
//  }
//
//  // Extract values
//  Serial.println(F("results:"));
//  Serial.println(root["sunrise"].as<char*>());
//  Serial.println(root["sunset"].as<char*>());
//  //Serial.println(root["data"][0].as<char*>());
//  //Serial.println(root["data"][1].as<char*>());
//
//  // Disconnect
//  client.stop();
//
//
//
*/


Serial.println("Test");
  
  /*** ThingSpeak Werte in Kanal schreiben***/
   if (client.connect(server, 80)) {
    Serial.println(client.connected());
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();
    
    Serial.print("RSSI: ");
    Serial.println(rssi); 

    Serial.print("Temperatur 0: ");
    Serial.println(i32arrTemperatur_adc[0]);

    Serial.print("Temperatur 1: ");
    Serial.println(i32arrTemperatur_adc[1]);
    
    // Construct API request body
    //String body = "field1=";
    //body += String(Temperatur_adc0);

    //Serial.println("ThingSpeak absturz");
    ThingSpeak.setField(1, i32arrTemperatur_adc[0]);
    ThingSpeak.setField(2, i32arrTemperatur_adc[1]);
    ThingSpeak.setField(3, rssi);
    //ThingSpeak.setField(4, timeRead);
    i32RetWrt = ThingSpeak.writeFields(channelID, writeAPIKey);

    Serial.print("Return Value: ");
    Serial.println(i32RetWrt);

    return i32RetWrt;
/*
    // create data string to send to ThingSpeak
    String body = "field1=" + String(Temperatur_adc0) + 
                  "&field2=" + String(rssi); //shows how to include additional field data in http post
        

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");
*/


  } else {
    Serial.println("connection to sunrise server failed");
    return -1;
  }
//  client.stop();
}
