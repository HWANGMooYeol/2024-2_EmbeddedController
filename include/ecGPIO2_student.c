/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : SSS LAB
Created          : 05-03-2021
Modified         : 08-23-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/



#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO2_student.h"



void GPIO_init(PinName_t pinName, uint32_t mode){     
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	
	//[TO-DO] YOUR CODE GOES HERE
	// Make it for GPIOB, GPIOD..GPIOH

	// You can also make a more general function of
	void RCC_GPIO_enable(GPIO_TypeDef *Port); 

	GPIO_mode(pinName, mode);
}


// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
   Port->MODER &= ~(3UL<<(2*pin));     
   Port->MODER |= mode<<(2*pin);    
}


// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, int speed){
	//[TO-DO] YOUR CODE GOES HERE
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	//[TO-DO] YOUR CODE GOES HERE
	Port->OSPEEDR &= ~(3UL << (2 * pin));
	Port->OSPEEDR |= speed<<(2 * pin);
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, int type){
   	//[TO-DO] YOUR CODE GOES HERE
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	//[TO-DO] YOUR CODE GOES HERE
	Port->OTYPER &= ~(1 << (pin));
	Port->OTYPER |= type << (pin);
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, int pupd){
   	//[TO-DO] YOUR CODE GOES HERE
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	//[TO-DO] YOUR CODE GOES HERE
	Port-> PUPDR &= ~(3UL << (2 * pin));
	Port-> PUPDR |= pupd << (2 * pin);
}

int GPIO_read(PinName_t pinName){
   	//[TO-DO] YOUR CODE GOES HERE
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	//[TO-DO] YOUR CODE GOES HERE
	return (Port->IDR >> pin) & (1UL); //[TO-DO] YOUR CODE GOES HERE	
}

void GPIO_write(PinName_t pinName, int Output) {
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	Port->ODR &= ~(1 << (pin));
	Port->ODR |= Output << (pin);
}

void GPIO_toggle(PinName_t pinName) {
	GPIO_TypeDef* Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	Port->ODR ^= 1 << (pin);
}



PinName_t pinName1, pinName2, pinName3, pinName4;

void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD) {
    pinName1 = pinNameA;
    pinName2 = pinNameB;
    pinName3 = pinNameC;
    pinName4 = pinNameD;
    
    GPIO_init(pinName1, OUTPUT);
    GPIO_init(pinName2, OUTPUT);
    GPIO_init(pinName3, OUTPUT);
    GPIO_init(pinName4, OUTPUT);
}

void sevensegment_display(uint8_t num) {
    uint8_t pattern_map[10] = {
        0b0000, // 0
        0b0001, // 1
        0b0010, // 2
        0b0011, // 3
        0b0100, // 4
        0b0101, // 5
        0b0110, // 6
        0b0111, // 7
        0b1000, // 8
        0b1001  // 9
    };

    uint8_t pattern = pattern_map[num]; 

    GPIO_write(pinName1, (pattern & 0b0001) ? HIGH : LOW);
    GPIO_write(pinName2, (pattern & 0b0010) ? HIGH : LOW);
    GPIO_write(pinName3, (pattern & 0b0100) ? HIGH : LOW);
    GPIO_write(pinName4, (pattern & 0b1000) ? HIGH : LOW);
}


void sevensegment_decoder_init(void){
	GPIO_init(PB_9, OUTPUT);  // 7segment-a
	GPIO_init(PA_6, OUTPUT);  // 7segment-b
	GPIO_init(PA_7, OUTPUT);  // 7segment-c
	GPIO_init(PB_6, OUTPUT);  // 7segment-d
	GPIO_init(PC_7, OUTPUT);  // 7segment-e
	GPIO_init(PA_9, OUTPUT);  // 7segment-f
	GPIO_init(PA_8, OUTPUT);  // 7segment-g
	GPIO_init(PB_10, OUTPUT); // 7segment-dp
}


void sevensegment_decoder(uint8_t num) {
    uint8_t segment_bit[10] = {
        0b00111111, // 0: a, b, c, d, e, f
        0b00000110, // 1: b, c
        0b01011011, // 2: a, b, d, e, g
        0b01001111, // 3: a, b, c, d, g
        0b01100110, // 4: b, c, f, g
        0b01101101, // 5: a, c, d, f, g
        0b01111101, // 6: a, c, d, e, f, g
        0b00000111, // 7: a, b, c
        0b01111111, // 8: a, b, c, d, e, f, g
        0b01101111  // 9: a, b, c, d, f, g
    };

    uint8_t pattern = segment_bit[num];

    GPIO_write(PB_9, (pattern & 0b00000001) ? LOW : HIGH); // a
    GPIO_write(PA_6, (pattern & 0b00000010) ? LOW : HIGH); // b
    GPIO_write(PA_7, (pattern & 0b00000100) ? LOW : HIGH); // c
    GPIO_write(PB_6, (pattern & 0b00001000) ? LOW : HIGH); // d
    GPIO_write(PC_7, (pattern & 0b00010000) ? LOW : HIGH); // e
    GPIO_write(PA_9, (pattern & 0b00100000) ? LOW : HIGH); // f
    GPIO_write(PA_8, (pattern & 0b01000000) ? LOW : HIGH); // g
    GPIO_write(PB_10, 1);

}
