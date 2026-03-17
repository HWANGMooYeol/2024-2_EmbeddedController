/**
******************************************************************************
* @author  HWANG MooYeol
* @Mod		 2024-08-23 by YKKIM  	
* @brief   Embedded Controller:  Tutorial Digital In/Out 7-segment Display
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include "ecGPIO2_student.h"

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	unsigned int cnt = 0;
	int lastButtonState = HIGH;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		
		int buttonState = GPIO_read(BUTTON_PIN);
		sevensegment_decoder(cnt % 10);
		if(buttonState == LOW && lastButtonState == HIGH) {
			cnt++; 
			if (cnt > 9) cnt = 0;
			//delay_ms(2000);
		}
		lastButtonState = buttonState;
	}
}

void setup(void)
	{
	RCC_HSI_init();
	GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_UP);
    
	sevensegment_decoder_init();
    uint16_t pins[] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};
		for (int i = 0; i < 8; i++) {
    	GPIO_otype(pins[i], PUSH_PULL);
    	GPIO_pupd(pins[i], NO_PUPD);
      GPIO_ospeed(pins[i], MEDIUM_SPEED);
		}
}