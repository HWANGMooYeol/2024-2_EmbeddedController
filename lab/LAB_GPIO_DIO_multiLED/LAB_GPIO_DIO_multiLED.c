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

PinName_t LED_pin1 = PA_5;
PinName_t LED_pin2 = PA_6;
PinName_t LED_pin3 = PA_7;
PinName_t LED_pin4 = PB_6;

PinName_t button_pin = PC_13;

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	int lastButtonState = HIGH;
	GPIO_write(LED_pin1 , LOW);
	GPIO_write(LED_pin2 , LOW);
	GPIO_write(LED_pin3 , LOW);
	GPIO_write(LED_pin4 , LOW);
	// Inifinite Loop ----------------------------------------------------------
	while(1){

		int buttonState = GPIO_read(BUTTON_PIN);
		
		if(buttonState == LOW && lastButtonState == HIGH && GPIO_read(LED_pin1) == LOW && GPIO_read(LED_pin2) == LOW && GPIO_read(LED_pin3) == LOW && GPIO_read(LED_pin4) == LOW)
			GPIO_toggle(LED_pin1);
		else if(buttonState == LOW && lastButtonState == HIGH && GPIO_read(LED_pin1) == HIGH){
			GPIO_toggle(LED_pin1);
			GPIO_toggle(LED_pin2);
		}
		else if (buttonState == LOW && lastButtonState == HIGH && GPIO_read(LED_pin2) == HIGH) {
			GPIO_toggle(LED_pin2);
			GPIO_toggle(LED_pin3);
		}
		else if (buttonState == LOW && lastButtonState == HIGH && GPIO_read(LED_pin3) == HIGH) {
			GPIO_toggle(LED_pin3);
			GPIO_toggle(LED_pin4);
		}
		else if (buttonState == LOW && lastButtonState == HIGH && GPIO_read(LED_pin4) == HIGH) {
			GPIO_toggle(LED_pin4);
			GPIO_toggle(LED_pin1);
		}
	lastButtonState = buttonState;
	}
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(button_pin, INPUT);  // calls RCC_GPIOC_enable()
	
	GPIO_init(LED_pin1, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_pin1, PULL_UP);
	GPIO_otype(LED_pin1, 0);
	
	GPIO_init(LED_pin2, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_pin2, PULL_UP);
	GPIO_otype(LED_pin2, 0);
	
	GPIO_init(LED_pin3, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_pin3, PULL_UP);
	GPIO_otype(LED_pin3, 0);
	
	GPIO_init(LED_pin4, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(LED_pin4, PULL_UP);
	GPIO_otype(LED_pin4, 0);
}