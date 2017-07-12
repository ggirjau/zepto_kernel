/*!
  ******************************************************************************
  * @File Name          : timers.c
  * @Description        : kernel timer source file
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 Ghirjev Gheorghe
  *
  *
  ******************************************************************************
  */
  
  
/*!
  * @Includes
  */
#include "timers.h"
#include "kernel_sys_cfg.h"
#include "mcu_port_cfg.h"
#include "task.h"




/*!
 * @brief:		Setup the SysTick timer to generate the tick interrupts at the required frequency.
 *
 * @param[in]:	none
 * @return: 	none
 **/
#if CHANGE_DEFAULT_TICK_CFG == TRUE

void cfg_systick_irq( void )
{
    /* Configure SysTick to interrupt at the requested rate. */
    SYST_RVR = ( GET_CPU_CLK_HZ / TICK_RATE_HZ ) - 1UL;
    SYST_CSR = ( SYST_CSR_CLKSOURCE_BIT | SYST_CSR_TICKINT_BIT | SYST_CSR_ENABLE_BIT );
}

#endif // end of CHANGE_DEFAULT_TICK_CFG macro

/*!
 * @brief  SYSTICK callback.
 * @retval None
 */
void HAL_SYSTICK_Callback(void)
{
    // Check for a context switching.
    update_timer_task();
}


