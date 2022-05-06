#include "ThisThread.h"
#include "mbed.h"
#include "BME280.h"



BME280 sensor(I2C_SDA, I2C_SCL);


DigitalOut oled1(LED1);

InterruptIn ibutton1(BUTTON1);

Ticker toggle_led_ticker;

static auto sleep_time = 1000ms;
void led_ticker()
{
    oled1=!oled1;
}
void pressed()
{
    toggle_led_ticker.detach(); //Открепляем таймер
    toggle_led_ticker.attach(&led_ticker, sleep_time);

}

char buf[2];

int main()
{
    toggle_led_ticker.attach(&led_ticker, sleep_time);
    while (true)
    {
        printf("%d degC, %d hPa, %d \n", (int)sensor.getTemperature(),(int)sensor.getPressure(), (int)sensor.getHumidity());
        if ((int)sensor.getTemperature()<28)
        {
            oled1=1;
        }
        if (((int)sensor.getTemperature()>=28) && ((int)sensor.getTemperature()<30))
        {
            oled1=1;
            ThisThread::sleep_for(100ms);
            oled1=0;
            ThisThread::sleep_for(100ms);
        }
        if ((int)sensor.getTemperature()>=30)
        {
             oled1=1;
            ThisThread::sleep_for(1s);
            oled1=0;
            ThisThread::sleep_for(1s);
        }

    }
    toggle_led_ticker.detach();
}