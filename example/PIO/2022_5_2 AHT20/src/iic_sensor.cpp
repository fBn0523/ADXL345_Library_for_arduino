/*
 <one line to give the program's name and a brief idea of what it does.>

    Copyright (C) <2022_5_2>  <feng bo ning 冯博宁>

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

bool iic_sensoer_init()
{
  bool iic_state;
  iic_state = Wire.begin();
  Wire.setClock(100000);
  return iic_state;
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
#if USE_SERIAL_DEBUG
  Serial.println("ADXL345 BRGIN");
#endif
  if (read_sensor_id() == 0xE5)
  {
    return 1;
#if USE_SERIAL_DEBUG
    Serial.println("ADXL345 READY");
#endif
  }
  else
  {
    return 0;
#if USE_SERIAL_DEBUG
    Serial.println("ADXL345 ERROR");
#endif
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
  // if(INT_S->source_overrun)    Serial.println("overrun");      //溢出
#if USE_SERIAL_DEBUG
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
#endif
  // if(INT_S->source_data_ready) Serial.println("data_ready");   //数据就绪
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
/*************************************************************************/
AHT10::AHT10() //初始化传感器地址
{
  aht_iic_addr = AHT10_DEFAULT_ADDRESS;
}
AHT10::AHT10(uint8_t address) 
{

  aht_iic_addr = address;
}

void AHT10::init_aht() //初始化传感器
{

  Wire.beginTransmission(aht_iic_addr);
  Wire.write(B01110000);
  Wire.write(B11110001);
  Wire.write(B00001000);
  Wire.write(B00000000);
  Wire.endTransmission();
  reset();
}
void AHT10::reset()//复位传感器
{
  Wire.beginTransmission(aht_iic_addr);
  Wire.write(B10000000);
  Wire.write(B10111010);
  Wire.endTransmission();
}
void AHT10::start_measure()//发起测量
{

  Wire.beginTransmission(aht_iic_addr);
  Wire.write(B01110000);
  Wire.write(B10101100);
  Wire.write(B00000000);
  Wire.write(B00000000);
  Wire.endTransmission();
}
void AHT10::read_raw_data()//分析数据
{
  Wire.beginTransmission(aht_iic_addr);
  Wire.write(B01110001);
  Wire.requestFrom(aht_iic_addr, (uint8_t)(6));

  data_buffer[0] = Wire.read();
  data_buffer[1] = Wire.read();
  data_buffer[2] = Wire.read();
  data_buffer[3] = Wire.read();
  data_buffer[4] = Wire.read();
  data_buffer[5] = Wire.read();
  Wire.endTransmission();

  uint32_t SRH = (data_buffer[1] << 12) + (data_buffer[2] << 4) + (data_buffer[3] >> 4);
  uint32_t ST = ((data_buffer[3] & 0X0f) << 16) + (data_buffer[4] << 8) + (data_buffer[5]);
  humidity = (int)(SRH * 100.0 / 1024 / 1024 + 0.5);
  temperature = ((int)(ST * 2000.0 / 1024 / 1024 + 0.5)) / 10.0 - 50;
#if USE_SERIAL_DEBUG
  Serial.println("iic_sensor.hpp/");
  Serial.println(humidity);
  Serial.println(temperature);
#endif
}
double AHT10::return_humidity(){//返回shi湿度百分数
return humidity;
}
double AHT10::return_temperature(){//返回摄氏wen温度

return temperature;
}
/**********************************************************************/
uint8_t AHT20::read_status()  //读取状态位
{
  uint8_t data;
  data = read_reg(AHT20_STATUS_REG);

  return data;
}

void AHT20::reset_reg(uint8_t addr)  //复位寄存器
{
  uint8_t Byte_first, Byte_second, Byte_third;
  Wire.beginTransmission(AHT20_DEVICE_ADDR);

  Wire.write(addr);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();

  vTaskDelay(5);

  Wire.beginTransmission(AHT20_DEVICE_ADDR);
  Wire.requestFrom(AHT20_DEVICE_ADDR, 3);
  Byte_first = Wire.read();
  Byte_second = Wire.read();
  Byte_third = Wire.read();
  Wire.endTransmission();

  vTaskDelay(10);

  Wire.beginTransmission(AHT20_DEVICE_ADDR);
  // Wire.write(B01110000);
  Wire.write(0xB0 | addr);
  Wire.write(Byte_second);
  Wire.write(Byte_third);
  Wire.endTransmission();

  Byte_first=0x00;
  Byte_second = 0x00;
  Byte_third = 0x00;
}

