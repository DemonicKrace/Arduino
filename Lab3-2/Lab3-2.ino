int analogPinA2 = A2; //可變電阻

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
 // 設定 A2 為輸入
  pinMode(analogPinA2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //L2
  // 可變電阻讀值
  float sensorValueA2;
  for(int i = 0 ; i< 5 ;i++){
    sensorValueA2 = analogRead(analogPinA2);
    sensorValueA2 = 0.7* sensorValueA2 + 0.3* analogRead(analogPinA2); 
  }
  float sensorVoltageA2 = sensorValueA2 * 5 / 1024;
  
  Serial.print("analogPinA2 sensorValueA2 = ");
  Serial.println(sensorValueA2);

  Serial.print("analogPinA2 sensorVoltageA2 = ");
  Serial.println(sensorVoltageA2);


  //B1M : R1 + R2 = 1M , Vin = 5
  //Voltage = Vin * R1 / (R1+R2)
  // => R1 = sensorVoltage * (R1+R2) / Vin
  float R1 = sensorVoltageA2 * 1000000 / 5.0 ;
  Serial.print("analogPinA2 R1 = ");
  Serial.println(R1);


  Serial.println("");

  delay(1000);
  
}
