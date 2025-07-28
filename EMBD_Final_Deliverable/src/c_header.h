/* Check to see if C_HEADER has already been defined (we don't want multiple instances of Global either) */
#ifndef C_HEADER
#define C_HEADER



/* ================================================================================
 *      C-Header File
 * --------------------------------------------------------------------------------
 *  +   This C-header file also contains all the SOURCES used to develop this proj.
 *  +   This  C-header file contains all of the "#include"s needed to operate the
 *      project. This file also includes all the bios externs.
 *  +   After doing the BIOS externs, macro definitions are made for a majority of the
 *
 *
 *
 * ================================================================================ */





/* ================================================================================
 *      SOURCES
 * --------------------------------------------------------------------------------
 * https://developer.arm.com/documentation/ka003963/latest/#:~:text=The%20__DATE__%20and%20__TIME__%20compiler%20macros%20automatically,are%20convenient%20to%20use%20for%20this%20example.
 * https://stackoverflow.com/questions/11997108/what-does-putty-send-when-i-press-enter-key
 * https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
 * https://stackoverflow.com/questions/14544043/operand-types-are-incompatible-char-and-const-char
 * https://schaumont.dyn.wpi.edu/ece4703b24/_downloads/989f3ffca014054aa3d80f13d7610a58/ccs-for-msp432.pdf
 * https://dev.ti.com/tirex/explore/node?node=A__AC7UNBWx3i6iMAUzzhqKwA__com.ti.SIMPLELINK_MSP432E4_SDK__J4.hfJy__LATEST
 * https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/582291/msp432p401m-stored-variables-in-msp432-flash-memory
 * https://stackoverflow.com/questions/8107826/proper-way-to-empty-a-c-string
 * https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/487784/availability-of-msp432-for-new-product/1762776#1762776
 * https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/486445/msp432-sram-memory-retention-in-lpm3
 * https://www.ti.com/lit/ug/slau748b/slau748b.pdf?ts=1748793094619
 * https://www.ti.com/lit/ds/slasen5/slasen5.pdf?ts=1748763851563
 * https://www.ti.com/lit/ug/slau670a/slau670a.pdf?ts=1748793118952
 * https://github.com/MarkDannemiller/Embedded-ECE4380-MSP432/blob/1ec07b40ef17dd38b7682a07079639a97d0950f4/udpecho_MSP_EXP432E401Y_tirtos_ccs/src/p100.h
 *
 * CODE EXAMPLES PROVIDED BY DR. BRIAN NUTTER
 *
 * ChatGPT (primarily for debugging warnings and errors)
 * ================================================================================ */





/* ================================================================================
 *      INCLUDES
 * --------------------------------------------------------------------------------
 *      Inlcudes all the libraries and files that are used throughout the entire
 *      program. Currently (06/16/2025), no networking has been imported!           */

#include <xdc/std.h>            /* System header */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>            /* POSIX Header files */
#include <math.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>


/* Driver Header files */
#include <ti/drivers/Board.h>   /* RTOS header files */
#include <ti/drivers/UART.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/ADCBuf.h>


/* BIOS Header files */
#include <ti/sysbios/BIOS.h>    /* RTOS header files */
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/gates/GateSwi.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Clock.h>


/* Driver configuration */
#include "ti_drivers_config.h"

/* ================================================================================ */





/* ================================================================================
 *      EXTERNS
 * --------------------------------------------------------------------------------
 *      This section externs all of the BIOS bullshit!                              */

extern Task_Handle      task0;      // This task is for taskAAA
extern Task_Handle      task1;      // This task is for taskUART0Read
extern Task_Handle      task2;      // This task is for taskUART0Write
extern Task_Handle      task3;      // This task is for taskADCStream
extern Task_Handle      task4;      // This task is for taskNETUDP
extern Task_Handle      task5;      // This task is for taskUART7Read
extern Task_Handle      task6;      // This task is for taskPayload

extern Semaphore_Handle sem0;       // UARTWriteSem
extern Semaphore_Handle sem1;       // PayloadSem
extern Semaphore_Handle sem2;       // TickerSem
extern Semaphore_Handle sem3;       // ADCSem
extern Semaphore_Handle sem4;       // VoiceSem0 (used for debugging the destinationChoice0 and destinationChoice1 bug)
extern Semaphore_Handle sem5;       // VoiceSem1 (used for debugging the destinationChoice0 and destinationChoice1 bug)

