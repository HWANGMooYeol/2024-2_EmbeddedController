/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : SSS LAB
Created          : 05-03-2021
Modified         : 08-23-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/


#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"


#define CLEAR_2BIT(PORT,PIN)  ((PORT) &= ~(3<<2*(PIN)))

typedef enum {INPUT = 0, OUTPUT, AF, ANALOG}GPIO_MODE;

/*
#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03
*/

typedef enum {PUSH_PULL = 0, OPEN_DRAIN = 1}GPIO_TYPE;

typedef enum { LOW_SPEED    = 0b00,
							 MEDIUM_SPEED = 0b01,
							 FAST_SPEED   = 0b10,
							 HIGH_SPEED   = 0b11
						 }GPIO_SPEED;

#define NO_PUPD 0x00
#define PULL_UP 0x01
#define PULL_DOWN 0x02

#define HIGH 1
#define LOW  0

#define LED_PIN PA_5//Find LED Port&Pin and Fill the blank	
#define BUTTON_PIN PC_13//Find BTN Port&Pin and Fill the blank

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_write(PinName_t pinName, int Output);
int  GPIO_read(PinName_t pinName);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, int speed);
void GPIO_otype(PinName_t pinName, int type);
void GPIO_pupd(PinName_t pinName, int pupd);
void GPIO_toggle(PinName_t pinName);

void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD); 
void sevensegment_display(uint8_t  num);
void sevensegment_decoder_init(void);
void sevensegment_decoder(uint8_t num);

 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
