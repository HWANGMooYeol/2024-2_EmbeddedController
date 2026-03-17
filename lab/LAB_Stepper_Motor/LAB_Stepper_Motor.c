#include "stm32f411xe.h"


#include "ecGPIO2_student.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecStepper2.h"

#define exti_2 PC_1

void setup(void);

	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	Stepper_step(2048, 0,FULL);  // (Step : Full: 2048 ,Half :4096 = 1 lap, Direction : 0 or 1, Mode : FULL or HALF)
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){}
		
		
}

// Initialiization 
void setup(void){
	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
	//EXTI_init(BUTTON_PIN, FALL,2);           // External Interrupt Setting
	GPIO_init(BUTTON_PIN, INPUT);           // GPIOC pin13 initialization
	
	EXTI_init(exti_2, FALL,1);           // External Interrupt Setting
	GPIO_init(exti_2, INPUT); 

	Stepper_init(PB_10,PB_4,PB_5,PB_3); // Stepper GPIO pin initialization
	Stepper_setSpeed(9);                          	//  set stepper motor speed   rpm
}

void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}

void EXTI1_IRQHandler(void) {  
	if (is_pending_EXTI(exti_2)) {
		
		Stepper_stop();
		delay_ms(1000);
		
		clear_pending_EXTI(exti_2); // cleared by writing '1'
	}
}
