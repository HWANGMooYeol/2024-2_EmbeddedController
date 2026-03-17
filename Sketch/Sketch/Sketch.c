#include "ecSTM32F4v2.h"
#include "math.h"

#define DIR_PIN PC_2
#define PWM_PIN PA_0
#define BUTTON_PIN PC_13

uint8_t pause_flag = 1;

uint32_t motorDIR=0;
float motorPWM=0.5f;

void setup(void);

int main(void) {
	// Initialiization --------------------------------------------------------
	setup();
	printf("Hello Nucleo\r\n");
	
	// Inifinite Loop ----------------------------------------------------------
	while (1){
		float duty = fabs(motorDIR - motorPWM); // duty with consideration of DIR=1 or 0
		PWM_duty(PWM_PIN, duty);
		delay_ms(500);
	}
}


// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	SysTick_init();
	//UART2 Configuration
	UART2_init();
	
	// External Interrupt Button input: Falling, Pull-Up
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	EXTI_init(BUTTON_PIN, FALL, 0);

	// Direction Output Configuration
	GPIO_init(DIR_PIN, OUTPUT);
	GPIO_write(DIR_PIN, 0);

	// PWM Configuration
	PWM_init(PWM_PIN);
	PWM_period_ms(PWM_PIN, 1);		// PWM period: 1msec
}

void EXTI15_10_IRQHandler(void)
{
	if(is_pending_EXTI(BUTTON_PIN)){
		//When Button is pressed, it should PAUSE or CONTINUE motor run (flag)
		pause_flag ^= 1;
		motorPWM *= (float)pause_flag;

		// Clear EXTI Pending
		clear_pending_EXTI(BUTTON_PIN);
	}
}