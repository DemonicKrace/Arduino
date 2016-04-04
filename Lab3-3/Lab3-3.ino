int analogPinA3 = A3; //光敏電阻

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
 // 設定 A2 為輸入
  pinMode(analogPinA3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //L3
  // 光敏電阻讀值
  float sensorValueA3;
  for(int i = 0 ; i< 5 ;i++){
    sensorValueA3 = analogRead(analogPinA3);
    sensorValueA3 = 0.7* sensorValueA3 + 0.3* analogRead(analogPinA3); 
  }
  float sensorVoltageA3 = sensorValueA3 * 5 / 1024;
  
  Serial.print("analogPinA3 sensorValueA3 = ");
  Serial.println(sensorValueA3);

  Serial.print("analogPinA3 sensorVoltageA3 = ");
  Serial.println(sensorVoltageA3);


  //R1 = 1k , Vin = 5
  //Voltage = Vin * R2 / (R1+R2)
  // => R2 = Voltage * (R1+R2) / Vin
  // => R2 = (Voltage * R1) / Vin + R2 * (Voltage / Vin)
  // => R2 * (1 - Voltage / Vin) = (Voltage * R1) / Vin
  // => R2 = (Voltage * R1 / Vin)/(1 - Voltage / Vin)
  float R2 = (sensorVoltageA3 * 1000 / 5.0) / (1 - sensorVoltageA3 / 5.0) ;
  Serial.print("analogPinA3 R2 = ");
  Serial.println(R2);

  

  Serial.println("");

  delay(1000);
  
  
}