extern Swi_Handle       swi0;       // Timer0Swi
extern Swi_Handle       swi1;       // Timer1Swi
extern Swi_Handle       swi2;       // SW1_Swi
extern Swi_Handle       swi3;       // SW2_Swi
extern Swi_Handle       swi4;       // ADC_ErrorSwi

extern GateSwi_Handle   gateSwi0;   // Timer
extern GateSwi_Handle   gateSwi1;   // OutMsgGateSwi
extern GateSwi_Handle   gateSwi2;   // Payload
extern GateSwi_Handle   gateSwi3;   // Callback
extern GateSwi_Handle   gateSwi4;   // Ticker
extern GateSwi_Handle   gateSwi5;   // Script
extern GateSwi_Handle   gateSwi6;   // NETUDP
extern GateSwi_Handle   gateSwi7;   // VoiceGateSwi (used for debugging the destinationChoice0 and destinationChoice1 bug)

/* ================================================================================ */





/* ================================================================================
 *      MACRO DEFS
 * --------------------------------------------------------------------------------
 *      The below macros are used for the various components of the program.
 *      Because they're created in the c_header.c, they can be used anywhere in the
 *      program.                                                                    */


/* GENERAL macro */
#define     puts(x)     addOutMsg((x), OUTMSG_N)    // print to console a string WITH a new line
#define     putSL(x)    addOutMsg((x), OUTMSG_SL)   // print to console a string WITHOUT a new line
#define     putB(x)     addOutMsg((x), OUTMSG_BOLD) // print to console a string in BOLD WITH a new line

/* BIOS macro definitions*/
#define     THREADSTACKSIZE          2048
#define     MAX_PAYLOAD_COUNT        32         // Count of the number of payloads that taskPayload will accept until it's out of luck!
#define     MAX_MSG_COUNT            64         // The total number of count msgs that can be lined up in the circular buffer for outmsgs
#define     MAX_NETUDP_COUNT         8          // COunt of the total number of NETUDP payloads out.

/* constant/macro definitions */
#define     BUFFER_SIZE              320
#define     NETUDP_BUFFER_SIZE       320
#define     INP_HISTORY_COUNT        16
#define     NEW_LINE                "\r\n"
#define     BACKSPACE_SEQ           "\b \b"
#define     BOLD_ON                 "\x1b[1m"
#define     BOLD_OFF                "\x1b[0m"
#define     UP_ARROW                "\0x1B[A"
#define     DOWN_ARROW              "\0x1B[B"
#define     RIGHT_ARROW             "\033[C"
#define     LEFT_ARROW              "\033[D"
#define     CLEAR_LINE_RESET        "\033[2K\033[1G\r"
#define     CLEAR_CONSOLE           "\033[2J\033[H"


