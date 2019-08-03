#include <stdint.h>
#include <stdlib.h>
#include "MKE04Z4.h" // all chip related crap
#include "typedef.h" // custom bool and etc. 
#include "PIT.h" // PIT driver
#include "LEDS.h" // leds mapping
#include "KBIDriver.h" // KBI driver
#include "GameFunctions.h"
															
int main (void){
	
	
		// --- SYSTICK ---
	SysTick_Config(SystemCoreClock /6);  // 
	
	
	// set up the GPIO 
	for(int i = 0; i < 18; i++){
		// set all leds as output	
		GPIOA->PDDR |= (1u << leds[i]);
		// turn off all leds
		GPIOA->PSOR |= (1u << leds[i]);
		
	}
	
	// disable the NMI 
	SIM->SOPT &= ~(1u << 1);
	
	// initialize the KBI module
	KBIInit();
	
	// turn on the jumper
	GPIOA->PCOR = (1u << jumper_screen_definition[0]);
	
	// initialize PIT 
	PIT_Init();
	
	// start timers
	// PIT_StartTimers();
	// GameStart();
	
	
	// never quit 
	while(1)
		__nop();
	
	
}







