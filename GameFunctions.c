#include "GameFunctions.h"

// game started var
bool game_started = false;

// seed for the rand()
int seed = 0;

// start the game
void GameStart(void){
	
	game_started = true;
	// clear all variables
	EnemyInit(seed);

	// start timers
	PIT_StartTimers();
	// declare game started 
	
}

void GameStop(void){
	
	game_started = false;
	// get the score
	// stop timers
	PIT_StopTimers();
	// reset screen
	
	// 
	
}

// pre-game/post-game loop 
void SysTick_Handler(void)  {   
		
	// check up on the system and perform moundane tasks 
	
	// up our seed to make it as random as possible
	seed++;
	
}




