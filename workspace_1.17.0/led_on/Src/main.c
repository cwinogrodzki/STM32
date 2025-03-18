#include <stdint.h>

int main(void)
{
	uint32_t *pClockControlReg = (uint32_t*)0x40021014;
	uint32_t *pGPIOAModeReg = (uint32_t*)0x48000000;
	uint32_t *pGPIADOutReg = (uint32_t*)0x48000014;

    //activate clock for GPIOA peripheral in AHBNENR
	*pClockControlReg |= (1 << 17); //set bit 17 to "1"

	//set GPIOA pin mode to output
	*pGPIOAModeReg &= ~(3 << 10); //clear the 10th and 11th bits
	*pGPIOAModeReg |= (1 << 10);  //set 10th bit to "1"

	//set pin 5 to high (turn on led)
	//*pGPIODOutReg |= (1 << 5); //set bit 5 to "1"

	//toggle the LED
	while(1)
	{
		*pGPIOAOutReg ^= (1 << 5);
		 for (uint32_t i = 0; i < 1000000; i++);
	}
}
