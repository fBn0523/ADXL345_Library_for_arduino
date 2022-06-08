# ADXL345_Library_for_arduino
cn->
一种简单方便的驱动库可以很好兼容arduino系列，更少的依赖方便移植到其他类型mcu，灵活配置寄存器

iicsensor ic传感器，这里包括adx345驱动和一个aht10的驱动 意味着他不能以spi方式操作。以后会加以改进。
这个库文件并不简洁。但是可读性非常高，主要弥补流行库文件不能涵盖的功能，例如低功耗，fifo。

en-> Please excuse my poor English  
A simple and convenient driver library can be well compatible with arduino series, less dependence easy to transplant to other types of MCU, flexible configuration register  
 
Iicsensor IC sensor, which includes adX345 driver and an AHT10 driver means it cannot operate in SPI mode.  It will be improved later.  
The library file is not neat.  But the readability is very high, mainly to compensate for popular library files can not cover the features, such as low power, FIFO.   
 
低功耗进入流程 配置auto sleep位为1，在第一次检测静止中断时停止读写ADXL345_REG_INT_SOURCE寄存器，在INT引脚接收到中断后读取寄存器恢复正常运行。意思是在休眠模式不要试图与其通讯。不这样做的后果会导致传感器退出休眠模式后无法再次读取中断标志位

Low power input process Configure the auto sleep bit as 1, stop reading and writing the ADXL345_REG_INT_SOURCE register when detecting the stationary interrupt for the first time, read and write the register after the INT pin receives the interrupt and restore normal operation.  Do not attempt to communicate while in hibernation mode.  Failure to do so will cause the sensor to be unable to read the interrupt flag again after it exits hibernation mode  

# AHT10

AHTxx是来自中国的一种温湿度传感器 aht10 20 21 有各种封装类型，aht10是初代版本，他价格在1——5cny左右。这是一个ADXL345驱动的附带产物。

AHT is a temperature and humidity sensor from China. Aht10 20 21 has various packaging types. Aht10 is the first generation version, and its price is about 1 to 5RMB.  This is a by-product of the ADXL345 drive.  

# AHT20
aht10的升级版本 拥有crc校验和更低的功耗
