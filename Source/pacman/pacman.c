//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include <stdint.h>
#include <GLCD.h>
#include <stdio.h>

		uint16_t color;
		uint16_t row;
		uint16_t col;
		
		volatile int START_X, START_Y;
		volatile int PacManX, PacManY;
	  extern char direction;
		int score;
		int powerPills=6;
		int powerPillsGenerated=0;
		int pillsGenerated;
		volatile int sec=60;
		volatile int lives;
		int lost_lives;
		extern unsigned int random;
	
		
	//labirinto di dimensione 240*320 
	//inizialmente non contiene le pills in quanto esse verranno generate in maniera casuale ad ogni partita
int LabyrinthMatrix[MATRIX_ROWS][MATRIX_COLS] = {
	/* 
		-1= pacman
		 0=path
		 1=wall
		 2=ghosts spawner
			3=no access to pacman 
		 4=normal pills 	
		 5=power pills 
		 6=left tp
		 7=right tp
	*/	
	  
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1},
    {1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,1,3,3,1,1,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,0,1,2,2,2,2,1,0,1,1,1,0,1,0,1,1,1,1,1},
    {6,0,0,0,0,0,0,0,1,0,0,0,1,2,2,2,2,1,0,0,0,1,0,0,0,0,0,0,0,7},
    {1,1,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,0,1,0,1,0,0,0,0,-1,0,0,0,1,0,1,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0,1,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//pacman
volatile int pacman_matrix[8][8]={
 {0,0,0,1,1,1,0,0},
 {0,1,1,1,1,1,1,1},
 {0,1,1,1,1,1,1,0},
 {1,1,1,1,1,1,0,0},
 {1,1,1,1,1,0,0,0},
 {1,1,1,1,1,1,0,0},
 {0,1,1,1,1,1,1,0},
 {0,0,0,1,1,1,1,1},
};

		
//contiene tutte le funzioni iniziali per il gioco 
void start(){
	//genera una posizione casuale per le pills nomrali, assegnando alla matrice al posto del valore 0-->4
  GenerateNormalPills();
	//disegna il labirinto
	DrawLabyrinth();
	//mostra a video il punteggio
	DrawScore();
	//mostra a video il timer 
	GameOver();
	//mostra a video le vite rimanenti
	RemainingLives(lives);

}


////////////////////////////////////////////////////////////////////-GRAFICA-////////////////////////////////////////////////////////////////////////////////////////////////
	
//Funzione per disegnare i cerchi 
void DrawCircle(uint16_t centerX, uint16_t centerY, uint16_t radius, uint16_t color) {
    int x = 0;
    int y = radius;
    int decision = 1 - radius; // Decision parameter

    while (x <= y) {
        // Disegna gli 8 ottanti del cerchio
        LCD_SetPoint(centerX + x, centerY + y, color);
        LCD_SetPoint(centerX + y, centerY + x, color);
        LCD_SetPoint(centerX - x, centerY + y, color);
        LCD_SetPoint(centerX - y, centerY + x, color);
        LCD_SetPoint(centerX + x, centerY - y, color);
        LCD_SetPoint(centerX + y, centerY - x, color);
        LCD_SetPoint(centerX - x, centerY - y, color);
        LCD_SetPoint(centerX - y, centerY - x, color);

        x++;
        if (decision < 0) {
            decision += 2 * x + 1;
        } else {
            y--;
            decision += 2 * (x - y) + 1;
        }
    }
}

//Funzione per disegnare blocco-muro del labirinto
void DrawBlock(int x, int y, uint16_t color){
// Draw the cell

						int i, j;
            for (i = 0; i < CELL_SIZE; i++) {
                for (j = 0; j < CELL_SIZE; j++) {
                    LCD_SetPoint(y * CELL_SIZE + j, x * CELL_SIZE + i, color);
                }
}
}

//Funzione per disegnare le pills
void DrawPills(int x, int y, uint16_t color, int radius){
		uint16_t centerX = y * CELL_SIZE + CELL_SIZE / 2; // Centro X
		uint16_t centerY = x * CELL_SIZE + CELL_SIZE / 2; // Centro Y
		uint16_t r = radius;                   						// Raggio del pallino
		uint16_t c=color;
	
		DrawCircle(centerX, centerY, r, c);	
}
//disegno la matrice
void DrawLabyrinth() {

    for (row = 0; row < MATRIX_ROWS; row++) {
        for (col = 0; col < MATRIX_COLS; col++) {
            switch (LabyrinthMatrix[row][col]) {
								case -1://pacman
										DrawPacman( row, col, Yellow);
										PacManX=row;
										PacManY=col;
										break;
                case 1: // Wall
                    color = Blue;
										DrawBlock(row, col, color);
                    break;
								case 4: //pills
											color=Yellow;
											DrawPills(row, col, color, CELL_SIZE / 5);
											break;	

                default:
                    //color = Green;
                    break;
            }

            
            }
        }
    }

//disegna pacman utilizzando la matrice pacman_matrix[r][c] definita tra le variabili
void DrawPacman(int x,int y,int color) {
 int r,c;
    for (r = 0; r < 8; r++) {
        for (c = 0; c < 8; c++) {
            if (pacman_matrix[r][c] == 1)
                LCD_SetPoint(y*CELL_SIZE+c,x*CELL_SIZE+r,color);
        }
    }
}

//mostra a video la scritta dello Score
void DrawScore(){
	GUI_Text(0, 280, (uint8_t *) " Score : ", Red, White);
}

//funzione che aggiorna lo score - viene chiamata ogni volta che pacman mangia una pills	
void updateScore(){
	char str[12];
	int additional_lives;
	
	//se tutte le pills sono state mangiate allora lo score==2700 e spunterà la scritta di vittoria
	if(score==2700){
		GUI_Text(80, 120, (uint8_t *) " !!VICTORY!! ", Red, White);
		TimerControl(1);
	}
	
	//controllo sullo score per aggiornare le vite - ogni volta che pacman acquisisce 1000 punti guadagna una vita 
	additional_lives=updateLives(score);			//variabile per segnare le vite guadagnate attraverso i punti 
	lives=additional_lives+1-lost_lives;			//le vite totali=quelle guadagnate tramite punti + la prima vita do default - vite perse
	RemainingLives(lives);										//aggiorno le vite sul display
	sprintf(str,"%d", score);									//stampo lo score attuale
	GUI_Text(80, 280, (uint8_t *)  str , Red, White);
}

//mostra a video la scritta game over in
void GameOver(){
	GUI_Text(0, 300, (uint8_t *) " GAME OVER in : " , Red, White);
}

//aggiorna la variabile sec per il timer e la mostra a schermo
void UpdateTime(){
	if(sec>0){
		sec--;
		char str[12];

		if(sec<10){
			sprintf(str, "0%d", sec);
		} 
		else {
			sprintf(str, "%d", sec);	
		}
		
		GUI_Text(140, 300, (uint8_t *)  str , Red, White);
	}
	else {
		//se le vite sono !=1 allora tolgo 1 vita e continuo a giocare resettando il timer
		if(lives>1)
		{ lives--;
			lost_lives++;
			deleteRemainingLives(lives);
			sec=60;
		} 
		else //se ho solo 1 vita è gameOver
		GUI_Text(80, 120, (uint8_t *) " !!GAME OVER!! ", Red, White);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////-GESTIONE PILLS-////////////////////////////////////////////////////////////////////////////////////////////////


// Funzione per generare le pills normali in posizioni casuali
//la casualità è stata gestita tramite il timer0 che preleva il TC del timer2(continuo) all'interno del timer Hanlder:
//		random=LPC_TIM2->TC;
//		srand(random);
void GenerateNormalPills() {

		int totalPills=240;
    pillsGenerated = 0;
		color=Yellow;
		uint16_t i, j;
		uint16_t row, col;

    while (pillsGenerated < totalPills) {
        // Genera coordinate casuali
        row = rand()% MATRIX_ROWS;
        col = rand() % MATRIX_COLS;
				
        // Se la posizione è 0(percorso), assegna a quella posizione 4(pill normale)
        if (LabyrinthMatrix[row][col] == 0 &&
						//controllo che la posizione non superi quella dell matrice
					  col * CELL_SIZE + CELL_SIZE < Max_X &&
            row * CELL_SIZE + CELL_SIZE < Max_Y) {
							
            LabyrinthMatrix[row][col] = 4; // cambia il valore della posizione in 4						
						pillsGenerated++;	
						}}}

// Funzione per generare le power pills in posizione e intervallo di tempo casuale
//chiamo la funzione all'interno del Timer Hanlder, utilizzando il Timer3
void GeneratePowerPills() {			
		
		uint16_t i, j;
	  uint16_t row, col;
	
		if(powerPillsGenerated < powerPills){
				// Genera coordinate casuali
        row = rand() % MATRIX_ROWS;
        col = rand() % MATRIX_COLS;
			 
				// Se la posizione è 0, piazza una power pill
        if (LabyrinthMatrix[row][col] == 0 &&
						//controllo che la posizione non superi quella dell matrice
					  col * CELL_SIZE + CELL_SIZE < Max_X &&
            row * CELL_SIZE + CELL_SIZE < Max_Y) {
            LabyrinthMatrix[row][col] = 5; // cambia il valore della posizione in 5
					
						DrawPills(row, col, Magenta, CELL_SIZE / 3);
						powerPillsGenerated++;	
							
	
						}}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////-GESTIONE MOVIMENTO PACMAN-//////////////////////////////////////////////////////////////////////////////////

//Funzione per rilevare la direzione di pacman e chiamo una funzione per muoverlo
	void CheckPosition(){
	int nextPosition;
	
	//acquisisco le coordinate di Pacman
	int nextX= PacManX;
  int nextY= PacManY;

        // Calcolo la prossima posizione in base alla direzione(var globale definita e modificata all'interno del RIT Handler)
        switch (direction) {
            case 'u':  
							nextPosition=LabyrinthMatrix[nextX-1][nextY]; 
						  MovePacman(nextX-1, nextY, nextPosition);
						break;
            case 'd':  
							nextPosition=LabyrinthMatrix[nextX+1][nextY]; 
						  MovePacman(nextX+1, nextY, nextPosition);
						break;
            case 'l':  
							nextPosition=LabyrinthMatrix[nextX][nextY-1]; 
						  MovePacman(nextX, nextY-1, nextPosition);
						break;
            case 'r':  
							nextPosition=LabyrinthMatrix[nextX][nextY+1]; 
						  MovePacman(nextX, nextY+1, nextPosition);
						break;
            default: break;
        }
	}
	
//Funzione per muovere pacman che utilizza l'input del joystick rilevato nel RIT Hanlder
	void MovePacman(int x, int y, int nextPosition) {
		
		//controllo se la posizione successviva è valida
		//pacman si può muovere in quella direzione a meno che questa non sia un muro o l'accesso al ghost spawner
		if (nextPosition!=1 && nextPosition!=3 && sec!=0){
			LabyrinthMatrix[PacManX][PacManY]=0;
			DrawBlock(PacManX, PacManY, Black);
			
		//controllo se la posizione successiva è una pill e aggiorno lo score
				//check if nextPosition=pill
				if(nextPosition==4){
					score+=10;
					updateScore();
				}
				if(nextPosition==5){
					score+=50;
					updateScore();
				}
		//controllo se sta attraversando un right/left teleport
				if(nextPosition==6){
					x=15;
					y=29;
				}
				if(nextPosition==7){
					x=15;
					y=0;
				}
				
			DrawPacman(x, y, Yellow);
			PacManX=x;
			PacManY=y;
		}}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
///////////////////////////////////////////////////////////-GESTIONE VITE-////////////////////////////////////////////////////////////////////////////////////////////

//Mostra a video le vite rimanenti di pacman
void RemainingLives(int lives){
	int i;
	switch(lives){
//lives-->variabile globale
		
		case 2:
			i=1;
		break;
		
		case 3:
			i=2;
		break;
	}
	
	 int r,c;
			for (r = 0; r < 8; r++) {
        for (c = 0; c < 8; c++) {
            if (pacman_matrix[r][c] == 1)
                LCD_SetPoint(0+i*10+c, 260+r, Yellow);
        }
    }
  }

//eimina le vite di pacman mostrate sullo schermo 
	void deleteRemainingLives(int lives){
	int i;
	switch(lives){
		case 1:
			i=1;
		break;
		
		case 2:
			i=2;
		break;
	}
	
	 int r,c;
			for (r = 0; r < 8; r++) {
        for (c = 0; c < 8; c++) {
            
                LCD_SetPoint(0+i*10+c, 260+r, Black);
        
    }
	}
}

	
//funzione per aumentare le vite se lo score raggiunge un multiplo di 1000
int updateLives (int x){
//ritorna le vite addizionali
	int additional_lives;
		if(x%1000>=0){
			//per evitare che lives venga incrementato erroneamente ogni volta che lo score è in un intervallo 1000<score<2000
			//utilizzo una nuova variabile additional_lives che prenderà un valore in base all'intervallo  
			 additional_lives=x/1000;		
					//se x=1200, additional_lives=1
					//se x=1600, additional_lives=1
		}
	return  additional_lives;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////-GESTIONE PAUSA-//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//funzione per stoppare e riavvire il timer attraversoil TCR usata all'interno del RIT handler
void TimerControl(uint8_t timer_num) {
    if (timer_num == 1) {
        disable_timer(0); // Fermo i timer
				disable_timer(1);
				disable_timer(2);
				disable_timer(3);
    } else {
				enable_timer(0); // Riavvio i Timer1
				enable_timer(1);
				enable_timer(2);
				enable_timer(3);
		}
			
}
	
//display scritta di pausa
int pauseDisplay(int x){
		
	GUI_Text(80, 120, (uint8_t *) " !!PAUSE!! ", Red, White);

		return x;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



