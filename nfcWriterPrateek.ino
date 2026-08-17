// Writes a single URI record (https://arduino.cc) to an NFC formatted tag. Note this erases all existing records.

#include <SPI.h>
#include <MFRC522.h>
#include "NfcAdapter.h"

#define CS_PIN 10

MFRC522 mfrc522(CS_PIN, UINT8_MAX); // Create MFRC522 instance


NfcAdapter nfc = NfcAdapter(&mfrc522);

void setup() {
    Serial.begin(9600);
    Serial.println("NDEF writer\nPlace a formatted Mifare Classic or Ultralight NFC tag on the reader.");
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    nfc.begin();
  pinMode(6, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
void loop()

{ digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  int sensorVal = digitalRead(6);
  Serial.println(sensorVal);
   if (sensorVal == LOW){
        digitalWrite(7, HIGH);
 
   if (nfc.tagPresent()) {
        Serial.println("Writing record to NFC tag");
        NdefMessage message = NdefMessage();
        message.addTextRecord("Hii its me , Prateek 😀");
        message.addUriRecord("Your_web_link");
        const char* ss="BEGIN:VCARD\nVERSION:4.0\nFN:Simon Perreault\nN:Perreault;Simon;;;ing. jr,M.Sc.\nBDAY:--0203\nGENDER:M\nEMAIL;TYPE=work:simon.perreault@viagenie.ca\nEND:VCARD";
        message.addMimeMediaRecord("text/vcard",ss);
        bool success = nfc.write(message);
        if (success) {
          Serial.println("\tSuccess. Try reading this tag with your phone.");        
          digitalWrite(9,HIGH);
          delay(80);
          digitalWrite(9, LOW);
          delay(500);
          
        } else {
          Serial.println("\tWrite failed.");
          digitalWrite(8 , HIGH);
          delay(80);
          digitalWrite(8, LOW);
        }
        bool success = Ndef.makeReadonly();
    }
        

   }
   delay(500);
    }


