#ifndef __ULRRASONIC_WAVE_UART
#define __ULRRASONIC_WAVE_UART

#include "ebox.h"


//基础超声波模块驱动
class UltrasonicWaveUart
{
    Uart *uart;
    uint16_t dis;
    bool isHigh;
    bool isReady;
public:

    //构造函数，确定Uart
    UltrasonicWaveUart(Uart *uartX):
    uart(uartX),
    dis(0),
    isHigh(true),
    isReady(false)
    {

    }

    //初始化函数，初始化uart口
    void begin()
    {
        uart->begin(9600);
        uart->attach(this,&UltrasonicWaveUart::rxEvent,RxIrq);
    }

    //uart字节处理中断函数
    void rxEvent()
    {
        if(isHigh)
        {
            isHigh=false;
            uint8_t c = uart->read();
            dis=c*256;
        }
        else
        {
            isHigh=true;
            uint8_t c = uart->read();
            dis=dis+c;
            isReady=true;
        }
    }

    //基于忙等的read函数
    uint16_t read()
    {
        while(!isReady)
        {
        }
        isReady=false;
        return dis;
    }

    //发送触发指令，开始测距
    void trig()
    {
        uart->write(0x55);
    }
};


#endif