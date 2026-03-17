/**
******************************************************************************
* @author  HWANG MooYeol
* @Mod	   2024-10-22 by HWANG MooYeol
* @brief   Embedded Controller Project1 RC car Manual Mode
******************************************************************************
*/

#include "stm32f411xe.h"
#include "math.h"
#include "ecSTM32F4v2.h"
#include "ecUART2.h"


// Definition Button Pin & PWM Port, Pin
#define Right_DIR_PIN PA_12
#define Right_PWM_PIN PA_1

#define Left_DIR_PIN PA_11
#define Left_PWM_PIN PA_0


float LEFTPWMState[20] = {1, 0, 0.7, 0.3, 0, 0.3, 0.7, 1, 0.3, 0.55, 0.8, 0, 0, 0, 0.7, 0.45, 0.2, 1, 1, 1};
float LEFTDirState[20] = {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,0};
float RIGHTPWMState[20] = {1, 0, 0.7, 0.3, 0, 0.3, 0.7, 1, 0, 0, 0, 0.3, 0.55, 0.8, 1, 1, 1, 0.7, 0.45, 0.2 };
float RIGHTDirState[20] = {1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};


void STATE_S0(void);
void STATE_S1(void);
void STATE_S2(void);
void STATE_S3(void);
void STATE_S4(void);
void STATE_S5(void);
void STATE_S6(void);
void STATE_S7(void);
void STATE_S8(void);
void STATE_S9(void);
void STATE_S10(void);
void STATE_S11(void);
void STATE_S12(void);
void STATE_S13(void);
void STATE_S14(void);
void STATE_S15(void);
void STATE_S16(void);
void STATE_S17(void);
void STATE_S18(void);
void STATE_S19(void);

void setup(void);

uint32_t LmotorDIR = 1;
uint32_t RmotorDIR = 1;
double  LmotorPWM = 1.0;
double RmotorPWM = 1.0;


volatile uint32_t currentState = 0;
volatile uint32_t k = 0;

char BT_string[100];
uint8_t BT_Data;



int main(void) {
	// Initialization --------------------------------------------------
	setup();

	//int wait;


	// Infinite Loop ---------------------------------------------------
	while (1) {}
}


/* Timer3 interrupt ISR
	* Print the car status every 1 sec such as ¡° ( ¡° MOD: A DIR: F STR: 00 VEL: 00 ¡±)
*/

void TIM3_IRQHandler(void) {
	if (is_UIF(TIM3)) {			// Check UIF(update isnterrupt flag)
		
		currentState = k;

		switch (currentState) {
		case 0: 
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 1:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 2:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 3:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 4:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 5:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 6:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 7:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 8:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 9:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 10:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 11:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 12:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 13:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 14:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 15:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 16:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 17:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 18:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		case 19:
			sprintf(BT_string, " MOD: M DIR: F STR: 00 VEL: 00 ");  
			USART_write(USART1, (uint8_t*)(BT_string), 20);
			break;
		}


		clear_UIF(TIM3); 		// Clear UI flag by writing 0
	}
}


