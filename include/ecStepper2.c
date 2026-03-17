#include "stm32f4xx.h"
#include "ecStepper2.h"

//State number 
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7


// Stepper Motor function
uint32_t direction = 1; 
double step_delay = 1.0; 
double step_per_rev = 64.0*32.0;
	 

// Stepper Motor variable
volatile Stepper_t myStepper; 


//FULL stepping sequence  - FSM
typedef struct {
  	uint32_t next[2];
		uint8_t out;
} State_full_t;

State_full_t FSM_full[4] = {  	// 1010 , 0110 , 0101 , 1001
 	{{S3,S1},0b1100},		// ABA'B'
 	{{S0,S2},0b0110},
 	{{S1,S3},0b0011},
 	{{S2,S0},0b1001}
};

//HALF stepping sequence
typedef struct {
  uint32_t next[2];
	uint8_t out;
} State_half_t;

State_half_t FSM_half[8] = {	// 1000 , 1010 , 0010 , 0110 , 0100 , 0101, 0001, 1001
 	{{S7,S1},0b1000},	
	 {{S0,S2},0b1100},
	 {{S1,S3},0b0100},
	 {{S2,S4},0b0110},
	 {{S3,S5},0b0010},
	 {{S4,S6},0b0011},
	 {{S5,S7},0b0001},
	 {{S6,S0},0b1001}
};



void Stepper_init(PinName_t pinName1, PinName_t pinName2, PinName_t pinName3, PinName_t pinName4){
	 
	//  GPIO Digital Out Initiation
	myStepper.pin1 = pinName1;
	myStepper.pin2 = pinName2;
	myStepper.pin3 = pinName3;
	myStepper.pin4 = pinName4;
	
	GPIO_init(pinName1, OUTPUT);
	GPIO_init(pinName2, OUTPUT);
	GPIO_init(pinName3, OUTPUT);
	GPIO_init(pinName4, OUTPUT);
	
	//  GPIO Digital Out Initiation
	// No pull-up Pull-down , Push-Pull, Fast	
	// Pin1 ~ Port4
	
	GPIO_pupd(pinName1, NO_PUPD);
	GPIO_pupd(pinName2, NO_PUPD);
	GPIO_pupd(pinName3, NO_PUPD);
	GPIO_pupd(pinName4, NO_PUPD);
	// YOUR CODE 
	GPIO_otype(pinName1,PUSH_PULL);
	GPIO_otype(pinName2,PUSH_PULL);
	GPIO_otype(pinName3,PUSH_PULL);
	GPIO_otype(pinName4,PUSH_PULL);
	// YOUR CODE 
	GPIO_ospeed(pinName1, FAST_SPEED);
	GPIO_ospeed(pinName2, FAST_SPEED);
	GPIO_ospeed(pinName3, FAST_SPEED);
	GPIO_ospeed(pinName4, FAST_SPEED);
}


void Stepper_pinOut (uint32_t state, uint32_t mode){	
   	if (mode == FULL){         // FULL mode
		GPIO_write(myStepper.pin1, (FSM_full[state].out & 0b1000) >> 3);
  		// Repeat for pin2~port4 
		GPIO_write(myStepper.pin2, (FSM_full[state].out & 0b0100) >> 2);
		GPIO_write(myStepper.pin3, (FSM_full[state].out & 0b0010) >> 1);
		GPIO_write(myStepper.pin4, (FSM_full[state].out & 0b0001) >> 0);
	}	 
 	else if (mode == HALF){    // HALF mode
		GPIO_write(myStepper.pin1, (FSM_half[state].out & 0b1000) >> 3);
		GPIO_write(myStepper.pin2, (FSM_half[state].out & 0b0100) >> 2);
		GPIO_write(myStepper.pin3, (FSM_half[state].out & 0b0010) >> 1);
		GPIO_write(myStepper.pin4, (FSM_half[state].out & 0b0001) >> 0);
	}
}


void Stepper_setSpeed (double whatSpeed){      // rpm [rev/min]
		step_delay = 	60000.0/(whatSpeed*step_per_rev);   //YOUR CODE   // Convert rpm to  [msec/step] delay
}


void Stepper_step(uint32_t steps, uint32_t direction, uint32_t mode){
	 uint32_t state = 0;
	 myStepper._step_num = steps;

	 for(; myStepper._step_num > 0; myStepper._step_num--){ // run for step size
	   if (mode == FULL) {												
			delay_ms(step_delay);
			state = FSM_full[state].next[direction];// YOUR CODE       // state = next state
		 }
		else if (mode == HALF) {
			delay_ms(step_delay/2);
			state = FSM_half[state].next[direction];// YOUR CODE       // state = next state	
		}			
		Stepper_pinOut(state, mode);
   	}
}


void Stepper_stop (void){ 
    	myStepper._step_num = 0;    
	// All pins(A,AN,B,BN) set as DigitalOut '0'
	GPIO_write(myStepper.pin1, 0);
	GPIO_write(myStepper.pin2, 0);
	GPIO_write(myStepper.pin3, 0);
	GPIO_write(myStepper.pin4, 0);
}

