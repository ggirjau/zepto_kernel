/*!
 ******************************************************************************
 * @File Name          : timers.h
 * @Description        : kernel timer definition file
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 Ghirjev Gheorghe
 *
 *
 ******************************************************************************
 */
  
  
#ifndef __TIMERS_H
    #define __TIMERS_H
  
/*!
 * @Includes
 */

/*!
 * @Defines
 */
 
/*!
 *  System timer, SysTick
 *  24-bit system timer, that counts down from the reload value to zero, reloads, that is wraps to, 
 *  the value in the SYST_RVR register on the next clock edge, then counts down on subsequent clocks.
 *
 *  When the processor is halted for debugging the counter does not decrement.
 */
 
/*!
 *  From: STM32F7 Series Cortex®-M7 processor programming manual pag 213
 *  System timer registers:
 *
 *  @define            | @value                                         | @type         | @required@privilege
 */
#define SYST_CSR        ( * ( ( volatile uint32_t * ) 0xe000e010 ) )    // RW           | privileged
#define SYST_RVR		( * ( ( volatile uint32_t * ) 0xe000e014 ) )    // RW           | privileged
#define SYST_CVR	    ( * ( ( volatile uint32_t * ) 0xe000e018 ) )
#define NVIC_SYSPRI2_REG				( * ( ( volatile uint32_t * ) 0xe000ed20 ) )

#define SYST_CSR_TICKINT_BIT	    ( 1UL << 1UL )
#define SYST_CSR_ENABLE_BIT			( 1UL << 0UL )
#define SYST_CSR_COUNT_FLAG_BIT		( 1UL << 16UL )
/* Ensure the SysTick is clocked at the same frequency as the core. */
#define SYST_CSR_CLKSOURCE_BIT	    ( 1UL << 2UL )
#define PENDSVCLEAR_BIT 			( 1UL << 27UL )
#define PEND_SYSTICK_CLEAR_BIT		( 1UL << 25UL )

/*!
 * @Functions
 */

/*!
 * @brief:		Setup the SysTick timer to generate the tick interrupts at the required frequency.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void cfg_systick_irq (void);

#endif  //END of TIMERS HEADER FILE


