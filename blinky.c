#include "stm32f407xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void SysClockConfig (void)
{
	
	#define PLL_M 	4
	#define PLL_N 	168
	#define PLL_P 	0  // PLLP = 2
  
	RCC->CR |= RCC_CR_HSEON;  // RCC->CR |= 1<<16;
	while (!(RCC->CR & RCC_CR_HSERDY));  // while (!(RCC->CR & (1<<17)));

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;  // RCC->APB1ENR |= 1<<28;
	PWR->CR |= PWR_CR_VOS;  // PWR->CR |= 3<<14;

	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;  // FLASH->ACR = (1<<8) | (1<<9)| (1<<10)| (5<<0);

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // RCC->CFGR &= ~(1<<4);

	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;  // RCC->CFGR |= (5<<10);

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;  // RCC->CFGR |= (4<<13);

	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (RCC_PLLCFGR_PLLSRC_HSE);  // (1<<22);

	RCC->CR |= RCC_CR_PLLON;  // RCC->CR |= (1<<24);
	while (!(RCC->CR & RCC_CR_PLLRDY));  // while (!(RCC->CR & (1<<25)));

	RCC->CFGR |= RCC_CFGR_SW_PLL;  // RCC->CFGR |= (2<<0);
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);  // while (!(RCC->CFGR & (2<<2)));
}


void GPIO_Config (void)
{
	
	RCC->AHB1ENR |= (1<<0);

	GPIOA->MODER |= (1<<10);  // pin PA5(bits 11:10) as Output (01)

	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}

void delay (uint32_t time)
{
	while (time--);
}

int main (void)
{

	SysClockConfig ();
	GPIO_Config ();

	while (1)
	{
		GPIOA->BSRR |= (1<<5);  // Set the pin PA5
		delay (20000000);
		GPIOA->BSRR |= ((1<<5) <<16);  // Reset pin PA5
		delay (20000000);
	}
}

