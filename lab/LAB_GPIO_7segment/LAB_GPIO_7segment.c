#include "stm32f4xx.h"
#include "ecGPIO2_student.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"

#define BUTTON_PIN PC_13

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	unsigned int cnt = 0;
	int lastButtonState = HIGH;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		
		int buttonState = GPIO_read(BUTTON_PIN);
		sevensegment_display(cnt % 10);
		if(buttonState == LOW && lastButtonState == HIGH) {
			cnt++; 
			if (cnt > 9) cnt = 0;
			//delay_ms(2000);
		}
		lastButtonState = buttonState;
	}
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
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
}