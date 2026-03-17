#include "stm32f411xe.h"
#include "ecGPIO2_student.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecEXTI2.h"

#define PWM_PIN PA_0        
#define DIR_PIN PA_11        
#define BUTTON_PIN PC_13    


void setup(void);

int dir  = 1;
int duty_cycle = 25;
int count = 0;

int main(void){
	setup();
	
	while(1){}

}


void TIM3_IRQHandler(void){
	
	
	if(dir){
		
		count++;
		if(count==4){ 							// 500ms * 4 = 2sec

				if(duty_cycle==1){         // LOW to HIGH speed
					PWM_duty(PWM_PIN, 0.75);
					duty_cycle = 0;           // for restart init
					
				}
				else{                         //HIGH to LOW speed
					PWM_duty(PWM_PIN,0.25);
					duty_cycle = 1;
				}
				count = 0;                   //reset count value
		}
	}
	
	clear_UIF(TIM3);

}


void EXTI15_10_IRQHandler(void){
	
	if(is_pending_EXTI(13)){
		dir = !dir;                   //toggle state
		
		if(dir){
			PWM_duty(PWM_PIN, (duty_cycle) ? 0.25 : 0.75);   // off->on state remember the last condition
			//PWM_duty(PWM_PIN, 0.25);                      // restart from LOW speed
		}
		
		else{
			PWM_duty(PWM_PIN, 0);          // on->off state
		}
		
		clear_pending_EXTI(13);
	
	}

}

// Initialiization
void setup(void){
	
	RCC_PLL_init();
	
	//PWM
	GPIO_init(PWM_PIN , AF);
	GPIO_otype(PWM_PIN, PUSH_PULL);
	GPIO_pupd(PWM_PIN, PULL_UP);
	
	// DIR SETUP
	GPIO_init(DIR_PIN, OUTPUT);
	GPIO_otype(DIR_PIN, PUSH_PULL);
	GPIO_pupd(DIR_PIN, NO_PUPD);
	GPIO_write(DIR_PIN, HIGH);              //dir=LOW , PWM=HIGH choosing moter direction 
	
	 //BUTTON
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	
	//PWM
	PWM_init(PWM_PIN);
	PWM_period(PWM_PIN,1);
	PWM_duty(PWM_PIN, 0.25);
	
	//inturrupt
	TIM_UI_init(TIM3, 500);
	EXTI_init(BUTTON_PIN,FALL,1);
}