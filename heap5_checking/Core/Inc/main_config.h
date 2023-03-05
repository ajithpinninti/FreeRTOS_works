/*
 * main_config.h
 *
 *  Created on: Mar 4, 2023
 *      Author: ajitp
 */

#ifndef INC_MAIN_CONFIG_H_
#define INC_MAIN_CONFIG_H_

#include "FreeRTOS.h"

#define SRAM1_AXI_START_ADDRESS ((uint8_t *) 0x24000000 )
#define SRAM1_AXI_SIZE ( 255 *1024)

//#define SRAM1_AXI_SIZE  (uint8_t)( 0x2403FFFF- 0x24000000) * 1024


#define SRAM2_AXI_START_ADDRESS	((uint8_t *) 0x24040000 )
#define SRAM2_AXI_SIZE ( 384 * 1024 )

#define SRAM3_AXI_START_ADDRESS ( (uint8_t *) 0x240A0000 )
#define SRAM3_AXI_SIZE ( 384* 1024 )


#define SRAM1_AHB_START_ADDRESS ( (uint8_t *)  0x30000000 )
#define SRAM1_AHB_SIZE ( 63 * 1024 )

#define SRAM2_AHB_START_ADDRESS ( (uint8_t *) 0x30010000)
#define SRAM2_AHB_SIZE ( 63 * 1024 )


//#define SRAM3_AXI_START_ADDRESS	((uint8_t *) 0x00000000 )

#define SRAM2_SIZE ( 32 * 1024)
//#define SRAM3_SIZE ( 32* 1024 )


#define RAM1_HEAP_SIZE ( 60 * 1024 )

static uint8_t ucHeap[RAM1_HEAP_SIZE];


const HeapRegion_t heap_region[] =
{
		{ucHeap, RAM1_HEAP_SIZE},
//		{SRAM1_AXI_START_ADDRESS,SRAM1_AXI_SIZE},
		{SRAM2_AXI_START_ADDRESS,SRAM2_AXI_SIZE},
		{SRAM3_AXI_START_ADDRESS,SRAM3_AXI_SIZE},
		{SRAM1_AHB_START_ADDRESS,SRAM1_AHB_SIZE},
		{SRAM2_AHB_START_ADDRESS,SRAM2_AHB_SIZE},
		{NULL,0}
};

#endif /* INC_MAIN_CONFIG_H_ */
