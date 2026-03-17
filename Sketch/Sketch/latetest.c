#include "stm32f411xe.h"
#include "math.h"

// #include "ecSTM32F411.h"
#include "ecPinNames.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
#include "ecEXTI2.h"
#include "ecRCC2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"   // ecPWM2.h 파일은 PWM 제어를 위한 커스텀 헤더 파일

// Definition of Button Pin & PWM Port, Pin
#define PWM_PIN PA_1    // PA_1 핀을 PWM 제어 핀으로 정의

// 함수 프로토타입 선언
void setup(void);           // 시스템 초기화를 위한 함수
void EXTI15_10_IRQHandler(void); // 외부 인터럽트 핸들러 (버튼 눌림 처리)
void TIM3_IRQHandler(void); // 타이머 3 인터럽트 핸들러

// 전역 변수 선언
int cnt = 0;         // 버튼 눌림 횟수 카운트, 모터 속도 및 LED 동작 결정
int cnt2 = 0;        // TIM3에서 1ms마다 증가하는 카운터
int cnt3 = 0;        // LED 토글 주기를 위한 카운터
int pause = 0;       // 모터 동작을 멈추는 플래그 (현재 사용되지 않음)
int button_signal = 0;  // 버튼 입력 신호 (현재 사용되지 않음)
int dir = 0;         // 모터 방향 제어 (0: 한 방향, 1: 반대 방향)

int main(void) {
	
  setup();   // 시스템 초기화 호출

  // 메인 루프
	while(1){
		sevensegment_display(cnt); // 7세그먼트 디스플레이에 cnt 값 출력
	}
}

// 시스템 초기화 함수
void setup(void) {   
	// 시스템 클럭 설정: PLL을 통해 클럭을 84MHz로 설정
   RCC_PLL_init();
   
	// LED 핀 설정 (출력으로 설정, 속도 및 출력 모드 설정)
   GPIO_init(GPIOA, LED_PIN, OUTPUT);    // LED_PIN (예: PA_5) 출력 모드
   GPIO_ospeed(GPIOA, LED_PIN, EC_MEDIUM); // 속도: 중간
   GPIO_otype(GPIOA, LED_PIN, EC_PUSH_PULL); // 출력 타입: Push-Pull
	
	// 버튼 핀 설정 (입력으로 설정, 풀다운 설정)
   GPIO_init(GPIOC, BUTTON_PIN, INPUT);   // BUTTON_PIN (예: PC_13) 입력 모드
   GPIO_pupd(GPIOC, BUTTON_PIN, EC_PD);   // 풀다운(Pull-Down) 설정
	
	// 모터 방향 제어 핀 설정 (출력으로 설정, 초기 상태는 Low)
   GPIO_init(GPIOC, 2, OUTPUT);   // GPIOC 2번 핀을 출력 모드로 설정 (모터 방향 제어)
   GPIO_otype(GPIOC, 2, EC_PUSH_PULL);   // 출력 타입: Push-Pull
	
	// PWM 제어 핀 설정 (PA_0 핀을 AF(대체 기능)으로 설정, 풀업 적용)
   GPIO_init(GPIOA, PA_0, AF);    // PA_0 핀을 대체 기능(AF) 모드로 설정
   GPIO_otype(GPIOA, PA_0, EC_PUSH_PULL); // 출력 타입: Push-Pull
   GPIO_pupd(GPIOA, PA_0, EC_PU);  // 풀업(Pull-Up) 설정
   GPIO_ospeed(GPIOA, PA_0, EC_FAST);  // 속도: 빠름
   
	// 타이머 2 설정 (1ms 주기로 인터럽트 발생)
   TIM_init(TIM2, 1);  // TIM2 초기화, 1ms 주기
   TIM2->DIER |= 1;	// 업데이트 인터럽트 활성화
   NVIC_EnableIRQ(TIM2_IRQn);	// TIM2 인터럽트 요청 활성화
   NVIC_SetPriority(TIM2_IRQn, 3); // TIM2 인터럽트 우선순위 설정 (3)
	 
	// 타이머 3 설정 (1ms 주기로 인터럽트 발생)
   TIM_init(TIM3, 1);  // TIM3 초기화, 1ms 주기
   TIM3->DIER |= 1;	// 업데이트 인터럽트 활성화
   NVIC_EnableIRQ(TIM3_IRQn);	// TIM3 인터럽트 요청 활성화
   NVIC_SetPriority(TIM3_IRQn, 2); // TIM3 인터럽트 우선순위 설정 (2)
	 
	// 외부 인터럽트 설정 (버튼 핀, 상승 신호에 반응하도록 설정)
   EXTI_init(GPIOC, 13, RISE, 0);  // GPIOC의 13번 핀(버튼)을 외부 인터럽트로 설정 (상승 엣지)
   NVIC_EnableIRQ(EXTI15_10_IRQn); // EXTI 인터럽트 활성화 (PC13은 10-15번 핀에 해당)
   NVIC_SetPriority(EXTI15_10_IRQn, 3); // EXTI 인터럽트 우선순위 설정 (3)
	 
	// PWM 설정 (PA_1 핀을 PWM 출력 핀으로 설정)
   PWM_init(PWM_PIN);  // PA_1 핀을 PWM 출력 핀으로 설정
   PWM_period(PWM_PIN, 1);  // PWM 주기를 1ms로 설정 (TIM2_CH1에 해당)
	 
	// 모터 방향 초기 설정 (초기 방향: 0)
   GPIO_write(GPIOC, 2, 0);  // 방향 핀을 Low로 설정 (모터 방향 0)
	 
	// 7세그먼트 디스플레이 초기화
   sevensegment_display_init();  // 7세그먼트 디스플레이 초기화 함수 호출
}