uint8_t AHT20::read_reg(uint8_t reg_addr) //读取寄存器
{
  uint8_t data;
  Wire.requestFrom(AHT20_DEVICE_ADDR, 1);
  data = Wire.read();
  Wire.endTransmission();
  return data;
}

void AHT20::init_aht() //初始化传感器
{
  vTaskDelay(500);
  if ((read_status() & 0x18) != 0x18)
  {
    reset_reg(0x1b);
    reset_reg(0x1c);
    reset_reg(0x1e);
    vTaskDelay(10);
  }
}

void AHT20::measure_read() //发起测量并计算数据
{

  uint8_t Byte_1th = 0;
  uint8_t Byte_2th = 0;
  uint8_t Byte_3th = 0;
  uint8_t Byte_4th = 0;
  uint8_t Byte_5th = 0;
  uint8_t Byte_6th = 0;
  uint8_t Byte_7th = 0;
  uint16_t cnt = 0;
  uint8_t CTDATA[6] = {0}; //用于CRC传递数组
  send_ac();
  vTaskDelay(80);
  cnt = 0;
  while (((read_status() & 0x80) == 0x80)) //直到状态bit[7]为0，表示为空闲状态，若为1，表示忙状态
  {
    vTaskDelay(1508);
    if (cnt++ >= 100)
    {
      break;
    }
  }


  Wire.requestFrom(AHT20_DEVICE_ADDR, 7);
  CTDATA[0] = Byte_1th = Wire.read(); //状态字，查询到状态为0x98,表示为忙状态，bit[7]为1；状态为0x1C，或者0x0C，或者0x08表示为空闲状态，bit[7]为0
  CTDATA[1] = Byte_2th = Wire.read(); //湿度
  CTDATA[2] = Byte_3th = Wire.read(); //湿度
  CTDATA[3] = Byte_4th = Wire.read(); //湿度/温度
  CTDATA[4] = Byte_5th = Wire.read(); //温度
  CTDATA[5] = Byte_6th = Wire.read(); //温度
  Byte_7th = Wire.read(); // CRC数据
  Wire.endTransmission();

  if (calc_crc8(CTDATA, 6) == Byte_7th)
  {
  
  uint32_t hdata = Byte_2th;
  hdata <<= 8;
  hdata |= Byte_3th;
  hdata <<= 4;
  hdata |= Byte_4th >> 4;
  _humidity = ((float)hdata * 100) / 0x100000;

  uint32_t tdata = Byte_4th & 0x0F;
  tdata <<= 8;
  tdata |= Byte_5th;
  tdata <<= 8;
  tdata |= Byte_6th;
  _temperature = ((float)tdata * 200 / 0x100000) - 50;
#ifdef USE_SERIAL_DEBUG
Serial.println(_humidity);
Serial.println(_temperature);
#endif
  }
 
  

}

uint8_t AHT20::calc_crc8(uint8_t *message,uint8_t Num) //验证校验位
{
        uint8_t i;
        uint8_t byte;
        uint8_t crc=0xFF;
  for(byte=0; byte<Num; byte++)
  {
    crc^=(message[byte]);
    for(i=8;i>0;--i)
    {
      if(crc&0x80) crc=(crc<<1)^0x31;
      else crc=(crc<<1);
    }
  }
        return crc;
}

void AHT20::send_ac(void) //向AHT20发送AC命令
{
 Wire.beginTransmission(AHT20_DEVICE_ADDR);

  Wire.write(0xac);
  Wire.write(0x33);
  Wire.write(0x00);
  Wire.endTransmission();
}

float AHT20::return_humidity(){//返回shi湿度百分数
return _humidity;
}
float AHT20::return_temperature(){//返回摄氏wen温度

return _temperature;
}