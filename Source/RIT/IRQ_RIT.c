/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "GLCD.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
volatile int down_0 = 0;
volatile int down_1 = 0;
volatile int down_2 = 0;
volatile char direction;		//variabile globale per definire la direzione di pacman 
volatile int pause;

extern volatile int START_X, START_Y;      // Posizione iniziale X
extern volatile int PacManX, PacManY;  
extern volatile int lives;
int moveCounter = 0;        							// Contatore per gestire il movimento continuo


///* Static as its value persists between calls to the function. It is not reinitialized each time the function is executed.*/
//static uint8_t position=0;


void RIT_IRQHandler (void)
{	
	
	//assegno un valore tra quelli di seguito alla variabile globale direction, 
	//per poi gestire il movimento all'interno di un'altra funzione (MovePacman())
	static int up = 0, down = 0, left = 0, right = 0;

		//aggiorno la direzione in base all'input del joystick rilevato
    // Rilevamento input del joystick
    if ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0) { // Joystick UP premuto
        up++;
        if (up == 1) direction = 'u'; // Registra la direzione solo al primo rilevamento
    } else up = 0;

    if ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0) { // Joystick DOWN premuto
        down++;
        if (down == 1) direction = 'd';
    } else down = 0;

    if ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0) { // Joystick LEFT premuto
        left++;
        if (left == 1) direction = 'l';
    } else left = 0;

    if ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0) { // Joystick RIGHT premuto
        right++;
        if (right == 1) direction = 'r';
    } else right = 0;
		


    // Azzera il flag dell'interrupt RIT
    LPC_RIT->RICTRL |= 0x1; 

			
/*************************INT0***************************/
//quando viene premuto il pulsante INT0, il gioco va in pausa o viene avviato a seconda del valore di pause
	if(down_0 !=0){
	down_0++;
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
		switch(down_0){
			case 2:
				if (pause==0){
					pause=pauseDisplay(1);
					TimerControl(1);
				} else {
				 	pause=pauseDisplay(0);
					LCD_Clear(Black);
					DrawLabyrinth();
					RemainingLives(lives);
					DrawScore();
					GameOver();
					TimerControl(0);
				}
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_0=0;			
		NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
} // end INT0

/*************************KEY1***************************/
if(down_1 !=0){
	down_1++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		switch(down_1){
			case 2:
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_1=0;			
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
} // end KEY1

/*************************KEY2***************************/
if(down_2 !=0){
	down_2++;
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		switch(down_2){
			case 2:
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down_2=0;		
		NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
} // end KEY2
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