/* Error macro definitions */
#define     ERR_WRITE_UNSUCCESSFUL  "00a"    // Protected write was unsuccessful
#define     ERR_LOC_NULL            "00b"    // Invlaid or Null location returned
#define     ERR_PARSE               "00c"    // Input command was unrecognized altogether
#define     ERR_BUFF_OVERFLOW       "00d"    // Buffer overflow occurred!
#define     ERR_HELP                "01a"    // Help for a specific command or unrecognized command was unavailable
#define     ERR_MEMR_OUT_OF_RANGE   "02a"    // The input memory address is out of range
#define     ERR_MEMR_INVALID_INP    "02b"    // The memr input is otherwise invalid
#define     ERR_INVALID_GPIO_IDX    "03a"    // Invalid GPIO index
#define     ERR_INVALID_GPIO_OP     "03b"    // Invalid GPIO operation was specified.
#define     ERR_INVALID_GPIO_VAL    "03c"    // Invalid or no GPIO values was specified.
#define     ERR_INVALID_GPIO_WT     "03d"    // Attempted to write/toggle to an invalid index.
#define     ERR_BIOS                "04a"    // Bios Error!
#define     ERR_PAYLOAD_Q_OF        "04b"    // Paylaod Queue overflowed!
#define     ERR_MSG_Q_OF            "04c"    // The output message queue overflowed!
#define     ERR_INVALID_TIMER_PER   "05a"    // If the user doesn't input a proper timer period.
#define     ERR_INVALID_TIMER_UNITS "05b"    // If the user doesn't input a proper unit
#define     ERR_MIN_TIMER_THRESH    "05c"    // THe user-defined period isn't within the timer threshold.
#define     ERR_MAX_TIMER_THRESH    "05d"    // The user-defined period in the -timer instruction was above max threshold.
#define     ERR_INVALID_CB_IDX      "06a"    // If the user offered an invalid! callback index
#define     ERR_INVALID_CB_COUNT    "06b"    // If the user offered an invalid! callback count
#define     ERR_UNSPEC_CB_FUNC      "06c"    // If the user offered an unspecified callback function (will not check if the payload is a viable command in func run...)
#define     ERR_NO_FREE_TKR         "07a"    // If there were no free tickers available when "next open ticker" operation was engaged
#define     ERR_TKR_INVALID_INDEX   "07b"    // If an invalid ticker index was specified.
#define     ERR_TKR_OUT_OF_BOUNDS   "07c"    // If an invalid ticker period or delay was specified.
#define     ERR_INVALID_TKR_COUNT   "07d"    // If an invalid ticker count was specified
#define     ERR_INVALID_TKR_PAYLOAD "07e"    // If an invalid ticker payload was specified
#define     ERR_TKR_ADD_FAILED      "07f"    // If the addTicker function failed to add a ticker (returned non-zero).
#define     ERR_INVALID_REG_IDX     "08a"    // If the user entered an invalid destination register index
#define     ERR_INVALID_OP_CODE     "08b"    // If the user entered an invalid op code or an op code that could not be parsed
#define     ERR_UNSPEC_INVALID_SRCA "08c"    // If the user entered an invalid srcA or FAILED TO SPECIFY a srcA
#define     ERR_UNSPEC_INVALID_SRCB "08d"    // If the user entered an invalid srcB or FAILED TO SPECIFY a srcB
#define     ERR_REG_REM_ZERO        "08e"    // If the user attempted to take the remainder of a div by zero!
#define     ERR_INV_SCRIPT_IDX      "09a"    // If the user entered an invalid script index or if it was unspecified
#define     ERR_INV_SCRIPT_PAYLOAD  "09b"    // If the user entered an invalid script payload
#define     ERR_COND_SA_INVALID     "10a"   // If the srcA in a conditional is invalid or unspecified
#define     ERR_COND_SB_INVALID     "10b"   // If the srcB in a conditional is invalid or unspecified
#define     ERR_COND_OP_INVALID     "10c"   // If the conditional operation is invalid or unspecified
#define     ERR_COND_PD_INVALID     "10d"   // If the conditional PD-T and/or PD-F is invalid or unspecified
#define     ERR_UNSPEC_DELIM        "10e"   // If the user fails to specify a conditional delimiter this error occurs
#define     ERR_INVALID_UART7       "11a"   // If the user failed to specify a payload for the -uart function.
#define     ERR_INVALID_FREQ        "12a"   // If the user entered an invalid frequency (sscanf for freq in -sine failed)
#define     ERR_FREQ_OUT_OF_RANGE   "12b"   // If the user-defined frequnecy was out of range
#define     ERR_VOICE_BUF           "12c"   // If the SPI transaction for the speaker got effed up.
#define     ERR_STREAM_ARG          "13a"
#define     ERR_ADC_BUF_INVALID     "14a"   // If the buffer of the ADCBuf Device failed!
#define     ERR_UNKNOWN_RX_BUF      "14b"   // If the RX_buffer from the ADC got effed up between ping and pong.
#define     ERR_CONV_CANC_FAIL      "14c"
#define     ERR_CONVERT_FAILED      "14d"
#define     ERR_MISSING_DEST_CHOICE "15a"   // destinationChoice not specified during -voice command
#define     ERR_MISSING_BUF_LENGTH  "15b"   // bufferLength was not specified during the -voice command
#define     ERR_DATA_BLOCK_MISMATCH "15c"   // mismatch between -voice specified datablock size and NECESSARY datablock size
#define     ERR_NOT_PINGED          "16a"   // -dial accept or -dial decline was called without a corresponding ping
#define     ERR_ACCEPT_FAILED       "16b"   // -dial accept failed
#define     ERR_DECLINE_FAILED      "16c"   // -dial decline failed
#define     ERR_REQ_FAILED          "16d"   // -dial request ... failed
#define     ERR_UNPROMPTED_RESP     "16e"   // -dial response ... triggered without a prompt
#define     ERR_ALREADY_IN_CALL     "16f"   // Attempting some dial action while already in a call.
#define     ERR_RESP_FAILED         "16g"   // -dial response ... failed.
#define     ERR_CONFIRM_FAILED      "16h"   // -dial confirm ... failed.
#define     ERR_DIAL_REQ_FAILED     "16i"   // User-defined dial request '-dial b1 b2' failed.


