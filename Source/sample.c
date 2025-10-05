/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
//#include <stdint.h>
#include "pacman/pacman.h"
//#include <stdio.h>                   
#include "joystick/joystick.h"
#include "button_EXINT/button.h"


volatile unsigned int random;

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
extern int pause;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();

  LPC_SC->PCONP |=(1<<22);				//attiva il timer 2 quando viene utilizzata la board
	LPC_SC->PCONP |=(1<<23);				//attiva il timer 3 quando viene utilizzata la board
	
	LCD_Initialization();
	LCD_Clear(Black);
	
	//T0-->per controllare la direzione di pacman dal joystick + gestire funzione rand()
	init_timer(0, 0, 0, 3, 0x2DC6C0 );//50ms
	//T2-->timer continuo per variabile randomica
	init_timer(2, 0, 0, 0, 0x0000); //1sec

	
	start();
	
	joystick_init();											/* Joystick Initialization */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec*/
	enable_RIT();
	
	//T1-MR0-->countdown
  init_timer(1, 0, 0, 3, 0x017D7840); //1sec
	//T3-MR0-->generazione a tempo randomico di power pills
	init_timer(3, 0, 0, 3, 0x2DC6C0); //1.5 sec
	
	//all'inizio il gioco è in pausa
	pause=pauseDisplay(1);					
	TimerControl(1);
	

	LPC_SC->PCON |= 0x1;									/* power-down	mode*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
