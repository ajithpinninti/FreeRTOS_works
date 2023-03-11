
#include "FreeRTOS.h"
#include "hook_function.h"

uint32_t idleCycleCount = 0;

void vApplicationIdleHook( void){

	idleCycleCount++;
}