/* GPIO macro definitions */
#define     GPIO_COUNT              8           // LEDS 0, 1, 2, 3; PDX Pins 4, 5; Switches 6, 7; Total - 8
#define     FTN_GPIO_READ           0
#define     FTN_GPIO_WRITE          1
#define     FTN_GPIO_TOGGLE         2


/* Callback definitions */
#define     CALLBACK_MAX            64
#define     CALLBACK_COUNT          4


/* TIMER definitions */
#define     MIN_TIMER_PERIOD        100         // In microseconds
#define     MAX_TIMER_PERIOD        37500000    // In microseconds
#define     MAX_TIMER_HZ            10000       // This corresponds to 100 microseconds
#define     MAX_TIMER_PERIOD_COUNT  4294967294  // In ticks of a 120 MHz clock teehee, this corresponds the 0xFFFFFFFE (E just to be safe)

/* TICKER definitions */
#define     TICKER_COUNT            16

/* REGISTER definitions */
#define     REG_COUNT               32

/* SCRIPT definitions */
#define     SCRIPT_COUNT            65
#define     SCRIPT_DISC             8
#define     MAX_SECTION_LINES       8


/* Sine table and Audio definitions */
#define     SINE_LUT_SIZE           257
#define     SINE_LUT_SIZE_MATH      256
#define     SAMPLE_RATE             8000
#define     SAMPLE_PERIOD           125         // In microseconds
#define     DATA_BLOCK_SIZE         128         // Number of samples for each voice/audio packet
#define     DATA_DELAY              8           // How much delay to account for
#define     TX_BUF_COUNT            2           // How many boards expected to connect to a call (# of channels / 2)


/* NETUDP Definitions */
#define     DEFAULT_NET_PORT        1000        // Default port to connect on for NETUDP communication
#define     CALL_INACTIVE           0           // Used during runDial();
#define     CALL_EXPECTING          2
#define     CALL_ACTIVE             1






/* ================================================================================ */




/* ================================================================================
 *      GLOBAL STRUCTURE DEFINITIONS
 * --------------------------------------------------------------------------------
 *      Below are the structures that will be used in the GLOBAL structure. The
 *      Global structure contains many structures within it that organizes its
 *      contents.
 *                                                                                   */
/* This structure contains all the devices and their handlers */
typedef struct _DeviceList {

    UART_Handle     uart0;
    UART_Handle     uart7;

    Timer_Handle    timer0;
    Timer_Handle    timer1;

    SPI_Handle      spi3;

    ADCBuf_Handle   adcBuf;

    char        gpioName[GPIO_COUNT][32];

} deviceList;



/* This structure contains all the parameters */
typedef struct _ParamList {

    UART_Params     uartParams0;
    UART_Params     uartParams7;

    Timer_Params    timerParams0;
    Timer_Params    timerParams1;

    SPI_Params      spiParams3;
    SPI_Transaction spiTransaction3;

    ADCBuf_Params   adcBufParams;

} paramList;



/* This structure contains the constants */
typedef struct _Constants {

} constList;



/* This structure contains the buffers (mainly for memory optimization) */
typedef struct _Buffers {

    char        inpBuff[BUFFER_SIZE];   // Only used for storing all the characters of an input preceding a return
    int         inpIndex;               // Used for logic with the inpBuff
    char        msgBuff[BUFFER_SIZE];   // Used as xmitbuf so a bunch of new xmitbufs aren't created when functions want to be run!
    char        uart7Buff[BUFFER_SIZE]; // NOT CURRENTLY USED (was going to initially be used in a similar implementation to inpBuffer
    char        inpArrowBuffer[INP_HISTORY_COUNT][BUFFER_SIZE];     // Circular buffer used to store remembered user inputs.
    int         inpArrowIndex;

} bufferList;



