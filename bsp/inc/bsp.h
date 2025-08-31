/*
 * bsp.h
 *
 *  Created on: Aug 31, 2025
 *      Author: Claire Winogrodzki
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "stm32f0xx.h"

/*
 * LED driver functions
 */

void	BSP_LED_Init	(void);
void	BSP_LED_On	(void);
void	BSP_LED_Off	(void);
void	BSP_LED_Toggle	(void);

#endif /* INC_BSP_H_ */