void USART1_IRQHandler() {
	if (is_USART1_RXNE()) {
		BT_Data =  USART1_read();

		if (BT_Data == 'i') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S2();
				break;
			case 1:
				STATE_S5();
				break;
			case 2:
				STATE_S3();
				break;
			case 3:
				STATE_S4();
				break;
			case 4:
				STATE_S4();
				break;
			case 5:
				STATE_S6();
				break;
			case 6:
				STATE_S7();
				break;
			case 7:
				sprintf(BT_string, " MAXIMUM SPEED ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 8:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 9:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 10:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 11:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);;
				break;
			case 12:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 13:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 14:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 15:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 16:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 17:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 18:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			case 19:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1,(uint8_t*)(BT_string), 20);
				break;
			}

		}
		else if (BT_Data == 'k') {

			currentState = k;

			switch (currentState) {
			case 0:
				sprintf(BT_string, "SLOWEST SPEED ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 1:
				sprintf(BT_string, "SLOWEST SPEED ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 2:
				STATE_S0();
				break;
			case 3:
				STATE_S2();
				break;
			case 4:
				STATE_S3();
				break;
			case 5:
				STATE_S1();
				break;
			case 6:
				STATE_S5();
				break;
			case 7:
				STATE_S6();
				break;
			case 8:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 9:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 10:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 11:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 12:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 13:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 14:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 15:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 16:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 17:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 18:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 19:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			}

		}
		else if (BT_Data == 'j') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S8();
				break;
			case 1:
				STATE_S14();
				break;
			case 2:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 3:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 4:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 5:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 6:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 7:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 8:
				STATE_S9();
				break;
			case 9:
				STATE_S10();
				break;
			case 10:
				sprintf(BT_string, " MAX ROUTATE SPEED for fwd_LEFT ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 11:
				STATE_S0();
				break;
			case 12:
				STATE_S11();
				break;
			case 13:
				STATE_S12();
				break;
			case 14:
				STATE_S15();
				break;
			case 15:
				STATE_S16();
				break;
			case 16:
				sprintf(BT_string, "MAX ROUTATE SPEED for bwd_LEFT ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 17:
				STATE_S1();
				break;
			case 18:
				STATE_S17();
				break;
			case 19:
				STATE_S18();
				break;
			}

		}
		else if (BT_Data == 'l') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S11();
				break;
			case 1:
				STATE_S17();
				break;
			case 2:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 3:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 4:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 5:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 6:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 7:
				sprintf(BT_string, " UNABLE input for CURRENT STATE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 8:
				STATE_S0();
				break;
			case 9:
				STATE_S8();
				break;
			case 10:
				STATE_S9();
				break;
			case 11:
				STATE_S12();
				break;
			case 12:
				STATE_S13();
				break;
			case 13:
				sprintf(BT_string, " MAX ROUTATE SPEED for fwd_RIGHT ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 14:
				STATE_S1();
				break;
			case 15:
				STATE_S14();
				break;
			case 16:
				STATE_S15();
				break;
			case 17:
				STATE_S18();
				break;
			case 18:
				STATE_S19();
				break;
			case 19:
				sprintf(BT_string, " MAX ROUTATE SPEED for bwd_RIGHT ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			}

		}
		else if (BT_Data == 'f') {

			currentState = k;

			switch (currentState) {
			case 0:
				sprintf(BT_string, " is already forward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 1:
				STATE_S0();
				break;
			case 2:
				sprintf(BT_string, " is already forward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 3:
				sprintf(BT_string, " is already forward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 4:
				sprintf(BT_string, " is already forward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 5:
				STATE_S2();
				break;
			case 6:
				STATE_S3();
				break;
			case 7:
				STATE_S4();
				break;
			case 8:
				STATE_S2();
				break;
			case 9:
				STATE_S2();
				break;
			case 10:
				STATE_S2();
				break;
			case 11:
				STATE_S2();
				break;
			case 12:
				STATE_S2();
				break;
			case 13:
				STATE_S2();
				break;
			case 14:
				STATE_S0();
				break;
			case 15:
				STATE_S0();
				break;
			case 16:
				STATE_S0();
				break;
			case 17:
				STATE_S0();
				break;
			case 18:
				STATE_S0();
				break;
			case 19:
				STATE_S0();
				break;
			}

		}
		else if (BT_Data == 'b') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S1();
				break;
			case 1:
				sprintf(BT_string, " is already backward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 2:
				STATE_S5();
				break;
			case 3:
				STATE_S6();
				break;
			case 4:
				STATE_S7();
				break;
			case 5:
				sprintf(BT_string, " is already backward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 6:
				sprintf(BT_string, " is already backward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 7:
				sprintf(BT_string, " is already backward MODE ");
				USART_write(USART1, (uint8_t*)(BT_string), 20);
				break;
			case 8:
				STATE_S1();
				break;
			case 9:
				STATE_S1();
				break;
			case 10:
				STATE_S1();
				break;
			case 11:
				STATE_S1();
				break;
			case 12:
				STATE_S1();
				break;
			case 13:
				STATE_S1();
				break;
			case 14:
				STATE_S5();
				break;
			case 15:
				STATE_S5();
				break;
			case 16:
				STATE_S5();
				break;
			case 17:
				STATE_S5();
				break;
			case 18:
				STATE_S5();
				break;
			case 19:
				STATE_S5();
				break;
			}

		}
		else if (BT_Data == 's') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S0();
				break;
			case 1:
				STATE_S0();
				break;
			case 2:
				STATE_S0();
				break;
			case 3:
				STATE_S0();
				break;
			case 4:
				STATE_S0();
				break;
			case 5:
				STATE_S0();
				break;
			case 6:
				STATE_S0();
				break;
			case 7:
				STATE_S0();
				break;
			case 8:
				STATE_S0();
				break;
			case 9:
				STATE_S0();
				break;
			case 10:
				STATE_S0();
				break;
			case 11:
				STATE_S0();
				break;
			case 12:
				STATE_S0();
				break;
			case 13:
				STATE_S0();
				break;
			case 14:
				STATE_S0();
				break;
			case 15:
				STATE_S0();
				break;
			case 16:
				STATE_S0();
				break;
			case 17:
				STATE_S0();
				break;
			case 18:
				STATE_S0();
				break;
			case 19:
				STATE_S0();
				break;
			}

		}
		else if (BT_Data == '0') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S0();
				break;
			case 1:
				STATE_S1();
				break;
			case 2:
				STATE_S0();
				break;
			case 3:
				STATE_S0();
				break;
			case 4:
				STATE_S0();
				break;
			case 5:
				STATE_S1();
				break;
			case 6:
				STATE_S1();
				break;
			case 7:
				STATE_S1();
				break;
			case 8:
				STATE_S0();
				break;
			case 9:
				STATE_S0();
				break;
			case 10:
				STATE_S0();
				break;
			case 11:
				STATE_S0();
				break;
			case 12:
				STATE_S0();
				break;
			case 13:
				STATE_S0();
				break;
			case 14:
				STATE_S1();
				break;
			case 15:
				STATE_S1();
				break;
			case 16:
				STATE_S1();
				break;
			case 17:
				STATE_S1();
				break;
			case 18:
				STATE_S1();
				break;
			case 19:
				STATE_S1();
				break;
			}

		}
		else if (BT_Data == '1') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S2();
				break;
			case 1:
				STATE_S5();
				break;
			case 2:
				STATE_S2();
				break;
			case 3:
				STATE_S2();
				break;
			case 4:
				STATE_S2();
				break;
			case 5:
				STATE_S5();
				break;
			case 6:
				STATE_S5();
				break;
			case 7:
				STATE_S5();
				break;
			case 8:
				STATE_S2();
				break;
			case 9:
				STATE_S2();
				break;
			case 10:
				STATE_S2();
				break;
			case 11:
				STATE_S2();
				break;
			case 12:
				STATE_S2();
				break;
			case 13:
				STATE_S2();
				break;
			case 14:
				STATE_S5();
				break;
			case 15:
				STATE_S5();
				break;
			case 16:
				STATE_S5();
				break;
			case 17:
				STATE_S5();
				break;
			case 18:
				STATE_S5();
				break;
			case 19:
				STATE_S5();
				break;
			}
		}
		else if (BT_Data == '2') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S3();
				break;
			case 1:
				STATE_S6();
				break;
			case 2:
				STATE_S3();
				break;
			case 3:
				STATE_S3();
				break;
			case 4:
				STATE_S3();
				break;
			case 5:
				STATE_S6();
				break;
			case 6:
				STATE_S6();
				break;
			case 7:
				STATE_S6();
				break;
			case 8:
				STATE_S3();
				break;
			case 9:
				STATE_S3();
				break;
			case 10:
				STATE_S3();
				break;
			case 11:
				STATE_S3();
				break;
			case 12:
				STATE_S3();
				break;
			case 13:
				STATE_S3();
				break;
			case 14:
				STATE_S6();
				break;
			case 15:
				STATE_S6();
				break;
			case 16:
				STATE_S6();
				break;
			case 17:
				STATE_S6();
				break;
			case 18:
				STATE_S6();
				break;
			case 19:
				STATE_S6();
				break;
			}
		}
		else if (BT_Data == '3') {

			currentState = k;

			switch (currentState) {
			case 0:
				STATE_S4();
				break;
			case 1:
				STATE_S7();
				break;
			case 2:
				STATE_S4();
				break;
			case 3:
				STATE_S4();
				break;
			case 4:
				STATE_S4();
				break;
			case 5:
				STATE_S7();
				break;
			case 6:
				STATE_S7();
				break;
			case 7:
				STATE_S7();
				break;
			case 8:
				STATE_S4();
				break;
			case 9:
				STATE_S4();
				break;
			case 10:
				STATE_S4();
				break;
			case 11:
				STATE_S4();
				break;
			case 12:
				STATE_S4();
				break;
			case 13:
				STATE_S4();
				break;
			case 14:
				STATE_S7();
				break;
			case 15:
				STATE_S7();
				break;
			case 16:
				STATE_S7();
				break;
			case 17:
				STATE_S7();
				break;
			case 18:
				STATE_S7();
				break;
			case 19:
				STATE_S7();
				break;
			}
			}
	}
}



