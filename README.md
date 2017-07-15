Zepto Kernel

Only for self improvement and deep learning of a real time kernel programming, Zeprto Kernel -  a minimal kernel ower cortex m7 MCU
The project is on build state, so there are a lot of TODO to be implemented.

Concept:

    * Max 21 task supported, stored in an array of pointers to task_t structure.
    * Priorities for tasks.
    * (MASTER priority) Tasks may have only one CHILD task with a predefined SLAVE priority.
    * (Master - Slave) priority for parent - child tasks.  

The main purpose of this project is to build a minimal RTOS kernel with maximum supported 21 tasks: Tasks are stored in an array of pointers to task_t structure: task_t * task_list[ZEPTO_N_TASKS];
Only Master priority Tasks may have cild task. 

Getting Started

Generate a clean project in Cube Mx or create arm project in any other tools.
In main() function call the kernel_init () function to init the kernel task_t structure and other, call the create_task() function to create own tasks. 
In while loop call the start_kernel () function to start tasks execution.
Prerequisite

HW

tested on STM32 F676ZI Nucleo 144.

Built With

KeilUvision 5
Cube Mx
Eclipse + arm_none_eabi


Versioning

Git was used as version control. Current version of SW 1.0

Authors

Gheorghe Ghirjev - Embedded C/C++ developer.

License

This project is free license.



