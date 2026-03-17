#include "stm32f411xe.h"
#include "math.h"
#include "ecSTM32F4v2.h"

#define IR_analog_pin PC_2
#define headlight_analog_pin PA_1
#define TRIG PA_6
#define ECHO PB_6
#define behind_warning_led_pin PC_0
#define exti_2 PC_1
#define exti_3_chin PB_2
#define vib_motor PC_8
#define gas_pin PC_10

//IR parameter
uint32_t value;

//Ultra sonic parameter
uint32_t ovf_cnt = 0;
float time_interval_us = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;

//stepper motor parameter
int dir = 0;
int step = 0;
int update_flag =0;

void setup(void);
	
int main(void) { 
	
	// Initialiization --------------------------------------------------------
	setup();
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		
		printf("value = %d \r\n",value);
		printf("\r\n");
		distance = (float) timeInterval * 340.0 / 2.0 / 10.0; 	// [mm] -> [cm]
		printf("Distance = %f cm\r\n", distance);
		printf("\r\n");
		delay_ms(1000);
		
	}
}

void TIM2_IRQHandler(void) {
	if (is_UIF(TIM2)) {			// Check UIF(update isnterrupt flag)
		
		// for dark mode
		if (value<800)
			PWM_duty(headlight_analog_pin, 0);
		else if (value >=800)
			PWM_duty(headlight_analog_pin, value*0.00025);
		
		//for behind alert
		if (distance < 15)
			GPIO_write(behind_warning_led_pin, HIGH);
		else if(distance >= 15)
			GPIO_write(behind_warning_led_pin, LOW);
		
		// for stepper moter
		if(update_flag == 1) {
			Stepper_step(step, dir, FULL);
			update_flag = 0;
		}
			
		
		
		clear_UIF(TIM2); 		// Clear UI flag by writing 0
	}
}

//Ultra sonic timerhandler
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

// ADC Interrupt
void ADC_IRQHandler(void){
    if(is_ADC_OVR())
		clear_ADC_OVR();

	if(is_ADC_EOC())
		value = ADC_read();
}

//intrup for PC_13 pin
void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		
		update_flag = 1;
		dir = 0;
		step = 2048;

		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}


//intrup for PC_1 pin
void EXTI1_IRQHandler(void) {  
	if (is_pending_EXTI(exti_2)) {
		
		update_flag = 1;
		dir = 0;
		step = 0;
		
		clear_pending_EXTI(exti_2); // cleared by writing '1'
	}
}

//intrup for PB_2 pin
void EXTI2_IRQHandler(void) {  
	if (is_pending_EXTI(exti_3_chin)) {
		
		update_flag = 1;
		dir = 1;
		step = 100;
		
		clear_pending_EXTI(exti_3_chin); // cleared by writing '1'
	}
}


// Initialiization 
void setup(void) {	
	RCC_PLL_init();		// System Clock = 84MHz
	UART2_init();		// UART2 Init
	
	SysTick_init();		// SysTick Init
	
	//ADC setting
	ADC_init(IR_analog_pin);		// Default: HW triggered by TIM3 counter @ 1msec
	TIM_UI_init(TIM2, 10);
	
	PWM_init(headlight_analog_pin);
	PWM_period(headlight_analog_pin, 1);
	
	// PWM configuration for Ultra Sonic---------------------------------------------------------------------	
	PWM_init(TRIG);								 // PA_6: Ultrasonic trig pulse
	PWM_period_us(TRIG, 1000);    // PWM of 50ms period. Use period_us()
	PWM_pulsewidth_us(TRIG, 10);   // PWM pulse width of 10us
	
	
	// Input Capture configuration -----------------------------------------------------------------------	
	ICAP_init(ECHO);    	         // PB_6 as input caputre
 	ICAP_counter_us(ECHO, 10);   	 // ICAP counter step time as 10us
	ICAP_setup(ECHO, 1, IC_RISE);  // TIM4_CH1 as IC1 , rising edge detect
	ICAP_setup(ECHO, 2, IC_FALL);  // TIM4_CH2 as IC2 , falling edge detect
	
	GPIO_init(behind_warning_led_pin, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_pupd(behind_warning_led_pin, PULL_UP);
	GPIO_otype(behind_warning_led_pin, PUSH_PULL);
	GPIO_ospeed(behind_warning_led_pin, FAST_SPEED);
	
	// interuppt
	EXTI_init(BUTTON_PIN, FALL,2);           // External Interrupt Setting
	GPIO_init(BUTTON_PIN, INPUT);           // GPIOC pin13 initialization
	
	EXTI_init(exti_2, FALL,1);           // External Interrupt Setting
	GPIO_init(exti_2, INPUT); 


	EXTI_init(exti_3_chin, FALL,0);   
	// External Interrupt Setting
	GPIO_init(exti_3_chin, INPUT);

	
	Stepper_init(PB_10,PB_4,PB_5,PB_3); // Stepper GPIO pin initialization
	Stepper_setSpeed(9);                          	//  set stepper motor speed   rpm
}
