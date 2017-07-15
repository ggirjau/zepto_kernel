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
#include "kernel_sys_cfg.h"
 
/*!
 * @Defines
 */
#define ZEPTO_N_TASKS           (21)
#define TASK_AMOUNT             (GET_N_ELEMENT_OF(task_list))
#define GET_N_ELEMENT_OF(a)     (sizeof(a) / sizeof(*a))
#define PEND_SWITCH_CONTEXT     (1)
#define CLEAR_SWITCH_CONTEXT    (0)
#define TASK_MATCH              (0) 
 
 
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

struct task_node 
{
    char * task_name;
    uint8_t priority : 4;
    
    uint16_t running_time;
    uint16_t offset;
    uint16_t timer;
    
    task_state_t state;                 // NEW, RUNNING...
    void (*func_p)();                   // call back of a new task.
    
    struct task_node * child_task;      // create a task child.
};
 
typedef struct task_node task_t;


/*!
 * @Functions
 */

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
os_status_t create_task (char * task_name, os_kernel_priority_t task_priority, uint16_t running_time, void (*callback));

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
os_status_t create_child_task (task_t * parent_task, char * task_name, uint16_t running_time, void (*callback));

/*!
 * @brief:      Delete task through checking of given task name in task_list.
 *                                         
 * @param[in]:	task_name string.              
 * @return: 	status of deletion.
 **/
os_status_t delete_task (char * task_name);

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

