// NOTE: for the ESP32 you can use: long val = EEPROM.readULong(address);

#include <EEPROM.h>

const int EEaddress = 0;
const long value = 2546824;

void setup() {

    Serial.begin(9600);
    EEPROM.begin(32);       // Initialising array of size 32 bytes in RAM to simulate the 32 bytes in Flash as EEPROM

    //writing
    EEPROMWrite(EEaddress, value);
    Serial.println("Wrote "+value+" to EEPROM");

    //reading
    long val;
    Serial.println("Reading from EEPROM");
    val = EEPROMRead(EEaddress);
    Serial.print("EEPROM content at 0 = ");
    Serial.println(val);
    
}

void loop() {

}


//function to write to EEPROM
void EEPROMWrite(int address, long value) {

    /* size of long is 32-bits but each memory location in EEPROM
     * takes only 8-bits and then rolls over. Thus, it is taken into 4 individual bytes
     * and then stored in consecutive memory locations.
     */
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);      // using bitwise operator here for shifting through bits
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);
    
    EEPROM.put(address, four);
    EEPROM.put(address + 1, three);
    EEPROM.put(address + 2, two);
    EEPROM.put(address + 3, one);
    EEPROM.commit();
}

//function to read from EEPROM
long EEPROMRead(long address) {
    
    /* Reading individual bytes here from each memory location into 
     * different variables.
     */
    byte four = EEPROM.get(address);       // least LSB
    byte three = EEPROM.get(address + 1);       
    byte two = EEPROM.get(address + 2);
    byte one = EEPROM.get(address + 3);     // most MSB

    return (
          /*Combining all the four read outputs for retrieving the saved value from EEPROM
          * It's reverse procedure of what is being done in EEPROMWrite().
          * Here, long is stored as big endian 
          */
          ((four << 0) & 0xFF) +        // retreiving least LSB
          ((three << 8) & 0xFFFF) + 
          ((two << 16) & 0xFFFFFF) + 
          ((one << 24) & 0xFFFFFFFF)    // retreiving most MSB
      );
}
