int CallMessen(){

  int16_t adc0, adc1, adc2, adc3;                                           //Ausgelesene ADC Werte
  int Voltage_adc0, Voltage_adc1, Voltage_adc2, Voltage_adc3;               //Spannungswerte berechnet aus ADC
  int *i32PtrTemp = i32ArrTemperaturtabelle;                                //Zeiger auf Temperaturtabelle
  
  adc0 = ads1115.readADC_SingleEnded(0);
  adc1 = ads1115.readADC_SingleEnded(1);
  adc2 = ads1115.readADC_SingleEnded(2);
  adc3 = ads1115.readADC_SingleEnded(3);
  //Serial.print("AIN0: "); Serial.println(adc0);
  //Serial.print("AIN1: "); Serial.println(adc1);
  //Serial.print("AIN2: "); Serial.println(adc2);
  //Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  
  Voltage_adc0 = int(adc0 * 0.125);
  Voltage_adc1 = int(adc1 * 0.125);  

  i32arrTemperatur_adc[0] = i32PtrTemp[Voltage_adc0];
  i32arrTemperatur_adc[1] = i32PtrTemp[Voltage_adc1];
  
  Serial.print("Volt_0: "); 
  Serial.print(Voltage_adc0);
  Serial.print(" mV | ");
  Serial.print("Temperatur_0: ");
  Serial.println(i32arrTemperatur_adc[0]);

  Serial.print("Volt_1: "); 
  Serial.print(Voltage_adc1);
  Serial.print(" mV | ");
  Serial.print("Temperatur_1: ");
  Serial.println(i32arrTemperatur_adc[1]);
  
  return 1;
}