// TIM2 인터럽트 핸들러
void TIM2_IRQHandler(void) {
	// TIM2의 업데이트 플래그(UIF) 확인
	if((TIM2->SR & TIM_SR_UIF) == 1){ 
		// 모터 속도 제어: dir 값에 따라 듀티 사이클을 다르게 설정
		if(dir == 0) PWM_duty(PWM_PIN, 0.5*cnt);  // dir = 0일 때, 듀티 사이클은 50% * cnt 값
		else if(dir == 1) PWM_duty(PWM_PIN, 1 - 0.5*cnt); // dir = 1일 때, 역방향으로 듀티 사이클 설정
		
		// 인터럽트 플래그(UIF) 클리어
		TIM2->SR &= ~ TIM_SR_UIF;                    
	}
}

// TIM3 인터럽트 핸들러 (LED 토글 및 주기적 동작 처리)
void TIM3_IRQHandler(void) {
	// TIM3의 업데이트 플래그(UIF) 확인
	if((TIM3->SR & TIM_SR_UIF) == 1){ 
		cnt2 ++;  // 1ms마다 카운트 증가
		if(cnt2 > 500) {  // 500ms마다 동작
			LED_toggle();  // LED 상태 변경 (토글)
			
			cnt2 = 0;   // 카운터 초기화
			cnt3++;     // LED 토글을 위한 추가 카운트
			
			// cnt 값에 따라 LED 동작 방식 결정
			if(cnt == 0) GPIO_write(GPIOA, LED_PIN, 0);  // cnt = 0일 때, LED 끔
			else if(cnt == 1) {
				if(cnt3 >= 2) {  // cnt = 1일 때, 2번 주기마다 LED 토글
					LED_toggle();
					cnt3 = 0;
				}
			}
			else if(cnt == 2){
				if(cnt3 >= 3){  // cnt = 2일 때, 3번 주기마다 LED 토글
					cnt3 = 0;
				}
			}
		}
		// 인터럽트 플래그(UIF) 클리어
		TIM3->SR &= ~ TIM_SR_UIF;                    
	}
}

// EXTI 인터럽트 핸들러 (버튼 눌림 처리)
void EXTI15_10_IRQHandler(void) {
   // 버튼 인터럽트가 발생했는지 확인
   if (is_pending_EXTI(BUTTON_PIN)) {
		  // 디바운스를 위한 딜레이 (간단한 방법으로 처리)
		  for(volatile int i = 0; i < 350000; i++){}

		  // 버튼을 누를 때마다 cnt 값을 증가
		  cnt++;
				
		  // cnt 값이 2보다 크면 방향을 전환하고 cnt 초기화
			if(cnt > 2) {
				cnt = 0;	
				dir ^= 1;  // dir 값 반전 (모터 방향 전환)
				GPIO_write(GPIOC, 2, dir);  // 방향 핀에 새로운 dir 값 설정
			}
		  
		  // EXTI 인터럽트 플래그 클리어
		  clear_pending_EXTI(BUTTON_PIN);
   }
}

/*

버튼을 한번씩 누를때마다,
0일때는 모터듀티비율 0 -> LED 꺼짐
1일때는 모터듀티비율 50 -> LED 2초주기로 느리게 깜빡
2일때는 모터듀티비율 100 -> LED 1초주기로 빠르게 깜빡

버튼을 또 누르면, 0으로 되며, 모터의 방향이 바뀜.

0,1,2 변화를 sevensegment에 출력

*/