/* This structure contains the number of each error that occurred. */
typedef struct _Errors  {

/* GENERAL      error counts */
    uint32_t    error0aCount;   // ERR_WRITE_UNSUCCESSFUL
    uint32_t    error0bCount;   // ERR_LOC_NULL
    uint32_t    error0cCount;   // ERR_PARSE
    uint32_t    error0dCount;   // ERR_BUFF_OVERFLOW

/* HELP         error counts */
    uint32_t    error1aCount;   // ERR_HELP
//    uint32_t    error1bCount;
//    uint32_t    error1cCount;
//    uint32_t    error1dCount;

/* MEMR         error counts */
    uint32_t    error2aCount;   // ERR_MEMR_OUT_OF_RANGE
    uint32_t    error2bCount;   // ERR_MEMR_INVALID_INP
//    uint32_t    error2cCount;
//    uint32_t    error2dCount;

/* GPIO         error counts */
    uint32_t    error3aCount;   // ERR_INVALID_GPIO_IDX
    uint32_t    error3bCount;   // ERR_INVALID_GPIO_OP
    uint32_t    error3cCount;   // ERR_INVALID_GPIO_VAL
    uint32_t    error3dCount;   // ERR_INVALID_GPIO_WT

/* BIOS         error counts */
    uint32_t    error4aCount;   // ERR_BIOS
    uint32_t    error4bCount;   // ERR_PAYLOAD_Q_OF
    uint32_t    error4cCount;   // ERR_MSG_Q_OF
//    uint32_t    error4dCount;

/* TIMER        error counts */
    uint32_t    error5aCount;   //  ERR_INVALID_TIMER_PER
    uint32_t    error5bCount;   //  ERR_INVALID_TIMER_UNITS
    uint32_t    error5cCount;   //  ERR_MIN_TIMER_THRESH
    uint32_t    error5dCount;   //  ERR_MAX_TIMER_THRESH

/* CALLBACK     error counts */
    uint32_t    error6aCount;   //  ERR_INVALID_CB_IDX
    uint32_t    error6bCount;   //  ERR_INVALID_CB_COUNT
    uint32_t    error6cCount;   //  ERR_UNSPEC_CB_FUNC
//    uint32_t    error6dCount;

/* TICKERS      error counts */
    uint32_t    error7aCount;   //  ERR_NO_FREE_TKR
    uint32_t    error7bCount;   //  ERR_TKR_INVALID_INDEX
    uint32_t    error7cCount;   //  ERR_TKR_OUT_OF_BOUNDS
    uint32_t    error7dCount;   //  ERR_INVALID_TKR_COUNT
    uint32_t    error7eCount;   //  ERR_INVALID_TKR_PAYLOAD
    uint32_t    error7fCount;   //  ERR_TKR_ADD_FAILED

/* REGISTER     error counts */
    uint32_t    error8aCount;   //  ERR_INVALID_REG_IDX
    uint32_t    error8bCount;   //  ERR_INVALID_OP_CODE
    uint32_t    error8cCount;   //  ERR_UNSPEC_INVALID_SRCA
    uint32_t    error8dCount;   //  ERR_UNSPEC_INVALID_SRCB
    uint32_t    error8eCount;   //  ERR_REG_REM_ZERO

/* SCRIPT       error counts */
    uint32_t    error9aCount;   //  ERR_INV_SCRIPT_IDX
    uint32_t    error9bCount;   //  ERR_INV_SCRIPT_PAYLOAD
//    uint32_t    error9cCount;
//    uint32_t    error9dCount;

/* CONDITIONALS error counts */
    uint32_t    error10aCount;  //  ERR_COND_SA_INVALID
    uint32_t    error10bCount;  //  ERR_COND_SB_INVALID
    uint32_t    error10cCount;  //  ERR_COND_OP_INVALID
    uint32_t    error10dCount;  //  ERR_COND_PD_INVALID
    uint32_t    error10eCount;  //  ERR_UNSPEC_DELIM

/* UART7        error counts */
    uint32_t    error11aCount;  //  ERR_INVALID_UART7
//    uint32_t    error11bCount;
//    uint32_t    error11cCount;
//    uint32_t    error11dCount;

/* SINE         error counts */
    uint32_t    error12aCount;  //  ERR_INVALID_FREQ
    uint32_t    error12bCount;  //  ERR_FREQ_OUT_OF_RANGE
    uint32_t    error12cCount;  //  ERR_VOICE_BUF
//    uint32_t    error12dCount;

/* AUDIO         error counts */
    uint32_t    error13aCount;  //  ERR_STREAM_ARG
//    uint32_t    error13bCount;
//    uint32_t    error13cCount;
//    uint32_t    error13dCount;

/* ADC          error counts */
    uint32_t    error14aCount;  //  ERR_ADC_BUF_INVALID
    uint32_t    error14bCount;  //  ERR_UNKNOWN_RX_BUF
    uint32_t    error14cCount;  //  ERR_CONV_CANC_FAIL
    uint32_t    error14dCount;  //  ERR_CONVERT_FAILED

/* STREAM         error counts */
    uint32_t    error15aCount;  //  ERR_MISSING_DEST_CHOICE
    uint32_t    error15bCount;  //  ERR_MISSING_BUF_LENGTH
    uint32_t    error15cCount;  //  ERR_DATA_BLOCK_MISMATCH
//    uint32_t    error15dCount;

/* DIAL         error counts */
        uint32_t    error16aCount;  //  ERR_NOT_PINGED
        uint32_t    error16bCount;  //  ERR_ACCEPT_FAILED
        uint32_t    error16cCount;  //  ERR_DECLINE_FAILED
        uint32_t    error16dCount;  //  ERR_REQ_FAILED
        uint32_t    error16eCount;  //  ERR_UNPROMPTED_RESP
        uint32_t    error16fCount;  //  ERR_ALREADY_IN_CALL
        uint32_t    error16gCount;  //  ERR_RESP_FAILED
        uint32_t    error16hCount;  //  ERR_CONFIRM_FAILED
        uint32_t    error16iCount;  //  ERR_DIAL_REQ_FAILED

} errorList;



