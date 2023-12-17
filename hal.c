 #include "stm32f10x.h"              // Device header
#include "hal.h"

void HAL_GPIO_init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_Init)
{
	GPIO_TypeDef  rezo = {0};
	//enable port
	if(GPIOx == GPIOA)
	{
		RCC->APB2ENR |= (1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2ENR |= (1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2ENR |= (1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2ENR |= (1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2ENR |= (1<<6);
	}
	//configuration input or output of pin
	if(GPIO_Init->GPIO_Pin <=7)
		{
			if((GPIO_Init->GPIO_Speed != OUTPUT_SPEED_2MHZ) && (GPIO_Init->GPIO_Speed != OUTPUT_SPEED_10MHZ) && (GPIO_Init->GPIO_Speed != OUTPUT_SPEED_50MHZ))//mode input
			{
					GPIOx->CRL &= ~(0x0C << (GPIO_Init->GPIO_Pin * 4));
					GPIOx->CRL |= GPIO_Init->GPIO_Mode << (GPIO_Init->GPIO_Pin * 4);
			}
			else if((GPIO_Init->GPIO_Speed == OUTPUT_SPEED_2MHZ) || (GPIO_Init->GPIO_Speed == OUTPUT_SPEED_10MHZ) || (GPIO_Init->GPIO_Speed == OUTPUT_SPEED_50MHZ))//mode output
			{
					GPIOx->CRL &= ~(0x0F<<(GPIO_Init->GPIO_Pin * 4));
					GPIOx->CRL |= ((GPIO_Init->GPIO_Mode << 2) | GPIO_Init->GPIO_Speed) << (GPIO_Init->GPIO_Pin * 4);
			}
		}
	else if(GPIO_Init->GPIO_Pin >7)
		{
			if((GPIO_Init->GPIO_Speed != OUTPUT_SPEED_2MHZ) && (GPIO_Init->GPIO_Speed != OUTPUT_SPEED_10MHZ) && (GPIO_Init->GPIO_Speed != OUTPUT_SPEED_50MHZ) )//mode input
			{
					GPIOx->CRH &= ~(0x0C << (GPIO_Init->GPIO_Pin * 4));
					GPIOx->CRH |= GPIO_Init->GPIO_Mode << (GPIO_Init->GPIO_Pin * 4);
			}
			else if((GPIO_Init->GPIO_Speed == OUTPUT_SPEED_2MHZ) || (GPIO_Init->GPIO_Speed == OUTPUT_SPEED_10MHZ) || (GPIO_Init->GPIO_Speed == OUTPUT_SPEED_50MHZ))//mode output
			{
					GPIOx->CRH &= ~(0x0F<<(GPIO_Init->GPIO_Pin * 4));
					GPIOx->CRH |= ((GPIO_Init->GPIO_Mode<<2) | GPIO_Init->GPIO_Speed) << (GPIO_Init->GPIO_Pin * 4);
			}
		}
		if(GPIO_Init->GPIO_Pull == PULL_UP)
		{
				GPIOx->BSRR = (1<< GPIO_Init->GPIO_Pin);
			//GPIOB->BSRR = GPIO_BSRR_BS0;
		}
		else if(GPIO_Init->GPIO_Pull == PULL_DOWN)
		{
				GPIOx->BSRR = (1<< (GPIO_Init->GPIO_Pin +16));
		}
	
		//configuration interrupt
		HAL_GPIO_Init_Interrupt(GPIOx, GPIO_Init);
		
		//*GPIOx = rezo;
		
}

void HAL_GPIO_Init_Interrupt(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_Init)
{
	//port select to choice interrupt 9.4.1 manual reference
	int PORT_Select = 0;
	if(GPIOx == GPIOA)
	{
		PORT_Select = 0;
	}
	else if(GPIOx == GPIOB)
	{
		PORT_Select = 1;
	}
	else if(GPIOx == GPIOC)
	{
		PORT_Select = 2;
	}
	else if(GPIOx == GPIOD)
	{
		PORT_Select = 3;
	}
	else if(GPIOx == GPIOE)
	{
		PORT_Select = 4;
	}

	if(GPIO_Init->GPIO_IT == GPIO_IT_RISING)
	{
			__disable_irq();
			RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
			if(GPIO_Init->GPIO_Pin <=  3)
			{
				AFIO->EXTICR[0] &= ~(0x0F << (GPIO_Init->GPIO_Pin * 4));
				AFIO->EXTICR[0] |= (PORT_Select << (GPIO_Init->GPIO_Pin * 4));
				
				EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
				
				EXTI->RTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
				EXTI->FTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
			}
			else if((GPIO_Init->GPIO_Pin <= 7) && (GPIO_Init->GPIO_Pin > 3))
			{
				AFIO->EXTICR[1] &= ~(0x0F << ((GPIO_Init->GPIO_Pin - 4)*4));
				AFIO->EXTICR[1] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 4)*4));
				EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
				
				EXTI->RTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
				EXTI->FTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
			}
			else if((GPIO_Init->GPIO_Pin <= 11) && (GPIO_Init->GPIO_Pin > 7))
			{
				AFIO->EXTICR[2] &= ~(0x0F << ((GPIO_Init->GPIO_Pin - 8)*4));
				AFIO->EXTICR[2] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 8)*4));
				EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
				
				EXTI->RTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
				EXTI->FTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
			}
			else if((GPIO_Init->GPIO_Pin <= 15) && (GPIO_Init->GPIO_Pin > 11))
			{
				AFIO->EXTICR[3] &= ~(0x0F << ((GPIO_Init->GPIO_Pin - 12)*4));
				AFIO->EXTICR[3] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 12)*4));
				EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
				
				EXTI->RTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
				EXTI->FTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
			}
			__enable_irq();
		}
		else if(GPIO_Init->GPIO_IT == GPIO_IT_FALLING)
		{
				__disable_irq();
				RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
				if(GPIO_Init->GPIO_Pin <=  3)
				{
					AFIO->EXTICR[0] &= ~(0x0F << (GPIO_Init->GPIO_Pin * 4));
					AFIO->EXTICR[0] |= (PORT_Select << (GPIO_Init->GPIO_Pin * 4));
					EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
					
					EXTI->FTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
					EXTI->RTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
				}
				else if((GPIO_Init->GPIO_Pin <= 7) && (GPIO_Init->GPIO_Pin > 3))
				{
					AFIO->EXTICR[1] &= ~(0x0F << ((GPIO_Init->GPIO_Pin - 4)*4));
					AFIO->EXTICR[1] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 4)*4));
					EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
					
					EXTI->FTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
					EXTI->RTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
				}
				else if((GPIO_Init->GPIO_Pin <= 11) && (GPIO_Init->GPIO_Pin > 7))
				{
					AFIO->EXTICR[2] &= ~(0x0F << ((GPIO_Init->GPIO_Pin - 8)*4));
					AFIO->EXTICR[2] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 8)*4));
					EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
					
					EXTI->FTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
					EXTI->RTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
				}
				else if((GPIO_Init->GPIO_Pin <= 15) && (GPIO_Init->GPIO_Pin > 11))
				{
					AFIO->EXTICR[3] &= ~(0x0F << (((GPIO_Init->GPIO_Pin - 12)*4)));
					AFIO->EXTICR[3] |= (PORT_Select << ((GPIO_Init->GPIO_Pin - 12)*4));
					EXTI->IMR |= (1 << GPIO_Init->GPIO_Pin);   // Enable the interrupt for EXTI0
					
					EXTI->FTSR |= (1 << GPIO_Init->GPIO_Pin);  // Enable falling edge trigger for EXTI0
					EXTI->RTSR &= ~(1 << GPIO_Init->GPIO_Pin); // Make sure the rising edge is not enabled for EXTI0
				}
				__enable_irq();
		}
		
}
void HAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint32_t pin, uint8_t PinState)
{
	if(PinState == GPIO_PIN_RESET)
	{
		GPIOx->ODR ^= (1<<pin);
	}
	else if(PinState == GPIO_PIN_SET)
	{
		GPIOx->ODR |= (1<<pin);
	}
}

uint8_t HAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint32_t pin)
{
	uint8_t state=0;
	state = GPIOx->IDR & (1<<pin);
	return state;
}

void HAL_GPIO_TogglePin(GPIO_TypeDef * const GPIOx, uint32_t pin)
{
	 GPIOx->BSRR = ((GPIOx->ODR & (1<<pin)) << 16u) | (~(GPIOx->ODR) & (1<<pin));
}