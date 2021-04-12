#include <Wire.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

//----I2C-------//
#define SLAVE_ADDRESS 0x04
int number = 0;
//---------//

#define Password_Length 8
const int relayLock = 2;
const int relayBuzzer = 3;

//----------KEYPAD-----------//
char STR[4] = {'2', '3', '1', '2'}; // Cài đặt mật khẩu tùy ý
char str[4] = {' ', ' ', ' ', ' '};
int i, j, count, error = 0;
char key;
char ch;
const byte ROWS = 4;
const byte COLS = 4;
String buff;

char hexaKeys[ROWS][COLS] = {

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};
 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//---------------------//

unsigned long time = 0;
unsigned long delayTime = 3000;


void setup() {
  Wire.begin(0x8);
 Wire.onReceive(receiveEvent);
  Serial.begin(9600);//bật serial, baudrate 9600
  pinMode(relayLock, OUTPUT);
  pinMode(relayBuzzer,OUTPUT);
  digitalWrite(relayLock,LOW);
  digitalWrite(relayBuzzer, LOW);


  //-------------//

}


void receiveEvent(int howMany) {

  while (Wire.available()) {
    ch = Wire.read();
    if (ch == 1) {
      digitalWrite(relayLock, HIGH);
      delay(500000);
      Serial.print("ON");
    }

  }
}

void loop() {

  //--------PHÁT HIỆN TÍN HIỆU----------//
  if (Serial.available()) {
    time = millis();
    digitalWrite(relayLock, HIGH);
    while (Serial.available()) {
      Serial.read();
      delay(3);
    }
  }


  if (millis() - time > delayTime) {
    digitalWrite(relayLock, LOW);
  }



  //------ĐỌC GIÁ TRỊ TỪ KEYPAD VÀ SO SÁNH PASSWORD--------//



  key = customKeypad.getKey();
  //char key = keypad.getKey(); // Ký tự nhập vào sẽ gán cho biến Key

  if (key) // Nhập mật khẩu
  {
    if (i == 0) {
      str[0] = key;

      Serial.print(str[0]);
      delay(100); // Ký tự hiển thị trên màn hình LCD trong 1s
      //      lcd.setCursor(6, 1);
      // Serial.print("*"); // Ký tự được che bởi dấu *
    }
    if (i == 1) {
      str[1] = key;

      Serial.print(str[1]);
      delay(100);

      //Serial.print("*");
    }
    if (i == 2) {
      str[2] = key;

      Serial.print(str[2]);
      delay(100);
      ;
      //Serial.print("*");
    }
    if (i == 3) {
      str[3] = key;

      Serial.print(str[3]);
      delay(100);

      //Serial.print("*");
      count = 1;
    }
    i = i + 1;
  }

  if (count == 1) {
    if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] &&
        str[3] == STR[3]) {

      Serial.print("    Correct!");
      digitalWrite(relayLock, HIGH);
      delay(3000);
      digitalWrite(relayLock, LOW);
      i = 0;
      count = 0;
      error = 0;
      delay(1000);
    } else {
      Serial.print("  Try Again!");
      digitalWrite(relayBuzzer,HIGH);
      delay(100);
      digitalWrite(relayBuzzer,LOW);
      error++;
      i = 0;
      count = 0;
      Serial.print("  ");
      Serial.println(error);

      if (error == 3) {
        Serial.println("Sai 3 lan");
        digitalWrite(relayBuzzer,HIGH);
        delay(2000);
        digitalWrite(relayBuzzer,LOW);
        error = 0;

      }
      Serial.println("Enter Password");
    }
  }
  //---------------------------//
}
