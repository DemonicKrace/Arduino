//R_Uno_TXTR
int LED_Pin = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_Pin,OUTPUT);
  Serial.begin(9600);
  Serial.println("COM14 is start");
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("COM14 Loopping");
  Serial.println("Serial.read() = " + Serial.read());
  Serial.write('Y');
  while(!Serial.available()){}
  if(Serial.read()=='Y'){
    LED_blink();
    LED_blink();
  }
//  Serial.write('Y');
}
void LED_blink(){
  digitalWrite(LED_Pin,HIGH);
  delay(2000);
  digitalWrite(LED_Pin,LOW);
  delay(2000);
}
