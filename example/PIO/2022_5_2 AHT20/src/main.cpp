#include <Arduino.h>
#include "iic_sensor.hpp"

AHT20 aht;
void setup() {
  Serial.begin(115200);
iic_sensoer_init();
aht.init_aht();
aht.measure_read();
}

void loop() {
  Serial.println("**************************");
 aht.measure_read();
 Serial.print(aht.return_humidity()); Serial.println("%");
 Serial.print(aht.return_temperature()); Serial.println(".C");
  vTaskDelay(1000);
}