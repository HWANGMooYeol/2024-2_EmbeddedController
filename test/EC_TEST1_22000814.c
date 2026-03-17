#include "stm32f411xe.h"
#include "math.h"

// #include "ecSTM32F411.h"
#include "ecPinNames.h"
#include "ecGPIO2_student.h"
#include "ecSysTick2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"   // ecPWM2.h
#include "ecEXTI2.h"
#include "ecUART2_simple_student.h"

// Definition Button Pin & PWM Port, Pin
#define PWM_PIN PA_6
#define DIR_PIN PC_2
#define BUTTON_PIN PC_13
#define IRsensor_PIN PB_1
uint16_t segment[] = {PA_7, PB_6, PC_7, PA_9};

void setup(void);
void EXTI15_10_IRQHandler(void);
void TIM3_IRQHandler(void);
void SysTick_Handler(void);
void EXTI1_IRQHandler(void);
void TIM2_IRQHandler(void);


int state = 0;
int dir  = 0;
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
double duty = 0;





int main(void) {
    // Initialization
    setup();
    // Infinite Loop
    while(1) {
			
			printf("state: %d\n",state);
			printf("DIR: %d\n",dir);
			printf("duty: %f\n",duty);
			
			
			
			if(state == 0){									//pause state
				GPIO_write(segment[0], HIGH);
				GPIO_write(segment[1], HIGH);
				GPIO_write(segment[2], HIGH);
				GPIO_write(segment[3], HIGH);
				
			} 
			else if (state == 1){									 //mid state & CW
			sevensegment_display(cnt1 % 10);
			
			}
			else if (state == 2) {									//high state &CW
			sevensegment_display(cnt2 % 10);
			

			}
			else if (state == 3) {									//pause state
				GPIO_write(segment[0], HIGH);
				GPIO_write(segment[1], HIGH);
				GPIO_write(segment[2], HIGH);
				GPIO_write(segment[3], HIGH);
				
			}
			else if (state == 4){									 //mid state &CCW
			sevensegment_display(cnt3 % 10);
			
			}
			else if (state == 5) {									//high state &CCW
			sevensegment_display(cnt4 % 10);
		
			}
		}
}

void TIM3_IRQHandler(void) {

    if (is_UIF(TIM3)) {
				cnt2 ++;
				cnt4 --;
				
				if (cnt2 > 9 | cnt4 <0) {
					cnt2 = 0;
					cnt4 = 9;
				}
				
				if(state == 0){									//pause state
				
				
				dir = 0;
				duty = 0;
					
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
				
			} 
			else if (state == 1){									 //mid state & CW
			
			
			dir  = 0;
			duty = 0.4;
				
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
			}
			else if (state == 2) {									//high state &CW
			
			
			dir  = 0;
			duty = 0.8;
				
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
			}
			else if (state == 3) {									//pause state
				
				dir = 0;
				duty = 0;
				
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
			}
			else if (state == 4){									 //mid state &CCW
			
				
			dir  = 1;
			duty = 0.8;
				
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
			}
			else if (state == 5) {									//high state &CCW
			
		
			dir  = 1;
			duty=0.4;
				
				GPIO_write(DIR_PIN,dir);
			PWM_duty(PWM_PIN,duty);
			}
				
        clear_UIF(TIM3); 
    }
}

void TIM2_IRQHandler(void) {

    if (is_UIF(TIM2)) {
				cnt1 ++;
				cnt3 --;
			
				if (cnt1 > 9 | cnt3 <0) {
					cnt1 = 0;
					cnt3 = 9;
				}
				
			
        clear_UIF(TIM2); 
    }
}

void EXTI15_10_IRQHandler(void) {
    if (is_pending_EXTI(13)) { // Check if EXTI line 13 is pending
      
			state++ ;   							//change state
			state = state%6 ;
			
      clear_pending_EXTI(13); 
    }
}

void EXTI1_IRQHandler(void) {
    if (is_pending_EXTI(1)) { // Check if EXTI line 13 is pending
      
			state = 0;							// pause state
			
      clear_pending_EXTI(1); 
    }
}


// Initialization
void setup(void) {
    RCC_PLL_init(); // System Clock = 84MHz
		SysTick_init(); // sysTick enable
		UART2_init();
    
		// Initialize Button Pin
    GPIO_init(DIR_PIN, OUTPUT);
		GPIO_write(DIR_PIN,dir);
	
		// Initialize Button Pin
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_DOWN);
		// Initialize external interrupt for button
    EXTI_init(BUTTON_PIN, RISE, 2); 
	
		// Initialize Button Pin
    GPIO_init(IRsensor_PIN, INPUT);
    GPIO_pupd(IRsensor_PIN, PULL_DOWN);
		// Initialize external interrupt for button
    EXTI_init(IRsensor_PIN, RISE, 1); 
	
	
		// Init External LED output pins
		for (int j = 0; j < 4; j++) {
			GPIO_init(segment[j], OUTPUT);
    	GPIO_otype(segment[j], PUSH_PULL);
    	GPIO_pupd(segment[j], NO_PUPD);
      GPIO_ospeed(segment[j], MEDIUM_SPEED);
		}
	
    // Initialize PWM Pin
    GPIO_init(PWM_PIN, AF); 
    GPIO_otype(PWM_PIN, PUSH_PULL);
    GPIO_pupd(PWM_PIN, PULL_UP);
    
    // PWM Initialization
    PWM_init(PWM_PIN);
    PWM_period_ms(PWM_PIN, 1); // Set PWM period to 1ms
		
    // Timer Initialization
    TIM_UI_init(TIM3, 500);      // Initialize timer for 500ms
		
		// Timer Initialization
    TIM_UI_init(TIM2, 1000);      // Initialize timer for 1s
		
		sevensegment_display_init(segment[0],segment[1],segment[2],segment[3]); //segment init
		
		
}

