/*
 * CS122A_SmartSprinkler.c
 *
 * Created: 11/23/2016 9:56:28 AM
 *  Author: Luis
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/delay.h>
#include <string.h>

#include "timer.h"
#include "task.h"
#include "usart_ATmega1284.h"
#include "HX8357_1284.h"

#define NUM_TASKS 1
task tasks[NUM_TASKS];
const unsigned short numTasks = NUM_TASKS;

enum Movement_Input_Controller_States {MIC_Start, MIC_Process};
int MIC_tick (int state);

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned int display_refresh_rate = 20;
	unsigned int input_rate = 40;
	unsigned long TimePeriodGCD = 20;
	
	unsigned char i = 0;
	
	tasks[i].state = MIC_Start;
	tasks[i].period = input_rate;
	tasks[i].elapsedTime = input_rate;
	tasks[i].TickFct = &MIC_tick;
	++i;
	
	
	TimerFlag = 0;
	TimerSet(TimePeriodGCD);
	TimerOn();
	
	SPI_MasterInit();
	displayInit();
	fillScreen(0xFFFF);
	
	while(1)
	{
		for ( unsigned char i = 0; i < numTasks; i++ ) {
			if ( tasks[i].elapsedTime >= tasks[i].period ) 
			{
				tasks[i].state = tasks[i].TickFct(tasks[i].state);
				tasks[i].elapsedTime = 0;
			}
			
			tasks[i].elapsedTime += TimePeriodGCD;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
}


int MIC_tick (int state)
{
	//unsigned char us_pina = ~PINA;
	//unsigned char up = GetBit(us_pina, MOVE_UP_BIT);
	//unsigned char down = GetBit(us_pina, MOVE_DOWN_BIT);
	//unsigned char left = GetBit(us_pina, MOVE_LEFT_BIT);
	//unsigned char right = GetBit(us_pina, MOVE_RIGHT_BIT);
	
	switch(state){
		case MIC_Start:
		state = MIC_Process;
		break;
	}
	
	switch(state){
		case MIC_Process:
		//controls[TANK_UP] = up;
		//controls[TANK_DOWN] = down;
		//controls[TANK_LEFT] = left;
		//controls[TANK_RIGHT] = right;
		break;
	}

	return state;
}