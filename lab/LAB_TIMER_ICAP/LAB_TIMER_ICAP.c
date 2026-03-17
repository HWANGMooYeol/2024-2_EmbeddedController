/**
******************************************************************************
* @author  HWANG MooYeol
* @Mod		 2023-10-31 by YKKIM  	
* @brief   Embedded Controller:  LAB - Timer Input Capture 
*					 						- with Ultrasonic Distance Sensor
* 
******************************************************************************
*/

#include "stm32f411xe.h"
#include "math.h"
#include "ecSTM32F4v2.h"

uint32_t ovf_cnt = 0;
float time_interval_us = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;

#define TRIG PA_6
#define ECHO PB_6

void setup(void);

int main(void){
	
	setup();
	
	while(1){
		distance = (float) timeInterval * 340.0 / 2.0 / 10.0; 	// [mm] -> [cm]
		printf("Distance = %f cm\r\n", distance);
		delay_ms(500);
	}
}

void TIM4_IRQHandler(void){
	if(is_UIF(TIM4)){                     // check Update interrupt
		ovf_cnt ++;													// count
		clear_UIF(TIM4);  							    // clear
	}
	if(is_CCIF(TIM4, 1)){ 								// TIM4_Ch1 (IC1) Capture Flag. Rising Edge Detect
		time1 = ICAP_capture(TIM4, 1);			// Capture Time_end
		clear_CCIF(TIM4, 1);                // clear
	}								                      
	else if(is_CCIF(TIM4, 2)){ 									// TIM4_Ch2 (IC2) Capture Flag. Falling Edge Detect
		time2 = ICAP_capture(TIM4, 2);									// Capture Time start
		time_interval_us = ((time2 - time1) + ovf_cnt * (TIM4->ARR + 1)) * 10; //[us]
		timeInterval = time_interval_us / 1000.0;                                 //[ms]
		ovf_cnt = 0;                        					// countreset
		clear_CCIF(TIM4,2);								  					// clear 
	}
}


void setup(){
	RCC_PLL_init();      
	SysTick_init();
	UART2_init();                  //for serial monitor
  
// PWM configuration ---------------------------------------------------------------------	
	PWM_init(TRIG);								 // PA_6: Ultrasonic trig pulse
	PWM_period_us(TRIG, 50000);    // PWM of 50ms period. Use period_us()
	PWM_pulsewidth_us(TRIG, 10);   // PWM pulse width of 10us
	
	
// Input Capture configuration -----------------------------------------------------------------------	
	ICAP_init(ECHO);    	         // PB_6 as input caputre
 	ICAP_counter_us(ECHO, 10);   	 // ICAP counter step time as 10us
	ICAP_setup(ECHO, 1, IC_RISE);  // TIM4_CH1 as IC1 , rising edge detect
	ICAP_setup(ECHO, 2, IC_FALL);  // TIM4_CH2 as IC2 , falling edge detect
}