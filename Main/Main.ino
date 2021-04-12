#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Wire.h>

#define SS_PIN 10
#define RST_PIN 9



MFRC522 mfrc522(SS_PIN, RST_PIN);
int button = 6;
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  mySerial.begin(9600);
  pinMode(button, INPUT);
  digitalWrite(button, LOW);

}

void loop() {

  //---GIAO TIẾP SERIAL----//

  if (Serial.available()) {
    String nhan = "";
    while (Serial.available()) {
      nhan = Serial.readString();
      Serial.print(nhan);
    }
    if (nhan == "ON") {

      char ch = Serial.read();
      Serial.write(ch);
      mySerial.write(ch);
      delay(500);
    }

  }


  //  //----------ĐỌC GIÁ TRỊ BUTTON-------------//
  int buttonStatus = digitalRead(button);
  if (buttonStatus == HIGH) {
    char ch = Serial.read();
    Serial.write(ch);
    mySerial.write(ch);
    delay(500);
    buttonStatus = LOW;
  }

  //--------THẺ TỪ----------//

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "B6 1C AE F8")
  {

    Serial.println("ID đúng, mở khóa");
    char ch = Serial.read();
    Serial.write(ch);
    mySerial.write(ch);
    delay(1000);
  }
}
