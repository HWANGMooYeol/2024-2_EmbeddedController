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


// Definition Button Pin & PWM Port, Pin
// #define PWM_PIN PA_11
#define BUTTON_PIN PC_13
#define LED_PIN PA_5

void setup(void);
void EXTI15_10_IRQHandler(void);
void TIM2_IRQHandler(void);
void SysTick_Handler(void);
void sevensegment_decoder_pause(void);

uint16_t LED[] = {PA_0, PA_1, PB_0, PC_1};
int state = 0;
int led_cnt = 0;
int segment_cnt = 0;
uint8_t ledpattern_map[16] = {
        0b0000, // 0
        0b0001, // 1
        0b0010, // 2
        0b0011, // 3
        0b0100, // 4
        0b0101, // 5
        0b0110, // 6
        0b0111, // 7
        0b1000, // 8
        0b1001, // 9
				0b1010, // 10
				0b1011, // 11
				0b1100, // 12
				0b1101, // 13
				0b1110, // 14
				0b1111, // 15
    };




int main(void) {
    // Initialization
    setup();
		GPIO_write(LED_PIN,LOW);
    // Infinite Loop
    while(1) {
			if(state){									//pause state
				
				GPIO_toggle(LED_PIN);
				delay_ms(1000);			              //state led
				
				sevensegment_decoder_pause();     // segment display
				
			} else {									 //play state
			
				GPIO_write(LED_PIN,HIGH);																						//state led
				
				GPIO_write(LED[0], (ledpattern_map[led_cnt] & 0b0001) ? HIGH : LOW);
				GPIO_write(LED[1], (ledpattern_map[led_cnt] & 0b0010) ? HIGH : LOW);
				GPIO_write(LED[2], (ledpattern_map[led_cnt] & 0b0100) ? HIGH : LOW);
				GPIO_write(LED[3], (ledpattern_map[led_cnt] & 0b1000) ? HIGH : LOW);     //led display
				
				sevensegment_decoder(segment_cnt);																			// segment display
				
			}
		}
}

void TIM2_IRQHandler(void) {

    if (is_UIF(TIM2)) {
					
				led_cnt ++;
			
				if (led_cnt > 16) {
						led_cnt = 0;
						segment_cnt++;
				}
				
				if (segment_cnt > 9)
					segment_cnt = 0;
					
			
        clear_UIF(TIM2); 
    }
}

void EXTI15_10_IRQHandler(void) {
    if (is_pending_EXTI(13)) { // Check if EXTI line 13 is pending
      
			state =! state;   //toggle state
			
      clear_pending_EXTI(13); 
    }
}


// Initialization
void setup(void) {
    RCC_PLL_init(); // System Clock = 84MHz
		SysTick_init(); // sysTick enable
    
		// Initialize Button Pin
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_DOWN);	
	
		// Init status LED output pin
		GPIO_init(LED_PIN, OUTPUT);
		GPIO_otype(LED_PIN, PUSH_PULL);
		GPIO_pupd(LED_PIN, NO_PUPD);
		GPIO_ospeed(LED_PIN, MEDIUM_SPEED);
	
		// Init External LED output pins
		for (int j = 0; j < 4; j++) {
			GPIO_init(LED[j], OUTPUT);
    	GPIO_otype(LED[j], PUSH_PULL);
    	GPIO_pupd(LED[j], NO_PUPD);
      GPIO_ospeed(LED[j], MEDIUM_SPEED);
		}
		
		// Init 7-segment output pin
		sevensegment_decoder_init();
    uint16_t pins[] = {PB_9, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};
		for (int i = 0; i < 8; i++) {
			GPIO_init(pins[i], OUTPUT);
    	GPIO_otype(pins[i], PUSH_PULL);
    	GPIO_pupd(pins[i], NO_PUPD);
      GPIO_ospeed(pins[i], MEDIUM_SPEED);
		}
	
	/*
    // Initialize PWM Pin
    GPIO_init(PWM_PIN, AF); 
    GPIO_otype(PWM_PIN, PUSH_PULL);
    GPIO_pupd(PWM_PIN, PULL_UP);
    
    // PWM Initialization
    PWM_init(PWM_PIN);
    PWM_period(PWM_PIN, 20); // Set PWM period to 20ms
    PWM_duty(PWM_PIN,0.025); // Start at 0
 */
		
    // Timer Initialization
    TIM_UI_init(TIM2, 500);      // Initialize timer for 500ms
		TIM_CountDIR(TIM1, DOWN_COUNTING); // Initialize timer direction
		
		// Initialize external interrupt for button
    EXTI_init(BUTTON_PIN, RISE, 0); 
}

void sevensegment_decoder_pause(void){					// display P.
	sevensegment_decoder_init();
	GPIO_write(PB_9, LOW);  // 7segment-a
	GPIO_write(PA_6, LOW);  // 7segment-b
	GPIO_write(PA_7, HIGH);  // 7segment-c
	GPIO_write(PB_6, HIGH);  // 7segment-d
	GPIO_write(PC_7, LOW);  // 7segment-e
	GPIO_write(PA_9, LOW);  // 7segment-f
	GPIO_write(PA_8, LOW);  // 7segment-g
	GPIO_write(PB_10, LOW); // 7segment-dp
}