/* This structure contains the Bios details and variables needed for operation! */
typedef struct _Bios {

    Task_Handle      AAATask;           // This task is for AAA first                   taskAAA();
    Task_Handle      UART0ReadTask;     // This task is for the UART0 read              taskUART0Read();
    Task_Handle      UART0WriteTask;    // This task is for the UARTWrite and outMsg    taskUART0Write();
    Task_Handle      ADCTask;           // This taks is for the ADC Stream!             taskADCStream();
    Task_Handle      NETUDPTask;        // This taks if for NETUDP                      taskNETUDP();
    Task_Handle      UART7ReadTask;     // This task is for the UART7Read               taskUART7Read();
    Task_Handle      PayloadTask;       // This task is for the taskPayload             taskPayload();

    Semaphore_Handle UARTWriteSem;      // This is the UARTWriteSem
    Semaphore_Handle PayloadSem;        // This is the PayloadSem
    Semaphore_Handle ADCSem;            // This is the ADCSem
    Semaphore_Handle NETUDPSem;         // This is the NETUDPSem for NETUDP
    Semaphore_Handle VoiceSem[TX_BUF_COUNT];

    Swi_Handle       Timer0Swi;         // Timer0Swi
    Swi_Handle       Timer1Swi;         // Timer1Swi
    Swi_Handle       SW1_Swi;           // SW1_Swi
    Swi_Handle       SW2_Swi;           // SW2_Swi
    Swi_Handle       ADC_ErrorSwi;      // ADC_ErrorSwi

    GateSwi_Handle   TimerGateSwi;      // Timer
    GateSwi_Handle   OutMsgGateSwi;     // OutMsg
    GateSwi_Handle   PayloadGateSwi;    // Payload
    GateSwi_Handle   CallbackGateSwi;   // Callback
    GateSwi_Handle   TickerGateSwi;     // Ticker
    GateSwi_Handle   ScriptGateSwi;     // Script
    GateSwi_Handle   NETUDPGateSwi;     // NETUDP
    GateSwi_Handle   VoiceGateSwi;

}  biosList;



/* This structure just defines the contents of a specific callback! */
typedef struct _callbackEntry {

    char            payload[BUFFER_SIZE];
    int32_t         count;

} callbackEntry;


/* This structure is used to define the callBackList and parameters that are used for the callbacks */
typedef struct _callback {

    int32_t         index;
    bool            Hwi_flag;
    char            name[16];
    char            callbackName[CALLBACK_COUNT][32];
    callbackEntry   callbacks[CALLBACK_COUNT];

} callbackList;



typedef struct _tickerEntry {

    char            payload[BUFFER_SIZE];
    int32_t         count;
    uint32_t        period;
    uint32_t        delay;

} tickerList;



/* This structure outlines the different variables needed for the queue payload. */
typedef struct _payloadQueue {

    char        payloads[MAX_PAYLOAD_COUNT][BUFFER_SIZE];
    uint32_t    payloadReading;
    uint32_t    payloadWriting;

}  payloadQList;



typedef struct _netudpQueue {

    char        netudpPayloads[MAX_NETUDP_COUNT][NETUDP_BUFFER_SIZE];
    uint32_t    netudpBinaryCount[MAX_NETUDP_COUNT];
    uint32_t    netudpReading;
    uint32_t    netudpWriting;

}   netudpQList;