// Initiallization 
void setup(void) {
	RCC_PLL_init();				// System Clock Initiallization 
	
	SysTick_init();

	UART2_init();
	UART1_init();

	/* Timer Update Interrupt
			*TIM3: set Update interrupt by Timer 3
			*1000: timeperiod = 1 sec
	*/
	TIM_UI_init(TIM3, 1000);

	GPIO_init(Right_DIR_PIN, OUTPUT);
	GPIO_otype(Right_DIR_PIN, PUSH_PULL);

	GPIO_init(Left_DIR_PIN, OUTPUT);
	GPIO_otype(Left_DIR_PIN, PUSH_PULL);


	// PWM of 20 msec:  TIM2_CH1 (PA_1 AFmode)
	PWM_init(Right_PWM_PIN);
	PWM_period(Right_PWM_PIN, 1);   // 1 msec PWM period
	
	PWM_init(Left_PWM_PIN);
	PWM_period(Left_PWM_PIN, 1);

}


void STATE_S0(void) {
	k = 0;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S1(void) {
	k = 1;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S2(void) {
	k = 2;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S3(void) {
	k = 3;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S4(void) {
	k = 4;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S5(void) {
	k = 5;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S6(void) {
	k = 6;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S7(void) {
	k = 7;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S8(void) {
	k = 8;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S9(void) {
	k = 9;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S10(void) {
	k = 10;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S11(void) {
	k = 11;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S12(void) {
	k = 12;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S13(void) {
	k = 13;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S14(void) {
	k = 14;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S15(void) {
	k = 15;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S16(void) {
	k = 16;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S17(void) {
	k = 17;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S18(void) {
	k = 18;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}

void STATE_S19(void) {
	k = 19;

	LmotorPWM = LEFTPWMState[k];
	LmotorDIR = LEFTDirState[k];
	RmotorPWM = RIGHTPWMState[k];
	RmotorDIR = RIGHTDirState[k];

	GPIO_write(Right_DIR_PIN, RmotorDIR);
	GPIO_write(Left_DIR_PIN, LmotorDIR);
	PWM_duty(Right_PWM_PIN, RmotorPWM);
	PWM_duty(Left_PWM_PIN, LmotorPWM);
}