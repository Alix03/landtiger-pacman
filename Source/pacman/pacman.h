#ifndef pacman_h
#define pacman_h
#include <stdint.h>
#define Max_X 240 // Maximum screen width
#define Max_Y 320 // Maximum screen height
#define CELL_SIZE 8 // Size of each cell in pixels
#define MATRIX_ROWS (Max_X / CELL_SIZE)
#define MATRIX_COLS (Max_Y / CELL_SIZE)


void start();

/////////////////////////////////////-GRAFICA-////////////////////////////////////////////
void DrawCircle(uint16_t centerX, uint16_t centerY, uint16_t radius, uint16_t color);
void DrawBlock(int x, int y, uint16_t color);
void DrawPills(int x, int y, uint16_t color, int radius);
void DrawLabyrinth();
void DrawPacman(int x,int y,int color);
void DrawScore();
void updateScore();
void GameOver();
void UpdateTime();

//////////////////////////////////-GESTIONE PILLS-////////////////////////////////////////////
void GenerateNormalPills();
void GeneratePowerPills();

/////////////////////////////-GESTIONE MOVIMENTO PACMAN-////////////////////////////////////////////
void CheckPosition();
void MovePacman(int x, int y, int nextPosition);

//////////////////////////////////-GESTIONE VITE-////////////////////////////////////////////
void RemainingLives(int lives);
void deleteRemainingLives(int lives);
int updateLives (int x);

//////////////////////////////////-GESTIONE PAUSA-////////////////////////////////////////////
void TimerControl(uint8_t timer_num);
int pauseDisplay(int x);


#endif