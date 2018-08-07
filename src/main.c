#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"
#include "stm32f4xx_conf.h"
#include "tm_stm32f4_usb_vcp.h"

extern void initialise_monitor_handles(void);

// Private variables
volatile uint32_t time_var1;
volatile uint32_t time_var2;

/*
 * Called from systick handler
 */
void timing_handler() 
{
  printf("in timing handler");
  if (time_var1) 
  {
	  time_var1--;
  }

  time_var2++;
}

/*
 * Dummy function to avoid compiler error
 */
void _init() 
{

}

void init_gpio()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  // GPIO D Periph clock enable
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  // GPIO D
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void init() 
{   
  if (SysTick_Config(SystemCoreClock / 1000)) 
  {
      while (1) 
      { 
      }
  }

  init_gpio();
}

int main(void) 
{
    initialise_monitor_handles();
    init();

    TM_USB_VCP_Init();

    printf("In main\n");
    GPIO_SetBits(GPIOD, GPIO_Pin_15);

    uint8_t c;
    while(1) 
    {
        if(TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) 
        {
           GPIO_SetBits(GPIOD, GPIO_Pin_12);
            GPIO_ResetBits(GPIOD, GPIO_Pin_14);
            if(TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK)
            {
                TM_USB_VCP_Putc(c);
                GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
            }
        }
        else 
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_14);
            GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        }      
    }
}
