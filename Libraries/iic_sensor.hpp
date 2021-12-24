#ifndef _IIC_SENSOR_HPP_
#define _IIC_SENSOR_HPP_
#include "Arduino.h"
#include "Wire.h"
//*****************************寄存器地址***********************************************
#define ADXL345_DEFAULT_ADDRESS (0x53)
#define ADXL345_REG_DEVID (0x00)          // Device ID
#define ADXL345_REG_THRESH_TAP (0x1D)     // Tap threshold
#define ADXL345_REG_OFSX (0x1E)           // X-axis offset
#define ADXL345_REG_OFSY (0x1F)           // Y-axis offset
#define ADXL345_REG_OFSZ (0x20)           // Z-axis offset
#define ADXL345_REG_DUR (0x21)            // Tap duration
#define ADXL345_REG_LATENT (0x22)         // Tap latency
#define ADXL345_REG_WINDOW (0x23)         // Tap window

#define ADXL345_REG_THRESH_ACT (0x24)     // Activity threshold
#define ADXL345_REG_THRESH_INACT (0x25)   // Inactivity threshold
#define ADXL345_REG_TIME_INACT (0x26)     // Inactivity time

#define ADXL345_REG_ACT_INACT_CTL (0x27)  // Axis enable control for activity and inactivity detection
#define ADXL345_REG_THRESH_FF (0x28)      // Free-fall threshold
#define ADXL345_REG_TIME_FF (0x29)        // Free-fall time
#define ADXL345_REG_TAP_AXES (0x2A)       // Axis control for single/double tap
#define ADXL345_REG_ACT_TAP_STATUS (0x2B) // map for single/double tap
#define ADXL345_REG_BW_RATE (0x2C)        // Data rate and power mode control
#define ADXL345_REG_POWER_CTL (0x2D)      // Power-saving features control
#define ADXL345_REG_INT_ENABLE (0x2E)     // Interrupt enable control
#define ADXL345_REG_INT_MAP (0x2F)        // Interrupt mapping control
#define ADXL345_REG_INT_SOURCE (0x30)     // map of interrupts
#define ADXL345_REG_DATA_FORMAT (0x31)    // Data format control
#define ADXL345_REG_DATAX0 (0x32)         // X-axis data 0
#define ADXL345_REG_DATAX1 (0x33)         // X-axis data 1
#define ADXL345_REG_DATAY0 (0x34)         // Y-axis data 0
#define ADXL345_REG_DATAY1 (0x35)         // Y-axis data 1
#define ADXL345_REG_DATAZ0 (0x36)         // Z-axis data 0
#define ADXL345_REG_DATAZ1 (0x37)         // Z-axis data 1
#define ADXL345_REG_FIFO_CTL (0x38)       // FIFO control
#define ADXL345_REG_FIFO_STATUS (0x39)    // FIFO status
//*******************测量时采样速率****************************************************//
#define ADXL345_DATARATE_3200_HZ ((uint8_t)B00001111) // 1600Hz Bandwidth   140µA IDD
#define ADXL345_DATARATE_1600_HZ ((uint8_t)B00001110) //  800Hz Bandwidth    90µA IDD
#define ADXL345_DATARATE_800_HZ ((uint8_t)B00001101)  //  400Hz Bandwidth   140µA IDD
#define ADXL345_DATARATE_400_HZ ((uint8_t)B00001100)  //  200Hz Bandwidth   140µA IDD
#define ADXL345_DATARATE_200_HZ ((uint8_t)B00001011)  //  100Hz Bandwidth   140µA IDD
#define ADXL345_DATARATE_100_HZ ((uint8_t)B00001010)  //   50Hz Bandwidth   140µA IDD
#define ADXL345_DATARATE_50_HZ ((uint8_t)B00001001)   //   25Hz Bandwidth    90µA IDD
#define ADXL345_DATARATE_25_HZ ((uint8_t)B00001000)   // 12.5Hz Bandwidth    60µA IDD
#define ADXL345_DATARATE_12_5_HZ ((uint8_t)B00000111) // 6.25Hz Bandwidth    50µA IDD
#define ADXL345_DATARATE_6_25HZ ((uint8_t)B00000110)  // 3.13Hz Bandwidth    45µA IDD
#define ADXL345_DATARATE_3_13_HZ ((uint8_t)B00000101) // 1.56Hz Bandwidth    40µA IDD
#define ADXL345_DATARATE_1_56_HZ ((uint8_t)B00000100) // 0.78Hz Bandwidth    34µA IDD
#define ADXL345_DATARATE_0_78_HZ ((uint8_t)B00000011) // 0.39Hz Bandwidth    23µA IDD
#define ADXL345_DATARATE_0_39_HZ ((uint8_t)B00000010) // 0.20Hz Bandwidth    23µA IDD
#define ADXL345_DATARATE_0_20_HZ ((uint8_t)B00000001) // 0.10Hz Bandwidth    23µA IDD
#define ADXL345_DATARATE_0_10_HZ ((uint8_t)B00000000) // 0.05Hz Bandwidth    23µA IDD
//******************************休眠采样速率*******************************************//
#define ADXL345_SLEEPDATARATE_8_HZ ((uint8_t)B00000000)
#define ADXL345_SLEEPDATARATE_4_HZ ((uint8_t)B00000001)
#define ADXL345_SLEEPDATARATE_2_HZ ((uint8_t)B00000010)
#define ADXL345_SLEEPDATARATE_1_HZ ((uint8_t)B00000011)
//*****************************测量范围************************************************//
#define ADXL345_RANGE_16_G (uint8_t)B00000011 // +/- 16g
#define ADXL345_RANGE_8_G (uint8_t) B00000010  // +/- 8g
#define ADXL345_RANGE_4_G (uint8_t)B00000001  // +/- 4g
#define ADXL345_RANGE_2_G (uint8_t)B00000000  // +/- 2g (default value)
//****************************FIFO模式*************************************************//
#define FIFO_BYPASS (uint8_t)B00000000
#define FIFO_FIFO (uint8_t)B01000000
#define FIFO_STREAM (uint8_t)B10000000
#define FIFO_TRIGGER (uint8_t)B11000000

