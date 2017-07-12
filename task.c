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
#include "stm32f7xx_hal.h"
#include "task.h"

 
 
 
 /* task scheduler declarations: */
uint8_t tick_event;
task_t * task_list;

#if 0
task_t tasks[TASK_AMOUNT] = {
							  	  {1, 0, 0, NEW, task_1ms}, 		// every 1ms
								  {5, 0, 0, NEW, task_5ms},			// every 5ms
								  {10,0,0, NEW, task_10ms}, 	 	// every 10ms
								  {30,0,0, NEW, task_30ms},			// every 20ms
								  {100,0,0, NEW, task_100ms},   	// every 100ms
								  {1000,0,0, NEW, task_1000ms} 		// every 1000ms
							  };
#endif




/*!
 * @brief:		Create task, add new task params to task_t task_list structure used in scheduler.
 *              Index task_list structure with static task_cnt which should be incremented at each new_task creation.                           
 *
 * @param[in]:	running time of a task in ms.
 * @param[in]:	callback to the new task function.                            
 * @return: 	none
 **/
void create_task (uint16_t running_time_ms, void (*callback))
{
    static uint8_t task_cnt = 0;
    
    task_list[task_cnt].duration = running_time_ms;
    task_list[task_cnt].state = NEW;
    task_list[task_cnt].func_p = (void *)&callback;
    
    task_cnt++;
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

	for (task_cnt = 0; task_cnt < TASK_AMOUNT; task_cnt++)
	{
		task_list[task_cnt].timer = task_list[task_cnt].offset + task_list[task_cnt].duration;
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
		for(task_cnt = 0; task_cnt < TASK_AMOUNT; task_cnt++)
		{
			if(task_list[task_cnt].state == RUNNING)
			{
				task_list[task_cnt].func_p();
				task_list[task_cnt].state = DEAD;
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
 * @brief:		Check for a context switching. Update time of tasks trough decrementing duration/timer value.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void update_timer_task(void)
{
	uint8_t task_cnt;

	for(task_cnt = 0; task_cnt < TASK_AMOUNT; task_cnt++)
	{
        /*  Task has been executed. Switch to other task, pending switch context */
		if(task_list[task_cnt].timer == 0)
		{
			task_list[task_cnt].state = RUNNING;
			tick_event = PEND_SWITCH_CONTEXT;
		}
        
        /*  Decrement running time (duration) of a task*/
		if(task_list[task_cnt].timer != 0)
		{
			task_list[task_cnt].timer = task_list[task_cnt].timer - 1;
		}
		else
		{
			task_list[task_cnt].timer = task_list[task_cnt].duration - 1;
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

