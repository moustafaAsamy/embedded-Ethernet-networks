/*
 * config.c
 *
 *  Created on: Oct 22, 2019
 *      Author: lenovo
 */

#include "config.h"

uint16_t ecu_1_S_port =35;
uint16_t ecu_2_S_port =70;
uint16_t ecu_1_D_port =70;
ip_addr_t dest_1_address ={0xfbb03020};
struct tcp_pcb * pcb;

#if ECU1
 struct netif g_sNetIF;
 struct ip_addr ip_addr  = {0xfbb02814};
 struct ip_addr net_mask;
 struct ip_addr gw_addr;
 const uint8_t mac[6] ={0x32,0x45,0x67,0x89,0xAB,0xCD};
#endif


#if ECU2
struct netif g_sNetIF;
struct ip_addr ip_addr ={0xfbb03020};
struct ip_addr net_mask;
struct ip_addr gw_addr;
const uint8_t mac[6] = {0x34,0x45,0x67,0x89,0xeB,0xeD};
#endif

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