/* This shit is confusing so let me break it down.
 *
 *  +   _OutMsgType enumeration basically creates macro definitions in numerical order for
 *      OUTMSG_N(=0), OUTMSG_SL(=1), OUTMSG_BOLD(=2) (they should all be integer datatypes).
 *      This allows me to pass just OUTMSG_N into addOutMsg(), neat shit.
 *
 *  +   _OutMsg is a structure that I will use to determine HOW I'd like to print out the
 *      msg. I can't just use a simple 2D array (arr of strings) like in Payload because each message will have
 *      an attached attribute like: "print as bold"/"only print a single line"/"print normally"
 *
 *  +   FINALLY, I create the Queue which has a circular buffer msgs of size MAX_MSG_COUNT.
 *      then I also have the msgReading and msgWriting like in PayloadQ!
 *
 *  +   Whenever I want to add something to the outMsgQ, you can use the following macro defs to
 *      make life easier:
 *          #define     puts(x)     addOutMsg((x), OUTMSG_N)    // print to console a string WITH a new line
 *          #define     putSL(x)    addOutMsg((x), OUTMSG_SL)   // print to console a string WITHOUT a new line
 *          #define     putB(x)     addOutMsg((x), OUTMSG_BOLD) // print to console a string in BOLD WITH a new line
 */
typedef enum    _OutMsgType {

    OUTMSG_N,
    OUTMSG_SL,
    OUTMSG_BOLD

} outMsgTypeList;

typedef struct  _OutMsg {

    outMsgTypeList  type;
    char            msg[BUFFER_SIZE];

} outMsg;

typedef struct  _msgOutQueue {

    outMsg      msgs[MAX_MSG_COUNT];
    uint32_t    msgReading;
    uint32_t    msgWriting;

}   outMsgQList;



typedef struct  _timers {

    uint32_t    periodT0;
    bool        countingT0;
    bool        freqT0;
    uint32_t    periodT1;
    bool        countingT1;
    bool        freqT1;

} timerList;



/* This structure contains all of the information necessary for the register function
 *  +   "registers" is the array of registers which are all signed 32-bit integers.
 *      The array is REGISTER_COUNT elements long!
 *
 *  +   | OP: ?(READ)   =(MOV)  x(XCG)
 *      | OP: +(ADD)   ++(INC)
 *      | OP: -(SUB)   --(DEC)
 *      | OP: ~(NOT)    _(NEG)
 *      | OP: &(AND)    |(IOR)  ^(XOR)
 *      | OP: *(MUL)    /(DIV)  %(REM)
 *      | OP: >(MAX)    <(MIN)  @(MEM)
 *      The enummeration allows me to assign a specific label to each opcode instead of relying on the
 *      character alone. More complicated, probably useless, but doin' it anyway
 */
typedef enum    _opType {
    READ, MOV, XCG,
    ADD, INC,
    SUB, DEC,
    NOT, NEG,
    AND, IOR, XOR,
    MUL, DIV, REM,
    MAX, MIN, MEM
} opTypeList;

typedef struct  _registers {

    int32_t     registers[REG_COUNT];

} regList;



typedef struct _scripts {

    char        script[SCRIPT_COUNT][BUFFER_SIZE];
    int32_t     currentLine;

} scriptList;



typedef enum   _opTypeCond {
    GREATER,
    LESS,
    EQUAL
} opTypeCond;

typedef enum   _opAddrMode {
    REG,
    IMM,
    DIR
} opAddrMode;



typedef struct _conditionals {


} conditionalList;



typedef struct _sineControl {

    uint32_t frequency;
    bool     speakerOn; /* True for On; False for Off */
    double   LUTPosition;
    double   LUTDelta;
    const uint16_t *sinLUT;


} sineControlList;


typedef struct  rxBufControl {

    uint16_t           *RX_Completed;
    uint32_t            pingCount; // For debugging
    uint32_t            pongCount; // For debugging
    uint16_t            RX_Ping[DATA_BLOCK_SIZE];
    uint16_t            RX_Pong[DATA_BLOCK_SIZE];
    int16_t             RX_Index;


} rxBufControlList;

typedef struct txBufControl {

    uint16_t           *TX_Completed;
    int32_t             TX_Index;
    int32_t             TX_Correction;
    uint32_t            TX_Delay;
    uint32_t            TX_sampleCount;
    bool                TX_updating;
    uint16_t            TX_Ping[DATA_BLOCK_SIZE];
    uint16_t            TX_Pong[DATA_BLOCK_SIZE];

} txBufControlList;

typedef struct audioControl {

    ADCBuf_Conversion   conversion;
    bool                local;
    bool                converting;
    rxBufControlList    rxBuf;
    txBufControlList    txBuf[TX_BUF_COUNT];
    uint8_t             localDestinationChoice;

} audioControlList;