#define FIFO_SAMPLES_8 (uint8_t)B00001000  //8
#define FIFO_SAMPLES_16 (uint8_t)B00010000 //16
#define FIFO_SAMPLES_24 (uint8_t)B00011000 //24
#define FIFO_SAMPLES_31 (uint8_t)B00011111 //31
//*************************************************************************************//
#define INT_ENABLE 1
#define INT_DISENABLE 0
#define INT_PIN1 0
#define INT_PIN2 1
#define INT_INVERT_HIGH 0
#define INT_INVERT_LOW 1
#define ACT_AXES_ENABLE 1
#define ACT_AXES_DISENABLE 0
#define ACT_DC 0
#define ACT_AC 1
//***************************************AHT10***********************************************/

#define AHT10_DEFAULT_ADDRESS 0x38

//***************************************AHT10***********************************************/

typedef enum
{
  ADXL345_INTERRUPT_DATA_READY = B10000000,
  ADXL345_INTERRUPT_SINGLE_TAP = B01000000,
  ADXL345_INTERRUPT_DOUBLE_TAP = B00100000,
  ADXL345_INTERRUPT_Activity = B00010000,
  ADXL345_INTERRUPT_Inactivity = B00001000,
  ADXL345_INTERRUPT_FREE_FALL = B00000100,
  ADXL345_INTERRUPT_Watermark = B00000010,
  ADXL345_INTERRUPT_Overrun = B00000001,
} interruptType_t;

//************************************寄存器抽象*********************
typedef struct //敲击功能
{
  uint8_t Tap_axes_x; //轴使能
  uint8_t Tap_axes_y;
  uint8_t Tap_axes_z;

  uint8_t Tap_Suppress; //抑制

  uint8_t Tap_Thresh;        //界限     敲击阈值
  uint8_t Tap_Dur;           //持续时间
  uint8_t Double_Tap_Latent; //延迟
  uint8_t Double_Tap_Window; //窗口

} TAP_InitTypeDef;

typedef struct //测量速率与低功耗
{
  uint8_t low_power; //低功耗
  uint8_t speed;     //速率

} BW_RATE_InitTypeDef;

typedef struct //电源控制寄存器
{

  uint8_t Link;         //链接
  uint8_t AUTO_SLEEP;   //自动休眠
  uint8_t Measure;      //测量
  uint8_t Sleep;        //休眠
  uint8_t Wakeup_speed; //休眠采样速率

} Power_InitTypeDef;
typedef struct
{

  uint8_t ACT, ACTX, ACTY, ACTZ;
  uint8_t INACT, INACT_X, INACT_Y, INACT_Z; //ACT_INACT_CTL，耦合

  uint8_t data_ready, single_tap, double_tap, activity; //INT_ENABLE中断使能
  uint8_t inactivity, free_fall, watermark, overrun;

  uint8_t map_data_ready, map_single_tap, map_double_tap, map_activity; //INT_MAP中断引脚映射
  uint8_t map_inactivity, map_free_fall, map_watermark, map_overrun;

} Interrupt_InitTypeDef;

typedef struct
{

  uint8_t self_test, spi, int_invert, full_res, justify, range;
  uint8_t fifo_mode, trigger, samples;

} Fifo_InitTypeDef;

typedef struct
{
  uint8_t source_read,
      source_data_ready,
      source_single_tap,
      source_double_tap,
      source_activity,
      source_inactivity,
      source_free_fall,
      source_watermark,
      source_overrun;

} Interruput_source_InitTypeDef;

class ADXL345
{

public:
  ADXL345(uint8_t);
  ADXL345();

  bool init_adxl345(); //初始化

  uint8_t read_sensor_id(); //读ID
  void reset_reg();
  //复位寄存器
  void set_ofs(uint8_t x, uint8_t y, uint8_t z);    //偏差校准
  void set_tap_mode(TAP_InitTypeDef *TAP);          //敲击模式
  void set_speed_mode(BW_RATE_InitTypeDef *BW);     //采样速率
  void set_power_mode(Power_InitTypeDef *P_CTL);    //电源，测量，休眠
  void set_interrput(Interrupt_InitTypeDef *INT_P); //中断初始化
  void set_fifo_mode(Fifo_InitTypeDef *FIO);
  void set_activity_inactivity(uint8_t act, uint8_t inact, uint8_t inact_time); //运动，静止阈值设置
  void read_InterruptSource(Interruput_source_InitTypeDef *INT_S);
  void readAccel(int *x, int *y, int *z) ;
  
  void set_reg(uint8_t reg_addr, uint8_t value); //写寄存器
  uint8_t read_reg(uint8_t reg_addr);            //读寄存器
 
private:
  uint8_t iic_addr;
  uint8_t _buff[6]={0,0,0,0,0,0};
};


class AHT10
{

public:

AHT10(uint8_t address);
AHT10();

void init_aht();
void reset();
void start_measure();
void read_raw_data();

private:

uint8_t aht_iic_addr;
uint8_t data_buffer[6]={0,0,0,0,0,0};
};

void epo_iic_sensoer_init();


#endif
