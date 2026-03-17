/**
******************************************************************************
* @author	HWANG MooYeol
* @Mod		2024-09-10
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle LED LD2 by Button B1 pressing
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include "ecGPIO2_student.h"

PinName_t LED_pin = PA_5;
PinName_t button_pin = PC_13;

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	int lastButtonState = HIGH;
	GPIO_write(LED_pin, LOW);
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		
		int buttonState = GPIO_read(BUTTON_PIN);
		
		if (buttonState == LOW && lastButtonState == HIGH) {		
			GPIO_toggle(LED_pin);
		}
	lastButtonState = buttonState;
	}
}

// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(button_pin, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_init(LED_pin, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_pin, PULL_UP);
	GPIO_pupd(button_pin, PULL_UP);
	GPIO_otype(LED_pin, 0);
	GPIO_ospeed(LED_pin, 1);
}
