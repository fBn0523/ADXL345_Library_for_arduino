#include <Arduino.h>
#include "iic_sensor.hpp"
#define USE_SERIAL_DEBUG
AHT10 aht;
void setup() {
Serial.begin(115200);
iic_sensoer_init();
aht.init_aht();
aht.reset();


}
/*
void AHT10::read_raw_data(){
Wire.beginTransmission(aht_iic_addr);
Wire.write(B01110001);
Wire.requestFrom(aht_iic_addr, (uint8_t)(6));

data_buffer[0]=Wire.read();
data_buffer[1]=Wire.read();
data_buffer[2]=Wire.read();
data_buffer[3]=Wire.read();
data_buffer[4]=Wire.read();
data_buffer[5]=Wire.read();
Wire.endTransmission();

uint32_t	SRH=(data_buffer[1]<<12)+(data_buffer[2]<<4)+(data_buffer[3]>>4);
uint32_t	ST=((data_buffer[3]&0X0f)<<16)+(data_buffer[4]<<8)+(data_buffer[5]);
double humidity=(int)(SRH*100.0/1024/1024+0.5);
double temperature=((int)(ST*2000.0/1024/1024+0.5))/10.0-50;

Serial.println(humidity);
Serial.println(temperature);
*/
void loop() {
 aht.start_measure();
 vTaskDelay(1000);
Serial.println(aht.return_humidity());//摄氏度，相对湿度。
Serial.println(aht.return_temperature());
}