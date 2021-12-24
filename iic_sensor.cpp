/*
 <one line to give the program's name and a brief idea of what it does.>
   
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    
    <一行给出程序的名称和它的作用的简要概念。>
     版权所有 (C) <年份> <作者姓名>
     该程序是免费软件：您可以重新分发和/或修改
     它根据由发布的 GNU 通用公共许可证的条款
     自由软件基金会，许可证的第 3 版，或
     （由您选择）任何更高版本。
     这个程序是分发的，希望它有用，
     但没有任何保证；  甚至没有暗示的保证
     特定用途的适销性或适用性。  见
     有关更多详细信息，请参阅 GNU 通用公共许可证。
     您应该已经收到一份 GNU 通用公共许可证的副本
     随着这个程序。如果没有，请参阅 <https://www.gnu.org/licenses/>。

*/

#include "iic_sensor.hpp"

void epo_iic_sensoer_init()
{

  Wire.begin();
  Wire.setClock(100000);
}

ADXL345::ADXL345(uint8_t address)
{

  iic_addr = address;
}

ADXL345::ADXL345()
{

  iic_addr = ADXL345_DEFAULT_ADDRESS;
}
bool ADXL345::init_adxl345()
{
  Serial.println("ADXL345 BRGIN");
  if (read_sensor_id() == 0xE5)
  {
    return 1;
    Serial.println("ADXL345 READY");
  }
  else
  {
    return 0;
    Serial.println("ADXL345 ERROR");
  }
}
void ADXL345::set_reg(uint8_t reg_addr, uint8_t value)
{

  Wire.beginTransmission(iic_addr);
  Wire.write(reg_addr);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t ADXL345::read_reg(uint8_t reg_addr)
{
  uint8_t data;
  Wire.beginTransmission(iic_addr);
  Wire.write(reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(iic_addr, (uint8_t)(1));
  data = Wire.read();
  return data;
}

uint8_t ADXL345::read_sensor_id()
{

  return read_reg(ADXL345_REG_DEVID);
}

void ADXL345::reset_reg()
{
  set_reg(ADXL345_REG_THRESH_TAP, 0x00);
  set_reg(ADXL345_REG_OFSX, 0x00);
  set_reg(ADXL345_REG_OFSY, 0x00);
  set_reg(ADXL345_REG_OFSZ, 0x00);
  set_reg(ADXL345_REG_DUR, 0x00);
  set_reg(ADXL345_REG_LATENT, 0x00);
  set_reg(ADXL345_REG_WINDOW, 0x00);
  set_reg(ADXL345_REG_THRESH_ACT, 0x00);
  set_reg(ADXL345_REG_THRESH_INACT, 0x00);
  set_reg(ADXL345_REG_TIME_INACT, 0x00);
  set_reg(ADXL345_REG_ACT_INACT_CTL, 0x00);
  set_reg(ADXL345_REG_THRESH_FF, 0x00);
  set_reg(ADXL345_REG_TIME_FF, 0x00);
  set_reg(ADXL345_REG_TAP_AXES, 0x00);
  set_reg(ADXL345_REG_BW_RATE, B00001010);
  set_reg(ADXL345_REG_POWER_CTL, 0x00);
  set_reg(ADXL345_REG_INT_ENABLE, 0x00);
  set_reg(ADXL345_REG_INT_MAP, 0x00);
  set_reg(ADXL345_REG_DATA_FORMAT, 0x00);
  set_reg(ADXL345_REG_FIFO_CTL, 0x00);
}

void ADXL345::set_ofs(uint8_t x, uint8_t y, uint8_t z)
{

  set_reg(ADXL345_REG_OFSX, x);
  set_reg(ADXL345_REG_OFSY, y);
  set_reg(ADXL345_REG_OFSZ, z);
}
void ADXL345::set_tap_mode(TAP_InitTypeDef *TAP)
{

  uint8_t tap_axes_default = B00000000;

  tap_axes_default |= (TAP->Tap_Suppress << 3); //其实这里不需要if，懒得改了。

  tap_axes_default |= (TAP->Tap_axes_x << 2);
  tap_axes_default |= (TAP->Tap_axes_y << 1);
  tap_axes_default |= (TAP->Tap_axes_z);

  set_reg(ADXL345_REG_TAP_AXES, tap_axes_default);

  set_reg(ADXL345_REG_THRESH_TAP, TAP->Tap_Thresh);
  set_reg(ADXL345_REG_DUR, TAP->Tap_Dur);

  set_reg(ADXL345_REG_LATENT, TAP->Double_Tap_Latent);
  set_reg(ADXL345_REG_WINDOW, TAP->Double_Tap_Window);
}
void ADXL345::set_speed_mode(BW_RATE_InitTypeDef *BW)
{
  uint8_t bw_rate_default = 0x00;
  bw_rate_default |= BW->speed;
  bw_rate_default |= (BW->low_power << 4);
  set_reg(ADXL345_REG_BW_RATE, bw_rate_default);
}

void ADXL345::set_power_mode(Power_InitTypeDef *P_CTL)
{

  uint8_t power_ctl_default = B00000000;

  power_ctl_default |= (P_CTL->Link << 5);
  power_ctl_default |= (P_CTL->AUTO_SLEEP << 4);
  power_ctl_default |= (P_CTL->Measure << 3);
  power_ctl_default |= (P_CTL->Sleep << 2);
  power_ctl_default |= P_CTL->Wakeup_speed;
  set_reg(ADXL345_REG_POWER_CTL, power_ctl_default);
}

void ADXL345::set_interrput(Interrupt_InitTypeDef *INT_P)
{
  uint8_t act_ctl_default = B00000000;
  uint8_t int_enable_default = B00000000;
  uint8_t int_map_default = B00000000;

  act_ctl_default |= INT_P->INACT_Z;
  act_ctl_default |= (INT_P->INACT_Y << 1);
  act_ctl_default |= (INT_P->INACT_X << 2);
  act_ctl_default |= (INT_P->INACT << 3);

  act_ctl_default |= (INT_P->ACTZ << 4);
  act_ctl_default |= (INT_P->ACTY << 5);
  act_ctl_default |= (INT_P->ACTX << 6);
  act_ctl_default |= (INT_P->ACT << 7);

  set_reg(ADXL345_REG_ACT_INACT_CTL, act_ctl_default);
  int_enable_default |= INT_P->overrun;
  int_enable_default |= (INT_P->watermark << 1);
  int_enable_default |= (INT_P->free_fall << 2);
  int_enable_default |= (INT_P->inactivity << 3);

  int_enable_default |= (INT_P->activity << 4);
  int_enable_default |= (INT_P->double_tap << 5);
  int_enable_default |= (INT_P->single_tap << 6);
  int_enable_default |= (INT_P->data_ready << 7);
  set_reg(ADXL345_REG_INT_ENABLE, int_enable_default);

  int_map_default |= (INT_P->map_overrun);
  int_map_default |= (INT_P->map_watermark << 1);
  int_map_default |= (INT_P->map_free_fall << 2);
  int_map_default |= (INT_P->map_inactivity << 3);

  int_map_default |= (INT_P->map_activity << 4);
  int_map_default |= (INT_P->map_double_tap << 5);
  int_map_default |= (INT_P->map_single_tap << 6);
  int_map_default |= (INT_P->map_data_ready << 7);
  set_reg(ADXL345_REG_INT_MAP, int_map_default);
}

void ADXL345::set_activity_inactivity(uint8_t act, uint8_t inact, uint8_t inact_time)
{
  set_reg(ADXL345_REG_THRESH_ACT, act);
  set_reg(ADXL345_REG_THRESH_INACT, inact);
  set_reg(ADXL345_REG_TIME_INACT, inact_time);
}
void ADXL345::set_fifo_mode(Fifo_InitTypeDef *FIO)
{
  uint8_t data_format_default = 0x00;
  uint8_t fifo_ctl_default = 0x00;

  data_format_default |= (FIO->range);
  data_format_default |= (FIO->justify << 2);
  data_format_default |= (FIO->full_res << 3);

  data_format_default |= (FIO->int_invert << 5);
  data_format_default |= (FIO->spi << 6);
  data_format_default |= (FIO->self_test << 7);
  set_reg(ADXL345_REG_DATA_FORMAT, data_format_default);

  fifo_ctl_default |= FIO->fifo_mode;
  fifo_ctl_default |= (FIO->trigger << 5);
  fifo_ctl_default |= FIO->samples;
  set_reg(ADXL345_REG_FIFO_CTL, fifo_ctl_default);
}
void ADXL345::read_InterruptSource(Interruput_source_InitTypeDef *INT_S)
{

  INT_S->source_read = read_reg(ADXL345_REG_INT_SOURCE);

  INT_S->source_overrun = bitRead(INT_S->source_read, 0);
  INT_S->source_watermark = bitRead(INT_S->source_read, 1);
  INT_S->source_free_fall = bitRead(INT_S->source_read, 2);
  INT_S->source_inactivity = bitRead(INT_S->source_read, 3);
  INT_S->source_activity = bitRead(INT_S->source_read, 4);
  INT_S->source_double_tap = bitRead(INT_S->source_read, 5);
  INT_S->source_single_tap = bitRead(INT_S->source_read, 6);
  INT_S->source_data_ready = bitRead(INT_S->source_read, 7);
  //if(INT_S->source_overrun)    Serial.println("overrun");      //溢出
  if (INT_S->source_watermark)
    Serial.println("watermark"); //水印
  if (INT_S->source_free_fall)
    Serial.println("free_fall"); //自由落体
  if (INT_S->source_inactivity)
    Serial.println("inactivity"); //静止
  if (INT_S->source_activity)
    Serial.println("activity"); //运动
  if (INT_S->source_double_tap)
    Serial.println("double_tap"); //双击
  if (INT_S->source_single_tap)
    Serial.println("single_tap"); //单次敲击
  //if(INT_S->source_data_ready) Serial.println("data_ready");   //数据就绪
}

void ADXL345::readAccel(int *x, int *y, int *z)
{
  // Read Accel Data from ADXL345
  _buff[0] = read_reg(ADXL345_REG_DATAX0);
  _buff[1] = read_reg(ADXL345_REG_DATAX1);
  _buff[2] = read_reg(ADXL345_REG_DATAY0);
  _buff[3] = read_reg(ADXL345_REG_DATAY1);
  _buff[4] = read_reg(ADXL345_REG_DATAZ0);
  _buff[5] = read_reg(ADXL345_REG_DATAZ1);
  // Each Axis @ All g Ranges: 10 Bit Resolution (2 Bytes)
  *x = (int16_t)((((int)_buff[1]) << 8) | _buff[0]);
  *y = (int16_t)((((int)_buff[3]) << 8) | _buff[2]);
  *z = (int16_t)((((int)_buff[5]) << 8) | _buff[4]);
}

AHT10::AHT10()
{
  aht_iic_addr = AHT10_DEFAULT_ADDRESS;
}
AHT10::AHT10(uint8_t address)
{

  aht_iic_addr = address;
}

void AHT10::init_aht(){
  
Wire.beginTransmission(aht_iic_addr);
Wire.write(B01110000);
Wire.write(B11110001);
Wire.write(B00001000);
Wire.write(B00000000);
Wire.endTransmission();
}
void AHT10::reset(){
Wire.beginTransmission(aht_iic_addr);
Wire.write(B10000000);
Wire.write(B10111010);
Wire.endTransmission();

}
void AHT10::start_measure(){

Wire.beginTransmission(aht_iic_addr);
Wire.write(B01110000);
Wire.write(B10101100);
Wire.write(B00000000);
Wire.write(B00000000);
Wire.endTransmission();
}
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
}

