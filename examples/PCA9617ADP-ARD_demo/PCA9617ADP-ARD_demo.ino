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

#define ENABLE_FULL_LDO2_VOLTAGE_VARIATION

M24C02 eeprom;
LDO1 ldo1;
LDO2 ldo2;

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

  Serial.println("");
  Serial.println("*** CAUTION! ***");

#ifdef ENABLE_FULL_LDO2_VOLTAGE_VARIATION
  Serial.println("Measure the behavior on an oscilloscope. Nothing will be appear on this terminal screen while program running.");
  Serial.println("You can enable periodic message on screen by disabling \"ENABLE_FULL_LDO2_VOLTAGE_VARIATION\".");
  Serial.println("However the \"ENABLE_FULL_LDO2_VOLTAGE_VARIATION\" setting take over LDO2 control signal partially.");
  Serial.println("To enable all voltage variation on LDO2, you need to enable \"ENABLE_FULL_LDO2_VOLTAGE_VARIATION\" option.");
  Serial.println("");
  Serial.end();
#else
  Serial.println("The \"ENABLE_FULL_LDO2_VOLTAGE_VARIATION\" setting is enabled.");
  Serial.println("Whith this setting, the LDO2 voltage will be controlled as 3.3V, 4.96V, 3.3V, 4.96V");
  Serial.println("");
#endif
}

void loop() {
  for (int i = 0; i < LDO1::VOLTAGES; i++) {
    ldo1.set(i);

    for (int j = 0; j < LDO2::VOLTAGES; j++) {
      ldo2.set(j);

      if ((3 == i) && (0 == j))
        continue;

#ifndef ENABLE_FULL_LDO2_VOLTAGE_VARIATION
      Serial.print("LDO1[V]=");
      Serial.print(ldo1.voltage());
      Serial.print(", LDO2[V]=");
      Serial.println(ldo2.voltage());
#endif

      delay(1000);
      try_eeprom_read();
    }
  }
}

void try_eeprom_read(void) {
  char read_str[READ_BUFFER_SIZE];

  eeprom.read(0, (uint8_t *)read_str, READ_BUFFER_SIZE);

#ifndef ENABLE_FULL_LDO2_VOLTAGE_VARIATION
  Serial.println(read_str);
#endif
}
