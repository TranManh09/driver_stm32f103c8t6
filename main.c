#include "stm32f10x.h"                  // Device header
#include "hal.h"


void delay(uint32_t mili)
{
	
	while(mili > 0)
	{
		mili--;
	}
}

void NVIC_EnableIrq(uint32_t n)
{
	NVIC->ICPR[n] = (1<<(n%32));
	NVIC->ISER[n] = (1<<(n%32));
	NVIC->IP[n] = 1;
}
void HAL_GPIO_EXTI_Callback(uint32_t pin)
{
	if(pin == 1)
	{
		GPIOA->ODR ^= (1 << 3);
	}
}
void EXTI3_IRQHandler()
{
	 if(((EXTI->PR & (1 << 3)) != 0) && (GPIOA->IDR & (1 << 3)))  // Check if the interrupt is triggered by EXTI4
    {
        EXTI->PR |= 1<<3;  // Clear the pending bit

       // if((GPIOB->IDR & (1 << 0)) != 0)  // Check if PA4 is high
        //{
            HAL_GPIO_EXTI_Callback(1);  // Toggle the state of PA3
        //}
    }
}


void EXTI0_IRQHandler()
{
	  if (((EXTI->PR & (1 << 0)) != 0) && (GPIOB->IDR & (1 << 0)))  // Check if the interrupt is triggered by EXTI0 (PB0)
    {
        EXTI->PR = (1 << 0);  // Clear the pending bit
			HAL_GPIO_EXTI_Callback(1);
//        // Toggle the state of PA3
//        GPIOA->ODR ^= (1 << 3);
    }

}

void EXTI9_5_IRQHandler()
{
	if (((EXTI->PR & (1 << 5)) != 0) && (GPIOA->IDR & (1 << 5)))  // Check if the interrupt is triggered by EXTI0 (PB0)
    {
        EXTI->PR = (1 << 5);  // Clear the pending bit, xóa c? ngat
			HAL_GPIO_EXTI_Callback(1);
//        // Toggle the state of PA3
//        GPIOA->ODR ^= (1 << 3);
    }
}

void EXTI4_IRQHandler(void)
{
    // Ki?m tra xem ng?t có phát sinh t? EXTI4 không
    if (((EXTI->PR & (1 << 4)) != 0) && (GPIOA->IDR & (1 << 4)))
    {
        // Th?c hi?n các hành d?ng b?n mu?n khi nút trên PA4 du?c nh?n
				 EXTI->PR |= (1 << 4);
        // Ð?o tr?ng thái LED trên PA3
        GPIOA->ODR ^= GPIO_ODR_ODR3;

        // Xóa c? ng?t
       
    }
}
void confi_gpio(void)
{
				GPIO_InitTypeDef GPIO_InitStruct = {0};
				GPIO_InitStruct.GPIO_Pin = GPIO_PIN_3;
				GPIO_InitStruct.GPIO_Mode = OUTPUT_PUSH_PULL;
				GPIO_InitStruct.GPIO_Speed = OUTPUT_SPEED_50MHZ;
				GPIO_InitStruct.GPIO_Pull = NO_PULL;
				//GPIO_InitStruct.GPIO_IT = GPIO_IT_RISING;
				HAL_GPIO_init(GPIOA, &GPIO_InitStruct);
				
				
				GPIO_InitStruct.GPIO_Pin = GPIO_PIN_4;
				GPIO_InitStruct.GPIO_Mode = PULL_UP_PULL_DOWN;
				GPIO_InitStruct.GPIO_Speed = 0;
				GPIO_InitStruct.GPIO_Pull = PULL_UP;
				GPIO_InitStruct.GPIO_IT = GPIO_IT_RISING;
				HAL_GPIO_init(GPIOA, &GPIO_InitStruct);
				//NVIC_SetPriority(EXTI0_IRQn, 1, 0);
				NVIC_EnableIRQ(EXTI4_IRQn);
//				
//				GPIO_InitStruct.GPIO_Pin = GPIO_PIN_0;
//				GPIO_InitStruct.GPIO_Mode = PULL_UP_PULL_DOWN;
//				GPIO_InitStruct.GPIO_Speed = 0;
//				GPIO_InitStruct.GPIO_Pull = PULL_UP;
//				GPIO_InitStruct.GPIO_IT = GPIO_IT_RISING;
//				HAL_GPIO_init(GPIOB, &GPIO_InitStruct);
//				//NVIC_SetPriority(EXTI0_IRQn, 1, 0);
//				NVIC_EnableIRQ(EXTI0_IRQn);
}

int main()
{

//	uint8_t i =1;
	confi_gpio();
	//port A
	//RCC->APB2ENR |= 0x00000004;
	//GPIOA->CRL &= 0xFF000FFF;
	//configuration output port A
	//GPIOA->CRL |= 0x00003000;
	//configuration input port A
	//GPIOA->CRL |= 0x00800000;
	
	//GPIOA->ODR |= 0x08;
	HAL_GPIO_WritePin(GPIOA,3,GPIO_PIN_SET);
		//RCC->APB2ENR |= 0x00000008;
	//GPIOB->CRL &= 0xFF000FFF;
	//configuration output port A
	//GPIOB->CRL |= 0x00003000;
	//configuration input port A
	//GPIOB->CRL |= 0x00800000;
//	//port B
//	RCC->APB2ENR |= 0x00000008;
//	GPIOB->CRL &= 0x00000000;
//	//configuration input port B
//	GPIOB->CRL |= 0x00000080;
//	//GPIOB->ODR |= 0x04;
	//GPIOA->BSRR = GPIO_BSRR_BS5;
	//GPIOB->BSRR = GPIO_BSRR_BS5;
//	GPIOB->BSRR = GPIO_BSRR_BS1;
//	
	//RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//	
//	__disable_irq();
//		
//    AFIO->EXTICR[0] &= ~(0x0F << 4);  // Clear the EXTI0 configuration
//    AFIO->EXTICR[0] |= 0x01 << 4;     // Set EXTI0 to be associated with GPIOB

//    EXTI->IMR |= (1 << 1);   // Enable the interrupt for EXTI0
//    EXTI->RTSR |= (1 << 1);  // Enable falling edge trigger for EXTI0
//    EXTI->FTSR &= ~(1 << 1); // Make sure the rising edge is not enabled for EXTI0

//  AFIO->EXTICR[1] &= ~(0x0F << 4);  // Clear the EXTI0 configuration
//  AFIO->EXTICR[1] |= 0x01 << 4;     // Set EXTI0 to be associated with GPIOB
//	EXTI->IMR |= (1<<5); /// Enable the interrupt for EXTI0
//	EXTI->RTSR |= (1<<5);// Generate a system interrupt at the rising edge
//	EXTI->RTSR &= (1<<5);
//	//NVIC_EnableIRQ(EXTI1_IRQn);
//	NVIC_EnableIRQ(EXTI9_5_IRQn);
	//__enable_irq();
		//GPIOC->CRH &= 0xFF0FFFFF;
	//GPIOC->CRH |= 0x00300000;
	//GPIOC->ODR |= 0x2000;


    __enable_irq();
	while(1)
	{
		
		//delay(2000000);
//		if((GPIOA->IDR & (1<<0)))
//		{
//			delay(20);
//		if((GPIOA->IDR & (1<<4)))
//		{
//			if(i==0)
//			{
//				GPIOA->ODR |= 0x08;
//				i=1;
//			}
//			if(i==1)
//			{
//				GPIOA->ODR ^= 0x08;
//				i=0;
//			}
//			
//		}
			
	//	}
}
	return 0;
}

