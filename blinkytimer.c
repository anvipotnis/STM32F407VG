#include “blinky.h”


void TIM6Config (void)
{

	RCC->APB1ENR |= (1<<4);  // Enable the timer6 clock
	
	TIM6->PSC = 90-1;  // 90MHz/90 = 1 MHz ~~ 1 uS delay
	TIM6->ARR = 0xffff;  // MAX ARR value
	
	TIM6->CR1 |= (1<<0); // Enable the Counter
	while (!(TIM6->SR & (1<<0)));  
}

void Delay_us (uint16_t us)
{
	TIM6->CNT = 0;
	while (TIM6->CNT < us);
}

void Delay_ms (uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++)
	{
		Delay_us (1000); 
	}
}


void GPIOConfig (void)
{

	RCC->AHB1ENR |= (1<<0);  // Enable the GPIOA clock
	
	GPIOA->MODER |= (1<<10);  // pin PA5(bits 11:10) as Output (01)
	  
	GPIOA->OTYPER &= ~(1<<5);  // bit 5=0 --> Output push pull
	GPIOA->OSPEEDR |= (1<<11);  // Pin PA5 (bits 11:10) as Fast Speed (1:0)
	GPIOA->PUPDR &= ~((1<<10) | (1<<11));  // Pin PA5 (bits 11:10) are 0:0 --> no pull up or pulldown
}

	


int main (void)
{
	SysClockConfig ();
	TIM6Config ();
	GPIOConfig ();
		
	while (1)
	{
		GPIOA->BSRR |= (1<<5); // Set the Pin PA5
		Delay_ms (250);
		GPIOA->BSRR |= (1<<5) <<16;  // Clear the Pin PA5
		Delay_ms (250);
	}
	
}
