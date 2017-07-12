/*!
 ******************************************************************************
 * @File Name          : task.h
 * @Description        : kernel tasks definition file
 ******************************************************************************
 *
 * COPYRIGHT(c) 2017 Ghirjev Gheorghe
 *
 *
 ******************************************************************************
 */
  
  
#ifndef __TASK_H
    #define __TASK_H
  
/*!
 * @Includes
 */
#include <stdint.h>
 
/*!
 * @Defines
 */
#define TASK_AMOUNT             (GET_N_ELEMENT_OF(task_list))
#define GET_N_ELEMENT_OF(a)     (sizeof(a) / sizeof(*a))
#define PEND_SWITCH_CONTEXT     (1)
#define CLEAR_SWITCH_CONTEXT    (0)
 
 
 
 /*
 *	According to http://www.ugrad.cs.ubc.ca/~cs219/CourseNotes/Threads/threads-states.html
 *	define Task states.
 */
typedef enum 
{
    NEW = 0,	//	In this state, the thread is inactive and consumes no CPU cycles.
	RUNNING,	//	A thread is in the runnable state if it is currently running or if it is ready to run.
	BLOCKED,	//	A thread is in the blocked state if it cannot continue execution.
	DEAD		//	A thread is in the dead state if it has completed the code in its run() method or if it terminates abnormally due to an exception.
} task_state_t;
 
typedef struct
{
    uint16_t duration;
	uint16_t offset;
	uint16_t timer;
	task_state_t state;
	void (*func_p)();
} task_t;


/*!
 * @Functions
 */

/*!
 * @brief:		Create task, add new task params to task_t task_list structure used in scheduler.
 *              Index task_list structure with static task_cnt which should be incremented at each new_task creation.                           
 *
 * @param[in]:	running time of a task in ms.
 * @param[in]:	callback to the new task function.                            
 * @return: 	none
 **/
void create_task (uint16_t running_time_ms, void (*callback));

/*!
 * @brief:		Init Scheduler. 
 *
 * @param[in]:	none
 * @return: 	none
 **/
void init_scheduler (void);

/*!
 * @brief:		Check for a context switching. Update time of tasks trough decrementing duration/timer value.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void update_timer_task (void);

/*!
 * @brief:		Start execution of tasks.
 *
 * @param[in]:	none
 * @return: 	none
 **/
void start_kernel (void);

/*tasks functions*/
/* Idle task */
void idle_task (void);

/* 1ms task */
void task_1ms (void);

/* 500ms task */
void task_500ms (void);

/* 1000ms task */
void task_1000ms (void);
 
#endif // END OF TASK FILE

