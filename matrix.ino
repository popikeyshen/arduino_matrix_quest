
        
 /*
 * RST/Reset   RST           3             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      9             53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14,
 * SPI SCK     SCK           13 / ICSP-3   52        D13        ICSP-3           15
 */

// Card UID 0: 69 64 9C 1A    702717210 
// Card UID 1: 69 64 9C 1A    1768201242
// Card UID 2: 19 A8 97 1A    430479130
// Card UID 3: 49 1D 98 1A    1226676250
// Card UID 4: 49 ED 97 1A    1240307482
// Card UID 5: 09 F5 9D 1A    167091482


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN        A0        //
#define SS_PIN        3        //

#define RST2_PIN    A1        //
#define SS2_PIN        4        //

#define RST2_PIN    A2        //
#define SS2_PIN        5        //



unsigned long uidDec1, uidDecTemp1;
unsigned long uidDec2, uidDecTemp2;
unsigned long uidDec3, uidDecTemp3;

int relay_dveri=2;
int relay_reshetka=7;
int diod=6;


MFRC522 mfrc522(SS_PIN, RST_PIN);    // Create MFRC522 instance
MFRC522 mfrc522_2(SS2_PIN, RST2_PIN);    // Create MFRC522 instance
MFRC522 mfrc522_3(SS2_PIN, RST2_PIN);    // Create MFRC522 instance


void setup() {
    pinMode(relay_dveri, OUTPUT);
    pinMode(relay_reshetka, OUTPUT);
    pinMode(diod, OUTPUT);

    Serial.begin(1200);        // Initialize serial communications with the PC
    Serial.println("Start SERIAL");
    while (!Serial);                // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();            // Init SPI bus
    SPI.setClockDivider(SPI_CLOCK_DIV128);


    mfrc522.PCD_Init();        // Init MFRC522
    mfrc522_2.PCD_Init();      // Init MFRC522
    mfrc522_3.PCD_Init();      // Init MFRC522

    mfrc522.PCD_AntennaOn();
    mfrc522_2.PCD_AntennaOn();
   mfrc522_3.PCD_AntennaOn();
   
    mfrc522.PCD_SetAntennaGain(0x07<<4);
    mfrc522_2.PCD_SetAntennaGain(0x07<<4);
    mfrc522_2.PCD_SetAntennaGain(0x07<<4);
   
    Serial.println(mfrc522.PCD_GetAntennaGain());
    Serial.println(mfrc522_2.PCD_GetAntennaGain());
    Serial.println(mfrc522_2.PCD_GetAntennaGain());
   
   

    ShowReaderDetails();    // Show details of PCD - MFRC522 Card Reader details

    Serial.println("Scan PICC to see UID, type, and data blocks...");
      

      
}

void loop() {
  
digitalWrite(diod,HIGH);

  delay(1000);
         // Поиск новой карточки

        if ( ! mfrc522.PICC_IsNewCardPresent() && ! mfrc522_2.PICC_IsNewCardPresent() && ! mfrc522_3.PICC_IsNewCardPresent() ) {
                return;
    }

        // Выбор карточки

    if ( ! mfrc522.PICC_ReadCardSerial() && ! mfrc522_2.PICC_ReadCardSerial() && ! mfrc522_3.PICC_ReadCardSerial() ) {
        return;
    }
       
        Serial.println("");
        Serial.print("Sensor 1 UID: ");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
                // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                // Serial.print(mfrc522.uid.uidByte[i], HEX);
                uidDecTemp1=mfrc522.uid.uidByte[i];
                uidDec1=uidDec1*256+uidDecTemp1;
        }
        Serial.println(uidDec1);
        Serial.println("--------------");
       
         Serial.println("");
        Serial.print("Sensor 2 UID: ");
        for (byte i = 0; i < mfrc522_2.uid.size; i++) {
                // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                // Serial.print(mfrc522.uid.uidByte[i], HEX);
                uidDecTemp2=mfrc522_2.uid.uidByte[i];
                uidDec2=uidDec2*256+uidDecTemp2;
        }
        Serial.println(uidDec2);
        Serial.println("--------------");
       
         Serial.println("");
        Serial.print("Sensor 3 UID: ");
        for (byte i = 0; i < mfrc522_3.uid.size; i++) {
                // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                // Serial.print(mfrc522.uid.uidByte[i], HEX);
                uidDecTemp3=mfrc522_3.uid.uidByte[i];
                uidDec3=uidDec3*256+uidDecTemp3;
        }
        Serial.println(uidDec3);
        Serial.println("--------------");
       

       
// Card UID 0: 69 64 9C 1A    702717210     
// Card UID 1: 69 64 9C 1A    1768201242
// Card UID 2: 19 A8 97 1A    430479130
// Card UID 3: 49 1D 98 1A    1226676250
// Card UID 4: 49 ED 97 1A    1240307482
// Card UID 5: 09 F5 9D 1A    167091482

        if(uidDec3 == 1226676250 && uidDec2 == 430479130 && uidDec1 == 1768201242)
        {
        digitalWrite(relay_dveri, HIGH);
        }
        else
        {
        digitalWrite(relay_dveri, LOW);
        }
       
    // Dump debug info about the card; PICC_HaltA() is automatically called
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    //mfrc522_2.PICC_DumpToSerial(&(mfrc522_2.uid));
        //mfrc522_3.PICC_DumpToSerial(&(mfrc522_3.uid));
        //mfrc522_4.PICC_DumpToSerial(&(mfrc522_4.uid));
        //mfrc522_5.PICC_DumpToSerial(&(mfrc522_5.uid));
       
}

void ShowReaderDetails() {
    // Get the MFRC522 software version
    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
        byte k = mfrc522_2.PCD_ReadRegister(mfrc522_2.VersionReg);
        byte m = mfrc522_3.PCD_ReadRegister(mfrc522_3.VersionReg);

               
               
    Serial.print("MFRC522 Software Version: 0x");
    Serial.print(v, HEX);
    if (v == 0x91)
        Serial.print(" = v1.0");
    else if (v == 0x92)
        Serial.print(" = v2.0");
    else
        Serial.print(" (unknown)");
    Serial.println("");
    // When 0x00 or 0xFF is returned, communication probably failed
    if ((v == 0x00) || (v == 0xFF)) {
        Serial.println("WARNING: Communication failure, is the MFRC522 properly connected?");
    }


    Serial.print("MFRC522 Software Version: 0x");
    Serial.print(k, HEX);
    if (k == 0x91)
        Serial.print(" = v1.0");
    else if (k == 0x92)
        Serial.print(" = v2.0");
    else
        Serial.print(" (unknown)");
    Serial.println("");
    // When 0x00 or 0xFF is returned, communication probably failed
    if ((k == 0x00) || (k == 0xFF)) {
        Serial.println("WARNING: Communication failure, is the MFRC522 properly connected?");
    }

            Serial.print("MFRC522 Software Version: 0x");
    Serial.print(m, HEX);
    if (m == 0x91)
        Serial.print(" = v1.0");
    else if (m == 0x92)
        Serial.print(" = v2.0");
    else
        Serial.print(" (unknown)");
    Serial.println("");
    // When 0x00 or 0xFF is returned, communication probably failed
    if ((m == 0x00) || (m == 0xFF)) {
        Serial.println("WARNING: Communication failure, is the MFRC522 properly connected?");
    }


}
