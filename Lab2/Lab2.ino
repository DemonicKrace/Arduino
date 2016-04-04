byte startPin = 6;
byte endPin = 13;
int delayTime = 200;
byte buttonPin = 2;

void setup() {
  // put your setup code here, to run once:
  for(byte i = startPin;i <= endPin;i++){
    pinMode(i,OUTPUT);
  }
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int switchStatus = digitalRead(buttonPin);
  Serial.println(switchStatus);
  if(switchStatus){
    lightAndDarkOneTime();
    lightAndDarkOneTime();
    rightMoveToLeft(true);
    lightAndDarkOneTime();
    lightAndDarkOneTime();
    rightMoveToLeft(false);
  }else{
    rightMoveToLeft(true);
    rightMoveToLeft(false);
  }
/* 
  lightAndDarkOneTime();
  lightAndDarkOneTime();
  rightMoveToLeft(true);
  
  lightAndDarkOneTime();
  lightAndDarkOneTime();
  rightMoveToLeft(false);
  */
}

void lightAndDarkOneTime(){
  allDark(false);
  delay(delayTime);
  allDark(true);
  delay(delayTime);
}

void allDark(bool isDark){
  for(byte i = startPin;i <= endPin;i++){
      digitalWrite(i,(isDark?LOW:HIGH));
  }
}

void rightMoveToLeft(bool isRightToLeft){
  int startLightPin = (isRightToLeft?8:1);

  if(isRightToLeft){
    //Pin endPin to Pin startPin
    for(byte i = endPin;i >= startPin;i--){
      LightPin(i);
      delay(delayTime);
    }
  }
  else{
    //Pin startPin to Pin endPin
    for(byte i = startPin;i <= endPin;i++){
      LightPin(i);
      delay(delayTime);
    }
  }
}

void LightPin(byte pinToLight){
  //To all dark
  allDark(true);

  //Pin to light
  digitalWrite(pinToLight,HIGH); 
}

