int analogPin5v = A0;   //5v
int analogPin3_3v = A1; //3.3v


void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Serial.println("Hello Arduino");

  pinMode(analogPin5v, INPUT);
  pinMode(analogPin3_3v, INPUT);

  // 設定 A2 為輸入
//  pinMode(analogPinA2, INPUT);

  // 設定 A3 為輸入
 // pinMode(analogPinA3, INPUT);

}

void loop() {
  //L1 
  // 5v & 3.3v 讀值
  
  float sensorValueA0 = 0;
  float sensorValueA1 = 0;

  float sensorVoltageA0;
  float sensorVoltageA1;
  
  for(int i = 0 ; i< 5 ;i++){
    sensorValueA0 = analogRead(analogPin5v);
    sensorValueA0 = 0.7* sensorValueA0 + 0.3* analogRead(analogPin5v);

    sensorVoltageA0 = sensorValueA0 * 5 / 1024;
    
    Serial.print("analogPin5v sensorVoltageA0 = ");
    Serial.println(sensorVoltageA0);
  }
  //Serial.print("analogPin5v sensorVoltageA0 = ");
  //Serial.println(sensorVoltageA0);
  Serial.print("analogPin5v sensorValueA0 = ");
  Serial.println(sensorValueA0);

  
  for(int i = 0 ; i< 5 ;i++){
    sensorValueA1 = analogRead(analogPin3_3v);
    sensorValueA1 = 0.7* sensorValueA1 + 0.3* analogRead(analogPin3_3v);

    sensorVoltageA1 = sensorValueA1 * 5 / 1024;

    Serial.print("analogPin3.3v sensorVoltageA1 = ");
    Serial.println(sensorVoltageA1);

  }
  //Serial.print("analogPin3.3v sensorVoltageA1 = ");
  //Serial.println(sensorVoltageA1);
  Serial.print("analogPin3.3v sensorValueA1 = ");
  Serial.println(sensorValueA1);



  Serial.println("\n   ");
  delay(1000);
}
