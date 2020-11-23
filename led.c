/*
 * led.c
 *
 *  Created on: Oct 23, 2019
 *      Author: lenovo
 * new edit on 23/10/2020
 */


#include "led.h"



void led_on(uint8_t led)
{
    MAP_GPIOPinWrite(GPIO_PORTF_BASE,led, led);
    //MAP_GPIOPinWrite(GPIO_PORTF_BASE,~led, ~led);
}
void led_off(void)
{
    MAP_GPIOPinWrite(GPIO_PORTF_BASE,all, 0);
}
