/*
 * driver_tester.c
 *
 *  Created on: Oct 22, 2019
 *      Author: moustafa
 */


#include <stdint.h>
#include "enc28j60.h"
#include "spi.h"
#include "config.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"


#include "enc28j60.h"
#include "lwip_int.h"


void SimpleDelay_2(void);
void buffer_update(void);
void buffer_update_2(void);
extern void  timer_start(void);

uint8_t my_fristpacket1[1514]= {0} ;

#if driver_tester
#if tx_rx_1
void main(void)
{
    gpio_comm_init();
    spi_init();
    enc_init(mac_addr_S1);
    buffer_update();
    timer_start();
  while(1)
   {
   }
}
#endif

#if tx_rx_2
void main(void) {
    gpio_comm_init();
    spi_init();
    enc_init(mac);
    timer_start();
    netif_add(&g_sNetIF, &ip_addr, &net_mask, &gw_addr, NULL, NULL,NULL);
    netif_set_default(&g_sNetIF);
    g_sNetIF.hwaddr[0] = mac[0];
    g_sNetIF.hwaddr[1] = mac[1];
    g_sNetIF.hwaddr[2] = mac[2];
    g_sNetIF.hwaddr[3] = mac[3];
    g_sNetIF.hwaddr[4] = mac[4];
    g_sNetIF.hwaddr[5] = mac[5];
    g_sNetIF.output = etharp_output;
    g_sNetIF.linkoutput = enc_low_level_output;
//    gpio_comm_init();
//    spi_init();
//    enc_init(mac_addr_S2);
//    buffer_update_2();
//    timer_start();

  while(1)
  {}
}
#endif

/****************************************************************************************************************************************************************************/

extern void application_timer(void)
{
    enc_send_packet(my_fristpacket1, 114);
}

void application_timer_off(void)
{
 MAP_GPIOPinWrite(GPIO_PORTF_BASE, 4, 0);
 MAP_GPIOPinWrite(GPIO_PORTF_BASE, 2, 0);
}

void buffer_update(void)
{
       int i=0;
       for(i = 0; i<113 ;i++)
       { my_fristpacket1[i] = '5';}
       my_fristpacket1[0]=mac_addr_dest1[0];
       my_fristpacket1[1]=mac_addr_dest1[1];
       my_fristpacket1[2]=mac_addr_dest1[2];
       my_fristpacket1[3]=mac_addr_dest1[3];
       my_fristpacket1[4]=mac_addr_dest1[4];
       my_fristpacket1[5]=mac_addr_dest1[5];
       my_fristpacket1[6]=mac_addr_S1[0];
       my_fristpacket1[7]=mac_addr_S1[1];
       my_fristpacket1[8]=mac_addr_S1[2];
       my_fristpacket1[9]=mac_addr_S1[3];
       my_fristpacket1[10]=mac_addr_S1[4];
       my_fristpacket1[11]=mac_addr_S1[5];
       my_fristpacket1[12]= 118 &0xFF;
       my_fristpacket1[13]= (118>>8) & 0xFF;
}

void buffer_update_2(void)
{
       int i=0;
       for(i = 0; i<113 ;i++)
       { my_fristpacket1[i] = '7';}
       my_fristpacket1[0]=mac_addr_dest2[0];
       my_fristpacket1[1]=mac_addr_dest2[1];
       my_fristpacket1[2]=mac_addr_dest2[2];
       my_fristpacket1[3]=mac_addr_dest2[3];
       my_fristpacket1[4]=mac_addr_dest2[4];
       my_fristpacket1[5]=mac_addr_dest2[5];
       my_fristpacket1[6]=mac_addr_S2[0];
       my_fristpacket1[7]=mac_addr_S2[1];
       my_fristpacket1[8]=mac_addr_S2[2];
       my_fristpacket1[9]=mac_addr_S2[3];
       my_fristpacket1[10]=mac_addr_S2[4];
       my_fristpacket1[11]=mac_addr_S2[5];
       my_fristpacket1[12]= 118 &0xFF;
       my_fristpacket1[13]= (118>>8) & 0xFF;
}
void SimpleDelay_2(void)
{
    SysCtlDelay(16000000 / 12);
}
#endif
