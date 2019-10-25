/*
 * lwip_int.c
 *
 *  Created on: Sep 29, 2019
 *      Author: lenovo
 */

#include "enc28j60.h"
#include "lwip_int.h"
#include <stdint.h>
#include "config.h"
#include "timer.h"
#include "led.h"



u8_t  buffer[data_lenght];
volatile uint8_t sent_triger =0;
uint8_t new_data =0;
u8_t  sent_buffer[data_lenght];
 struct tcp_pcb * TCP_list[5]={0};

void ECU_int(void)
{
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
}

uint8_t ECU_Connect(uint16_t D_Port ,uint16_t S_Port, ip_addr_t * dest_address, ip_addr_t *local_addr )
{
 pcb = tcp_new();
 tcp_bind(pcb, local_addr, S_Port);
 uint8_t eTCPReturnCode;
 tcp_sent(pcb, NULL);
 tcp_recv(pcb, NULL);
 tcp_err(pcb, error_event);
 eTCPReturnCode = tcp_connect(pcb, dest_address, D_Port, conection_established);
 return(eTCPReturnCode);
}

void SimpleDelay_2(void)
{
    SysCtlDelay(16000000 / 6);
}
void TCP_passive(ip_addr_t *local_addr ,u16_t port)
{
  pcb = tcp_new();
  tcp_bind(pcb, local_addr, port);
  tcp_listen(pcb,port,local_addr);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  tcp_err(pcb, error_event);
  pcb->connected =conection_established;
  TCP_REG_LISTEN(pcb);
}

void ECU_START_TX(void)
{
    ECU_int();
    SimpleDelay_2();
    ECU_Connect(ecu_1_D_port ,ecu_1_S_port, &dest_1_address, & ip_addr);
}

void ECU_START_RX(void)
{
    ECU_int();
    TCP_passive(& ip_addr ,ecu_2_S_port);
}
void timer(void)
{
     //tcp_slowtmr();
    // etharp_request(&g_sNetIF, &dest_1_address);
    //tcp_connect(pcb, &dest_1_address, ecu_1_D_port+1, 0);
}
void app_task_tx(void)
{
    SEND_data();
}
void app_task_rx(void)
{

}
err_t conection_established(void *pvArg, struct tcp_pcb *psPcb, err_t iErr)
{
    if(iErr != ERR_OK) // Check if there was a TCP error.
    {
        /* callback functions are deactivated */
        tcp_sent(psPcb, NULL);
        tcp_recv(psPcb, NULL);
        tcp_err(psPcb, NULL);
        tcp_close(psPcb);// Close the TCP connection.
        led_on(green);
        return (ERR_OK);
    }
    tcp_recv(psPcb, TCPReceive);
    sent_triger =1;           // ready to send data
    led_on(indego);
    return(ERR_OK);

}

err_t TCPReceive(void *pvArg, struct tcp_pcb *psPcb, struct pbuf *psBuf, err_t iErr)
{   u8_t * RX_Buffer;
    if(psBuf == 0)
    {
     // Tell the application that the connection was closed.
     tcp_close(psPcb);  // Close out the port.
     return(ERR_OK);
    }
    RX_Buffer = &buffer[0];
    memcpy(  RX_Buffer , (u8_t *) psBuf->payload,   psBuf->len);
    new_data=1;
    tcp_recved(psPcb, psBuf->len);             // Indicate that you have received and processed this set of TCP data.
    pbuf_free(psBuf);                          // Free the memory space allocated for this receive.
    RX_Buffer=NULL;
    led_on(white);
    return(ERR_OK);
}

void SEND_data(void)
{ if(pcb!=NULL)
{
  update_data_TX_buffer();
  err_t re= tcp_write(pcb, sent_buffer, data_lenght, 0x01);
  tcp_output(pcb);
}
}

void update_data_TX_buffer()
{
    uint16_t i =0;
    static uint8_t constant =2;
    for(i=0;i<800;i++)
    { sent_buffer[i]=constant;}
    constant =constant+3;
}

void error_event(struct tcp_pcb *psPcb)
{
 pcb =0 ;
 led_off();
 led_on (yellow);
 SimpleDelay_2();
 led_off();
 SimpleDelay_2();
 led_on (yellow);
 SimpleDelay_2();
 led_on (yellow);

}

