Zepto Kernel

Only for self improvement and deep learning of a real time kernel programming, Zeprto Kernel -  a minimal kernel ower cortex m7 MCU
The project is on build state, so there are a lot of TODO to be implemented.

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



