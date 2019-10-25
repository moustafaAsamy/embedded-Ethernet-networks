


#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "lwip_int.h"
#include "config.h"

volatile uint32_t g_ui32Counter = 0;
volatile uint32_t app_Counter = 0;
volatile uint32_t host_timer = 0;
volatile uint32_t host_timer_off = 0;
volatile uint32_t delay_int = 0;
volatile uint8_t int_flag =0;

extern volatile uint8_t sent_triger;

extern void application_timer(void);

extern void SysTickIntHandler(void)
{
#if driver_tester
  g_ui32Counter++;       // Update the Systick interrupt counter. each 10ms
  host_timer++;
  host_timer_off++;
//  if (host_timer == 100)      /*  * 10 ms */
//  {
//      host_timer=0;
//      application_timer();
//  }
//  if (host_timer > 100)
//  {
//     int zc =12;host_timer=0;
//     zc =15;zc=zc;
//  }
  if (host_timer_off == 40 )      /*  * 10 ms */
  {
      host_timer_off=0;
       application_timer_off();
  }
  if (host_timer_off > 40)
  {
       int zc =12;host_timer_off=0;
       zc =15;zc=zc;
  }
#endif
#if tcpip
  if (host_timer_off == 110 )      /*  * 10 ms */
    {
        host_timer_off=0;
         led_off();
    }
    if (host_timer_off > 110)
    {
         int zc =12;host_timer_off=0;
         zc =15;zc=zc;
    }
    host_timer_off++;
if ( (g_ui32Counter == time_ticks) ||(g_ui32Counter > time_ticks) )
    {
       timer();
       g_ui32Counter=0;
    }
g_ui32Counter++;

if(sent_triger == 1)
{
    app_Counter++;
if ((app_Counter == APP_TICKS) )
{
    app_task_tx();
    app_Counter=0;
}
}

#endif
}

extern void  timer_start(void)
{
    g_ui32Counter = 0;
    SysTickPeriodSet(systic_rate);
    IntMasterEnable();
    SysTickIntEnable();
    SysTickEnable();
}
