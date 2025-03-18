#include <stdint.h>

int main(void)
{
	uint32_t *pClockControlReg = (uint32_t*)0x40021014;
	uint32_t *pGPIOAModeReg = (uint32_t*)0x48000000;
	uint32_t *pGPIOAOutReg = (uint32_t*)0x48000014;

	uint32_t *pGPIOBModeReg = (uint32_t*)0x48000400;
	uint32_t *pGPIOBInReg = (uint32_t*)0x48000410;

	//activate clock for GPIOA, GPIOB peripheral in AHBNENR
	*pClockControlReg |= (3 << 17); //set bit 17 (GPIOAEN) and 18 (GPIOBEN) to "1"

	//set GPIOA pin mode to output
	*pGPIOAModeReg &= ~(3 << 10); //clear the 10th and 11th bits
	*pGPIOAModeReg |= (1 << 10);  //set 10th bit to "1"

	//set GPIOB pin mode to input
	*pGPIOBModeReg &= ~(3 << 0); //clear the 0th and 1st bits

	while(1){
		//read status of PB0
		uint8_t pinStatus = (uint8_t)(*pGPIOBInReg & 0x1); //zero out all bits except position 0 (reads 32 bits but we only need one)

		if(pinStatus){
			*pGPIOAOutReg |= (1 << 5); //turn on LED
		}
		else{
			*pGPIOAOutReg &= ~(1 << 5); //turn off LED
		}
	}
}
