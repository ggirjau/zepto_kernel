/*!
  ******************************************************************************
  * @File Name          : kernel_init.c
  * @Description        : kernel init source file. Call all init functions in this module.
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
#include <string.h>
#include "kernel_init.h"
#include "task.h"

// global struct with all os tasks created
extern task_t * task_list;

/*!
 * @brief       Clear task_list structure, to avoid garbage.
 * @param[in]   none.
 * @return      none.
 */
void clear_task_list (void)
{
    memset((task_t *)&task_list, 0x00, sizeof(task_list[ZEPTO_N_TASKS]));
}

/*!
 * @brief       Call all init functions into this fuction.
 * @param[in]   none.
 * @return      status of type os_status_t.
 */
os_status_t kernel_init (void)
{
    // TODO: call here all init functions
    
    // Init task_t task_list structure with running time and offset.
    init_scheduler ();
    return OS_SUCCESS;
}


