

#include "ecALL.h"

#define time 				500
#define PWM_PIN			PA_0
#define DIR_PIN 		2

void setup(void);


int num = 0;
int duration = 0;
int dly = 0; 
int btn = 0;
int cnt = 1;
float duty = 1;
int DIR = 0;
int blktime = 0; 
int Dtime = 0;

float low = 0;
float high = 0;


int stateWD[3][4] =		// state variable with decoder
{					 						//ALL LED OFF, initial state
	{0,0,0,0},
	{0,0,0,1},
	{0,0,1,0}
};

int main(void){
	
	setup();
	
	while(1){
		
		//GPIO_write(GPIOA, LED_PIN, HIGH);
		
		GPIO_write(GPIOC, DIR_PIN, DIR);
		PWM_duty(PWM_PIN, duty);
		
		if(btn == 0){
			GPIO_write(GPIOA, LED_PIN, 1);
		}
		if (btn == 1){
			GPIO_write(GPIOA, 5, !GPIO_read(GPIOA, 5));
			delay_ms(500);
			SysTick_reset();
		}
		if (btn == 2){
			GPIO_write(GPIOA, 5, !GPIO_read(GPIOA, 5));
			delay_ms(1000);
			SysTick_reset();
			}
		}
	}



void setup(void){
	RCC_PLL_init();
	
	SysTick_init();
	
	PWM_init(PWM_PIN);	
	PWM_period(PWM_PIN, 1);
	
	//TIM_UI_init(TIM2, 1);
	TIM_UI_init(TIM3, 1);

	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
	
	GPIO_init(GPIOA, 5, OUTPUT);
	
	//button pin setup
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);
	GPIO_otype(GPIOC, BUTTON_PIN, OT_PP);
	GPIO_pupd(GPIOC, BUTTON_PIN, PUPDR_PD);
	
	//sevensegment pin setup
	sevensegment_decoder_init(OUTPUT, OT_PP, SP_FA, PUPDR_N);
	
	
	//Direction
	GPIO_init(GPIOC, DIR_PIN, OUTPUT);
	GPIO_otype(GPIOC, DIR_PIN, OT_PP);	
	
}

/*
void TIM3_IRQHandler(void){
	if(is_UIF(TIM3)){
	Dtime++;
		
		if(Dtime > time){
			
			if(btn == 0){
				duty = DIR;
				sevensegment(stateWD, 0);
				
				
			}
			if(btn == 1){
				blktime = 1000;
				btn = 2 ;
				duty = low;
				sevensegment(stateWD, 2);
				
			}
			if(btn ==2){
				blktime = 500;
				duty = high;
				sevensegment(stateWD, 1);
			}
			Dtime = 0;
		 clear_UIF(TIM3);
		}
	}
}*/

void EXTI15_10_IRQHandler(void) 
{
		duration++;
	
		if (is_pending_EXTI(BUTTON_PIN) && duration > 10000) {
		duration = 0;
			cnt ++;
			if(cnt == 1){
				btn  = 1;
				//blktime = 1000;
			}
			if(cnt == 2){
				btn = 2;
				//blktime = 500;
			}
			if(cnt == 3){
				btn = 0;
			}
			
			if(cnt > 3) cnt = 0;
				
		clear_pending_EXTI(BUTTON_PIN);
		}
}


