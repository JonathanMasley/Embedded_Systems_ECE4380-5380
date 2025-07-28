# TTU ECE 4380/5380: Embedded Systems Project

This embedded systems project is implemented for the TI MSP432E401Y LaunchPad development board in conjunction with the TI-BOOSTXL Audio expansion board. The system is built on TI-RTOS and compiled using Code Composer Studio 12.8.0.

The implementation follows a series of embedded systems design principles and requirements established by Dr. Brian Nutter at Texas Tech University's Department of Electrical and Computer Engineering. The project demonstrates real-time operating system concepts, hardware abstraction, peripheral interfacing, and networked embedded systems communication.

## Acknowledgements

This code was developed by Jonathan Masley under the guidance of Dr. Brian Nutter while taking Embedded Systems (ECE 5380) at Texas Tech University. Without his help and feedback, this project would not have been possible. See section [6 Credits](#6-credits) for additional sources and acknowledgements.

## Table of Contents

 &nbsp;&nbsp;&nbsp;&nbsp; [1 Project Setup](#1-project-setup)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.1 Building the Project](#11-building-the-project)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.2 Project Requirements](#12-project-requirements)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3 tirtos_builds Configuration](#13-tirtos_builds-configuration)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3.1 GateSwi Configuration](#131-gateswi-config)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3.2 HeapMem Configuration](#132-heapmem-config)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3.3 Semaphore Configuration](#133-semaphore-config)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3.4 Software Interrupt (Swi) Configuration](#134-swi-config)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.3.5 Task Configuration](#135-task-config)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [1.4 PuTTY Configuration](#14-putty-configuration)

 &nbsp;&nbsp;&nbsp;&nbsp;  [2 Features](#2-features)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.1 General System Interaction](#21-general-system-interaction)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.2 GPIO Control](#22-gpio-control)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.3 Timer Management](#23-timer-management)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.4 Callback Scheduling](#24-callback-scheduling)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.5 Ticker Scheduling](#25-ticker-scheduling)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.6 Script Management](#26-script-management)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.7 Memory and Register Tools](#27-memory-and-register-tools)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.8 Audio Functions](#28-audio-functions)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.9 UART and UDP Connections/Networks](#29-uart-and-udp-connectionnetwork)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.10 Robust Error Tracking](#210-robust-error-tracking)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [2.11 System Use Cases and Summary of Features](#211-system-use-cases-and-summary-of-features)

 &nbsp;&nbsp;&nbsp;&nbsp;  [3 File Structure](#3-file-structure)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [3.1 src\c_header](#31-srcc_header)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [3.2 src\callbacks.c](#32-srccallbacksc)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [3.3 src\infrastructure.c](#33-srcinfrastructurec)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [3.4 src\main_tirtos.c](#34-srcmain_tirtosc)

 &nbsp;&nbsp;&nbsp;&nbsp; [4 Code Overview](#4-code-overview)

 &nbsp;&nbsp;&nbsp;&nbsp; [5 Troubleshooting](#5-troubleshooting)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [5.1 `udpEcho.c` Redundancy](#51-udpechoc-redundancy)

 &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; [5.2 runVoice and Unused Semaphores](#52-runvoicechar-input-and-unused-semaphores)

 &nbsp;&nbsp;&nbsp;&nbsp; [6 Credits](#6-credits)

## 1 Project Setup

### 1.1 Building the Project

Developed using:

* Code Composer Studio 12.8.0
* TI-RTOS for MSP432E4
* "udpecho" canned example from the Resource Explorer.

To build the project:

 1. Import the project into CCS using File > Import > CCS Projects
 2. Connect the MSP432E401Y Launchpad and the TI-BOOSTXL Audio board.
 3. Build and debug!

### 1.2 Project Requirements

* Proper setup of the udpecho.syscfg
* After building the project for the first time, the automatically generated "tirtos_builds_MSP_EXP432E401Y_release_ccs" RTSC project must have the following configuration in its release.cfg (see 1.3 tirtos_builds Configuration)

### 1.3 tirtos_builds Configuration

To edit the "tirtos_builds" configuration, right click the release.cfg file inside the project, click "Open With", and select "XGCONF". Before editing the configuration, add "GateSwi" to the GUI by doing the following:

* Open the "Available Products" window. (This can be found via View > Other > RTSC dropdown > Available Products)
* Inside "Available Products", navigate through Other Products > tirtos > ti > sysbios > gates > GateSwi
* Add the GateSwi module to your configuration (please note that you may have to restart to notice these changes).

Ensure the following modules are inside your release.cfg XGCONF GUI:

1. GateSwi
2. HeapMem
3. Semaphore
4. Swi
5. Task

Add the following resources/instances to your "release.cfg" as outlined in sections 1.3.1, 1.3.2, 1.3.3, 1.3.4, and 1.3.5. While the release.cfg has been attached outside the project folder for import, importing this file directly into tirtos_builds should be done with caution.

### 1.3.1 GateSwi Config

Add 8 gateSwis to the project by right clicking on "GateSwi" and clicking "New GateSwi...". Each GateSwi should be named "gateSwi0", "gateSwi1", "gateSwi2"... No additional configuration is necessary for GateSwis.

### 1.3.2 HeapMem Config

While not used in this program, it is best to add one HeapMem instance to the release.cfg. Right click "HeapMem" and click "New HeapMem...". Keep the default settings on this new HeapMem instance.

### 1.3.3 Semaphore Config

This program requires the use of 6 semaphores (though the VoiceSems are technically not required). Create new Semaphores by right clicking "Semaphore" and clicking "New Seamphore...". Each semaphore instance (enter each instance by clicking on a semaphore) should be named "sem0", "sem1", "sem2", etc; should have an initial conunt of 0; and should have the Semaphore type "counting (FIFO)"

### 1.3.4 Swi Config

The software interrupt (Swi) instances should include the following:

* "swi0" with the function "timer0SWI" and no other changes.
* "swi1" with the function "timer1SWI" and no other changes.
* "swi2" with a function "SWIgpioButtonSw1" and no other changes.
* "swi3" with the function "SWIgpioButtonSw2" and no other changes.
* "swi4" with the function "adcErrorSWI" and no other changes.

### 1.3.5 Task Config

The task instances is the most exhaustive and, arguably, the most important as the functionality of the program relies on the operation of tasks.

* "task0" requires the function "taskAAA" with a priority of 1. Its stack size should be 2048 (though considerably less would also work for this function).
* "task1" requires the function "taskUART0Read" and must have a priority of 2. It should also have a stack size of 2048.
* "task2" requires the function "taskUART0Write" and must have a priority of 3. Its stack size should also be 2048.
* "task3" requires the function "taskADCStream" and must have a priority of 4. Its stack size should also be 2048.
* "task4" requires the function "taskNETUDP" and must have a priority of 5. Its stack size should be 2048.
* "task5" requires the function "taskUART7Read" and must have a priority of 6. Its stack size should be 2048.
* "task6" rqeuires the function "taskPayload" and must have the priority of 7. Its stack size should be 2048.

### 1.4 PuTTY Configuration

After plugging in the board, it will appear in Device Manager under "Ports (COM & LPT)". Make note of which COM the board is utilizing. Once this note has been made, download PuTTY from [PuTTY.org](https://www.putty.org/). Once PuTTY has been installed, open it and create a new configuration. This new configuration should have the following settings selected:

* Under Session:
  * Connection Type: "Serial"
  * Serial line: (aforementioend COM identified in Device Manager) "COM3"
  * Speed: 115200
* Inside "Connection" and under Serial:
  * Specify the Serial line to connect to (aforementioend COM identified in Device Manager) "COM3"
  * Speed (baud): 115200
  * Data bits: 8
  * Parity: 1

## 2 Features

This program hosts the following capabilties:

### 2.1 General System Interaction

* **Help System**
  * `-help`, `-help [command]`: Displays usage guidance for all supported commands.
  * Organized and modular help responses for each command.

* **About**
  * `-about`: Displays metadata about the project and platform.

### 2.2 GPIO Control

* `-gpio [index]`: View status of a specific GPIO pin.
* `-gpio [index] r/w/t`: Read, write, or toggle GPIO pin.
* `-gpio`: View the state of all GPIOs with user-friendly labels.

### 2.3 Timer Management

* `-timer`: View current timer configuration.
* `-timer 0`: Disable the timer.
* `-timer [value] [unit]`: Set timer period in microseconds, milliseconds, seconds, Hz, or raw counts.

### 2.4 Callback Scheduling

* `-callback`: Display all configured callbacks.
* `-callback [index] [count] [payload]`: Configure a callback to run a specific payload multiple times.
* `-callback clr`: Clear all callbacks.

### 2.5 Ticker Scheduling

* `-ticker`: View all ticker timers, their delay/period/payload.
* `-ticker [idx] [delay] [period] [count] [payload]`: Schedule repetitive or one-shot actions.
* `-ticker k/p/r`: Kill, pause, or resume all tickers.

### 2.6 Script Management

* `-script [index] [payload]`: Assign a command payload to a user script index.
* `-script`: View current scripts and their payloads.
* `-if [A B op payload]`: Execute conditionally based on comparison.

### 2.7 Memory and Register Tools

* `-memr [addr]`: Read memory from a specified address.
* `-reg`: View and manipulate simulated software registers.

### 2.8 Audio Functions

* `-sine [freq]`: Generate sine wave output using the DAC.
* `-stream`: Begin streaming local or networked voice.

### 2.9 UART and UDP Connection/Network

* `-uart [payload]`: Send commands via UART7 interface.
* `-netudp`: Execute or configure UDP-based commands.
* `-dial`: Manage multi-device audio call sessions (two-way or three-way).

### 2.10 Robust Error Tracking

* `-error`: View logged error counts and descriptions.

### 2.11 System Use Cases and Summary of Features

* Real-time command/response testing
* Audio streaming and signal generation
* Custom script-based sequencing
* User defined programming enabled via SW -defined registers
* Multinode communication over UART and UDP

## 3 File Structure

The program consists of largely Code Composer Studio-generated files from the TI-RTOS, MSP432E401Y "udpecho" canned example which can be found in the Resource Explorer. Inside this canned example there is a `/src` folder that contains the user-defined code.

### 3.1 `src\c_header`

This file contains the "#include"s for many of the files (except for `udpEcho.c` and `udpEchoHooks.c`). It also includes the macro definitions for the various macros used throughout the program. This file also contains the typedef structs for the various structures in the Global variable list and the structures used in the program. See [4 Code Overview](#4-code-overview) for a description of the global variables. Finally, this code section includes function declarations for each of the functions used in the program.

### 3.2 `src\callbacks.c`

This file contains all of the callback functions that each of hardware interrupts and software interrupts call whenever they're triggered. Anytime a hardware interrupt is entered, it immediately engages a software interrupt to drop it down a priority level and allow future hardware interrupts to be engaged. The following functions are found in the `callbacks.c` file:

```c
void    adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion conversion, *buffer, uint32_t channel, int_fast16_t var);
void    adcErrorSWI(UArg arg0, UArg arg1);
void    timer0Callback();
void    timer1Callback();
void    timer0SWI(UArg arg0, UArg arg1);
void    timer1SWI(UArg arg0, UArg arg1);
void    gpioButtonSw1Callback(uint_least8_t index);
void    SWIgpioButtonSw1(UArg arg0, UArg arg1);
void    gpioButtonSw2Callback(uint_least8_t index);
void    SWIgpioButtonSw2(UArg arg0, UArg arg1);
```

### 3.3 `src\infrastructure.c`

This file is where all the magic happens. All of the functions in this file are what add up to create the majority of the functionalities offered by this program. The infrastrucure program offers global and program initialization via the `void initProgram();` function and driver initialization via the `void initDrivers();` function.

The program also offers output to the console via the `UART_write_protected...();` functions and proper callback, payload, script, ticker, output message, and error  management via the  following functions:

```c
int32_t addCallback(int32_t index, int32_t count, char *payload);
void    addOutMsg(const char *msg, outMsgTypeList type);
void    addPayload(char *input);
int32_t addScript(uint32_t index, char *payload);
void    execPayload(char *input);
int32_t addTicker(int32_t index, uint32_t delay, uint32_t period, int32_t count, char *payload);
char   *getNextInp(char *input, bool printLog);
void    addError(char *input, char *inpError);
```

The program continues by adding command functionality via an assortment of "run" messages that handle user-input commands from "-help" to "-netudp".

Finally, the program has an assortment of output help messages when users prompt them by entering "-help [command]".

### 3.4 `src\main_tirtos.c`

This file serves as the primary entry point for the TI-RTOS application and handles the initialization and launch of the real-time operating system. The key functions include:

```c
int main(void);
void *mainThread(void *arg0);
```

The main thread performs the following critical operations:

* Initializes the Board Support Package (BSP)
* Configures system clocks and peripherals
* Sets up the network stack for UDP communication
* Launches the program initialization sequence
* Starts the RTOS scheduler

This file ties together the hardware initialization, driver setup, and task creation required for the program.

### 3.5 `src\sinlut.c` and `src\sinlut.h`

This file is where the sine function lookup table is stored for use in the `runSine()` function. This was separated largely for aesthetic purposes. Excel was used to generate the Sine lookup table. The table contains 257 entries to allow for proper operation of the sine function.

## 4 Code Overview

The following coding conventions were used:

* camelCase for functions and variables.
* PascalCase for structures and typdef structures.
* SCREAMING_SNAKE_CASE for macro and constant definitions.
* snake_case occasionally for special cases or in use by the canned examples.

*A more detailed code overview has yet to be implemented.*

## 5 Troubleshooting

Only one recorded issue with the program as of 07/28/2025. Please create an issue on the repository if you encounter one.

### 5.1 `udpEcho.c` Redundancy

There exists a redundant check for malformed -voice packets in udpEcho.c that is no longer possible as the buffer has been debugged. See the repository's issues for more details.

### 5.2 `runVoice(char *input);` and Unused Semaphores

There is one unnecessary gateSwi inside the `runVoice(char *input);` function that resides in `src\infrastructure.c` and there are two unused semaphores inside `Global.Bios`.

## 6 Credits

As mentioned above, special thanks to Brian Nutter, PhD at Texas Tech University's Electrical and Computer Engineering Department. Much of the code is referenced firectly from Dr. Brian Nutter's code. Mark Danemiller's repository, [Embedded-ECE4380-MSP432](https://github.com/MarkDannemiller/Embedded-ECE4380-MSP432/tree/main) was also used as a resource during the development of this program. AI platforms including ChatGPT and ClaudeAI were used during the development of this program (though largely for debugging purposes). Additional sources are indicated in the `src\c_header.c` file.
