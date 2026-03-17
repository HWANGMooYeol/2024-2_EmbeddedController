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
#define PWM_PIN PA_1
#define BUTTON_PIN PC_13

void setup(void);
void EXTI15_10_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

 int angle = 0;
 int direction = 1;
 float duty_cycle = 0;

int main(void) {
    // Initialization
    setup();
    
    // Infinite Loop
    while(1) {}   
}


void TIM3_IRQHandler(void) {

    if (is_UIF(TIM3)) {
        angle += direction * 10; // Increase angle by 10
        
        if (angle >= 180) {
            angle = 180;
            direction = -1; // Change to decreasing when 180 over
        } else if (angle <= 0) {
            angle = 0;
            direction = 1; // Change to increasing when 0 over
        }
        
    
        duty_cycle = (angle / 180.0) * 0.1 + 0.025; // plusewidth 
        PWM_duty(PWM_PIN, duty_cycle); 
				
        clear_UIF(TIM3); 
    }
}

void EXTI15_10_IRQHandler(void) {
    if (is_pending_EXTI(13)) { // Check if EXTI line 13 is pending
       angle = 0;
       clear_pending_EXTI(13); 
    }
}


// Initialization
void setup(void) {
    RCC_PLL_init(); // System Clock = 84MHz
    
    // Initialize PWM Pin
    GPIO_init(PWM_PIN, AF); 
    GPIO_otype(PWM_PIN, PUSH_PULL);
    GPIO_pupd(PWM_PIN, PULL_UP);
    
    // Initialize Button Pin
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_UP);
    
    // PWM Initialization
    PWM_init(PWM_PIN);
    PWM_period(PWM_PIN, 20); // Set PWM period to 20ms
    PWM_duty(PWM_PIN,0.025); // Start at 0
    
    // Timer Initialization
    TIM_UI_init(TIM3, 500);      // Initialize timer for 500ms
    EXTI_init(BUTTON_PIN, FALL, 1); // Initialize external interrupt for button
}
