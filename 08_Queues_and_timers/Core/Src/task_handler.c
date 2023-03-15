/*
 * task_handler.c
 *
 *  Created on: Mar 12, 2023
 *      Author: ajitp
 */



#include "main.h"
#include <string.h>

const char *msg_inv = "---- Invalid Option -----";


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

	uint32_t cmd_addr;

	command_t *cmd;

	uint8_t option;
	const char* msg_menu = "===============\n"
							"        Menu   \n"
							"================\n"
							" LED effect    ----> 0\n"
							" Date and Time ----> 1\n"
							" Exit          ----> 2\n"
							"Enter your choice here : ";

	while(1){

		xQueueSend(q_print,&msg_menu,portMAX_DELAY);

		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);
		cmd = (command_t*)cmd_addr;

		if(cmd ->len == 1)
		{
			option = cmd ->payload[0] - 48;

			switch(option){

			case 0:
				curr_state = sLedEffect;
				xTaskNotify(handle_led_task,0, eNoAction);
				break;
			case 1:
				curr_state = sRtcMenu;
				xTaskNotify(handle_rtc_task,0, eNoAction);
				break;
			case 2:/* Implement exit */
				break;
			default:
				xQueueSend(q_print, &msg_inv,portMAX_DELAY);
				continue;

			}

		}else{

			//invalid entry
			xQueueSend(q_print,&msg_inv,portMAX_DELAY);
			continue;
		}

		//wait to run again when somme other rask notifies
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

	}//while super loop
}




void led_task(void * param){

	uint32_t cmd_addr;
	command_t *cmd;
	const char*msg_led = "================\n"
						"     LED effect \n"
						"================\n"
						"(none,e1,e2,e3,e4)\n"
						"Enter your choice here: \n";

	while(1){
		/* Wait for notification ( Notify wait) */

		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		xQueueSend(q_print,&msg_led,portMAX_DELAY);

		/*wait for LED command( Notify wait) */
		xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);

		cmd = ( command_t*)cmd_addr;

		if(cmd->len <=4){

			if(! strcmp( (char*)cmd->payload,"none" ))
				led_effect_stop();
			else if(! strcmp((char*)cmd->payload,"e1" )){
							led_effect(1);
						}
			else if(! strcmp((char*)cmd->payload,"e2" )){
							led_effect(2);
						}
			else if(! strcmp((char*)cmd->payload,"e3" )){
							led_effect(3);
						}
			else if(! strcmp((char*)cmd->payload,"e4" )){
							led_effect(4);
			}
			else{
				xQueueSend(q_print,&msg_inv,portMAX_DELAY);
			}

		}
		else{
			/* Print invalid message */
			xQueueSend(q_print,&msg_inv,portMAX_DELAY);
		}

		curr_state = sMainMenu;

		xTaskNotify(handle_menu_task,0,eNoAction);

	}
}

void rtc_task(void* param){

	while(1){


	}
}


void print_task(void * param){

	uint32_t *msg;
#ifdef  DEBUG
	uint8_t debug_msg[20]="Hello";
#endif
	while(1){
		xQueueReceive(q_print,&msg,portMAX_DELAY);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg,strlen((char*)msg),HAL_MAX_DELAY);
//		strlen((char*)debug_msg)
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
	}while(item!='\r');

	cmd->payload[i-1] = '\0';
	cmd->len = i-1;

	return 0;
}


void process_command(command_t *cmd){

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

