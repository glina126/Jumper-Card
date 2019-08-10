#include "GameFunctions.h"

// game started var
bool game_started = false;
bool game_show_score = false;
uint16_t game_score_pos = 0;
bool game_init_animate_score = false;

// seed for the rand()
int seed = 0;

// program state
uint16_t game_program_state = 0; 

// game score
uint32_t game_score = 0;

// ++ game score 
void GameUpScore(void){
	
	game_score ++; 
	
}

// display the score on the enemy screen
void GameAnimateScore(void){
	
	// normalize the game score -- we have 15 available leds			
	game_score /= 50;
	
 	if(game_score > 14)
		game_score = 14;
	
	// light up LEDS
	for(int i = 0; i < game_score; i++)
		GPIOA->PCOR = (1u << leds_score[i]);
	
}


// start the game
void GameStart(void){
	
	// declare game started 
	game_started = true;
	
	// clear all variables except the seed
	EnemyInit(seed);
	game_score = 0;
	
	// start timers
	PIT_StartTimers();
		
}

void GameStop(void){
	
	// declare game stopped
	game_started = false;
	
 	// stop timers
	PIT_StopTimers();
	
	// animate score onto screen
	GameAnimateScore();
	
}

// pre-game/post-game loop 
void SysTick_Handler(void)  {   
		
	// check up on the system and perform moundane tasks 
	
	// up our seed to make it as random as possible
	seed++;

		// game
	// GameStart();
	
	// determine the state of the program and follow through
	switch(game_program_state){
		
		case 0:
			// intro 
			GameIntroRandomSequence();
			break;
		case 1:
			// gameplay
			break;
		case 2:
			// flash
			game_show_score = true;
			break;

		default:
			break;
		
	}
	
	// up the game score if the game is started
	if(game_started == true)
		game_score ++; 

	
}

// KBI interrupt on falling edge. button press 
// PIT 0 interrupt - jumper animation
void KBI0_IRQHandler(void){ 
    
    // if game is not started, start the game and exit
    if(!game_started){
			// up the game_program_state 
			game_program_state++;
			

			// check to make sure we are not overflowing
			if(game_program_state > 2)
				game_program_state = 1;
			
			// start the game if we are in state of 1
			if(game_program_state == 1){
				GameStart();
				// kick start the jumper for the effect
				JumperSetEnergy(4);
			}
				
			// debounce delay
			for(int i = 0; i < 1000000; i++)
				__nop();
			
			
			// clear the KBI interrupt flag
			KBI0->SC |= (1u << 2);
			
			// clear ARM IRQ
			NVIC_ClearPendingIRQ(KBI0_IRQn);
			
			// end the function here
			return;
    }
    
    // run the jumper! 
    JumperSetEnergy(4);
    
    // clear the KBI interrupt flag
    KBI0->SC |= (1u << 2);
    
    // clear ARM IRQ
    NVIC_ClearPendingIRQ(KBI0_IRQn);
    
    
}





