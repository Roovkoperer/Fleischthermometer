/***********************************************************************************************************************

  ID des Chat --> i32IdChat
  Schwelle setzen --> i32Alarm01, i32AlarmVal01

  Updaate intervall in Minuten setzten --> i32UpdateIntervall

***********************************************************************************************************************/
int CallTelegram() {
  String strTemp0;
  String strTemp1;
  String strStatus;
  int i32Alarm0 = 0;         //Alarm0 on/off
  int i32Alarm1 = 0;         //Alarm1 on/off
  int i32Alarm2 = 0;         //Alarm2 on/off
  int i32Alarm3 = 0;         //Alarm3 on/off
  int i32AlarmVal0 = 0;      //Temperaturschwelle0
  int i32AlarmVal1 = 0;      //Temperaturschwelle0
  int i32AlarmVal2 = 0;      //Temperaturschwelle0
  int i32AlarmVal3 = 0;      //Temperaturschwelle0
  /*
  File f = SPIFFS.open("/Alarm.txt", "r");
  if (!f) {
      Serial.println("file open failed");
  }  Serial.println("====== Reading from SPIFFS file =======");
  String s=f.readStringUntil('\n');
  i32Alarm0 = s.toInt();
  Serial.println(s);
  
  s=f.readStringUntil('\n');
  i32Alarm1 = s.toInt();
  Serial.println(s);
  
  s=f.readStringUntil('\n');
  i32Alarm2 = s.toInt();
  Serial.println(s);
  
  s=f.readStringUntil('\n');
  i32Alarm3 = s.toInt();
  Serial.println(s);

  s=f.readStringUntil('\n');
  i32AlarmVal0 = s.toInt();
  Serial.println(s);

  s=f.readStringUntil('\n');
  i32AlarmVal1 = s.toInt();
  Serial.println(s);

  s=f.readStringUntil('\n');
  i32AlarmVal2 = s.toInt();
  Serial.println(s);

  s=f.readStringUntil('\n');
  i32AlarmVal3 = s.toInt();
  Serial.println(s);

  f.close();
  */
  // write 10 strings to file
//  for (int i=1; i<=8; i++){
//    String s=f.readStringUntil('\n');
//    Serial.print(i);
//    Serial.print(":");
//    Serial.println(s);
//
//    
//  }

  
  Serial.println("Tele sub1");

  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
    Serial.println(bot.message[i][4]);
    i32IdChat = bot.message[i][4].toInt();
    Serial.println(i32IdChat);

    String strIncomming = bot.message[1][5];

    if (bot.message[1][5] == "Status") {
      strStatus = ("Time: " + String(millis()/1000));
      bot.sendMessage(bot.message[i][4], strStatus, "");
      strTemp0 = ("Temperatur_0: " + String(i32arrTemperatur_adc[0]));
      strTemp1 = ("Temperatur_1: " + String(i32arrTemperatur_adc[1]));
      bot.sendMessage(String(i32IdChat), strTemp0, "");
      bot.sendMessage(String(i32IdChat), strTemp1, "");
    }
//    
//    if (bot.message[1][5] == "Alarm on") {
//      bot.sendMessage(bot.message[i][4], "Alarm on", "");
//      i32Alarm0 = 1;
//
//
//      File f = SPIFFS.open("/Alarm.txt", "r+");
//      if (!f) {
//          Serial.println("file open failed");
//      }
//      f.println(1);  // Alarm0 off
//      f.close();
//      
//    } else if (bot.message[1][5] == "Alarm off") {
//      bot.sendMessage(bot.message[i][4], "Alarm off", "");
//      i32Alarm0 = 0;
//    } else if (bot.message[1][5] == "Int 01") {
//      bot.sendMessage(bot.message[i][4], "Jede fucking Minute", "");
//      i32UpdateIntervall = 60 * 1000;
//    } else if (bot.message[1][5] == "Int 05") {
//      bot.sendMessage(bot.message[i][4], "Alle 5min", "");
//      i32UpdateIntervall = 60 * 5 * 1000;
//    } else if (bot.message[1][5] == "Int 10") {
//      bot.sendMessage(bot.message[i][4], "Alle 10min", "");
//      i32UpdateIntervall = 60 * 10 * 1000;
//    } else if (bot.message[1][5] == "Int 15") {
//      bot.sendMessage(bot.message[i][4], "Alle 15min", "");
//      i32UpdateIntervall = 60 * 15 * 1000;
//    } else if (bot.message[1][5] == "Int 30") {
//      bot.sendMessage(bot.message[i][4], "Alle 30min", "");
//      i32UpdateIntervall = 60 * 30 * 1000;
//    } else if (bot.message[1][5] == "Int 60") {
//      bot.sendMessage(bot.message[i][4], "Alle 60min", "");
//      i32UpdateIntervall = 60 * 60 * 1000;
//    } else if (bot.message[1][5] == "Int off") {
//      bot.sendMessage(bot.message[i][4], "Intervall aus", "");
//      i32UpdateIntervall = 0;
//    }
//
//    if (strIncomming.startsWith("Temp ")) {
//      Serial.print("Alarmtemperatur: ");
//      Serial.println(strIncomming.length());
//      strIncomming.replace("Temp ", "");
//      i32AlarmVal0 = strIncomming.toInt();
//      Serial.println(i32AlarmVal0);
//
//      if(strIncomming.length() > 8 || i32AlarmVal0 == 0) {
//        Serial.println("Falsche Eingabe");
//        bot.sendMessage(String(i32IdChat), "Falsche Eingabe!!!", "");
//      }
//    }
  }
//  //Status
//
//  //Alarm on/off
//  if (i32Alarm0 == 1 && i32AlarmVal0 != 0 && i32AlarmVal0 < i32arrTemperatur_adc[0]) {
//    bot.sendMessage(String(i32IdChat), "Alarm Alarm!!!", "");
//  }
//
//  //i32UpdateIntervall
//  if (i32UpdateIntervall != 0 && millis() > i32TeleAktTemp_lasttime + i32UpdateIntervall) {
//    strTemp0 = ("Temperatur_0: " + String(i32arrTemperatur_adc[0]));
//    strTemp1 = ("Temperatur_1: " + String(i32arrTemperatur_adc[1]));
//    bot.sendMessage(String(i32IdChat), strTemp0, "");
//    bot.sendMessage(String(i32IdChat), strTemp1, "");
//    i32TeleAktTemp_lasttime  = millis();
//  }
  Serial.println("Tele sub end");
  
  return 1;
}
