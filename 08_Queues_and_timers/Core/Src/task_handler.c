/*
 * task_handler.c
 *
 *  Created on: Mar 12, 2023
 *      Author: ajitp
 */



#include "main.h"




void cmd_task(void *param){

	BaseType_t ret;
	command_t cmd;

	while(1){
		ret = xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		if(ret == pdTRUE){
			process_command(&cmd);
		}

	}
	return;
}
void menu_task(void * param){


	while(1){


	}
}


void led_task(void * param){

	while(1){


	}
}

void rtc_task(void* param){

	while(1){


	}
}


void print_task(void * param){

	while(1){

	}
}


int extract_command(command_t *cmd){

	uint8_t item;
	BaseType_t status;

	status = uxQueueMessagesWaiting(q_data);
	if(!status) return -1;
	uint8_t i=0;

	do{
		status = xQueueReceive(q_data, &item, 0);
		if(status == pdTRUE) cmd->payload[i++] = item;
	}while(item!='\n');

	cmd->payload[i-1] = '\0';
	cmd->len = i-1;

	return 0;
}


void process_command(command_t *cmd){

	/* Extrct data bytes from*/
//	cmd ->payload = q_data;
//	cmd ->len = strlen(q_data);

	extract_command(cmd);

	switch(curr_state){
	case sMainMenu:
		xTaskNotify(handle_menu_task,(uint32_t)cmd, eSetValueWithOverwrite);
		break;
	case sLedEffect:
		xTaskNotify(handle_led_task,(uint32_t)cmd, eSetValueWithOverwrite);
		break;
	case sRtcMenu:
	case sRtcTimeConfig:
	case sRtcDateConfig:
	case sRtcReport:
		xTaskNotify(handle_rtc_task,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	}

}

