/*!
 ******************************************************************************
 * @File Name          : task.c
 * @Description        : kernel task source file
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f7xx_hal.h"
#include "task.h"


 
/* os tick event, each 1ms */
uint8_t tick_event;
/* global struct with all os tasks created */
task_t * task_list[ZEPTO_N_TASKS];


/*!
 * @Functions:
 */
 
/*!
 * @brief:		Alloc memory for new task. calloc() used                                    
 *
 * @param[in]:	new_task item 
 * @param[in]:	task counter.                        
 * @return: 	status of memory allocation.
 **/
os_status_t task_alloc (task_t * new_task[], uint8_t task_cnt)
{
    new_task[task_cnt] = (task_t *) calloc(1, sizeof(task_t));
    
    if(new_task[task_cnt] == NULL)                     
    {
        printf("Error! memory not allocated for task %d,",task_cnt);
        return OS_ERR_NO_MEM;
    }
 
    return OS_SUCCESS;
}

/*!
 * @brief:		Create task, add new task params to task_t task_list structure used in scheduler.
 *              Index task_list structure with static task_cnt which should be incremented at each new_task creation.                           
 *
 * @param[in]:	task name.
 * @param[in]:	running time of a task in ms.
 * @param[in]:	task priority.
 * @param[in]:	callback to the new task function.                            
 * @return: 	status of task creation.
 **/
os_status_t create_task (char * task_name, os_kernel_priority_t task_priority, uint16_t running_time, void (*callback))
{
    static uint8_t task_cnt = 0;
    
    if (task_alloc (task_list, task_cnt) == OS_ERR_NO_MEM)
    {
        return OS_ERR_NO_MEM;
    }
    else
    {
        task_list[task_cnt]->task_name = task_name;
        task_list[task_cnt]->running_time = running_time;
        task_list[task_cnt]->priority = task_priority;
        task_list[task_cnt]->func_p = callback;
        task_list[task_cnt]->state = NEW;
    
        task_cnt++; // task has been alocated, increment task_cnt to next task.
    }
    
    return OS_SUCCESS;
}

/*!
 * @brief:		Create child task, of a task_t * parent_task. calloc() is used to alloc mem for child task.
 *              Parent task should have MASTER PRIORITY to afford child creation.                            
 *
 * @param[in]:	parent task.
 * @param[in]:	task_name string.
 * @param[in]:	running time of a task in ms.
 * @param[in]:	callback to the new task function.                            
 * @return: 	status of task creation.
 **/
os_status_t create_child_task (task_t * parent_task, char * task_name, uint16_t running_time, void (*callback))
{
    /*  ONLY TASKS WITH MASTER PRIORITY MAY HAVE CHILD TASK.
     *  Check if parent priority is MASTER_PRI... else reject child mem alocation and return PRIORITY_ERR, 
     */
    if (parent_task->priority == OS_MASTER_PRIORITY)
    {
        parent_task->child_task = calloc(1, sizeof(task_t));
        
        if(parent_task->child_task == NULL)                     
        {
            printf("Error! memory not allocated for task %s,",task_name);
            return OS_ERR_NO_MEM;
        }
        
        parent_task->child_task->task_name = task_name;
        parent_task->child_task->running_time = running_time;
        parent_task->child_task->priority = OS_SLAVE_PRIORITY;
        parent_task->child_task->func_p = callback;
        parent_task->child_task->state = NEW;
    }
    else
    {
        return OS_ERR_PRIORITY;
    }        
    
}

/*!
 * @brief:      Delete task through checking of given task name in task_list.
 *                                         
 * @param[in]:  task_name string.              
 * @return:     status of deletion.
 **/
os_status_t delete_task (char * task_name)
{
    uint8_t task_cnt = 0;
    
    /*  cycle until no pointer to heap found (task_list[task_cnt] != 0) */
	for (task_cnt = 0; task_list[task_cnt] != 0; task_cnt++)
	{
        // Init task timer with offset + running_time value.
		if (strcmp(task_list[task_cnt]->task_name, task_name) == TASK_MATCH)
        {
            // Task match.
            free(task_list[task_cnt]);
            return OS_SUCCESS;
        }
	}
    
    return OS_NO_TASK_FOUND;
}
                              
/*!
 * @brief:		Init Scheduler. 
 *
 * @param[in]:	none
 * @return: 	none
 **/
void init_scheduler (void)
{
	uint8_t task_cnt;

    /*  cycle until no pointer to heap found (task_list[task_cnt] != 0) */
	for (task_cnt = 0; task_list[task_cnt] != 0; task_cnt++)
	{
        // Init task timer with offset + running_time value.
		task_list[task_cnt]->timer = task_list[task_cnt]->offset + task_list[task_cnt]->running_time;
	}
}

/*!
 * @brief:		Start execution of tasks.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void start_kernel (void)
{
	uint8_t task_cnt;

	if(tick_event == PEND_SWITCH_CONTEXT)
	{
        /*  cycle until no pointer to heap found (task_list[task_cnt] != 0) */
		for(task_cnt = 0; task_list[task_cnt] != 0; task_cnt++)
		{
            // timer value of task has been decremented to 0, task is running state.
			if(task_list[task_cnt]->state == RUNNING)
			{
				task_list[task_cnt]->func_p();
                // ste task to dead state to avoid multiple execution in time.
				task_list[task_cnt]->state = DEAD;  
			}
		}

		tick_event = CLEAR_SWITCH_CONTEXT;
	}

    /*!
    *   @TODO: add forever loop in a task body implementation.
    *   idle_task function has the lowest priority, but in this scheduler policy,
    *   this function will even a task is active, after task execution cause task at this moment,
    *   don't have implemented while(1) forever loop in their body.
    */
	idle_task();
}

/*!
 * @brief:		Check for a context switching. 
 *              Update time of tasks trough decrementing duration/timer value.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void update_timer_task(void)
{
	uint8_t task_cnt;

	for(task_cnt = 0; task_list[task_cnt] != 0; task_cnt++)
	{
        /*  timer value of task has been decremented. Set task to running state. Pend switch context */
		if(task_list[task_cnt]->timer == 0)
		{
			task_list[task_cnt]->state = RUNNING;
			tick_event = PEND_SWITCH_CONTEXT;
		}
        
        /*  Decrement running time (duration) of a task*/
		if(task_list[task_cnt]->timer != 0)
		{
			task_list[task_cnt]->timer = task_list[task_cnt]->timer - 1;
		}
		else
		{
			task_list[task_cnt]->timer = task_list[task_cnt]->running_time - 1;
		}
	}
}

/*  tasks functions ******************************************************/

/*!
 * @brief:		idle_task
 * @param[in]:	none
 * @return: 	none
 **/
void idle_task (void)
{
	;
}

/*!
 * @brief:		1 ms task
 * @param[in]:	none
 * @return: 	none
 **/
void task_1ms (void)
{
	;
}

/*!
 * @brief:		500 ms task
 * @param[in]:	none
 * @return: 	none
 **/
void task_500ms (void)
{
    // Toogle BLUE led of STM32 F676ZI Nucleo 144 board
	HAL_GPIO_TogglePin(GPIOB, LD2_Pin);
}

/*!
 * @brief:		1000 ms task
 * @param[in]:	none
 * @return: 	none
 **/
void task_1000ms (void)
{
    // Toogle RED led of STM32 F676ZI Nucleo 144 board
	HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
}

