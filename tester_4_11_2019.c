#if 0
/*
 * tester_4_11_2019.c
 *
 *  Created on: Apr 11, 2019
 *      Author: moustafa ahmed
 */
#include <stdint.h>
#include "enc28j60.h"
#include "spi.h"
#include "driverlib/gpio.h"
#include "lwip_int.h"
#include "config.h"
#include "driverlib/rom_map.h"
void SimpleDelay_2(void);
void buffer_update(void);
void buffer_update_2(void);


extern void ButtonsInit(void);
uint8_t my_fristpacket1[1514]= {0} ;
uint8_t frame[110];
const uint8_t mac_addr_S3[6]     =   {0x32,0x45,0x66,0x8b,0xAB,0xCD};

#if uincast
const uint8_t mac_addr_dest2[6]  =   {0x32,0x45,0x67,0x89,0xAB,0xCD};
const uint8_t mac_addr_S2[6]     =   {0x34,0x45,0x67,0x89,0xeB,0xeD};

const uint8_t mac_addr_dest1[6]  =   {0x34,0x45,0x67,0x89,0xeB,0xeD};
const uint8_t mac_addr_S1[6]     =   {0x32,0x45,0x67,0x89,0xAB,0xCD};
#endif

#if brodcast
const uint8_t mac_addr_dest2[6]  =   {0xff,0xff,0xff,0xff,0xff,0xff};
const uint8_t mac_addr_S2[6]     =   {0x34,0x45,0x67,0x89,0xeB,0xeD};
const uint8_t mac_addr_dest1[6]  =   {0xff,0xff,0xff,0xff,0xff,0xff};
const uint8_t mac_addr_S1[6]     =   {0x32,0x45,0x67,0x89,0xAB,0xCD};
#endif



#if tx
int main(void)
{
    enc28j60_comm_init();
    spi_init();
    enc_init(mac_addr_S1);
    buffer_update();
    timer_start();


  while(1)
   {
   }
  return 0;
}
#endif

#if rx
int counter;
uint8_t x,y;
uint8_t c;
int main(void) {
    gpio_comm_init();
    spi_init();
    //enc_init(mac_addr_S2);
    buffer_update_2();
    ButtonsInit();
    lwIPPrivateInit(0);
    timer_start();
  while(1) {
      //uint8_t c=READ_REG(ENC_ECON1);
   }
  return 0;
}
#endif
extern void transfer(int countd)
{
    enc_send_packet(my_fristpacket1, countd);
}

#if tx2
int counter;
uint8_t x,y;
uint8_t c;
int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    enc28j60_comm_init();
    spi_init();
    enc_init(mac_addr_S2);
    timer_start();
  while(1)
   {
   }


  return 0;
}
#endif

/****************************************************************************************************************************************************************************/

void
SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}

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
       { my_fristpacket1[i] = '78';}
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
void
SimpleDelay_2(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 12);
}

//extern void check_incoming_2(void )
//{
//         if  ( (  my2[0]== mac_addr_S2[0]  ) &&(  my2[1]==mac_addr_S2[1]  )  &&(  my2[2]== mac_addr_S2[2]  ) &&(  my2[3]== mac_addr_S2[3]  ) &&(  my2[4]==mac_addr_S2[4]  ) && (  my2[5]== mac_addr_S2[5]  )  )
//         {
//             buffer_update_2();
//             enc_send_packet(my_fristpacket1, 114);
//         }
//         if  ( (  my2[0]== 0xff  ) &&(  my2[1]==0xff  )  &&(  my2[2]== 0xff  ) &&(  my2[3]== 0xff  ) &&(  my2[4]==0xff  ) && (  my2[5]== 0xff  )  )
//                  {
//                      buffer_update_2();
//                      enc_send_packet(my_fristpacket1, 114);
//                  }
//}
//
//extern void check_incoming_1(void)
//{
//    if  ( (  my2[0]== mac_addr_S1[0]  ) &&(  my2[1]==mac_addr_S1[1]  )  &&(  my2[2]== mac_addr_S1[2]  ) &&(  my2[3]== mac_addr_S1[3]  ) &&(  my2[4]==mac_addr_S1[4]  ) && (  my2[5]== mac_addr_S1[5]  )  )
//            {
//                buffer_update();
//                enc_send_packet(my_fristpacket1, 42);
//            }
//    if  ( (  my2[0]== 0xff  ) &&(  my2[1]==0xff  )  &&(  my2[2]== 0xff  ) &&(  my2[3]== 0xff  ) &&(  my2[4]==0xff  ) && (  my2[5]== 0xff  )  )
//                      {
//                          buffer_update();
//                          enc_send_packet(my_fristpacket1, 42);
//                      }
//
//}
//
#endif
