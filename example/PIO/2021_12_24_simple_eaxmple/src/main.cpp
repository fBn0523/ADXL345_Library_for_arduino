#include <Arduino.h>
#include "iic_sensor.hpp"

ADXL345 acc;


void epo_adxl345_init(){

acc.init_adxl345();
acc.reset_reg();
}
void adxl345_test(){
/*

这是一个简单的测试程序，你可以根据需要配置各种功能。这里测试最低休眠为27ua通过运动中断唤醒并发生中断（可以唤醒主机）进入采样模式100ua左右，随后自动休眠
具体参见手册，少许不足多多指教。
This is a simple test program that you can configure as much as you need.  The minimum sleep tested here is 27UA, which is woken up by motion interrupt and interrupted (which can wake the host up) to enter sampling mode about 100uA, followed by automatic sleep  
See the manual for details, a little less than a lot of advice.  
*/
    acc.set_ofs(0, 0, 0);
    acc.set_activity_inactivity((uint8_t)16, (uint8_t)15, (uint8_t)10);
    Power_InitTypeDef power_ctl;
    power_ctl.Link = 1;
    power_ctl.AUTO_SLEEP = 0;
    power_ctl.Measure = 1;
    power_ctl.Sleep=0;
    power_ctl.Wakeup_speed = ADXL345_SLEEPDATARATE_1_HZ;
    acc.set_power_mode(&power_ctl);
delay(100);


    TAP_InitTypeDef tap;
    tap.Tap_axes_x = 0;
    tap.Tap_axes_y = 0;
    tap.Tap_axes_z = 1;
    tap.Tap_Suppress = 0;

    tap.Tap_Thresh=(uint8_t)50;       //界限
    tap.Tap_Dur = (uint8_t)15;            //持续时间
    tap.Double_Tap_Latent = (uint8_t)80;  //延迟
    tap.Double_Tap_Window = (uint8_t)200; //窗口

    acc.set_tap_mode(&tap);

    
    BW_RATE_InitTypeDef bw_rate;
    bw_rate.low_power = 1;
    bw_rate.speed = ADXL345_DATARATE_400_HZ;
    acc.set_speed_mode(&bw_rate);
delay(100);
    Interrupt_InitTypeDef Interrput;
    Interrput.ACT = ACT_AC;
    Interrput.ACTX = ACT_AXES_ENABLE;
    Interrput.ACTY = ACT_AXES_ENABLE;
    Interrput.ACTZ = ACT_AXES_ENABLE;
    Interrput.INACT = ACT_AC;
    Interrput.INACT_X = ACT_AXES_ENABLE;
    Interrput.INACT_Y = ACT_AXES_ENABLE;
    Interrput.INACT_Z = ACT_AXES_ENABLE;

    Interrput.data_ready = INT_DISENABLE;
    Interrput.single_tap = INT_DISENABLE;
    Interrput.double_tap = INT_DISENABLE;
    Interrput.activity = INT_ENABLE;
    Interrput.inactivity = INT_ENABLE;
    Interrput.free_fall = INT_DISENABLE;
    Interrput.watermark = INT_DISENABLE;
    Interrput.overrun =   INT_DISENABLE;

    Interrput.map_data_ready = INT_PIN1;
    Interrput.map_single_tap = INT_PIN1;
    Interrput.map_double_tap = INT_PIN1;
    Interrput.map_activity = INT_PIN2;
    Interrput.map_inactivity = INT_PIN1;
    Interrput.map_free_fall = INT_PIN1;
    Interrput.map_watermark = INT_PIN1;
    Interrput.map_overrun = INT_PIN1;

    acc.set_interrput(&Interrput);
    delay(100);


    Fifo_InitTypeDef fio;
    fio.self_test = 0;                //自测
    fio.spi = 0;                      //spi模式选择，1三线，0四线
    fio.int_invert = INT_INVERT_HIGH; //中断高低电平
    fio.full_res =1;                 //1全分辨率，0 10位分辨
    fio.justify = 0;                  //对齐
    fio.range = ADXL345_RANGE_16_G;   //量程

    fio.fifo_mode =FIFO_BYPASS;  //旁路
    fio.trigger = INT_PIN1;       //触发中断1
    fio.samples =FIFO_SAMPLES_31; //8
    acc.set_fifo_mode(&fio);
 delay(100);

}

void setup() {
  Serial.begin(115200);
  epo_iic_sensoer_init();
  epo_adxl345_init();//even_power_on->epo
  adxl345_test();


}
 Interruput_source_InitTypeDef isr;
void loop() {
  int x,y,z;
   acc.read_InterruptSource(&isr);
   acc.readAccel(&x, &y, &z);
   float x_=(atan(x/sqrt(y*y+z*z)))*180/PI;
   float y_=(atan(y/sqrt(x*x+z*z)))*180/PI;
   float z_=(atan(z/sqrt(x*x+y*y)))*180/PI;
   Serial.print(x_);  Serial.print("|"); Serial.print(y_); Serial.print("|");Serial.println(z_);
   delay(100);
}