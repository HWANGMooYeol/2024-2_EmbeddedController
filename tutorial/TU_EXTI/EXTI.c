

//#include "ecSTM32F4v2.h"
#include "ecRCC2.h"
#include "ecGPIO2_student.h"

#define LED_PIN  PA_5
#define BUTTON_PIN PC_13

void setup(void);
void LED_toggle(void);

int main(void) {

	// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();


	// EXTI Initialiization ------------------------------------------------------	

	// SYSCFG peripheral clock enable
	RCC->APB2ENR |= 1<<14;

	// Connect External Line to the GPIO
	// Button: PC_13 -> EXTICR3(EXTI13)
	SYSCFG->EXTICR[3] &= ~(15<<4);
	SYSCFG->EXTICR[3] |= 2<<4;

	// Falling trigger enable (Button: pull-up)
	EXTI->FTSR |= 1UL << 13;

	// Unmask (Enable) EXT interrupt
	EXTI->IMR |= 1UL << 13;

	// Interrupt IRQn, Priority
	NVIC_SetPriority(EXTI15_10_IRQn, 0);  		// Set EXTI priority as 0	
	NVIC_EnableIRQ(EXTI15_10_IRQn); 			// Enable EXTI 


	while (1);
}


void EXTI15_10_IRQHandler(void) {
	if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13) {
		LED_toggle();
		EXTI->PR |= EXTI_PR_PR13; // cleared by writing '1'
	}
}


// Initialiization 
void setup(void)
{
	RCC_PLL_init();                         // System Clock = 84MHz
	GPIO_init(PA_5, OUTPUT);
	GPIO_otype(PA_5, PUSH_PULL);
	GPIO_pupd(PA_5, NO_PUPD);

	GPIO_init(PC_13, INPUT);
	GPIO_pupd(PC_13, NO_PUPD);

}

void LED_toggle(void) {
	GPIO_toggle(PA_5);
}  //toggle led2
