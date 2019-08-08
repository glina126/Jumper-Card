#include "GameFunctions.h"

// game started var
bool game_started = false;

// seed for the rand()
int seed = 0;

// game score
uint32_t game_score = 0;

// ++ game score 
void GameUpScore(void){
	
	game_score ++; 
	
}
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

// KBI interrupt on falling edge. button press 
// PIT 0 interrupt - jumper animation
void KBI0_IRQHandler(void){ 
    
    // if game is not started, start the game and exit
    if(!game_started){
        GameStart();
        return;
    }
    
    // run the jumper! 
    JumperSetEnergy(4);
    
    // clear the KBI interrupt flag
    KBI0->SC |= (1u << 2);
    
    // clear ARM IRQ
    NVIC_ClearPendingIRQ(KBI0_IRQn);
    
    
}





