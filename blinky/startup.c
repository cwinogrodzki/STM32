#define SRAM_START (0x20000000U)
#define SRAM_SIZE (32U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

#include <stdint.h>
#define ISR_VECTOR_SIZE_WORDS 114
#define DUMMY __attribute__ ((weak, alias ("default_handler")))

//cortex m0 handlers
void reset_handler(void);
void default_handler(void);
DUMMY void nmi_handler(void);
DUMMY void hard_fault_handler(void);
DUMMY void svcall_handler(void);
DUMMY void pendsv_handler(void);
DUMMY void systick_handler(void);
DUMMY void IRQ0_handler(void);
DUMMY void IRQ1_handler(void);
DUMMY void IRQ2_handler(void);
//device handlers
DUMMY void wwdg_handler(void);
DUMMY void rtc_handler(void);
DUMMY void flash_handler(void);
DUMMY void rcc_handler(void);
DUMMY void exti0_1_handler(void);
DUMMY void exti2_3_handler(void);
DUMMY void exti4_15_handler(void);
DUMMY void dma1_stream1_handler(void);
DUMMY void dma1_stream2_3_handler(void);
DUMMY void dma1_stream4_5_handler(void);
DUMMY void adc_handler(void);
DUMMY void tim1_brk_up_trg_com_handler(void);
DUMMY void tim1_cc_handler(void);
DUMMY void tim3_handler(void);
DUMMY void tim6_handler(void);
DUMMY void tim14_handler(void);
DUMMY void tim15_handler(void);
DUMMY void tim16_handler(void);
DUMMY void tim17_handler(void);
DUMMY void i2c1_handler(void);
DUMMY void i2c2_handler(void);
DUMMY void spi1_handler(void);
DUMMY void spi2_handler(void);
DUMMY void usart1_handler(void);
DUMMY void usart2_handler(void);
DUMMY void usart3_4_5_6_handler(void);
DUMMY void usb_handler(void);

uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
  STACK_POINTER_INIT_ADDRESS,
  (uint32_t)&reset_handler,
  (uint32_t)&nmi_handler,
  (uint32_t)&hard_fault_handler,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  (uint32_t)&svcall_handler,
  0,
  0,
  (uint32_t)&pendsv_handler,
  (uint32_t)&systick_handler,
  //device   
  (uint32_t)&wwdg_handler,
  0, //reserved
  (uint32_t)&rtc_handler,
  (uint32_t)&flash_handler,
  (uint32_t)&rcc_handler,
  (uint32_t)&exti0_1_handler,
  (uint32_t)&exti2_3_handler,
  (uint32_t)&exti4_15_handler,
  0, //reserved
  (uint32_t)&dma1_stream1_handler,
  (uint32_t)&dma1_stream2_3_handler,
  (uint32_t)&dma1_stream4_5_handler,
  (uint32_t)&adc_handler,
  (uint32_t)&tim1_brk_up_trg_com_handler,
  (uint32_t)&tim1_cc_handler,
  0, //reserved
  (uint32_t)&tim3_handler,
  (uint32_t)&tim6_handler,
  0, //reserved
  (uint32_t)&tim14_handler,
  (uint32_t)&tim15_handler,
  (uint32_t)&tim16_handler,
  (uint32_t)&tim17_handler,
  (uint32_t)&i2c1_handler,
  (uint32_t)&i2c2_handler,
  (uint32_t)&spi1_handler,
  (uint32_t)&spi2_handler,
  (uint32_t)&usart1_handler,
  (uint32_t)&usart2_handler,
  (uint32_t)&usart3_4_5_6_handler,
  0, //reserved
  (uint32_t)&usb_handler
};

void default_handler(void)
{
  while(1);
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

void reset_handler(void)
{
  // Copy .data from FLASH to SRAM
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_etext;
  uint8_t *sram_data = (uint8_t*) &_sdata;

  for (uint32_t i = 0; i < data_size; i++)
  {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < bss_size; i++)
  {
    bss[i] = 0;
  }

  main();
}
