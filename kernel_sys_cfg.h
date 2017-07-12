/*!
 ******************************************************************************
 * @File Name          : kernel_sys_cfg.h
 * @Description        : kernel system config definition file
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 Ghirjev Gheorghe
 *
 *
 ******************************************************************************
 */
  
#ifndef __KERNEL_SYS_CFG_H
    #define __KERNEL_SYS_CFG_H
  
/*!
 * @Includes
 */
  
/*!
 * @Defines
 */
#define FALSE                       (0)
#define TRUE                        (!FALSE)
 
#define CHANGE_DEFAULT_TICK_CFG      (TRUE)
 
/*
 * System kernel Priorities used for thread control.
 * These defines shall not be changed !
 */
typedef enum  
{
    OS_KERNEL_PRIORITY      = 6,    // realtime (highest) priority.
    OS_HIGH_PRIORITY        = 5,    // high priority.
    OS_MASTER_PRIORITY      = 4,    // master priority.
    OS_SLAVE_PRIORITY       = 3,    // slave priority.
    OS_MIDDLE_PRIORITY      = 2,    // medium priority
    OS_LOW_PRIORITY         = 1,    // low_priority. Not the lowest!
    OS_IDLE_PRIORITY        = 0,    // idle (lowest) priority
    OS_UNDEFINED_PRIORITY   = 0x55  // system cannot determine priority or thread has illegal priority
} os_kernel_priority_t;

/*
 * Status code values returned by kernel os functions.
 * These defines shall not be changed !
 */

typedef enum  
{
    OS_SUCCESS          = 0,    // function completed; no error or event occurred.
    OS_ERROR            = 1,    // unspecified run-time kernel os error.   
    OS_ERR_PRIORITY     = 0x55, // system cannot determine priority or thread has illegal priority.
    OS_EVENT_TIMEOUT    = 0x20, // function completed; timeout occurred.
    OS_ERR_NO_MEM       = 0x21, // system is out of memory: it was impossible to allocate or reserve memory for the operation.
} os_status_t;

#endif // END OF KERNEL_SYS_CFG HEADER FILE

