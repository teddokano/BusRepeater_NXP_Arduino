/** PCA9617ADP-ARD demo sample
 *
 *  Simple sample to operate two LDOs to try signal voltage convination
 *  All possible convination is demonstrated with 0.8V, 1.8V, 2.5V, 3.3V, 4.96V at LDO1 and 
 *  2.5V, 3.0V, 3.3V, 4.96V at LDO2 except condition of "LDO1=4.96 and LDO2=2.5V". 
 *  
 *  To perform sample I2C transfer, it uses M24C02 class library which is defined in "MUX_SW_NXP_Arduino" library. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9617A:
 *    https://www.nxp.com/products/interfaces/ic-spi-i3c-interface-devices/ic-bus-repeaters-hubs-extenders/level-translating-fm-plus-ic-bus-repeater:PCA9617A
 */

#include "M24C02.h"
#include "PCA9617ADP_ARD_LDO.h"

#define SERIAL_OUT_DISABLE

#if defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI)
#undef SERIAL_OUT_DISABLE
#endif

M24C02 eeprom;
Pca9617adp_Ard_LDO1 ldo1;
Pca9617adp_Ard_LDO2 ldo2;

#define READ_BUFFER_SIZE 128

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin();

  Serial.println("\n***** Hello, PCA9617A! *****");

  char test_str[] = "EEPROM is responding - Hello, PCA9617A Arduino shield evaluation board test program";

  Serial.print("test string: ");
  Serial.println(test_str);
  Serial.print("test string length: ");
  Serial.println(sizeof(test_str));

  eeprom.write(0, (uint8_t *)test_str, sizeof(test_str));

#if !(defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI))
  Serial.println("");
  Serial.println("*** CAUTION! ***");

#ifdef SERIAL_OUT_DISABLE
  Serial.println("Measure the behavior on an oscilloscope. Nothing will be appear on this terminal screen while program running.");
  Serial.println("You can enable periodic message on screen by disabling \"SERIAL_OUT_DISABLE\".");
  Serial.println("However the \"SERIAL_OUT_DISABLE\" setting take over LDO2 control signal partially.");
  Serial.println("To enable all voltage variation on LDO2, you need to define \"SERIAL_OUT_DISABLE\" option.");
  Serial.println("");
  Serial.end();
#else
  Serial.println("The \"SERIAL_OUT_DISABLE\" setting is undefined.");
  Serial.println("Whith this setting, the LDO2 voltage will be controlled in order of 3.3V, 4.96V, 3.3V, 4.96V");
  Serial.println("");
#endif  // SERIAL_OUT_DISABLE

#endif  // !(defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI))
}

void loop() {
  for (int v1 = 0; v1 < Pca9617adp_Ard_LDO::v1_variation; v1++) {
    ldo1 = v1;

    for (int v2 = 0; v2 < Pca9617adp_Ard_LDO::v2_variation; v2++) {
      ldo2 = v2;

      if ((3 == v1) && (0 == v2))
        continue;

#ifndef SERIAL_OUT_DISABLE
      Serial.print("LDO1[V]=");
      Serial.print(ldo1.voltage(v1));
      Serial.print(", LDO2[V]=");
      Serial.println(ldo2.voltage(v2));
#endif

      delay(1000);
      try_eeprom_read();
    }
  }
}

void try_eeprom_read(void) {
  char read_str[READ_BUFFER_SIZE];

  eeprom.read(0, (uint8_t *)read_str, READ_BUFFER_SIZE);

#ifndef SERIAL_OUT_DISABLE
  Serial.println(read_str);
#endif
}
