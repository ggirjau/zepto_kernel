/*!
 ******************************************************************************
 * @File Name          : kernel_init.h
 * @Description        : kernel init definition file
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 Ghirjev Gheorghe
 *
 *
 ******************************************************************************
 */
  
#ifndef __KERNEL_INIT_H
    #define __KERNEL_INIT_H
  
/*!
 * @Includes
 */
#include "kernel_sys_cfg.h"
  
/*!
 * @Defines
 */
 
/*!
 * @Functions
 */
 
/*!
 * @brief       Call all init functions into this fuction.
 * @param[in]   none.
 * @return      status of type os_status_t.
 */
os_status_t kernel_init (void);



#endif // END OF KERNEL_INIT HEADER FILE


