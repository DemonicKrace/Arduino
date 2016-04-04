#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7','4','1','0'},
  {'8','5','2','A'},
  {'9','6','3','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


#define NUM 7
int pins[NUM] = {A1, A2, 10, 11, 12, A0, 13};
/*
A1連到7(A)。 
A2連到6(B)。
10連到4(C)。
11連到2(D)。
12連到1(E)。
A0連到9(F)。
13連到10(G)。
*/
#define t true
#define f false
boolean data[16][NUM] = {
  {t, t, t, t, t, t, f}, // 0
  {f, t, t, f, f, f, f}, // 1
  {t, t, f, t, t, f, t}, // 2
  {t, t, t, t, f, f, t}, // 3
  {f, t, t, f, f, t, t}, // 4
  {t, f, t, t, f, t, t}, // 5
  {t, f, t, t, t, t, t}, // 6
  {t, t, t, f, f, f, f}, // 7
  {t, t, t, t, t, t, t}, // 8
  {t, t, t, t, f, t, t}, // 9
  {t, t, t, f, t, t, t}, // a
  {f, f, t, t, t, t, t}, // b
  {t, f, f, t, t, t, f}, // c
  {f, t, t, t, t, f, t}, // d
  {t, t, f, t, t, t, t}, // e
  {t, f, f, f, t, t, t}  // f 
};


void setup(){
  Serial.begin(9600);

  for(int i = 0; i < NUM; i++){
    pinMode(pins[i], OUTPUT);    
  } for(int i = 0; i < NUM; i++){
    pinMode(pins[i], OUTPUT);    
  } 
}
void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    Serial.println(key);
  }
  if(key>='0'&&key<='9'){
    writeNumber(key - '0');
  }
  else if(key >= 'A' && key <= 'F'){
    writeNumber(key - 'A' + 10);    
  }
  
}

void writeNumber(int n){
  for(int i = 0; i < NUM; i++){
    digitalWrite(pins[i], data[n][i] == t ? HIGH : LOW);
  }
}

