
#ifndef _DRIVER_H
#define _DRIVER_H
#include "stdint.h"

#define INPUT 0x00u
#define ANALOG_MODE_INPUT 0x0000u
#define FLOATING_INPUT    0x04u
#define PULL_UP_PULL_DOWN 0x08u

#define OUTPUT 0x01u
#define OUTPUT_PUSH_PULL	0x00
#define OPEN_DRAIN_OUTPUT	0x01u
#define AlTERNATE_PUSH_PULL_OUTPUT 0x02u
#define ALTERNATE_OPEN_DRAIN_OUTPUT 0x03u

#define OUTPUT_SPEED_10MHZ 0x01u
#define OUTPUT_SPEED_2MHZ	0x2u
#define OUTPUT_SPEED_50MHZ	0x3u

#define GPIO_IT_RISING 1
#define GPIO_IT_FALLING 2

#define NO_PULL 0
#define PULL_DOWN 1
#define PULL_UP 2



//define pin

#define GPIO_PIN_0                 0
#define GPIO_PIN_1                 1
#define GPIO_PIN_2                 2
#define GPIO_PIN_3                 3
#define GPIO_PIN_4                 4
#define GPIO_PIN_5                 5
#define GPIO_PIN_6                 6
#define GPIO_PIN_7                 7
#define GPIO_PIN_8                 8
#define GPIO_PIN_9                 9
#define GPIO_PIN_10                10
#define GPIO_PIN_11                11
#define GPIO_PIN_13                13
#define GPIO_PIN_14                14
#define GPIO_PIN_15                15
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              0x0000FFFFu /* PIN mask for assert test */

//#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
//#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
//#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
//#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
//#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
//#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
//#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
//#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
//#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
//#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
//#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
//#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
//#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
//#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
//#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
//#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
//#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

//#define GPIO_PIN_MASK              0x0000FFFFu /* PIN mask for assert test */

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;		

typedef struct
{
	uint32_t GPIO_Pin;
	uint32_t GPIO_Mode;
	uint32_t GPIO_Pull;
	uint32_t GPIO_Speed;
	uint32_t GPIO_IT;
	
	
}GPIO_InitTypeDef;
void HAL_GPIO_init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_Init);
void HAL_GPIO_Init_Interrupt(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_Init);
void HAL_GPIO_WritePin(GPIO_TypeDef * GPIOx, uint32_t pin, uint8_t PinState);
uint8_t HAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx, uint32_t pin);
void HAL_GPIO_TogglePin( GPIO_TypeDef * const GPIOx, uint32_t pin);
#endif /*_DRIVER_H*/