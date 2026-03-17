
#include "stm32f4xx.h"
#include "ecGPIO2_student.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"


//#define LED_PIN	PA_5
#define BUTTON_PIN PC_13

//void LED_toggle(void);

// Initialiization 
void setup(void);
unsigned int cnt = 0;

int main(void) {
	setup();
	while (1) {}
}

//EXTI for Pin 13
void EXTI15_10_IRQHandler(void) {
	if (is_pending_EXTI(BUTTON_PIN)) {
		
		sevensegment_display(cnt % 10);
		cnt++; 
		if (cnt > 9) cnt = 0;
		
		clear_pending_EXTI(BUTTON_PIN); 
	}
}

void setup(void) {
	RCC_PLL_init();
	SysTick_init();
	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	
	sevensegment_display_init(PA_7, PB_6, PC_7, PA_9);  // Decoder input A,B,C,D
	GPIO_otype(PA_7, PUSH_PULL);
	GPIO_otype(PB_6, PUSH_PULL);
	GPIO_otype(PC_7, PUSH_PULL);
	GPIO_otype(PA_9, PUSH_PULL);
	
	GPIO_pupd(PA_7, NO_PUPD);
	GPIO_pupd(PB_6, NO_PUPD);
	GPIO_pupd(PC_7, NO_PUPD);
	GPIO_pupd(PA_9, NO_PUPD);
	
	GPIO_ospeed(PA_7, MEDIUM_SPEED);
	GPIO_ospeed(PB_6, MEDIUM_SPEED);
	GPIO_ospeed(PC_7, MEDIUM_SPEED);
	GPIO_ospeed(PA_9, MEDIUM_SPEED);
	// Priority Highest(0) External Interrupt 
	EXTI_init(BUTTON_PIN, FALL, 0);
}

/* void LED_toggle(void) {
	GPIO_toggle(PA_5);
}  //toggle led2 */