typedef struct dialControl {

    uint16_t            callTwoWay;     /* 0 = No two-way call;      1 = two-way-call Active;    2 = three-way call Exepected */
    uint16_t            callThreeWay;   /* 0 = No three-way call;    1 = three-way call Active;  2 = three-way call Exepected */
    uint32_t            ipAddr1;
    uint32_t            ipAddr2;
    bool                callPing;
    char                ip0String[16];
    char                ip1String[16];
    char                ip2String[16];

} dialControlList;


/* GLOBAL STRUCTURE! */
typedef struct _Global {

    deviceList          Devices;
    paramList           Parameters;
    constList           Constants;
    bufferList          Buffers;
    errorList           Errors;
    biosList            Bios;
    callbackList        Callback;
    payloadQList        PayloadQ;
    outMsgQList         OutMsgQ;
    tickerList          Tickers[TICKER_COUNT];
    timerList           Timers;
    regList             Regs;
    scriptList          Script;
    sineControlList     Sine;
    audioControlList    audioControl;
    netudpQList         netudpQueue;
    dialControlList     Dial;

} glo;

glo Global;

/* ================================================================================ */



/* ================================================================================
 *      FUNC DEFINITIONS!
 * --------------------------------------------------------------------------------
 *      Function definitions for Infrastructure, tasks, callbacks, etc.             */

/* INFRASTRUCTURE FUNCTION DECLARATIONS */
void    initProgram();
void    initDrivers();
void    initMsg();
void    UART_write_prot(const char *msg);
void    UART_write_prot_sl(const char *msg);
void    UART_write_prot_bold(const char *msg);
int32_t addCallback(int32_t index, int32_t count, char *payload);
void    addOutMsg(const char *msg, outMsgTypeList type);
void    addPayload(char *input);
int32_t addScript(uint32_t index, char *payload);
void    execPayload(char *input);
int32_t addTicker(int32_t index, uint32_t delay, uint32_t period, int32_t count, char *payload);
char   *getNextInp(char *input, bool printLog);
void    addError(char *input, char *inpError);
void    helpLookUp(char *input);
void    runClear();
void    runMemr(char *input);
void    runGPIO(char *input);
void    runTimer(char *input, bool putOut);
void    runCallback(char *input, bool putOut);
void    runTicker(char *input);
void    runRegister(char *input);
void    runScript(char *input);
void    runRem();
void    runConditional(char *input);
void    runUART7 (char *input);
void    runSine(char *input);
void    runAudio();
void    runVoice(char *input);
void    runStream(char *input);
void    runDial(char *input);
void    runNETUDP(char *input, int32_t binaryCount);
void    msgHelp();
void    msgHelpHelp();
void    msgHelpAbout();
void    msgHelpPrint();
void    msgHelpMemr();
void    msgHelpGPIO();
void    msgHelpError();
void    msgHelpTimer();
void    msgHelpCallback();
void    msgHelpTicker();
void    msgHelpReg();
void    msgHelpScript();
void    msgHelpConditional();
void    msgHelpUART7();
void    msgHelpClear();
void    msgHelpRem();
void    msgHelpSine();
void    msgHelpAudio();
void    msgHelpStream();
void    msgHelpVoice();
void    msgHelpDial();
void    msgHelpNETUDP();
void    msgAbout();
void    msgPrint(char *input);
void    msgError(char *input);
bool    charCmp(char a, char b);
int     strncmpi(const char *s1, const char *s2, size_t n);


/* TASKS FUNCTION DECLARATIONS */
void    taskAAA();
void    taskUART0Read();
void    taskUART0Write(UArg arg0, UArg arg1);
void    taskADCStream();
void    taskNETUDP();
void    taskUART7Read();
void    taskPayload();


/* CALLBACKS FUNCTION DECLARATIONS */
void    adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t var);
void    adcErrorSWI(UArg arg0, UArg arg1);
void    timer0Callback();
void    timer1Callback();
void    timer0SWI(UArg arg0, UArg arg1);
void    timer1SWI(UArg arg0, UArg arg1);
void    gpioButtonSw1Callback(uint_least8_t index);
void    SWIgpioButtonSw1(UArg arg0, UArg arg1);
void    gpioButtonSw2Callback(uint_least8_t index);
void    SWIgpioButtonSw2(UArg arg0, UArg arg1);



/* udpEcho and udpEchoHooks FUNCTION DECLARATIONS */
void   *transmitFunction(void *arg0);
void   *receiveFunction(void *arg0);
void    netIPAddrHook(uint32_t IPAddr, unsigned int IfIdx, unsigned int fAdd);
void    serviceReport(uint32_t item, uint32_t status, uint32_t report, void *h);


/* ================================================================================ */


#endif
