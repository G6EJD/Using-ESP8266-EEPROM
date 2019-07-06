#include <EEPROM.h>

const int EEaddress = 0;
const long value = 2546824;

void setup() {

    Serial.begin(9600);
    EEPROM.begin(32);

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

    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
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
    long four = EEPROM.get(address);
    long three = EEPROM.get(address + 1);
    long two = EEPROM.get(address + 2);
    long one = EEPROM.get(address + 3);

    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
