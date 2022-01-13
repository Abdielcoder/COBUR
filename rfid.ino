#include <SPI.h>
#include <MFRC522.h>

#include <SoftwareSerial.h>
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
SoftwareSerial BTSerial(2, 3);
void setup() {
  Serial.begin(9600); //Iniciamos La comunicacion serial
  BTSerial.begin(9600);
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Control de acceso:");
}

byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0x4D, 0x5C, 0x6A, 0x45} ; //código del usuario 1
byte Usuario2[4]= {0xC1, 0x2F, 0xD6, 0x0E} ; //código del usuario 2
void loop() {

if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
  
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();         
            }      
  } 
}
