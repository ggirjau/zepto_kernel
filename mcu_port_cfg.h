/*!
  ******************************************************************************
  * @File Name          : mcu_port_cfg.h
  * @Description        : Kernel header port file, to specify MCU defines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 Ghirjev Gheorghe
  *
  *
  ******************************************************************************
  */
  
  
#ifndef  __MCU_PORT_CFG
    #define __MCU_PORT_CFG
  
/*!
 * @Includes
 */
 #include <stdint.h>
//#include "stm32f7xx_hal_rcc.h"
 
/*!
 * @Defines
 */
#define GET_CPU_CLK_HZ      (16000000)   // HAL_RCC_GetSysClockFreq(void)
#define TICK_RATE_HZ        ((uint32_t)1000)              // 1 / 1000 = 1 ms  
  
#endif  // END OF MCU_PORT_CFG HEADER FILE

