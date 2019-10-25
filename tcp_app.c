/*
 * tcp_app.c
 *
 *  Created on: Oct 22, 2019
 *      Author: lenovo
 */

#include "lwip_int.h"
#include "config.h"

#if tcpip



#if ECU1
void main()
{
ECU_START_TX();
while(1){}
}
#endif



#if ECU2
void main()
{
ECU_START_RX();

while(1){}
}
#endif


#endif


