/* ================================================================================
 *
 *      C-Infrastructure File
 * --------------------------------------------------------------------------------
 *  + Contains the following function DEFINITIONS:
 *      Functions to call by default in main:
 *      - initProgram: initialization of constants, etc.
 *      - initGPIO: initialization of the various GPIO functionalities
 *      - initUART: initialization of the UART
 *
 *     Functions used by other functions or by main (not initialization or defaults though):
 *      - UART_write_protected: protected UART_write
 *      - msgParser:    parses the messages formed by UART read and separated by spaces
 *      - msgHelp: contains the "-help" command output sequence
 *      - msgHelpHelp: contains the "-help help" command output sequence
 *      - msgHelpAbout: contains the "-help about" command output sequence
 *      - msgHelpPrint: contains the "-help print" command output sequence
 *      - msgHelpMemr: contains the "-help memr" command output sequence
 *      - msgAbout: contains the "-about" command output sequence
 *  +
 *  +
 *
 * ================================================================================ */

#include "c_header.h"
#include "sinlut.h"

#ifdef glo
extern glo Global;
#endif





/* ================================================================================
 *   PROGRAM INITALIZATION FUNCTION
 * --------------------------------------------------------------------------------
 *  This function initializes various components of the program for operation in
 *  various contexts. Primarily initialization of Global variables and clearing out
 *  setting strings or messages.
 *  It also establishes the connection between the Global.Bios structure and the
 *  tirtos_builds handles for the various BIOS components!
 */
void initProgram() {

    /* Declaration of int for-loops     */
    int i;

    /* Buffers Initialization           */
    memset(Global.Buffers.inpBuff,      0, BUFFER_SIZE);
    memset(Global.Buffers.msgBuff,      0, BUFFER_SIZE);
    memset(Global.Buffers.uart7Buff,    0, BUFFER_SIZE);
    for (i = 0; i < INP_HISTORY_COUNT; i++) {
        memset(Global.Buffers.inpArrowBuffer[i], 0, BUFFER_SIZE);
    }
           Global.Buffers.inpIndex =        0;
           Global.Buffers.inpArrowIndex =   0;

    /* Global "Errors" initialization   */
    Global.Errors.error0aCount  =       0;
    Global.Errors.error0bCount  =       0;
    Global.Errors.error0cCount  =       0;
    Global.Errors.error0dCount  =       0;
    Global.Errors.error1aCount  =       0;
    Global.Errors.error2aCount  =       0;
    Global.Errors.error2bCount  =       0;
    Global.Errors.error3aCount  =       0;
    Global.Errors.error3bCount  =       0;
    Global.Errors.error3cCount  =       0;
    Global.Errors.error3dCount  =       0;
    Global.Errors.error4aCount  =       0;
    Global.Errors.error4bCount  =       0;
    Global.Errors.error4cCount  =       0;
//    Global.Errors.error4dCount  =       0;
    Global.Errors.error5aCount  =       0;
    Global.Errors.error5bCount  =       0;
    Global.Errors.error5cCount  =       0;
    Global.Errors.error5dCount  =       0;
    Global.Errors.error6aCount  =       0;
    Global.Errors.error6bCount  =       0;
    Global.Errors.error6cCount  =       0;
//    Global.Errors.error6dCount  =       0;
    Global.Errors.error7aCount  =       0;
    Global.Errors.error7bCount  =       0;
    Global.Errors.error7cCount  =       0;
    Global.Errors.error7dCount  =       0;
    Global.Errors.error7eCount  =       0;
    Global.Errors.error7fCount  =       0;
    Global.Errors.error8aCount  =       0;
    Global.Errors.error8bCount  =       0;
    Global.Errors.error8cCount  =       0;
    Global.Errors.error8dCount  =       0;
    Global.Errors.error8eCount  =       0;
    Global.Errors.error9aCount  =       0;
    Global.Errors.error9bCount  =       0;
//    Global.Errors.error9cCount  =       0;
//    Global.Errors.error6dCount  =       0;
    Global.Errors.error10aCount =       0;
    Global.Errors.error10bCount =       0;
    Global.Errors.error10cCount =       0;
    Global.Errors.error10dCount =       0;
    Global.Errors.error11aCount =       0;
//    Global.Errors.error11bCount =       0;
//    Global.Errors.error11cCount =       0;
//    Global.Errors.error11dCount =       0;
    Global.Errors.error12aCount =       0;
    Global.Errors.error12bCount =       0;
    Global.Errors.error12cCount =       0;
//    Global.Errors.error12dCount =       0;
//    Global.Errors.error13aCount =       0;
//    Global.Errors.error13bCount =       0;
//    Global.Errors.error13cCount =       0;
//    Global.Errors.error13dCount =       0;
    Global.Errors.error14aCount =       0;
    Global.Errors.error14bCount =       0;
    Global.Errors.error14cCount =       0;
    Global.Errors.error14dCount =       0;
    Global.Errors.error15aCount =       0;
    Global.Errors.error15bCount =       0;
    Global.Errors.error15cCount =       0;
//    Global.Errors.error15dCount =       0;
    Global.Errors.error16aCount  =       0;
    Global.Errors.error16bCount  =       0;
    Global.Errors.error16cCount  =       0;
    Global.Errors.error16dCount  =       0;
    Global.Errors.error16eCount  =       0;
    Global.Errors.error16fCount  =       0;
    Global.Errors.error16gCount  =       0;
    Global.Errors.error16hCount  =       0;
    Global.Errors.error16iCount  =       0;



    /* Global gpioName initialization   */
    strcpy(Global.Devices.gpioName[0],  "LED D1 ");
    strcpy(Global.Devices.gpioName[1],  "LED D2 ");
    strcpy(Global.Devices.gpioName[2],  "LED D3 ");
    strcpy(Global.Devices.gpioName[3],  "LED D4 ");
    strcpy(Global.Devices.gpioName[4],  "PIN PK5");
    strcpy(Global.Devices.gpioName[5],  "PIN PD4");
    strcpy(Global.Devices.gpioName[6],  "USR SW1");
    strcpy(Global.Devices.gpioName[7],  "USR SW2");


    /* Global BIOS initialization       */
    Global.Bios.AAATask         =       task0;
    Global.Bios.UART0ReadTask   =       task1;
    Global.Bios.UART0WriteTask  =       task2;
    Global.Bios.ADCTask         =       task3;
    Global.Bios.NETUDPTask      =       task4;
    Global.Bios.UART7ReadTask   =       task5;
    Global.Bios.PayloadTask     =       task6;

    Global.Bios.UARTWriteSem    =       sem0;
    Global.Bios.PayloadSem      =       sem1;
    Global.Bios.ADCSem          =       sem2;
    Global.Bios.NETUDPSem       =       sem3;
    Global.Bios.VoiceSem[0]     =       sem4;
    Global.Bios.VoiceSem[1]     =       sem5;

    Global.Bios.Timer0Swi       =       swi0;
    Global.Bios.Timer1Swi       =       swi1;
    Global.Bios.SW1_Swi         =       swi2;
    Global.Bios.SW2_Swi         =       swi3;
    Global.Bios.ADC_ErrorSwi    =       swi4;

    Global.Bios.TimerGateSwi    =       gateSwi0;
    Global.Bios.OutMsgGateSwi   =       gateSwi1;
    Global.Bios.PayloadGateSwi  =       gateSwi2;
    Global.Bios.CallbackGateSwi =       gateSwi3;
    Global.Bios.TickerGateSwi   =       gateSwi4;
    Global.Bios.ScriptGateSwi   =       gateSwi5;
    Global.Bios.NETUDPGateSwi   =       gateSwi6;
    Global.Bios.VoiceGateSwi    =       gateSwi7;

    /* PayloadQ initialization          */
    Global.PayloadQ.payloadReading  =   0;
    Global.PayloadQ.payloadWriting  =   0;
    memset(Global.PayloadQ.payloads,    0, sizeof(Global.PayloadQ.payloads));

    /* OUTMSGQ initializaiton           */
    Global.OutMsgQ.msgReading       =   0;
    Global.OutMsgQ.msgWriting       =   0;
    memset(Global.OutMsgQ.msgs,         0, sizeof(Global.OutMsgQ.msgs));

    /* NETUDPQ initialization */
    Global.netudpQueue.netudpReading =   0;
    Global.netudpQueue.netudpWriting =   0;
    memset(Global.netudpQueue.netudpPayloads, 0, sizeof(Global.netudpQueue.netudpPayloads));
    memset(Global.netudpQueue.netudpBinaryCount, 0, sizeof(Global.netudpQueue.netudpBinaryCount));

    /* DIAL initialization */
    Global.Dial.callThreeWay = CALL_INACTIVE;
    Global.Dial.callTwoWay = CALL_INACTIVE;
    Global.Dial.ipAddr1 = 0;
    Global.Dial.ipAddr2 = 0;
    Global.Dial.callPing = false;
    memset(Global.Dial.ip0String, 0, sizeof(Global.Dial.ip0String));
    memset(Global.Dial.ip1String, 0, sizeof(Global.Dial.ip1String));
    memset(Global.Dial.ip2String, 0, sizeof(Global.Dial.ip2String));
    Global.audioControl.local = false;

    /* Timer DETAIL initialization      */
    Global.Timers.countingT0 =          false;
    Global.Timers.countingT1 =          false;
    Global.Timers.freqT0 =              false;
    Global.Timers.freqT1 =              false;
    Global.Timers.periodT0 =            1000000;
    Global.Timers.periodT1 =            10000;

    /* Callback initializations         */
    Global.Callback.callbacks[0].count =         0;
    Global.Callback.callbacks[1].count =         0;
    Global.Callback.callbacks[2].count =         0;
    Global.Callback.callbacks[3].count =         0;
    memset(Global.Callback.callbacks[0].payload, 0, sizeof(Global.Callback.callbacks[0].payload));
    memset(Global.Callback.callbacks[1].payload, 0, sizeof(Global.Callback.callbacks[1].payload));
    memset(Global.Callback.callbacks[2].payload, 0, sizeof(Global.Callback.callbacks[2].payload));
    memset(Global.Callback.callbacks[3].payload, 0, sizeof(Global.Callback.callbacks[3].payload));
    strcpy(Global.Callback.callbackName[0],     "TIMER 0");
    strcpy(Global.Callback.callbackName[1],     "USR_SW1");
    strcpy(Global.Callback.callbackName[2],     "USR_SW2");
    strcpy(Global.Callback.callbackName[3],     "TBD    ");

    /* TICKER INITIALIZATION */
    for (i = 0; i < TICKER_COUNT;   i++) {
        Global.Tickers[i].count  =        0;
        Global.Tickers[i].delay  =        0;
        Global.Tickers[i].period =        0;
        memset(Global.Tickers[i].payload, 0, sizeof(Global.Tickers[i].payload));
    }

    /* REGISTER INITIALIZAZTION */
    for (i = 0; i < REG_COUNT;      i++) {
        Global.Regs.registers[i] = 0;
    }

    /* SCRIPT INITIALIZATION! */
    for (i = 0; i < SCRIPT_COUNT; i++) {
        addScript(i, NULL);
    }
    addScript( 0, "-gpio 0 t");
    addScript( 1, "-gpio 1 t");
    addScript( 2, "-gpio 2 t");
    addScript( 3, "-gpio 3 t");
    addScript( 4, "-print abc");
    addScript( 5, "-print 123");
    addScript(50, "-gpio 0 t");
    addScript(61, "-gpio 1 t");
    addScript(62, "-gpio 2 t");
    addScript(63, "-gpio 3 t");

    Global.Sine.sinLUT = sinLUT;





    return;

} // void programInit();
/* ================================================================================ */





/* ================================================================================
 *      DRIVER INITIALIZATION
 * --------------------------------------------------------------------------------
 *  Includes initialization of Drivers for all of the drivers in the Global.Devices
 *  structure. This initializes the following systems:
 *      + GPIO
 *      + UART0
 *      + UART7
 *      + TIMER0 (for timer callback)
 *      + TIMER1 (for tickers)
 *      + SPI (to BOOSTXL DAC for speaker output)
 *      + ADCBuf (read off BOOSTXL microphone and alternate into TWO buffers; ping, pong)
 */
void initDrivers() {

    int i;

    /* Initialize all the different periphery, make sure to have #include <ti/drivers/[driver].h> in c_header */
    Board_init();
    GPIO_init();
    UART_init();
    Timer_init();
    SPI_init();
    ADCBuf_init();

    /* Turn on all the board LEDs */
    GPIO_write(CONFIG_GPIO_0, CONFIG_GPIO_LED_ON);
    GPIO_write(CONFIG_GPIO_1, CONFIG_GPIO_LED_ON);
    GPIO_write(CONFIG_GPIO_2, CONFIG_GPIO_LED_ON);
    GPIO_write(CONFIG_GPIO_3, CONFIG_GPIO_LED_ON);

    /* Initialize GPIO 6 and GPIO 7 ISRs for the side switches */
    GPIO_enableInt(CONFIG_GPIO_6);
    GPIO_enableInt(CONFIG_GPIO_7);


    /* UART Parameter initialization */
    UART_Params_init(&Global.Parameters.uartParams0);
    Global.Parameters.uartParams0.writeDataMode =       UART_DATA_BINARY;
    Global.Parameters.uartParams0.readDataMode =        UART_DATA_BINARY;
    Global.Parameters.uartParams0.readReturnMode =      UART_RETURN_FULL;
    Global.Parameters.uartParams0.baudRate =            115200;

    UART_Params_init(&Global.Parameters.uartParams7);
    Global.Parameters.uartParams7.writeDataMode =       UART_DATA_BINARY;
    Global.Parameters.uartParams7.readDataMode =        UART_DATA_TEXT;
    Global.Parameters.uartParams7.readReturnMode =      UART_RETURN_NEWLINE;
    Global.Parameters.uartParams7.baudRate =            115200;
    Global.Parameters.uartParams7.readEcho =            UART_ECHO_OFF;

    /* Initializes both UART0 and UART7 connection */
    Global.Devices.uart0 = UART_open(CONFIG_UART_0, &Global.Parameters.uartParams0);
    Global.Devices.uart7 = UART_open(CONFIG_UART_1, &Global.Parameters.uartParams7);

    /* Hang the program if uart0 or uart7 initialization was unsuccessful. */
    if (Global.Devices.uart0 == NULL) {
        while(1);
    }

    if (Global.Devices.uart7 == NULL) {
        while(1);
    }

    Timer_Params_init(&Global.Parameters.timerParams0);
    Global.Parameters.timerParams0.period = 125;                          // Default timer0 to 125 microseconds
    Global.Parameters.timerParams0.periodUnits = Timer_PERIOD_US;         // Default timer units to microseconds
    Global.Parameters.timerParams0.timerCallback = timer0Callback;        // Default callback for timer is timer0.
    Global.Parameters.timerParams0.timerMode = Timer_CONTINUOUS_CALLBACK; // Continuous callback

    Global.Devices.timer0 = Timer_open(CONFIG_TIMER_0, &Global.Parameters.timerParams0);

    Timer_Params_init(&Global.Parameters.timerParams1);
    Global.Parameters.timerParams1.period = 10000;                        // Default timers to 10 ms
    Global.Parameters.timerParams1.periodUnits = Timer_PERIOD_US;         // Default timer units to milliseconds
    Global.Parameters.timerParams1.timerCallback = timer1Callback;        // Default callback for timer is timer0.
    Global.Parameters.timerParams1.timerMode = Timer_CONTINUOUS_CALLBACK; // Continuous callback

    Global.Devices.timer1 = Timer_open(CONFIG_TIMER_1, &Global.Parameters.timerParams1);

    /* If timer0 and/or timer1 failed to initialize, then hang the program! */
    if (Global.Devices.timer0 == NULL) {
        while(1);
    }

    if (Global.Devices.timer1 == NULL) {
        while(1);
    }

    /* Also hang the program if timer0 and timer1 fail to start! */
    if (Timer_start(Global.Devices.timer0) == Timer_STATUS_ERROR) {
        while(1);
    }

    if (Timer_start(Global.Devices.timer1) == Timer_STATUS_ERROR) {
        while(1);
    }

    /* INITIALIZE SPI COMMUNICATION         */
    SPI_Params_init(&Global.Parameters.spiParams3);
    Global.Parameters.spiParams3.dataSize = 16;
    Global.Parameters.spiParams3.frameFormat = SPI_POL0_PHA1;
    Global.Devices.spi3 = SPI_open(CONFIG_SPI_0, &Global.Parameters.spiParams3);

    /* Hang the program if SPI communication fails */
    if (Global.Devices.spi3 == NULL) {
        while(1);
    }

    ADCBuf_Params_init(&Global.Parameters.adcBufParams);
    Global.Parameters.adcBufParams.returnMode = ADCBuf_RETURN_MODE_CALLBACK;
    Global.Parameters.adcBufParams.recurrenceMode = ADCBuf_RECURRENCE_MODE_CONTINUOUS;
    Global.Parameters.adcBufParams.callbackFxn = adcBufCallback;
    Global.Parameters.adcBufParams.samplingFrequency = SAMPLE_RATE;
    Global.Devices.adcBuf = ADCBuf_open(CONFIG_ADCBUF_0, &Global.Parameters.adcBufParams);

    /* Hang the program if ADC and/or ADC Buf communication fails */
    if (Global.Devices.adcBuf == NULL) {
        while(1);
    }

    Global.audioControl.conversion.adcChannel = ADCBUF_CHANNEL_0;
    Global.audioControl.conversion.arg = NULL;
    Global.audioControl.conversion.sampleBuffer = Global.audioControl.rxBuf.RX_Ping;
    Global.audioControl.conversion.sampleBufferTwo = Global.audioControl.rxBuf.RX_Pong;
    Global.audioControl.conversion.samplesRequestedCount = DATA_BLOCK_SIZE;

    Global.audioControl.converting = false;
    Global.audioControl.local = true;
    Global.audioControl.rxBuf.RX_Completed = NULL;
    memset(Global.audioControl.rxBuf.RX_Ping, 0, DATA_BLOCK_SIZE);
    memset(Global.audioControl.rxBuf.RX_Pong, 0, DATA_BLOCK_SIZE);
    for (i = 0; i < TX_BUF_COUNT; i++) {
        memset(Global.audioControl.txBuf[i].TX_Ping, 0, DATA_BLOCK_SIZE * (sizeof(uint16_t)));
        memset(Global.audioControl.txBuf[i].TX_Pong, 0, DATA_BLOCK_SIZE * (sizeof(uint16_t)));
        Global.audioControl.txBuf[i].TX_Completed = NULL;
        Global.audioControl.txBuf[i].TX_Index = -1;
        Global.audioControl.txBuf[i].TX_Delay = DATA_DELAY;
        Global.audioControl.txBuf[i].TX_Correction = 0;
    }

    return;

} // void driverInit();
/* ================================================================================ */





/* ================================================================================
 *      INITIAL MESSAGE
 * --------------------------------------------------------------------------------
 *
 */
void initMsg() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, "--------------------------------------------------------------------------------");
    puts(xmitbuf);
    strcpy(xmitbuf, " Connection to MSP-EXP432E401Y Launchpad Successful");
    puts(xmitbuf);
    strcpy(xmitbuf, "--------------------------------------------------------------------------------");
    puts(xmitbuf);

    puts(NEW_LINE);

    return;

} // void initMsg();
/* ================================================================================ */





/* ================================================================================
 *      UART WRITE PROTECTED FOR A GIVEN LINE
 * --------------------------------------------------------------------------------
 *  This function contains the UART_write for a given message (used in msg... funcs)
 *  This code is sourced from Dr. Brian Nutter.
 *  Prints text on a given line and then enters a return to the next line.
 *  PuTTY by default supports 80 characters, so it is adviced that input String lengths
 *  not exceed 80.
 */
void UART_write_prot(const char *msg) {

    ti_sysbios_BIOS_ThreadType  tType;
    const char                 *found;

    /* return if the buffer is empty (nothing to write!) */
    if (msg == NULL || msg[0] == 0) {
        return;
    }

    tType = BIOS_getThreadType();
    if(tType == ti_sysbios_BIOS_ThreadType_Hwi || tType == ti_sysbios_BIOS_ThreadType_Swi) {
       addError(NULL, ERR_BIOS);
       return;
    }


    found = memchr(msg, 0, BUFFER_SIZE);
    if(!found) {
        addError(NULL, ERR_WRITE_UNSUCCESSFUL);
    }

    else {
        UART_write(Global.Devices.uart0, msg, (size_t)(found - msg));
        UART_write(Global.Devices.uart0, NEW_LINE, sizeof(NEW_LINE));
    }

    return;

} // void UART_write_prot(const char *msg);
/* ================================================================================ */





/* ================================================================================
 *      UART WRITE PROTECTED FOR A SINGLE LINE
 * --------------------------------------------------------------------------------
 *  Engages the same protections as the regular UART WRITE PROTECTED.
 *  This program will output a string to a line without a "return" to a new line.
 *  THIS IS LARGELY USED IN ECHOING INPUTS!
 */
void UART_write_prot_sl(const char *msg) {

    ti_sysbios_BIOS_ThreadType  tType;
    const char                 *found;

    /* return if the buffer is empty (nothing to write!) */
    if (msg == NULL || msg[0] == 0) {
        return;
    }

    tType = BIOS_getThreadType();
    if(tType == ti_sysbios_BIOS_ThreadType_Hwi || tType == ti_sysbios_BIOS_ThreadType_Swi) {
        addError(NULL, ERR_BIOS);
        return;
    }


    found = memchr(msg, 0, BUFFER_SIZE);
    if(!found) {
        addError(NULL, ERR_WRITE_UNSUCCESSFUL);
        return;
    }

    else {
        UART_write(Global.Devices.uart0, msg, (size_t)(found - msg));
    }

    return;

} // void UART_write_prot_sl(const char *msg);
/* ================================================================================ */





/* ================================================================================
 *      UART WRITE PROTECTED FOR BOLD OUTPUTS
 * --------------------------------------------------------------------------------
 *  Engages the same protections as the regular UART WRITE PROTECTED.
 *  This program will output a string in BOLD to a given line AND it will return to
 *  a new line!
 */
void UART_write_prot_bold(const char *msg) {

    // QUEUING STUFF!
    ti_sysbios_BIOS_ThreadType  tType;
    const char                 *found;

    /* return if the buffer is empty (nothing to write!) */
    if (msg == NULL || msg[0] == 0) {
        return;
    }

    tType = BIOS_getThreadType();
    if(tType == ti_sysbios_BIOS_ThreadType_Hwi || tType == ti_sysbios_BIOS_ThreadType_Swi) {
        addError(NULL, ERR_BIOS);
        return;
    }


    found = memchr(msg, 0, BUFFER_SIZE);
    if(!found) {
        addError(NULL, ERR_WRITE_UNSUCCESSFUL);
        return;
    }


    else {
        UART_write(Global.Devices.uart0, BOLD_ON, sizeof(BOLD_ON));
        UART_write(Global.Devices.uart0, msg, (size_t)(found - msg));
        UART_write(Global.Devices.uart0, BOLD_OFF, sizeof(BOLD_OFF));
        UART_write(Global.Devices.uart0, NEW_LINE, sizeof(NEW_LINE));
    }

    return;

} // void UART_write_prot(const char *msg);
/* ================================================================================ */





/* ================================================================================
 *      LOAD A CALLBACK COUNT AND PAYLOAD TO A SPECIFIC CALLBACK INDEX
 * --------------------------------------------------------------------------------
 *
 */
int32_t addCallback(int32_t index, int32_t count, char *payload) {

    uint32_t                    gateKey;
    ti_sysbios_BIOS_ThreadType  tType;

    tType = BIOS_getThreadType();
    if (tType == ti_sysbios_BIOS_ThreadType_Hwi) {
        addError(NULL, ERR_BIOS);
        return -1;
    }

    if (index < 0 || index >= CALLBACK_MAX) {
        return -1;
    }

    if (tType != ti_sysbios_BIOS_ThreadType_Hwi) {
        gateKey = GateSwi_enter(Global.Bios.CallbackGateSwi);
    }

    Global.Callback.callbacks[index].count = count;
    strcpy(Global.Callback.callbacks[index].payload, payload);

    if (tType != ti_sysbios_BIOS_ThreadType_Hwi) {
        GateSwi_leave(Global.Bios.CallbackGateSwi, gateKey);
    }

    return index;
}
/* ================================================================================ */





/* ================================================================================
 *      ADD A MESSAGE TO THE "MESSAGE OUTPUT QUEUE" (Global.OutMsgQ)
 * --------------------------------------------------------------------------------
 *
 */
void addOutMsg(const char *msg, outMsgTypeList type) {

    uint32_t    gateKey;
    int32_t     index;

    gateKey =   GateSwi_enter(Global.Bios.OutMsgGateSwi);

    if (Semaphore_getCount(Global.Bios.UARTWriteSem) >= MAX_MSG_COUNT) {
        addError(NULL, ERR_MSG_Q_OF);
        GateSwi_leave(Global.Bios.OutMsgGateSwi, gateKey);
        return;
    }

    index = Global.OutMsgQ.msgWriting;

    strncpy(Global.OutMsgQ.msgs[index].msg, msg, BUFFER_SIZE - 1);
    Global.OutMsgQ.msgs[index].msg[BUFFER_SIZE-1] = '\0';
    Global.OutMsgQ.msgs[index].type = type;

    index = (index + 1) % MAX_MSG_COUNT;
    Global.OutMsgQ.msgWriting = index;

    GateSwi_leave(Global.Bios.OutMsgGateSwi, gateKey);

    Semaphore_post(Global.Bios.UARTWriteSem);

    return;

} // void addOutMsg(const char *msg, outMsgTypeList type);
/* ================================================================================ */






/* ================================================================================
 *      PAYLOAD FUNCTIONS
 * --------------------------------------------------------------------------------
 *      Function definitions for executePayload and addPayload! These two functions
 *      are crucial for, first lining up things into the payLoad, and second for
 *      executing whatever payload is lined up!
 *      This function is used to parse the first portion of an input
 *      to identify substrings, use the "inpSubString()" function
 */
void addPayload(char *input) {

    uint32_t    gateKey;
    int32_t     index;

    gateKey =   GateSwi_enter(Global.Bios.PayloadGateSwi);

    if (Semaphore_getCount(Global.Bios.PayloadSem) >= MAX_PAYLOAD_COUNT) {
        addError(NULL, ERR_PAYLOAD_Q_OF);
        GateSwi_leave(Global.Bios.PayloadGateSwi, gateKey);
        return;
    }

    index = Global.PayloadQ.payloadWriting;

    strncpy(Global.PayloadQ.payloads[index], input, BUFFER_SIZE - 1);
    Global.PayloadQ.payloads[index][BUFFER_SIZE - 1] = '\0';

    index = (index + 1) % MAX_PAYLOAD_COUNT;
    Global.PayloadQ.payloadWriting = index;

    GateSwi_leave(Global.Bios.PayloadGateSwi, gateKey);

    Semaphore_post(Global.Bios.PayloadSem);

    return;

} // void addPayload(char *input);
/* ================================================================================ */





/* ================================================================================
 *      ADD THE VARIOUS ELEMENTS OF A TICKER INTO A SPECIFIED TICKER INDEX
 * --------------------------------------------------------------------------------
 *
 */
int32_t addTicker(int32_t index, uint32_t delay, uint32_t period, int32_t count, char *payload) {

    uint32_t                    gateKey;
    ti_sysbios_BIOS_ThreadType  tType;

    tType = BIOS_getThreadType();
    if (tType == ti_sysbios_BIOS_ThreadType_Hwi) {
        addError(NULL, ERR_BIOS);
        return -1;
    }

    /* Ensures the delay and period are within the specified bounds (see msgHelpTicker) */
    if (delay > 3750 || period > 3750) {
        addError(NULL, ERR_TKR_OUT_OF_BOUNDS);
        return -1;
    }

    /* Ensures the index parameter is within the specified ticker indices (see TICKER_COUNT) */
    if (index < 0 || index >= TICKER_COUNT) {
        addError(NULL, ERR_TKR_INVALID_INDEX);
        return -1;
    }

    gateKey = GateSwi_enter(Global.Bios.TickerGateSwi);

    Global.Tickers[index].delay     = delay;
    Global.Tickers[index].period    = period;
    Global.Tickers[index].count     = count;
    if (payload == NULL) {
        Global.Tickers[index].payload[0] = '\0';
    }
    else {
        strncpy(Global.Tickers[index].payload, payload, BUFFER_SIZE - 1);
        Global.Tickers[index].payload[BUFFER_SIZE - 1] = '\0';
    }

    GateSwi_leave(Global.Bios.TickerGateSwi, gateKey);

    return 0;

} // int32_t addTicker(int32_t index, uint32_t delay, uint32_t period, int32_t count, char *payload);
/* ================================================================================ */





/* ================================================================================
 *      ADD A SCRIPT PAYLOAD (OR CLEAR) FOR A USER-DEFINED SCRIPT INDEX
 * --------------------------------------------------------------------------------
 *
 */
int32_t addScript(uint32_t index, char *payload) {

    uint32_t                    gateKey;
    ti_sysbios_BIOS_ThreadType  tType;

    tType = BIOS_getThreadType();
    if (tType == ti_sysbios_BIOS_ThreadType_Hwi) {
        addError(NULL, ERR_BIOS);
        return -1;
    }

    gateKey = GateSwi_enter(Global.Bios.ScriptGateSwi);

    if (payload == NULL) {
        Global.Script.script[index][0] = '\0';
    }
    else {
        strncpy(Global.Script.script[index], payload, BUFFER_SIZE - 1);
        Global.Script.script[index][BUFFER_SIZE - 1] = '\0';
    }

    GateSwi_leave(Global.Bios.ScriptGateSwi, gateKey);

    return 0;

} // int32_t addScript(int32_t index, char *payload);
/* ================================================================================ */




/* ================================================================================
 *      EXECUTE THE NEXT PAYLOAD IN THE "PAYLOAD QUEUE" (Global.PayloadQ)
 * --------------------------------------------------------------------------------
 *
 */
void execPayload(char *input) {

    /* If the user entered "-help" then engage in the following help sequence! */
    if      (strncmpi(input, "-help" , strlen("-help"))  == 0) { /* Tests both "-help" and "-HELP" */
        helpLookUp(input);
    }

    /* If the user entered "-about" display about this program */
    else if (strncmpi(input, "-about", strlen("-about")) == 0) { /* Tests both "-about" and "-ABOUT" */
        msgAbout();
    }

    else if (strncmpi(input, "-print", strlen("-print")) == 0) { /* Tests both "-print" and "-PRINT" */
        msgPrint(input);
    }

    else if (strncmpi(input, "-memr" , strlen("-memr"))  == 0) { /* Tests both "-memr" and "-MEMR" */
        runMemr(input);
    }

    else if (strncmpi(input, "-gpio" , strlen("-gpio"))  == 0) { /* Tests both "-gpio" and "-GPIO" */
        runGPIO(input);
    }

    else if (strncmpi(input, "-error", strlen("-error")) == 0) { /* Tests both "-error"/"-ERROR" and "-errors"/"-ERRORS" */
        msgError(input);
    }

    else if (strncmpi(input, "-timer", strlen("-timer")) == 0) { /* Tests both "-timer" and "-timers" */
        runTimer(input, true);
    }

    else if (strncmpi(input, "-callback", strlen("-callback")) == 0) { /* Tests both "-callback" and "-callbacks" */
        runCallback(input, true);
    }

    else if (strncmpi(input, "-ticker", strlen("-ticker")) == 0) { /* Tests both "-ticker" and "-tickers" */
        runTicker(input);
    }

    else if (strncmpi(input, "-reg", strlen("-reg")) == 0) { /* Tests both "-reg" and "-regs" */
        runRegister(input);
    }

    else if (strncmpi(input, "-script", strlen("-script")) == 0) { /* Tests both "-script" and "-scripts" */
        runScript(input);
    }

    else if (strncmpi(input, "-rem", strlen("-rem")) == 0) { /* Tests both "-rem" and "-rems" */
        runRem();
    }

    else if (strncmpi(input, "-if", strlen("-if")) == 0) { /* Tests only "-if" or "-IF" */
        runConditional(input);
    }

    else if (strncmpi(input, "-uart", strlen("-uart")) == 0) { /* Tests only "-uart" or "-UART" */
        runUART7(input);
    }

    else if (strncmpi(input, "-clear", strlen("-clear")) == 0) { /* Tests only "-clear" */
        runClear();
    }

    else if (strncmpi(input, "-sine", strlen("-sine")) == 0) { /* Tests only "-sine" */
        runSine(input);
    }

    else if (strncmpi(input, "-audio", strlen("-audio")) == 0) { /* Tests only "-dial" */
        runAudio();
    }

    else if (strncmpi(input, "-stream", strlen("-stream")) == 0) { /* Tests only "-stream" */
        runStream(input);
    }

    else if (strncmpi(input, "-dial", strlen("-dial")) == 0) { /* Tests only "-dial" */
        runDial(input);
    }

    else if (strncmpi(input, "-netudp", strlen("-netudp")) == 0) {
        runNETUDP(input, 0);
    }

    else {
        addError(input, ERR_PARSE);
        return;
    }

} // void inpLookUp(char *input);
/* ================================================================================ */





/* ================================================================================
 *      POINTS TO THE NEXT TOKEN IN A GIVEN USER INPUT
 * --------------------------------------------------------------------------------
 *  This function grabs the next index of the input command and returns it.
 *  printLog (print logic) is set to FALSE ONLY for print statements.
 */
char *getNextInp(char *input, bool printLog) {

    char    *loc;

    if (input == NULL) {
        return NULL;
    }
    loc = strchr(input, ' ');
    if (!loc) {
        return NULL;
    }
    if (printLog) {
        while (*loc == ' ') {
            loc++;
        }
    }
    else {
        if (*loc == ' ') {
            loc++;
        }
    }
    if (!*loc) {
        return NULL;
    }

    return loc;

} // char *getNextInp(char *input, bool printLog);
/* ================================================================================ */





/* ================================================================================
 *      ADD ERROR
 * --------------------------------------------------------------------------------
 *  This function will add error codes to the error table
 *  and output a string corresponding to whichever error was called.
 */
void addError(char *input, char *inpError) {
    char   *xmitbuf = Global.Buffers.msgBuff;

    /* The following below is likely a TASK! ERROR 0a */
    if (inpError == ERR_WRITE_UNSUCCESSFUL) {
        Global.Errors.error0aCount++;
        strcpy(xmitbuf, "Error 0a: Protected write previously unsuccessful");
        putB(xmitbuf);
    }

    /* The remaining commands use UART_write_prot_bold! */

    // Error 0b
    else if (strcmp(inpError, ERR_LOC_NULL)             == 0) {
        Global.Errors.error0bCount++;
        sprintf(xmitbuf, "Error %s: Command \"%s\" not recognized.", ERR_LOC_NULL, input);
        putB(xmitbuf);
    }

    // Error 0c
    else if (strcmp(inpError, ERR_PARSE)                == 0) {
        Global.Errors.error0cCount++;
        sprintf(xmitbuf, "Error %s: Command \"%s\" not recognized.", ERR_PARSE, input);
        putB(xmitbuf);
    }

    // Error 0d
    else if (strcmp(inpError, ERR_BUFF_OVERFLOW)        == 0) {
        Global.Errors.error0dCount++;
        puts(NEW_LINE);
        sprintf(xmitbuf, "Error %s: Buffer Overflow", ERR_BUFF_OVERFLOW);
        putB(xmitbuf);
    }

    // Error 1a
    else if (strcmp(inpError,  ERR_HELP)                == 0) {
        Global.Errors.error1aCount++;
        sprintf(xmitbuf, "Error %s: Could not find help for \"%s\"", ERR_HELP, input);
        putB(xmitbuf);
    }

    // Error 2a
    else if (strcmp(inpError, ERR_MEMR_OUT_OF_RANGE)    == 0) {
        Global.Errors.error2aCount++;
        sprintf(xmitbuf, "Error %s: Memory address \"%s\" is out of range.", ERR_MEMR_OUT_OF_RANGE, input);
        putB(xmitbuf);
    }

    // Error 2b
    else if (strcmp(inpError, ERR_MEMR_INVALID_INP)     == 0) {
        Global.Errors.error2bCount++;
        sprintf(xmitbuf, "Error %s: Specific \"%s\" command could not be recognized.", ERR_MEMR_INVALID_INP, input);
        putB(xmitbuf);
    }

    // Error 3a
    else if (strcmp(inpError, ERR_INVALID_GPIO_IDX)     == 0) {
        Global.Errors.error3aCount++;
        sprintf(xmitbuf, "Error %s: %s is an invalid GPIO index.", ERR_INVALID_GPIO_IDX, input);
        putB(xmitbuf);
    }

    // Error 3b: ERR_INVALID_GPIO_OP
    else if (strcmp(inpError, ERR_INVALID_GPIO_OP)      == 0) {
        Global.Errors.error3bCount++;
        sprintf(xmitbuf, "Error %s: %s is an invalid GPIO operation.", ERR_INVALID_GPIO_OP, input);
        putB(xmitbuf);
    }

    // Error 3c: ERR_INVALID_GPIO_VAL
    else if (strcmp(inpError, ERR_INVALID_GPIO_VAL)     == 0) {
        Global.Errors.error3cCount++;
        sprintf(xmitbuf, "Error %s: User failed to or entered an invalid GPIO value.", ERR_INVALID_GPIO_VAL);
        putB(xmitbuf);
    }

    // Error 3d: ERR_INVALID_GPIO_WT
    else if (strcmp(inpError, ERR_INVALID_GPIO_WT)      == 0) {
        Global.Errors.error3dCount++;
        sprintf(xmitbuf, "Error %s: User attempted to write/toggle to an invalid GPIO.", ERR_INVALID_GPIO_WT);
        putB(xmitbuf);
    }

    // Error 4a: ERR_BIOS
    else if (strcmp(inpError, ERR_BIOS)                 == 0) {
        Global.Errors.error4aCount++;
        sprintf(xmitbuf, "Error %s: A BIOS error occurred.", ERR_BIOS);
        putB(xmitbuf);
    }

    // Error 4b: ERR_PAYLOAD_Q_OF
    else if (strcmp(inpError, ERR_BIOS)                 == 0) {
        Global.Errors.error4bCount++;
        sprintf(xmitbuf, "Error %s: The payload queue overflowed.", ERR_PAYLOAD_Q_OF);
        putB(xmitbuf);
    }

    // Error 4c: ERR_MSG_Q_OF
    else if (strcmp(inpError, ERR_MSG_Q_OF)             == 0) {
        Global.Errors.error4cCount++;
        sprintf(xmitbuf, "Error %s: The message queue overflowed.", ERR_MSG_Q_OF);
        putB(xmitbuf);
    }

    // Error 5a: ERR_INVALID_TIMER_PER
    else if (strcmp(inpError, ERR_INVALID_TIMER_PER)    == 0) {
        Global.Errors.error5aCount++;
        sprintf(xmitbuf, "Error %s: Please enter a valid timer period.", ERR_INVALID_TIMER_PER);
        putB(xmitbuf);
    }

    // Error 5b: ERR_INVALID_TIMER_UNITS
    else if (strcmp(inpError, ERR_INVALID_TIMER_UNITS)  == 0) {
        Global.Errors.error5bCount++;
        sprintf(xmitbuf, "Error %s: Please enter a valid unit.", ERR_INVALID_TIMER_UNITS);
        putB(xmitbuf);
    }

    // Error 5c: ERR_MIN_TIMER_THRESH
    else if (strcmp(inpError, ERR_MIN_TIMER_THRESH)     == 0) {
        Global.Errors.error5cCount++;
        sprintf(xmitbuf, "Error %s: Period for timer below minimum threshold.", ERR_MIN_TIMER_THRESH);
        putB(xmitbuf);
    }

    // Error 5d: ERR_MAX_TIMER_THRESH
    else if (strcmp(inpError, ERR_MAX_TIMER_THRESH)     == 0) {
        Global.Errors.error5dCount++;
        sprintf(xmitbuf, "Error %s: Period for timer above maximum threshold.", ERR_MAX_TIMER_THRESH);
        putB(xmitbuf);
    }

    // Error 6a: ERR_INVALID_CB_IDX
    else if (strcmp(inpError, ERR_INVALID_CB_IDX)       == 0) {
        Global.Errors.error6aCount++;
        sprintf(xmitbuf, "Error %s: Invalid CB index.", ERR_INVALID_CB_IDX);
        putB(xmitbuf);
    }

    // Error 6b: ERR_INVALID_CB_COUNT
    else if (strcmp(inpError, ERR_INVALID_CB_COUNT)     == 0) {
        Global.Errors.error6bCount++;
        sprintf(xmitbuf, "Error %s: Invalid CB count.", ERR_INVALID_CB_COUNT);
        putB(xmitbuf);
    }

    // Error 6c: ERR_UNSPEC_CB_FUNC
    else if (strcmp(inpError, ERR_UNSPEC_CB_FUNC)       == 0) {
        Global.Errors.error6cCount++;
        sprintf(xmitbuf, "Error %s: CB payload not specified.", ERR_UNSPEC_CB_FUNC);
        putB(xmitbuf);
    }

    // Error 7a: ERR_NO_FREE_TKR
    else if (strcmp(inpError, ERR_NO_FREE_TKR)       == 0) {
        Global.Errors.error7aCount++;
        sprintf(xmitbuf, "Error %s: No free ticker available.", ERR_NO_FREE_TKR);
        putB(xmitbuf);
    }

    // Error 7b: ERR_TKR_INVALID_INDEX
    else if (strcmp(inpError, ERR_TKR_INVALID_INDEX)       == 0) {
        Global.Errors.error7bCount++;
        sprintf(xmitbuf, "Error %s: Invalid ticker index specified.", ERR_TKR_INVALID_INDEX);
        putB(xmitbuf);
    }

    // Error 7c: ERR_TKR_OUT_OF_BOUNDS
    else if (strcmp(inpError, ERR_TKR_OUT_OF_BOUNDS)       == 0) {
        Global.Errors.error7cCount++;
        sprintf(xmitbuf, "Error %s: Tkr period/delay invalid.", ERR_TKR_OUT_OF_BOUNDS);
        putB(xmitbuf);
    }

    // Error 7d: ERR_INVALID_TKR_COUNT
    else if (strcmp(inpError, ERR_INVALID_TKR_COUNT)       == 0) {
        Global.Errors.error7dCount++;
        sprintf(xmitbuf, "Error %s: CB Invalid ticker count specified.", ERR_INVALID_TKR_COUNT);
        putB(xmitbuf);
    }

    // Error 7e: ERR_INVALID_TKR_PAYLOAD
    else if (strcmp(inpError, ERR_INVALID_TKR_PAYLOAD)       == 0) {
        Global.Errors.error7eCount++;
        sprintf(xmitbuf, "Error %s: Invalid ticker payload specified.", ERR_INVALID_TKR_PAYLOAD);
        putB(xmitbuf);
    }

    // Error 7f: ERR_TKR_ADD_FAILED
    else if (strcmp(inpError, ERR_TKR_ADD_FAILED)       == 0) {
        Global.Errors.error7fCount++;
        sprintf(xmitbuf, "Error %s: addTicker function failed.", ERR_TKR_ADD_FAILED);
        putB(xmitbuf);
    }

    // Error 8a: ERR_INVALID_REG_IDX
    else if (strcmp(inpError, ERR_INVALID_REG_IDX)       == 0) {
        Global.Errors.error8aCount++;
        sprintf(xmitbuf, "Error %s: Register index invalid/unspecified.", ERR_INVALID_REG_IDX);
        putB(xmitbuf);
    }

    // Error 8b: ERR_INVALID_OP_CODE
    else if (strcmp(inpError, ERR_INVALID_OP_CODE)       == 0) {
        Global.Errors.error8bCount++;
        sprintf(xmitbuf, "Error %s: Register op code invalid/unspecified.", ERR_INVALID_OP_CODE);
        putB(xmitbuf);
    }

    // Error 8c: ERR_UNSPEC_INVALID_SRCA
    else if (strcmp(inpError, ERR_UNSPEC_INVALID_SRCA)       == 0) {
        Global.Errors.error8cCount++;
        sprintf(xmitbuf, "Error %s: Invalid or unspecified Source A.", ERR_UNSPEC_INVALID_SRCA);
        putB(xmitbuf);
    }

    // Error 8d: ERR_UNSPEC_INVALID_SRCB
    else if (strcmp(inpError, ERR_UNSPEC_INVALID_SRCB)       == 0) {
        Global.Errors.error8dCount++;
        sprintf(xmitbuf, "Error %s: Invalid or unspecified Source B.", ERR_UNSPEC_INVALID_SRCB);
        putB(xmitbuf);
    }

    // Error 8e: ERR_REG_REM_ZERO
    else if (strcmp(inpError, ERR_REG_REM_ZERO)             == 0) {
        Global.Errors.error8eCount++;
        sprintf(xmitbuf, "Error %s: Attempted to take remainder w/ 0.", ERR_REG_REM_ZERO);
        putB(xmitbuf);
    }

    // Error 9a: ERR_INV_SCRIPT_IDX
    else if (strcmp(inpError, ERR_INV_SCRIPT_IDX)           == 0) {
        Global.Errors.error9aCount++;
        sprintf(xmitbuf, "Error %s: Script index unspecified or invalid.", ERR_INV_SCRIPT_IDX);
        putB(xmitbuf);
    }

    // Error 9b: ERR_INV_SCRIPT_PAYLOAD
    else if (strcmp(inpError, ERR_INV_SCRIPT_PAYLOAD)       == 0) {
        Global.Errors.error9bCount++;
        sprintf(xmitbuf, "Error %s: Script payload unspecified or invalid.", ERR_INV_SCRIPT_PAYLOAD);
        putB(xmitbuf);
    }

    // Error 10a: ERR_COND_SA_INVALID
    else if (strcmp(inpError, ERR_COND_SA_INVALID)       == 0) {
        Global.Errors.error10aCount++;
        sprintf(xmitbuf, "Error %s: Source A invalid or unspecified.", ERR_COND_SA_INVALID);
        putB(xmitbuf);
    }

    // Error 10b: ERR_COND_SB_INVALID
    else if (strcmp(inpError, ERR_COND_SB_INVALID)       == 0) {
        Global.Errors.error10bCount++;
        sprintf(xmitbuf, "Error %s: Source B invalid or unspecified.", ERR_COND_SB_INVALID);
        putB(xmitbuf);
    }

    // Error 10c: ERR_COND_OP_INVALID
    else if (strcmp(inpError, ERR_COND_OP_INVALID)       == 0) {
        Global.Errors.error10cCount++;
        sprintf(xmitbuf, "Error %s: Script payload unspecified or invalid.", ERR_COND_OP_INVALID);
        putB(xmitbuf);
    }

    // Error 10d: ERR_COND_PD_INVALID
    else if (strcmp(inpError, ERR_COND_PD_INVALID)       == 0) {
        Global.Errors.error10dCount++;
        sprintf(xmitbuf, "Error %s: Conditional payload unspecified or invalid.", ERR_COND_PD_INVALID);
        putB(xmitbuf);
    }

    // Error 10e: ERR_UNSPEC_DELIM
    else if (strcmp(inpError, ERR_UNSPEC_DELIM)       == 0) {
        Global.Errors.error10eCount++;
        sprintf(xmitbuf, "Error %s: Conditional delimiter unspecified or invalid.", ERR_UNSPEC_DELIM);
        putB(xmitbuf);
    }

    // Error 11a: ERR_INVALID_UART7
    else if (strcmp(inpError, ERR_INVALID_UART7)       == 0) {
        Global.Errors.error11aCount++;
        sprintf(xmitbuf, "Error %s: UART7 payload was invalid or unspecified.", ERR_INVALID_UART7);
        putB(xmitbuf);
    }

    // Error 12a: ERR_INVALID_FREQ
    else if (strcmp(inpError, ERR_INVALID_FREQ)       == 0) {
        Global.Errors.error12aCount++;
        sprintf(xmitbuf, "Error %s:  Sine frequency invalid.", ERR_INVALID_FREQ);
        putB(xmitbuf);
    }

    // Error 12b: ERR_FREQ_OUT_OF_RANGE
    else if (strcmp(inpError, ERR_FREQ_OUT_OF_RANGE)       == 0) {
        Global.Errors.error12bCount++;
        sprintf(xmitbuf, "Error %s: Sine frequency out of range.", ERR_FREQ_OUT_OF_RANGE);
        putB(xmitbuf);
    }

    // Error 12c: ERR_VOICE_BUF
    else if (strcmp(inpError, ERR_VOICE_BUF)       == 0) {
        Global.Errors.error12cCount++;
        sprintf(xmitbuf, "Error %s: SPI Transaction or speaker buffer bad.", ERR_VOICE_BUF);
        putB(xmitbuf);
    }


    // Error 14a: ERR_ADC_BUF_INVALID
    else if (strcmp(inpError, ERR_ADC_BUF_INVALID)       == 0) {
        Global.Errors.error14aCount++;
        sprintf(xmitbuf, "Error %s: Buffer of the ADCBuf driver was invalid.", ERR_ADC_BUF_INVALID);
        putB(xmitbuf);
    }

    // Error 14b: ERR_UNKNOWN_RX_BUF
    else if (strcmp(inpError, ERR_UNKNOWN_RX_BUF)       == 0) {
        Global.Errors.error14bCount++;
        sprintf(xmitbuf, "Error %s: ADC Buf not good between ping/pong.", ERR_UNKNOWN_RX_BUF);
        putB(xmitbuf);
    }




    // Error 16a: ERR_NOT_PINGED
    else if (strcmp(inpError, ERR_NOT_PINGED)       == 0) {
        Global.Errors.error16aCount++;
        sprintf(xmitbuf, "Error %s: -dial accept/decline entered w/o prompt.", ERR_NOT_PINGED);
        putB(xmitbuf);
    }

    // Error 16b: ERR_ACCEPT_FAILED
    else if (strcmp(inpError, ERR_ACCEPT_FAILED)       == 0) {
        Global.Errors.error16bCount++;
        sprintf(xmitbuf, "Error %s: -dial accept failed.", ERR_ACCEPT_FAILED);
        putB(xmitbuf);
    }

    // Error 16c: ERR_DECLINE_FAILED
    else if (strcmp(inpError, ERR_DECLINE_FAILED)       == 0) {
        Global.Errors.error16cCount++;
        sprintf(xmitbuf, "Error %s: -dial decline failed.", ERR_DECLINE_FAILED);
        putB(xmitbuf);
    }

    // Error 16d: ERR_REQ_FAILED
    else if (strcmp(inpError, ERR_REQ_FAILED)       == 0) {
        Global.Errors.error16dCount++;
        sprintf(xmitbuf, "Error %s: -dial request failed or misformatted.", ERR_REQ_FAILED);
        putB(xmitbuf);
    }

    // Error 16e: ERR_UNPROMPTED_RESP
    else if (strcmp(inpError, ERR_UNPROMPTED_RESP)       == 0) {
        Global.Errors.error16eCount++;
        sprintf(xmitbuf, "Error %s: -dial response done erroneously.", ERR_UNPROMPTED_RESP);
        putB(xmitbuf);
    }

    // Error 16f: ERR_ALREADY_IN_CALL
    else if (strcmp(inpError, ERR_ALREADY_IN_CALL)       == 0) {
        Global.Errors.error16fCount++;
        sprintf(xmitbuf, "Error %s: -dial action attempted whil already in call.", ERR_ALREADY_IN_CALL);
        putB(xmitbuf);
    }

    // Error 16g: ERR_RESP_FAILED
    else if (strcmp(inpError, ERR_RESP_FAILED)       == 0) {
        Global.Errors.error16gCount++;
        sprintf(xmitbuf, "Error %s: -dial resposne failed or misformatted.", ERR_RESP_FAILED);
        putB(xmitbuf);
    }

    // Error 16h: ERR_CONFIRM_FAILED
    else if (strcmp(inpError, ERR_CONFIRM_FAILED)       == 0) {
        Global.Errors.error16hCount++;
        sprintf(xmitbuf, "Error %s: -dial confirm failed or misformatted.", ERR_CONFIRM_FAILED);
        putB(xmitbuf);
    }

    // Error 16i: ERR_DIAL_REQ_FAILED
    else if (strcmp(inpError, ERR_DIAL_REQ_FAILED)       == 0) {
        Global.Errors.error16iCount++;
        sprintf(xmitbuf, "Error %s: User-defined dial request '-dial b1/b2' failed.", ERR_DIAL_REQ_FAILED);
        putB(xmitbuf);
    }


    return;

} // void addError(char *input, char *inpError);
/* ================================================================================ */





/* ================================================================================
 *      HELP LOOK UP
 * --------------------------------------------------------------------------------
 */
void helpLookUp(char *input) {

    char *loc;

    /* If the user entered "-help about" display what the 'about' command does */
    if      (strstr(input, "about") != NULL ) {
        msgHelpAbout();
    }
    else if (strstr(input, "audio") != NULL ) {
        msgHelpAudio();
    }
    else if (strstr(input, "callback") != NULL ) {
        msgHelpCallback();
    }
    else if (strstr(input, "clear") != NULL) {
        msgHelpClear();
    }
    else if (strstr(input, "dial") != NULL ) {
        msgHelpDial();
    }
    else if (strstr(input, "error") != NULL ) {
        msgHelpError();
    }
    else if (strstr(input, "gpio")  != NULL ) {
        msgHelpGPIO();
    }
    else if (strstr(input, "if") != NULL ) {
        msgHelpConditional();
    }
    else if (strstr(input, "memr")  != NULL ) {
        msgHelpMemr();
    }
    else if (strstr(input, "print") != NULL ) {
        msgHelpPrint();
    }
    else if (strstr(input, "reg") != NULL ) {   // If the user types "-help [reg, regs, register, registers].
        msgHelpReg();
    }
    else if (strstr(input, "rem") != NULL ) {
        msgHelpRem();
    }
    else if (strstr(input, "script") != NULL ) {
        msgHelpScript();
    }
    else if (strstr(input, "sine") != NULL ) {
        msgHelpSine();
    }
    else if (strstr(input, "stream") != NULL ) {
        msgHelpStream();
    }
    else if (strstr(input, "ticker") != NULL ) {
        msgHelpTicker();
    }
    else if (strstr(input, "timer") != NULL ) {
        msgHelpTimer();
    }
    else if (strstr(input, "uart") != NULL ) {
        msgHelpUART7();
    }
    else if (strstr(input, "voice") != NULL ) {
        msgHelpVoice();
    }
    else if (strstr(input, "netudp") != NULL ) {
        msgHelpNETUDP();
    }

    /* If the user entered "-help help" display what the 'help' command does */
    else if ((&input[5] != '\0') && (strstr(&input[5], "help") != NULL)) {
        msgHelpHelp();
    }
    else if (strncmp(input, "-help" , 5) == 0) {
        char *arg = input + 5;

        while (*arg && isspace(*arg)) {
            arg++;
        }
        if (*arg == '\0') {
            msgHelp();
        }
        else {
            loc = getNextInp(input, true);
            if (!loc) {
                addError(NULL, ERR_LOC_NULL);
            }
            else {
                addError(loc, ERR_HELP);
            }
        }
    }
    /* If the user entered a command unfamiliar to the program, display the CMD DNE error */
    else {
        addError(input, ERR_HELP);
    }

    return;

} // void helpLookUp(char *input);
/* ================================================================================ */




/* ================================================================================
 *      HELP LOOK UP
 * --------------------------------------------------------------------------------
 *
 */
void runClear() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, CLEAR_LINE_RESET);
    puts    (xmitbuf);
    strcpy  (xmitbuf, CLEAR_CONSOLE);
    putSL   (xmitbuf);

    return;

}





/* ================================================================================
 *      RUN MEMR
 * --------------------------------------------------------------------------------
 *  This code is executed when the user inputs the command "-memr [address]"
 *  It will output that address and the next four memory locations and their contents.
 */
void runMemr(char *input) {

    char       xmitbufmem[BUFFER_SIZE];
    char       *loc;
    uintptr_t   addr;
    uint32_t    val;
    uint32_t    MASK = 0xFFFFFFF0;

    loc = getNextInp(input, true);

    /* Scan the user input (sscanf will only scan the hex input needed for uintptr_t
     * encode each character as hex into the uintptr_t type addr */

    if (!loc) {
        addError(NULL, ERR_LOC_NULL);
    }
    else if (sscanf(loc, "%x", &addr) == 1) {
        if ((addr <= 0x000FFFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
            addr = addr & MASK;
            char resTemp[50]        = {0};
            char result[50]         = {0};
            char addrOutTemp[50]    = {0};
            char addrOut[50]        = {0};
            int i = 0;
            for (i = 0; i < 13; i = i + 4) {
                 snprintf(addrOutTemp, sizeof(addrOutTemp), "0x%08X ", (unsigned int)(addr + i));
                 val = *((volatile uint32_t *)(uintptr_t)((unsigned int)(addr + i)));
                 snprintf(resTemp, sizeof(resTemp), "0x%08X ", (unsigned int)val);
                 strcat(addrOut, addrOutTemp);
                 strcat(result, resTemp);
             }
             puts(addrOut);
             puts(result);
         }
         /* If the address is not in the viable range */
         else {
             snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
             addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
             return;
         }
    }
    /* If the memory address was not in the valid format (contained something besides 0123456789ABCDEF) */
    else {
         addError(input, ERR_MEMR_INVALID_INP);
         return;
    }

    return;

} // void runMemr(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN GPIO
 * --------------------------------------------------------------------------------
 * -gpio           :   Displays all of the GPIO and their states
 * -gpio #         :   Displays the info for that GPIO index (on, off, etc.)
 * -gpio # t       :   Toggles that specific GPIO index if it can be toggled
 * -gpio # r/w     :   Read or write a value from/to a GPIO
 *
 *  strncmpi (2 strings are exact but compares only a specific number of characters and case insensitive
 *  Create a subroutine for each.
 */
void runGPIO(char *input) {

    char       *xmitbuf = Global.Buffers.msgBuff;
    int32_t     index,
                ftn,
                val,
                i;
    char       *loc;

    loc = getNextInp(input, true);
	/* If there is no other parameter in -gpio, makes the index -1 */
    if (!loc) {
	    /* if index is -1, then print the entire GPIO menu */
	    index = -1;
	}

    /* This block account for whether a digit is present and loc isn't a negative sign */
	else {
	    if ((isdigit(*loc) == 0) && (*loc != '-')) {    /* If not a digit & does not equal a negative */
	        char errBuff[2] = {*loc, '\0'};             /* add to the GPIO index error! */
	        addError(errBuff, ERR_INVALID_GPIO_IDX);    /* Missing required digits */
	        return;
	    }
	    index = atoi(loc);
	}

    /* If no index was provided or the index was over the GPIO count, then print a read/status of all the GPIO */
	if (index < 0 || index >= GPIO_COUNT) {
	    /* Print GPIO Info */
	    for (i = 0; i < GPIO_COUNT; i++) {
	        val = GPIO_read(i);
	        /* LATER IMPLEMENTATION! */ // writeShadow() /* WTH is this? */ // A shadow register is a copy of another thing! Used for peripheral read/writes
	        sprintf(xmitbuf, "GPIO %d - %s : %d", i, Global.Devices.gpioName[i], val);
	        puts(xmitbuf);
	    }
	    return;
	}

	/* Default to a GPIO read function if the second parameter of the -gpio fxn is empty;
	 * otherwise, write the following
	 * In all honesty, the FTN_GPIO... stuff is only ever useful for writes... */
	loc = getNextInp(loc, true);
	if      ( (!loc) || (charCmp(*loc, 'r')) ) {
	    ftn = FTN_GPIO_READ;
	}
	else if (charCmp(*loc, 'w')) {
	    ftn = FTN_GPIO_WRITE;
	}
	else if (charCmp(*loc, 't')) {
	    ftn = FTN_GPIO_TOGGLE;
	}
	else {
	    char buffErr[2] = {*loc, '\0'};
	    addError(buffErr, ERR_INVALID_GPIO_OP);
	    return;
	}

	if ( (ftn == FTN_GPIO_WRITE ) && ( (index != 6) && (index != 7) ) ) {
	    loc = getNextInp(loc, true);
	    if (!loc) {
	        addError(NULL, ERR_INVALID_GPIO_VAL);
	        return;
	    }
	    else {
	        val = atoi(loc);
	        if ((val != 0) && (val != 1)) {
	            addError(NULL, ERR_INVALID_GPIO_VAL);
	            return;
	        }
	    }
	}

	if ( (ftn == FTN_GPIO_TOGGLE) && ( (index == 6) || (index == 7) ) ) {
	    addError(NULL, ERR_INVALID_GPIO_WT);
	    return;
	}

	/* If ftn is a 'r' or FTN_GPIO_READ; then perform a read of the GPIO of a given idx */
	switch(ftn) {
        case FTN_GPIO_READ:
        case 'r':
            val = GPIO_read(index);
            sprintf(xmitbuf, "GPIO %d - %s : %d", index, Global.Devices.gpioName[index], val);
            puts(xmitbuf);
            return;
        default:
            break;
	}

	switch(ftn) {
	    case FTN_GPIO_WRITE:
	    case 'w':
	        GPIO_write(index, val & 0x1);
	        return;
	    default:
	        break;
	}

	switch(ftn) {
	    case FTN_GPIO_TOGGLE:
	    case 't':
	        val = GPIO_read(index);
	        GPIO_write(index, val ^ 0x1);
	    default:
	        break;
	}

	return;

} // void runGPIO(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN TIMER
 * --------------------------------------------------------------------------------
 * -timer           | print current timer period (in us) to perform CALLBACK 0
 * -timer 0         | turn timer off
 * -timer VAL       | set timer period to VAL (in us)
 * -timer VAL m     | set timer period to VAL (in ms)
 * -timer VAL s     | set timer period to VAL (in s )
 * -timer VAL Unit  | set timer period to VAL (in TI=RTOS "enum-UNITs")
 *                  | timer period must be >= 100 us or 0
 *                  | timer period must be < 35.7 s
 */
void runTimer(char *input, bool putOut) {

    char               *xmitbuf = Global.Buffers.msgBuff;
    char               *loc;
    int32_t             period;

    /* Return the next input from the user-input string. */
    loc = getNextInp(input, true);

    /* If there is no other parameter in -timer then print out the current period of the timer */
    if (!loc) {
        goto PRINT_TIMER;
    }
    else {
        if (sscanf(loc, "%d", &period) != 1) {
            addError(NULL, ERR_INVALID_TIMER_PER);
            return;
        }
    }

    if (period == 0) {
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_US, period);
        Global.Timers.periodT0 = period;
        goto PRINT_TIMER;
    }

    loc = getNextInp(loc, true);

    if (!loc || *loc == 'u') {
        if (period < MIN_TIMER_PERIOD) {
            addError(NULL, ERR_MIN_TIMER_THRESH);
            return;
        }
        else if (period > MAX_TIMER_PERIOD) {
            addError(NULL, ERR_MAX_TIMER_THRESH);
            return;
        }
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_US, period);
        Global.Timers.periodT0 =    period;
        Global.Timers.countingT0 =  false;
        Global.Timers.freqT0 =      false;
        goto PRINT_TIMER;
    }

    else if (*loc == 'm') {
        if (period * 1000 > MAX_TIMER_PERIOD) {
            addError(NULL, ERR_MAX_TIMER_THRESH);
            return;
        }
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_US, period * 1000);
        Global.Timers.periodT0 =    period * 1000;
        Global.Timers.countingT0 =  false;
        Global.Timers.freqT0 =      false;
        goto PRINT_TIMER;
    }

    else if (*loc == 's') {
        if (period * 1000000 > MAX_TIMER_PERIOD) {
            addError(NULL, ERR_MAX_TIMER_THRESH);
            return;
        }
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_US, period * 1000000);
        Global.Timers.periodT0 =    period * 1000000;
        Global.Timers.countingT0 =  false;
        Global.Timers.freqT0 =      false;
        goto PRINT_TIMER;
    }

    else if ((strncmpi(loc, "hz", strlen("hz")) == 0) || (strncmpi(loc, "Timer_PERIOD_HZ", strlen("Timer_PERIOD_Hz")) == 0)) {
        if (period > MAX_TIMER_HZ) {
            addError(NULL, ERR_MIN_TIMER_THRESH);
            return;
        }
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_HZ, period);
        Global.Timers.periodT0 =    period;
        Global.Timers.countingT0 =  false;
        Global.Timers.freqT0 =      true;
        goto PRINT_TIMER;
    }

    else if ((strncmpi(loc, "count", strlen("count")) == 0) || (strncmpi(loc, "Timer_PERIOD_COUNT", strlen("Timer_PERIOD_COUNT")) == 0)) {
        if (period < MIN_TIMER_PERIOD * 10) {
            addError(NULL, ERR_MIN_TIMER_THRESH);
            return;
        }
        else if (period > MAX_TIMER_PERIOD_COUNT) {
            addError(NULL, ERR_MAX_TIMER_THRESH);
            return;
        }
        Timer_setPeriod(Global.Devices.timer0, Timer_PERIOD_COUNTS, period);
        Global.Timers.periodT0 =    period;
        Global.Timers.countingT0 =  true;
        Global.Timers.freqT0 =      false;
        sprintf(xmitbuf, "TIMER 0: %d counts", Global.Timers.periodT0);
        goto PRINT_TIMER;
    }

    else {
        addError(NULL, ERR_INVALID_TIMER_UNITS);
        return;
    }


    PRINT_TIMER:
        if (putOut == false) {
            return;
        }
        else if      (Global.Timers.periodT0 == 0) {
            sprintf(xmitbuf, "TIMER 0: OFF");
            puts(xmitbuf);
        }
        else if (Global.Timers.countingT0 == true) {
            sprintf(xmitbuf, "TIMER 0: %d counts",          Global.Timers.periodT0);
            puts(xmitbuf);
        }
        else if (Global.Timers.freqT0 == true) {
            sprintf(xmitbuf, "TIMER 0: %d Hz",              Global.Timers.periodT0);
            puts(xmitbuf);
        }
        else if (Global.Timers.periodT0 < 1000) {
            sprintf(xmitbuf, "TIMER 0: %d microseconds",    Global.Timers.periodT0);
            puts(xmitbuf);
        }
        else if (Global.Timers.periodT0 < 1000000) {
            sprintf(xmitbuf, "TIMER 0: %d milliseconds",    Global.Timers.periodT0 / 1000);
            puts(xmitbuf);
        }
        else {
            sprintf(xmitbuf, "TIMER 0: %d seconds",         Global.Timers.periodT0 / 1000000);
            puts(xmitbuf);
        }

    return;

} // void runTimer(char *input, bool putOut);
/* ================================================================================ */





/* ================================================================================
 *      RUN CALLBACK
 * --------------------------------------------------------------------------------
 *  -callback                    :   Displays all callbacks, counts, and functions
 *  -callback clr                :   Clears ALL callbacks
 *  -callback [idx]              :   Displays details for a callback.
 *  -callback [idx] clr          :   Clears a callback at that specific index.
 *  -callback [idx] [cnt] [func] :   CB_idx will execute func \"cnt\" times.
 *  The addCallback FUNCTION: int32_t addCallback(int32_t index, int32_t count, char *payload)
 */
void runCallback(char *input, bool putOut) {

    char               *xmitbuf = Global.Buffers.msgBuff;
    char               *loc;
    int32_t             index;
    int32_t             count;
    int                 i;


    loc = getNextInp(input, true);

    /* If there is no index, then set index to -1 and then print ALL of the callbacks */
    if (!loc) {
        index = -1;
        goto PRINT_CALLBACK;
    }
    else {
        /* If the user entered "-callback clr" or "-callback clear", then clear ALL CALLBACKS */
        if      ( (strncmpi(loc, "clr", strlen("clr")) == 0) || (strncmpi(loc, "clear", strlen("clear")) == 0) ) {
            for (i = 0; i < CALLBACK_COUNT; i++) {
                memset(Global.Callback.callbacks[i].payload, 0, BUFFER_SIZE);
                Global.Callback.callbacks[i].count = 0;
            }
        }
        /* If there is a valid integer at the loc, then store it in index */
        else if (sscanf(loc, "%d", &index) != 1) {
            addError(NULL, ERR_INVALID_CB_IDX);
            return;
        }
    }

    /* If there is an index but no count, set the the count for the callback to the loc */
    loc = getNextInp(loc, true);
    if (!loc) {
        goto PRINT_CALLBACK;
    }
    else {
        /* If the user entered "-callback [idx] clr" or "-callback [index] clear", then clear ALL CALLBACKS */
        if ( (strncmpi(loc, "clr", strlen("clr")) == 0) || (strncmpi(loc, "clear", strlen("clear")) == 0) ) {
            memset(Global.Callback.callbacks[index].payload, 0, BUFFER_SIZE);
            Global.Callback.callbacks[index].count = 0;
        }
        /* If the loc is not a valid integer, then reject the "callback_count"!; otherwise, store it in count! */
        if (sscanf(loc, "%d", &count) != 1) {
            addError(NULL, ERR_INVALID_CB_COUNT);
            return;
        }
    }

    loc = getNextInp(loc, true);
    if (!loc) {
        addError(NULL, ERR_UNSPEC_CB_FUNC); /* Callback function not specified */
        return;
    }
    else {
        /* add the callback to the Global callback structure with the appropriate index, count, and payload */
        addCallback(index, count, loc);
        goto PRINT_CALLBACK;
    }


    PRINT_CALLBACK:
        if (putOut == false) {
            return;
        }
        else {
            sprintf(xmitbuf, "          Name        | Count | Payload");
            puts(xmitbuf);
            if  (!(index >= 0 && index <= (CALLBACK_COUNT - 1))) {
                for (i = 0; i < CALLBACK_COUNT; i++) {
                    sprintf(xmitbuf, "   CALLBACK %d %s : %5d | %s", i, Global.Callback.callbackName[i], Global.Callback.callbacks[i].count, Global.Callback.callbacks[i].payload);
                    puts(xmitbuf);
                }
            }
            else {
                    sprintf(xmitbuf, "   CALLBACK %d %s : %5d | %s", index, Global.Callback.callbackName[index], Global.Callback.callbacks[index].count, Global.Callback.callbacks[index].payload);
                    puts(xmitbuf);
            }
        }

    return;

} // void runCallback(char *input, bool putOut);
/* ================================================================================ */






/* ================================================================================
 *      RUN TICKER
 * --------------------------------------------------------------------------------
 *  -ticker       :  Displays a list of the all the tickers and ticker implementation status (running/paused)
 *                  also outlines their delays, periods, count, and payload.
 *  -ticker 'k'   :  Ticker kill - Clears the entire ticker table.
 *  -ticker 'p'   :  Pause all tickers.
 *  -ticker 'r'   :  Run/Resume all tickers.
 *  -ticker [idx] :  Shows details of the ticker at the specified index.
 *  -ticker [idx] [del] [per] [cnt] [payload] : Sets up ticker_idx
 *   idx     |   index    ('u' specifies next open ticker slot)
 *   del     |   delay    (between 1 - 3750)
 *   per     |   period   (between 1 - 3750)
 *   cnt     |   count    (-1 for unlimited)
 *   payload |   payload  (payload to run on ticker activation)
 */
void runTicker(char *input) {

    char       *xmitbuf = Global.Buffers.msgBuff;
    char       *loc;
    int32_t     index;
    uint32_t    delay;
    uint32_t    period;
    int32_t     count;
    char       *payload;
    int         i;

    loc = getNextInp(input, true);

    if (!loc) {
        /* Prints all the tickers in the ticker table, also prints whether the tickers are on or off (nonzero timer1 period) */
        goto PRINT_TKRS;
    }

    else if (*loc == 'k') {
        /* Clears the entire tkr table! */
        for (i = 0; i < TICKER_COUNT; i++) {
            addTicker(i, 0, 0, 0, NULL);
        }
        strcpy  (xmitbuf, " TICKERS CLEARED");
        puts(xmitbuf);
        return;
    }

    /* If the user enters 'p' then disable timer1 (by setting period to 0)
     * (REFACTORING: put an if statement to do this only if it is currently enabled) */
    else if (*loc == 'p') {
        Timer_setPeriod(Global.Devices.timer1, Timer_PERIOD_US, 0);
        Global.Timers.periodT1 = 0;
        strcpy  (xmitbuf, " TICKER STATUS: OFF");
        puts(xmitbuf);
        return;
    }

    /* If the user enters 'r' then re-enable the timer1 period
     * (REFACTORING: put an if statement so it only does this if not currently enabled) */
    else if (*loc == 'r') {
        Timer_setPeriod(Global.Devices.timer1, Timer_PERIOD_US, 10000);
        Global.Timers.periodT1 = 10000;
        strcpy  (xmitbuf, " TICKER STATUS: ON");
        puts(xmitbuf);
        return;
    }

    /* If user specifies 'u' for the index, then look for an open ticker slot */
    else if (*loc == 'u') {
        index = -1;
        for (i = 0; i < TICKER_COUNT; i++) {
            if (Global.Tickers[i].count == 0 && Global.Tickers[i].delay == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            addError(NULL, ERR_NO_FREE_TKR);
            return;
        }
    }

    /* This code is hella spaghettified, but if the user does not enter an accepted char then it throws an invalid index error
     * Otherwise if the index is outside the given bounds (0 to TICKER_COUNT), search the ticker table for an open slot.
     * If no slot is available, then and only then, give a NO FREE TKR error                                                    */
    else {
        index = -1;
        index = atoi(loc);
        if  (index < 0 || index >= TICKER_COUNT) {
            for (i = 0; i < TICKER_COUNT; i++) {
                if (Global.Tickers[i].count == 0 && Global.Tickers[i].delay == 0) {
                    index = i;
                    break;
                }
            }
        }
        if (index == -1) {
            addError(NULL, ERR_NO_FREE_TKR);
            return;
        }
    }

    loc = getNextInp(loc, true);
    if (!loc) {
        sprintf (xmitbuf, " TICKER %2d   : %5d   %6d   %5d    %s", index, Global.Tickers[index].delay, Global.Tickers[index].period, Global.Tickers[index].count, Global.Tickers[index].payload);
        puts(xmitbuf);
        return;
    }

    delay = atoi(loc);
    if ( (delay < 1) || (delay > 3750) ) {
        addError(NULL, ERR_TKR_OUT_OF_BOUNDS);
        return;
    }

    loc = getNextInp(loc, true);
    period = atoi(loc);
    if (!loc || (period < 1) || (period > 3750) ) {
        addError(NULL, ERR_TKR_OUT_OF_BOUNDS);
        return;
    }

    loc = getNextInp(loc, true);
    count = atoi(loc);
    if (!loc || (count < -1) ) {
        addError(NULL, ERR_INVALID_TKR_COUNT);
        return;
    }

    payload = getNextInp(loc, true);
    if (!payload || strlen(payload) == 0) {
        addError(NULL, ERR_INVALID_TKR_PAYLOAD);
        return;
    }

    if (addTicker(index, delay, period, count, payload) == 0) {
        return;
    }
    else {
        addError(NULL, ERR_TKR_ADD_FAILED);
        return;
    }

    PRINT_TKRS:
        /* Print the ticker status before each ticker slot */
        if (Global.Timers.periodT1 > 0) {
            strcpy  (xmitbuf, " TICKER STATUS: ON");
            puts(xmitbuf);
        }

        else {
            strcpy  (xmitbuf, " TICKER STATUS: OFF");
            puts(xmitbuf);
        }

            strcpy  (xmitbuf, " NAME & IDX  | Delay | Period | Count | Payload");
            puts(xmitbuf);

        /* Output the details of each ticker slot! */
        for (i = 0; i < TICKER_COUNT; i++) {
            sprintf (xmitbuf, " TICKER %2d   : %5d   %6d   %5d    %s", i, Global.Tickers[i].delay, Global.Tickers[i].period, Global.Tickers[i].count, Global.Tickers[i].payload);
            puts(xmitbuf);
        }

        return;

} // void runTicker(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN REGISTERS
 * --------------------------------------------------------------------------------
 * -reg                 | show all registers and contents
 * -reg [idx]           | show contents of register at index
 * -reg (0-31) OP (0-31, #) (0-31, #)
 * -reg  DST   OP    SA        SB
 *                      | reg DST <= reg SA OP reg SB
 * -reg   4    ^    5         #666
 *                      | reg 4 <= reg 5 XOR #666
 *                      | reg DST will be modified using contents of SA and SB
 *                      | OPCODES:
 *                      | OP: ?(READ)   =(MOV)  x(XCG)
 *                      | OP: +(ADD)   ++(INC)
 *                      | OP: -(SUB)   --(DEC)
 *                      | OP: ~(NOT)    _(NEG)
 *                      | OP: &(AND)    |(IOR)  ^(XOR)
 *                      | OP: *(MUL)    /(DIV)  %(REM)
 *                      | OP: >(MAX)    <(MIN)  @(MEM)
 *                      | #  is IMMEDIATE DECIMAL
 *                      | #x is IMMEDIATE HEX
 *                      | If #SA or #SB, operand OP be immediate (DEC)
 *                      | If #xSA or #xSB, operand OP be immediate (HEX)
 * - reg DST @ SRC      | reg DST is set to data at address in reg SRC
 * - reg DST @ #SRC     | reg DST is set to data at address in #SRC (dec)
 * - reg DST @ #xSRC    | reg DST is set to data at address in #SRC (hex)
 * - reg  13 @ #x200    | reg 13 is set to the data at address 0x00000200
 *                      | POS / 0 = MAX POS ; NEG / 0 = MAX NEG
 *
 * UNARY INSTRUCTIONS (src A only):
 *      READ (technically 0), MOV, XCG, INC, DEC, NOT, NEG, MEM
 *
 * BINARY INSTRUCTIONS (src A and src B):
 *      ADD, SUB, AND, IOR, XOR, MUL, DIV, REM, MAX, MIN
 */
void runRegister(char *input) {

    char       *xmitbuf = Global.Buffers.msgBuff;
    char        xmitbufmem[64];
    char       *loc;
    int32_t     dst;
    int32_t     srcA;
    bool        srcAImm;
    int32_t     srcB;
    bool        srcBImm;
    int32_t     tmp;
    int         i;
    opTypeList  OP;
    uintptr_t   addr;
    uint32_t                    gateKey;
    ti_sysbios_BIOS_ThreadType  tType;


    /* Initialization */
    srcA = -1;
    srcB = -1;
    srcAImm = false;
    srcBImm = false;

    // EXPECTS TO FIND THE REGISTER INDEX!
    loc = getNextInp(input, true);
    if (!loc) {
        /* Prints all the registers in the register arr */
        goto PRINT_REGS;
    }

    else {
        if (sscanf(loc, "%d", &dst) != 1) {
            addError(NULL, ERR_INVALID_REG_IDX);
            return;
        }
    }

    // EXPECTS TO FIND THE OP CODE!
    loc = getNextInp(loc, true);
    if (!loc) {
        /* If index is set to a valid index then it will print ONE index; otherwise, print all registers */
        goto PRINT_REGS;
    }
    /* Parse the opcode into the variable 'OP' of type 'opTypeList' */
    else {
        if      (strncmp(loc, "++",  strlen("++"))   == 0) OP = INC;
        else if (strncmp(loc, "--",  strlen("--"))   == 0) OP = DEC;
        else if (strncmp(loc, "x" ,  1)              == 0) OP = XCG;
        else if (strchr(loc, '=')) OP = MOV;
        else if (strchr(loc, '@')) OP = MEM;
        else if (strchr(loc, '+')) OP = ADD;
        else if (strchr(loc, '-')) OP = SUB;
        else if (strchr(loc, '~')) OP = NOT;
        else if (strchr(loc, '_')) OP = NEG;
        else if (strchr(loc, '&')) OP = AND;
        else if (strchr(loc, '|')) OP = IOR;
        else if (strchr(loc, '^')) OP = XOR;
        else if (strchr(loc, '*')) OP = MUL;
        else if (strchr(loc, '/')) OP = DIV;
        else if (strchr(loc, '%')) OP = REM;
        else if (strchr(loc, '>')) OP = MAX;
        else if (strchr(loc, '<')) OP = MIN;
        else if (strchr(loc, '?')) OP = READ;
        else {
            addError(NULL, ERR_INVALID_OP_CODE);
            return;
        }
    }

    // EXPECTS TO FIND srcA
    loc = getNextInp(loc, true);
    if      (!loc) {
        if (OP == READ) {
            goto OP_OUTS;
        }
        else {
            addError(NULL, ERR_UNSPEC_INVALID_SRCA);
            return;
        }
    }
    /* if immediate addressing then check for hex or decimal, if hex sscanf as hex, if decimal scanf as demical.
     * if not immedate addressing sscanf as integer and store into srcA
     */
    else if (*loc == '#') {
        srcAImm = true;
        loc++;

        if (OP == XCG) {
            addError(NULL, ERR_UNSPEC_INVALID_SRCA);
            return;
        }

        // Handle both hex and decimal
        if (*loc == 'x' || *loc == 'X') {
            loc++;
            if (sscanf(loc, "%x", &srcA) != 1) {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "Invalid hex: %s", loc);
                addError(xmitbufmem, ERR_UNSPEC_INVALID_SRCA);
                return;
            }
        } else {
            if (sscanf(loc, "%d", &srcA) != 1) {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "Invalid decimal: %s", loc);
                addError(xmitbufmem, ERR_UNSPEC_INVALID_SRCA);
                return;
            }
        }
    }
    else {
        if (sscanf(loc, "%d", &srcA) != 1 || srcA < 0 || srcA >= REG_COUNT) {
            addError(NULL, ERR_UNSPEC_INVALID_SRCA);
            return;
        }
    }

    tType = BIOS_getThreadType();
    if(tType == ti_sysbios_BIOS_ThreadType_Hwi) {
        addError(NULL, ERR_BIOS);
        return;
    }


    // GATE HAS BEEN OPEN, EVERYTHING FROM HERE ON OUT MUST "GOTO REL_GATE" !!!!!
    gateKey = GateSwi_enter(Global.Bios.ScriptGateSwi);

OP_OUTS:
    /* TEST UNARY OP_OUTS, ALL UNARY OP_OUTS should NOT use immediate addressing (except for MEM)! */
    switch (OP) {

        case READ: // 0 Sources Instruction (ignores SRCA and SRCB)
            goto PRINT_REGS_REL_GATE;


        case MOV: // 1 Source Instruction
            if (srcAImm)
                Global.Regs.registers[dst] = srcA;
            else
                Global.Regs.registers[dst] = Global.Regs.registers[srcA];
            goto PRINT_REGS_REL_GATE;


        case XCG: // 1 Source Instruction - CANNOT XCG an IMMEDIATE VALUE!
            if (srcAImm) {
                addError(NULL, ERR_UNSPEC_INVALID_SRCA);
                goto REL_GATE;
            }
            tmp                         = Global.Regs.registers[dst];
            Global.Regs.registers[dst]  = Global.Regs.registers[srcA];
            Global.Regs.registers[srcA] = tmp;
            goto PRINT_REGS_REL_GATE;


        case INC: // 1 Source Instruction - MUST SPECIFY A VALID REGISTER!
            if (srcAImm) {
                Global.Regs.registers[dst] = srcA + 1;
                goto PRINT_REGS_REL_GATE;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] + 1;
                goto PRINT_REGS_REL_GATE;
            }


        case DEC:
            if (srcAImm) {
                Global.Regs.registers[dst] = srcA - 1;
                goto PRINT_REGS_REL_GATE;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] - 1;
                goto PRINT_REGS_REL_GATE;
            }


        case NOT:
            if (srcAImm) {
                Global.Regs.registers[dst] = ~srcA;
                goto PRINT_REGS_REL_GATE;
            }
            else {
                Global.Regs.registers[dst] = ~(Global.Regs.registers[srcA]);
                goto PRINT_REGS_REL_GATE;
            }


        case NEG:
            if (srcAImm) {
                Global.Regs.registers[dst] = (-1)*(srcA);
                goto PRINT_REGS_REL_GATE;
            }
            else {
                Global.Regs.registers[dst] = (-1)*(Global.Regs.registers[srcA]);
                goto PRINT_REGS_REL_GATE;
            }


        case MEM:
            if (srcAImm) {
                addr = (uintptr_t)((unsigned int)(srcA));
            }
            else {
                addr = (uintptr_t)((unsigned int)(Global.Regs.registers[srcA]));
            }

            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                Global.Regs.registers[dst] = *((volatile int32_t *)(addr));
            }

            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                goto REL_GATE;
            }
            goto PRINT_REGS_REL_GATE;


        default:
            break;
    }


    /* PARSES SRCB After it has tested the op code for all the unary operations */
    /* Expect to find SRC B HERE */
    loc = getNextInp(loc, true);
    if      (!loc) {
    	addError(NULL, ERR_UNSPEC_INVALID_SRCB);
    	goto REL_GATE;
    }
    else if (*loc == '#') {
        srcBImm = true;
        loc = loc + 1;
        if (*loc == 'x') {
            loc = loc + 1;
            if (sscanf(loc, "%x", &srcB) != 1) {
               addError(NULL, ERR_UNSPEC_INVALID_SRCB);
               goto REL_GATE;
            }
        }
        else {
            if (sscanf(loc, "%d", &srcB) != 1) {
                addError(NULL, ERR_UNSPEC_INVALID_SRCB);
                goto REL_GATE;
            }
        }
    }
    else {
        if (sscanf(loc, "%d", &srcB) != 1 || srcB < 0 || srcB >= REG_COUNT) {
            addError(NULL, ERR_UNSPEC_INVALID_SRCB);
            goto REL_GATE;
        }
    }



   /*
    * "BINARY" INSTRUCTIONS (src A and src B):
    *      ADD, SUB, AND, IOR, XOR, MUL, DIV, REM, MAX, MIN
    */
    switch (OP) {

        case ADD:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA + srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA + Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] + srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] + Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case SUB:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA - srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA - Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] - srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] - Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case AND:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA & srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA & Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] & srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] & Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case IOR:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA | srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA | Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] | srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] | Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case XOR:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA ^ srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA ^ Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] ^ srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] ^ Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case MUL:
            if      ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA * srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA * Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] * srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] * Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case DIV:
            if ( (srcBImm && srcB == 0) || (!srcBImm && Global.Regs.registers[srcB] == 0) ) {

                /* If srcB is 0 and srcA is addressed then the following "if"-statement and "else if"-statements are to handle immediate srcA div by zero */
                if      ( (srcAImm) && (srcA < 0) ) {
                    Global.Regs.registers[dst] = 0x80000000;
                }
                else if ( (srcAImm) && (srcA > 0) ) {
                    Global.Regs.registers[dst] = 0x7FFFFFFF;
                }

                else if (Global.Regs.registers[srcA] < 0) {
                    Global.Regs.registers[dst] = 0x80000000;
                }
                else {
                    Global.Regs.registers[dst] = 0x7FFFFFFF;
                }

            }

            else if ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA / srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA / Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] / srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] / Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case REM:
            if ( (srcBImm && srcB == 0) || (!srcBImm && Global.Regs.registers[srcB] == 0) ) {
                addError(NULL, ERR_REG_REM_ZERO);
                goto REL_GATE;
            }
            else if ( srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = srcA % srcB;
            }
            else if ( srcAImm && !srcBImm) {
                Global.Regs.registers[dst] = srcA % Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] % srcB;
            }
            else {
                Global.Regs.registers[dst] = Global.Regs.registers[srcA] % Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case MAX:
            if      ( srcAImm &&  srcBImm) {
                if (srcA > srcB)
                    Global.Regs.registers[dst] = srcA;
                else
                    Global.Regs.registers[dst] = srcB;
            }
            else if ( srcAImm && !srcBImm) {
                if (srcA > Global.Regs.registers[srcB])
                    Global.Regs.registers[dst] = srcA;
                else
                    Global.Regs.registers[dst] = Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                if (Global.Regs.registers[srcA] > srcB)
                    Global.Regs.registers[dst] = Global.Regs.registers[srcA];
                else
                    Global.Regs.registers[dst] = srcB;
            }
            else {
                if (Global.Regs.registers[srcA] > Global.Regs.registers[srcB])
                    Global.Regs.registers[dst] = Global.Regs.registers[srcA];
                else
                    Global.Regs.registers[dst] = Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;


        case MIN:
            if      ( srcAImm &&  srcBImm) {
                if (srcA < srcB)
                    Global.Regs.registers[dst] = srcA;
                else
                    Global.Regs.registers[dst] = srcB;
            }
            else if ( srcAImm && !srcBImm) {
                if (srcA < Global.Regs.registers[srcB])
                    Global.Regs.registers[dst] = srcA;
                else
                    Global.Regs.registers[dst] = Global.Regs.registers[srcB];
            }
            else if (!srcAImm &&  srcBImm) {
                if (Global.Regs.registers[srcA] < srcB)
                    Global.Regs.registers[dst] = Global.Regs.registers[srcA];
                else
                    Global.Regs.registers[dst] = srcB;
            }
            else {
                if (Global.Regs.registers[srcA] < Global.Regs.registers[srcB])
                    Global.Regs.registers[dst] = Global.Regs.registers[srcA];
                else
                    Global.Regs.registers[dst] = Global.Regs.registers[srcB];
            }
            goto PRINT_REGS_REL_GATE;

        default:
            break;
    }

    REL_GATE:
        GateSwi_leave(Global.Bios.ScriptGateSwi, gateKey);
        return;

    PRINT_REGS_REL_GATE:
        GateSwi_leave(Global.Bios.ScriptGateSwi, gateKey);

    PRINT_REGS:
        if ( (dst < 0) || (dst > REG_COUNT) ) {
            for (i = 0; i < REG_COUNT; i++) {
                sprintf(xmitbuf, " REGISTER %2d:  %11d   (0x%08X)", i, Global.Regs.registers[i], Global.Regs.registers[i]);
                puts(xmitbuf);
            }
        }
        else {
            sprintf(xmitbuf, " REGISTER %2d:  %11d   (0x%08X)", dst, Global.Regs.registers[dst], Global.Regs.registers[dst]);
            puts(xmitbuf);
        }

        return;

} // void runRegister(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN SCRIPT
 * --------------------------------------------------------------------------------
 *  -script                      displays the entire script table
 *  -script [index]              loads the entry at that script line
 *  -script clr                  clears out entire script table
 *  -script [index] clr          clears out a line of the script.
 *  -script [index] clr all      clears out index and all lines under it.
 *  -script [index] r            reads from a line of the script.
 *  -script [index] w [payload]  writes into the script at that index
 *  -script [index] x            executes from that index to the next blank line.
 *  FUTURE IMPLEMENTATION!
 *  -script l                    displays a list of scripts that can be loaded in
 *  -script l [index]            loads a pre-defined script of specified index.
 *  Use "Semaphore_getCount([Semaphore Handle])" to get the length of the Payload queue at any given time.
 *  Make sure to never pull "script[64]" as WE DON"T KNOW ITS CONTENTS!
 *  Create a "rom" version of some scripts that did not fit.
 */
void runScript(char *input) {

    char       *xmitbuf = Global.Buffers.msgBuff;
    char       *loc;
    int32_t     index;
    uint32_t    semCount;
    uint32_t    scriptCount;
    int         i;

    index = -1;
    semCount = 0;
    scriptCount = 0;

    /* This should return loc with the user-specified index */
    loc = getNextInp(input, true);
    if      (!loc) {
        goto PRINT_SCRIPT;
    }
    else {
//        if      (*loc = 'l') {
//            loadScript(loc)
//        }
        if (strncmpi(loc, "clr", strlen("clr")) == 0) {
            for (i = 0; i < SCRIPT_COUNT; i++) {
                addScript(i, NULL);
            }
            strcpy  (xmitbuf, " ALL SCRIPTS CLEARED");
            puts(xmitbuf);
            return;
        }
        else if (sscanf(loc, "%d", &index) != 1) {
            addError(NULL, ERR_INV_SCRIPT_IDX);
            return;
        }
    }

    /* This should return loc with the user-specified script command. */
    loc = getNextInp(loc, true);
    if      (!loc) {
        goto PRINT_SCRIPT;
    }
    else if (*loc == 'r') {
        goto PRINT_SCRIPT;
    }
    else if (*loc == 'w') {
        goto WRITE_PAYLOAD;
    }
    else if (*loc == 'x') {
        goto EXEC_SCRIPT;
    }
    else if (strncmpi(loc, "clr", strlen("clr")) == 0) {
        loc = getNextInp(loc, true);
        if      (!loc) {
            goto CLR_SCRIPT;
        }
        else if (strncmpi(loc, "all", strlen("all")) == 0) {
            for (i = index; i < SCRIPT_COUNT - 1; i++) {
                addScript(i, NULL);
            }
            sprintf(xmitbuf, " ALL SCRIPTS AFTER INDEX %2d CLEARED", index);
            puts(xmitbuf);
            return;
        }
        else {
            goto CLR_SCRIPT;
        }
    }

    WRITE_PAYLOAD:
        loc = getNextInp(loc, true);
        if (!loc || index == 64) {
            addError(NULL, ERR_INV_SCRIPT_PAYLOAD);
            return;
        }
        else {
            addScript(index, loc);
            goto PRINT_SCRIPT;
        }


    CLR_SCRIPT:
        addScript(index, NULL);
        sprintf (xmitbuf, " SCRIPT %2d CLEARED", index);
        puts    (xmitbuf);
        return;

    EXEC_SCRIPT:
        Global.Script.currentLine = index;
        while (Global.Script.script[Global.Script.currentLine][0] != '\0')  {
            /* For every iteration of the loop, the scriptCount is reset, this number should be between 0 and 7 */
            scriptCount = 0;

            /* This for-loop sets i to be the currentLine and will increment i up to 8, or until it reaches end of the space, or until it encounters a blank line */
            for (i = Global.Script.currentLine; (i < Global.Script.currentLine + MAX_SECTION_LINES) && (Global.Script.script[i][0] != '\0'); i++) {
                scriptCount++;
            }

            /* Collect the semaphore count, if the semCount has as many slots open (or more) as there are scripts to add to payload (scriptCount), then add all the payloads to the queue */
            semCount = Semaphore_getCount(Global.Bios.PayloadSem);
            if (semCount <= MAX_PAYLOAD_COUNT - scriptCount) {
                for (i = 0; i < scriptCount; i++) {
                    addPayload(Global.Script.script[Global.Script.currentLine + i]);
                }
                /* Increment the currentLine (cursor in the script) by however many scripts have been placed in the queue */
                Global.Script.currentLine += scriptCount;
            }
            /* If there is not space in the queue yield to other tasks until space frees up;
             * If space never frees up, the script will never run and other things will take priority;
             * AKA: your shit is cooked and there should not be a circumstance in which you are consistently at payload queue of MAX_PAYLOAD_COUNT - 8 */
            else {
                Task_yield();
            }

            /* break from the while loop if the Global.Script.currentLine is above or equal to SCRIPT_COUNT or if the currentLine is empty */
            if ( (Global.Script.script[Global.Script.currentLine][0] == '\0')) {
                Global.Script.currentLine++;
                break;
           }

        }
        return;



    PRINT_SCRIPT:
        if  ( (index < 0) || (index >= SCRIPT_COUNT - 1) ) {
            for (i = 0; i < SCRIPT_COUNT - 1; i++) {
                sprintf(xmitbuf, " SCRIPT %2d: %s", i, Global.Script.script[i]);
                puts(xmitbuf);
            }
        }
        else {
            sprintf(xmitbuf, " SCRIPT %2d: %s", index, Global.Script.script[index]);
            puts(xmitbuf);
        }

        return;

} // void runScript(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN REMARK
 * --------------------------------------------------------------------------------
 *
 */
void runRem() {

    return;

} // void runRem();
/* ================================================================================ */





/* ================================================================================
 *      RUN CONDITIONAL
 * --------------------------------------------------------------------------------
 *  - if [reg_a] (>, <, =) [reg_b]  ?   [PayloaD]
 *   IF   VAL   CONDITION   VAL   THEN   CMD
 *          | [reg_a] (SA) and [reg_b] (SB) are register contents
 *          | Only valid conditions are (>, = , <)
 *          | This conditional command will only queue payload on CONDITION
 * - if   [SA]  (>, <, =)   [SB]   ?   [PD-T]   :   [PD-F]
 *   IF   VAL   CONDITION   VAL   THEN   CMD    ELSE  CMD
 *          | This conditional will queue PD-T on true or PD-F on false
 *          |  RSA and  RSB  are REGISTER  contents
 *          |  #SA and  #SB  are IMMEDIATE decimal values
 *          | #xSA and #xSB  are IMMEDIATE hex values
 *          |  @SA and  @SB  are MEMORY ADDRESS contents
 *          | @xSA and @xSB  are HEX MEM ADDRESS contents
 *          | @RSA and @RSB  are INDIRECT MEM ADDRESS contents
 *          | >=, <=, and != can be made with >, <, = ...
 * - if   R0        >       240    ?  -print abc : -print 123
 *          | If R0 is greater than 240, then print 'abc', else print '123'
 *          | ':' is a delimiter and must not be used inside of a
 *          | conditional payload; if one must be used, use a script.
 */
void runConditional(char *input) {

    char        xmitbufmem[64];
    char       *loc;
    opTypeCond  compOp;
    int32_t     srcA;
    int32_t     srcB;
    uintptr_t   addr;
    char       *colon;
    bool        condition;
    bool        ifElse;
    char        payloadT[BUFFER_SIZE];
    char        payloadF[BUFFER_SIZE];
    int         len;

    addr = 0;
    ifElse = false;
    condition = false;

    /* Expect to parse SA here, check for each fo the addressing modes */
    loc = getNextInp(input, true);
    if      (!loc) {
        addError(NULL, ERR_COND_SA_INVALID);
        return;
    }
    /* Handles register addressing */
    else if ( (*loc == 'r') || (*loc == 'R') ) {
        loc++;
        if (sscanf(loc, "%d", &srcA) != 1) {
            addError(NULL, ERR_COND_SA_INVALID);
            return;
        }
        else {
            srcA = Global.Regs.registers[srcA];
        }
    }
    /* Handles immediate addressing */
    else if (*loc == '#') {
        loc++;
        if ( (*loc == 'x') || (*loc == 'X') ) {
            loc++;
            if (sscanf(loc, "%x", &srcA) != 1) {
                addError(NULL, ERR_COND_SA_INVALID);
                return;
            }
        }
        else if (sscanf(loc, "%d", &srcA) != 1) {
            addError(NULL, ERR_COND_SA_INVALID);
            return;
        }
    }
    /* Handles direct/indirect addressing */
    else if (*loc == '@') {
        loc++;
        /* Determines whether user wants to do direct direct hex */
        if      ( (*loc == 'x') || (*loc == 'X') ) {
            loc++;
            /* Reads the user's hex input */
            if (sscanf(loc, "%x", &srcA) != 1) {
                addError(NULL, ERR_COND_SA_INVALID);
                return;
            }
            /* Assigns the contents of the user-defined address into srcA */
            addr = (uintptr_t)((unsigned int)(srcA));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcA = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
        /* Determines whether the user wants to do indirect addressing */
        else if ( (*loc == 'r') || (*loc == 'R') ) {
            loc++;
            /* Reads the decimal input after the R (the index of the register) */
            if (sscanf(loc, "%d", &srcA) != 1) {
                addError(NULL, ERR_COND_SA_INVALID);
                return;
            }
            /* Assigns the contents of the memory addressed by the register at the given index into srcA */
            addr = (uintptr_t)((unsigned int)(Global.Regs.registers[srcA]));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcA = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
        /* Direct decimal memory addressing checked last */
        else {
            /* Reads the decimal memory address provided by the user */
            if (sscanf(loc, "%d", &srcA) != 1) {
                addError(NULL, ERR_COND_SA_INVALID);
                return;
            }
            /* Assigns the contents of the memory addressed by the register at the given index into srcA */
            addr = (uintptr_t)((unsigned int)(Global.Regs.registers[srcA]));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcA = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
    }
    /* Error occurs if an invalid srcA was provided after stepping through all the previous parsing */
    else {
        addError(NULL, ERR_COND_SA_INVALID);
        return;
    }

    /* Expect to parse conditional op here, check for the 3 different conditional comparisons */
    loc = getNextInp(loc, true);
    if (!loc) {
        addError(NULL, ERR_COND_OP_INVALID);
        return;
    }
    else {
        switch (*loc) {
            case ('>'):
                compOp = GREATER;
                break;
            case ('<'):
                compOp = LESS;
                break;
            case ('='):
                compOp = EQUAL;
                break;
            default:
                break;
        }
    }

    /* Expect to parse SB here, check for each of the addressing modes again */
    loc = getNextInp(loc, true);
    if      (!loc) {
        addError(NULL, ERR_COND_SB_INVALID);
        return;
    }
    /* Handles register addressing */
    else if ( (*loc == 'r') || (*loc == 'R') ) {
        loc++;
        if (sscanf(loc, "%d", &srcB) != 1) {
            addError(NULL, ERR_COND_SB_INVALID);
            return;
        }
        else {
            srcB = Global.Regs.registers[srcB];
        }
    }
    /* Handles immediate addressing */
    else if (*loc == '#') {
        loc++;
        if ( (*loc == 'x') || (*loc == 'X') ) {
            loc++;
            if (sscanf(loc, "%x", &srcB) != 1) {
                addError(NULL, ERR_COND_SB_INVALID);
                return;
            }
        }
        else if (sscanf(loc, "%d", &srcB) != 1) {
            addError(NULL, ERR_COND_SB_INVALID);
            return;
        }
    }
    /* Handles direct/indirect addressing */
    else if (*loc == '@') {
        loc++;
        /* Determines whether user wants to do direct direct hex */
        if      ( (*loc == 'x') || (*loc == 'X') ) {
            loc++;
            /* Reads the user's hex input */
            if (sscanf(loc, "%x", &srcB) != 1) {
                addError(NULL, ERR_COND_SB_INVALID);
                return;
            }
            /* Assigns the contents of the user-defined address into srcA */
            addr = (uintptr_t)((unsigned int)(srcB));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcB = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
        /* Determines whether the user wants to do indirect addressing */
        else if ( (*loc == 'r') || (*loc == 'R') ) {
            loc++;
            /* Reads the decimal input after the R (the index of the register) */
            if (sscanf(loc, "%d", &srcB) != 1) {
                addError(NULL, ERR_COND_SB_INVALID);
                return;
            }
            /* Assigns the contents of the memory addressed by the register at the given index into srcA */
            addr = (uintptr_t)((unsigned int)(Global.Regs.registers[srcB]));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcB = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
        /* Direct decimal memory addressing checked last */
        else {
            /* Reads the decimal memory address provided by the user */
            if (sscanf(loc, "%d", &srcB) != 1) {
                addError(NULL, ERR_COND_SB_INVALID);
                return;
            }
            /* Assigns the contents of the memory addressed by the register at the given index into srcA */
            addr = (uintptr_t)((unsigned int)(Global.Regs.registers[srcB]));
            addr = addr & ~0x3u;
            if ((addr <= 0x000FFFF) || (addr >= 0x20000000 && addr <= 0x2003FFFF)) {
                srcB = *((volatile int32_t *)(addr));
            }
            /* If the memory address was out of range, an error occurs */
            else {
                snprintf(xmitbufmem, sizeof(xmitbufmem), "0x%08X", (unsigned int)(addr));
                addError(xmitbufmem, ERR_MEMR_OUT_OF_RANGE);
                return;
            }
        }
    }
    /* Error occurs if an invalid srcA was provided after stepping through all the previous parsing */
    else {
        addError(NULL, ERR_COND_SB_INVALID);
        return;
    }

    /* Parser expects to find the '?' delimiter here */
    loc = getNextInp(loc, true);
    if      (!loc || *loc != '?') {
        addError(NULL, ERR_UNSPEC_DELIM);
        return;
    }

    loc = getNextInp(loc, true);
    if (!loc) {
        addError(NULL, ERR_COND_PD_INVALID);
        return;
    }

    /* Checks to see if a colon is present in the code, if so then extra logic must occur to separate the two payloads */
    colon = loc;
    while (*colon && *colon != ':') {
        colon++;
    }

    len = colon - loc;
    if (len > BUFFER_SIZE) {
        addError(NULL, ERR_COND_PD_INVALID);
        return;
    }
    if (*colon == ':') {
        ifElse = true;
        strncpy(payloadT, loc, len);
        payloadT[len] = '\0';

        loc = colon;
        loc = getNextInp(loc, true);
        if (!loc) {
            strncpy(payloadT, loc, sizeof(payloadT));
            payloadF[0] = '\0';
        }
        strncpy(payloadF, loc, sizeof(payloadF));
        payloadF[sizeof(payloadF) - 1] = '\0';
    }

    /* No false payload */
    else {
        strncpy(payloadT, loc, sizeof(payloadT));
        payloadF[0] = '\0';
    }

    switch (compOp) {
        case GREATER:
            condition = (srcA > srcB);
            break;
        case LESS:
            condition = (srcA < srcB);
            break;
        case EQUAL:
            condition = (srcA == srcB);
            break;
    }

    if (condition) {
        addPayload(payloadT);
    }
    else if (ifElse) {
        addPayload(payloadF);
    }
    else {
        return;
    }

    return;

} // void runConditional(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN UART7
 * --------------------------------------------------------------------------------
 *  Make sure that you retain the \r\n on MY TRANSMITS, so the other guy knows to
 *  return or that it is a command (You have to do this because you
 *  "addPayload(inpBuffer)" on \r\n which isn't appended to the buffer!
 */
void runUART7(char *input) {

    char                       *payload;
    ti_sysbios_BIOS_ThreadType  tType;

    /* Advance past the initial "-uart" */
    payload = getNextInp(input, true);
    if (!payload) {
        addError(NULL, ERR_INVALID_UART7);
        return;
    }

    /* Ensure it's not in Hwi or Swi context */
    tType = BIOS_getThreadType();
    if (tType == ti_sysbios_BIOS_ThreadType_Hwi || tType == ti_sysbios_BIOS_ThreadType_Swi) {
        addError(NULL, ERR_BIOS);
        return;
    }

    int len = strlen(payload);

    if (UART_write(Global.Devices.uart7, payload, len) != len) {
        addError(NULL, ERR_WRITE_UNSUCCESSFUL);
        return;
    }

    /* Transmit safely using the protected buffer */
    UART_write(Global.Devices.uart7, "\n", 1);

    return;

} // void runUART7(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN SINE
 * --------------------------------------------------------------------------------
 *  -sine           | Used in callback 0 to
 *  -sine info      | Shows details of the current sine-wave audio output.
 *  -sine [freq]    | Output a sine-wave at the user-specified frequency.
 *                  | Sine waves may only output at a frequency up to 3999 Hz.
 *                  | Speakers have minimal low-frequency response.
 *                  |   + Human ear is also largely incapable of hearing <20 Hz.
 *                  | It is suggested that only frequencies >20 Hz are entered.
 *                  | Interface details:
 *                  |   + For this to operate, move R6 to R8 on BOOSTXL board.
 *                  |   + Make note of the audio amp pin! (PK5/GPIO4 must be zero)
 */
void runSine(char *input) {

    char       *xmitbuf = Global.Buffers.msgBuff;
    char       *loc;
    uint32_t    frequency;
    uint32_t    lowerIndex;
    uint32_t    upperIndex;
    double      upperWeight;
    double      lowerWeight;
    double      answer;
    uint32_t    outputValue;
    uint32_t    transferGood;


    loc = getNextInp(input, true);
    /* Expects to find info or frequency, if nothing then it's just the callback */
    if (!loc) {
        goto OUT_SINE;
    }
    /* If user entered "info", print out the info of the current sinwave */
    else if (strncmpi(loc, "info", strlen("info")) == 0) {
        goto PRINT_SINE_INFO;
    }
    /* Scan for a frequency */
    else {
        /* If an invalid frequency was entered, add the INVALID freq error */
        if (sscanf(loc, "%d", &frequency) != 1) {
            addError(NULL, ERR_INVALID_FREQ);
            return;
        }
    }

    /* Do this if the frequency was out of range */
    if (frequency > 3999) {
        addError(NULL, ERR_FREQ_OUT_OF_RANGE);
        return;
    }

    if (frequency == 0) {
        runGPIO(" 4 w 1"); /* Turn off the amp/speaker if a frequency of 0 is input (sine off) */
        runStream(" 0"); /* Turn off audio stream if local/network voice/audio is enabled */
        Global.Sine.speakerOn = false;
        Global.Sine.frequency = frequency;
        Global.Sine.LUTPosition = 0;
        Global.Sine.LUTDelta = 0;
        goto PRINT_SINE_INFO;
    }

    /* At this point frequency should be valid, so (re)set the global frequency */
    Global.Sine.frequency = frequency;

    /* (re)calculate the sin LUT delta based on the user-defined frequency */
    Global.Sine.LUTDelta = (frequency * SINE_LUT_SIZE_MATH) / SAMPLE_RATE;

    /* Enable speaker and set it on */
    runStream(" 0");
    runTimer(" 125", false); /* Set timer to 125 microseconds */
    runCallback(" 0 -1 -sine", false);
    runGPIO(" 4 w 0"); /* Set GPIO PK5 (AUDIO_OUTPUT) to low to turn speaker on */
    Global.Sine.speakerOn = true;

    return;

    OUT_SINE:
        lowerIndex = (uint32_t)Global.Sine.LUTPosition;
        upperIndex = lowerIndex + 1;
        upperWeight = Global.Sine.LUTPosition - (double)lowerIndex;
        lowerWeight = 1. - upperWeight;
        answer = (double)Global.Sine.sinLUT[lowerIndex] * lowerWeight + (double)Global.Sine.sinLUT[upperIndex] * upperWeight;
        outputValue = round(answer);

        Global.Parameters.spiTransaction3.count = 1;
        Global.Parameters.spiTransaction3.txBuf = (void *) &outputValue;
        Global.Parameters.spiTransaction3.rxBuf = (void *) NULL;

        transferGood = SPI_transfer(Global.Devices.spi3, &Global.Parameters.spiTransaction3);
        if (!transferGood) {
            addError(NULL, ERR_VOICE_BUF);
            return;
        }

        Global.Sine.LUTPosition += Global.Sine.LUTDelta;

        while (Global.Sine.LUTPosition >= (double)SINE_LUT_SIZE_MATH) {
            Global.Sine.LUTPosition -= (double)SINE_LUT_SIZE_MATH;
        }
        return;

    PRINT_SINE_INFO:
        if (Global.Sine.frequency > 0) {
            sprintf(xmitbuf, "Currently playing a sine wave of frequency: %4d", Global.Sine.frequency);
            puts(xmitbuf);
        }
        else {
            sprintf(xmitbuf, "Sine wave is not playing.");
            puts(xmitbuf);
        }
    return;

} // void runSine(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN AUDIO
 * --------------------------------------------------------------------------------
 *  The audio command handles the TX buffers and will output the appropriate sample
 *  to SPI communication to the device's DAC, this function is WHOLLY LOCAL!
 *      + This function is called by timer0 to output samples at 125 us.         */
void runAudio() {

    int             i;
    uint16_t        outputValue;
    uint32_t        transferGood;

    if ( (Global.Dial.callThreeWay == CALL_INACTIVE) && (Global.Dial.callTwoWay == CALL_INACTIVE) ) {

        outputValue = (uint16_t)Global.audioControl.rxBuf.RX_Completed[Global.audioControl.rxBuf.RX_Index++] << 2;
        if (Global.audioControl.rxBuf.RX_Index >= DATA_BLOCK_SIZE) {
            Global.audioControl.rxBuf.RX_Index = 0;
        }

    }

    else {
        for (i = 0; i < TX_BUF_COUNT; i++) {

            /* Make sure that this txBuf is completed otherwise it will point to garbage */
            if (Global.audioControl.txBuf[i].TX_Completed != NULL) {

                /* Make sure the index is non-negative, otherwise something is effed up */
                if (Global.audioControl.txBuf[i].TX_Index >= 0) {

                    /* Respects delay first and foremost, and drops this ONE value from the outbound sample */
                    if (Global.audioControl.txBuf[i].TX_Delay > 0) {
                        Global.audioControl.txBuf[i].TX_Delay--;
                        return;
                    }

                    /* Add the sample to the outband SPI transfer (outputValue) */
                    outputValue += Global.audioControl.txBuf[i].TX_Completed[Global.audioControl.txBuf[i].TX_Index++];

                    /* Applies correction, that is: Takes correction found from runVoice and applies it to the index and zeros out correction */
                    Global.audioControl.txBuf[i].TX_Index += Global.audioControl.txBuf[i].TX_Correction;
                    Global.audioControl.txBuf[i].TX_Correction = 0;

                    /*Wrap around the end of the block if/when it is reached */
                    if (Global.audioControl.txBuf[i].TX_Index >= DATA_BLOCK_SIZE) {
                        Global.audioControl.txBuf[i].TX_Index = 0;

                        /* Switch between ping and pong */
                        if (Global.audioControl.txBuf[i].TX_Completed == Global.audioControl.txBuf[i].TX_Ping) {
                            Global.audioControl.txBuf[i].TX_Completed = Global.audioControl.txBuf[i].TX_Pong;
                        }
                        else {
                            Global.audioControl.txBuf[i].TX_Completed = Global.audioControl.txBuf[i].TX_Ping;
                        }
                    }
                }
            }
        }
    }

    Global.Parameters.spiTransaction3.count = 1;
    Global.Parameters.spiTransaction3.txBuf = (void *) &outputValue;
    Global.Parameters.spiTransaction3.rxBuf = (void *) NULL;

    transferGood = SPI_transfer(Global.Devices.spi3, &Global.Parameters.spiTransaction3);
    if (!transferGood) {
        addError(NULL, ERR_VOICE_BUF);
        return;
    }

} // void runAudio();
/* ================================================================================ */





/* ================================================================================
 *      RUN VOICE
 * --------------------------------------------------------------------------------
 *  The voice command determines which TX Buf(s) to send audio out to.
 *  Determines the source for the adcBuf and also changes the destChoice
 *      + for networking dialIP0 can get destChoice 0, 1 and dialIP1 can get 2, 3.
 *      + for local audio destChoice is either 0 or 1
 *  This function expects the following input:
 *   -voice [destinationChoice] [bufferLength]  \0['bufferLength' number of samples]
 */
void runVoice(char *input) {

    char       *loc;
    int         i;
    uint16_t    destinationChoice;
    uint16_t    bufferLength;
    uint16_t   *destinationBuffer;
    uint8_t     TX01;
    int32_t     current;
    uint32_t    gateKey;

    static int32_t  last[2]     = {-2, -2};
    static int32_t  lastlast[2] = {-4, -4};

    /* Expects to find the destinationChoice here */
    loc = getNextInp(input, true);
    if (!loc) {
        addError(NULL, ERR_MISSING_DEST_CHOICE);
        return;
    }
    destinationChoice = atoi(loc);

    /* Expects to find the bufferLength here */
    loc = getNextInp(loc, true);
    if (!loc) {
        addError(NULL, ERR_MISSING_BUF_LENGTH);
        return;
    }
    bufferLength = atoi(loc);   // Should be "DATA_BLOCK_SIZE"

    /* Error out if the data block size is unmanageable */
    if (bufferLength != DATA_BLOCK_SIZE) {
        addError(NULL, ERR_DATA_BLOCK_MISMATCH);
        return;
    }

    /* loc should be pointing to beginning of bufferLength at this point.
     *      -voice 0 128  \0['bufferLength' number of samples]
     *  LOC:         ^
     *  Needs to increment 6 times to hit samples! */
    for (i = 0; i < 6; i++) {
        loc++;
    }

    /* For network audio, destinationChoice is both 0 and 2 or 1 and 3
     * TX0 will always transmit first per taskADCStream
     * TX1 will always transmit second and only on channel 2 or 3*/
    if      (destinationChoice == 0) {
        TX01 = 0;
        destinationBuffer = Global.audioControl.txBuf[TX01].TX_Ping;
    }
    else if (destinationChoice == 1) {
        TX01 = 0;
        destinationBuffer = Global.audioControl.txBuf[TX01].TX_Pong;
    }

    else if (destinationChoice == 2) {
        TX01 = 1;
        destinationBuffer = Global.audioControl.txBuf[TX01].TX_Ping;
    }

    else if (destinationChoice == 3) {
        TX01 = 1;
        destinationBuffer = Global.audioControl.txBuf[TX01].TX_Pong;
    }

    /* Setup destinationBuffer with necessary data */


    gateKey = GateSwi_enter(Global.Bios.VoiceGateSwi);
    memcpy(destinationBuffer, loc, DATA_BLOCK_SIZE * sizeof(uint16_t));
    if ( Global.audioControl.txBuf[TX01].TX_Completed == NULL) {
        Global.audioControl.txBuf[TX01].TX_Completed = destinationBuffer;
        Global.audioControl.txBuf[TX01].TX_Index = 0;
    }
    GateSwi_leave(Global.Bios.VoiceGateSwi, gateKey);


    current = Global.audioControl.txBuf[TX01].TX_Index;
    if ( (last[TX01] != current) && (lastlast[TX01] != current) ) {

        lastlast[TX01] = last[TX01];
        last[TX01] = current;

        if (current >= DATA_BLOCK_SIZE - DATA_DELAY + 4) {
            Global.audioControl.txBuf[TX01].TX_Correction = -1;
        }

        else if (current <= DATA_BLOCK_SIZE - DATA_DELAY - 4) {
            Global.audioControl.txBuf[TX01].TX_Correction = +1;
        }
    }

    return;

} // void runVoice(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN STREAM
 * --------------------------------------------------------------------------------
 *  The stream commands engages in a "stream sequence" that will perform various
 *  disables, clears, re-enables, and perform the initial ADCBuf conversion
 *  in preparation for streaming audio!
 */
void runStream(char *input) {

    char    *loc;
    uint8_t  val;
    int i;

    loc = getNextInp(input, true);
    if (!loc) {
        addError(NULL, ERR_STREAM_ARG);
        return;
    }
    val = atoi(loc);

    if (val == 0) {

        memset(Global.Callback.callbacks[0].payload, 0, BUFFER_SIZE);
        Global.Callback.callbacks[0].count = 0;
        runTimer(" 0", false);

        if (Global.audioControl.converting == true) {

            /* Cancel the ADCBuf conversion! */
            if (ADCBuf_convertCancel(Global.Devices.adcBuf) != ADCBuf_STATUS_SUCCESS) {
                putB("ADCBuf_convertCancel FAILED!");
                addError(NULL, ERR_CONV_CANC_FAIL);
                return;
            }

            Global.audioControl.converting = false;
            Global.audioControl.rxBuf.RX_Index = -1;

            for (i = 0; i < TX_BUF_COUNT; i++) {
                Global.audioControl.txBuf[i].TX_Completed = NULL;
                Global.audioControl.txBuf[i].TX_Index = -1;
            }

        }

    }

    if (val == 1) {
        if (Global.audioControl.converting == true) {
            putB("Stream already running!");
            return;
        }

        runGPIO(" 4 w 0"); /* TURN AMP ON */
        runGPIO(" 5 w 1"); /* TURN MIC ON */
        runTimer(" 125", false); /* Set timer to 125 milliseconds */

        memset(Global.audioControl.rxBuf.RX_Ping, 0, DATA_BLOCK_SIZE);
        memset(Global.audioControl.rxBuf.RX_Pong, 0, DATA_BLOCK_SIZE);

        for (i = 0; i < TX_BUF_COUNT; i++) {
            memset(Global.audioControl.txBuf[i].TX_Ping, 0, DATA_BLOCK_SIZE);
            memset(Global.audioControl.txBuf[i].TX_Pong, 0, DATA_BLOCK_SIZE);
            Global.audioControl.txBuf[i].TX_Completed = NULL;
            Global.audioControl.txBuf[i].TX_Index = -1;
            Global.audioControl.txBuf[i].TX_Delay = DATA_DELAY;
            Global.audioControl.txBuf[i].TX_Correction = 0;
        }

        Global.audioControl.converting = false;

    }

    if (val == 2) {
        if (Global.audioControl.converting == true) {

            putB("Conversion in progress, please begin at beginning of stream sequence");
            return;
        }

        putSL(" \b");
        if (ADCBuf_convert(Global.Devices.adcBuf, &Global.audioControl.conversion, 1) != ADCBuf_STATUS_SUCCESS) {
            addError(NULL, ERR_CONVERT_FAILED);
            putB("ERR CONVERT FAILED");
            return;
        }
        putSL(" \b");

        runCallback(" 0 -1 -audio", false);

        Global.audioControl.converting = true;
    }

    return;

} // void runStream(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN DIAL
 * --------------------------------------------------------------------------------
 * Frontend -dial commands:
 * DONE: -dial               | Displays whether a call is active and the callers if so.
 * DONE: -dial local/slef    | Engages in a local audio call. NO NETWORKING!
 * DONE: -dial IP1           | Begins a call with 'IP1' on default port 1000.
 * DONE: -dial IP1 IP2       | Begins a call with 'IP1' and 'IP2' on default port 1000.
 *  -dial accept        | Accepts an incoming dial request.
 *  -dial decline       | Declines an incoming dial request.
 *  -dial leave         | Leaves an active call.
 *  -dial join          | Joins an ongoing call.
 *
 * Backend -dial commands:
 *  -dial request b0    | Sends a dial request from b0 to b1 and/or b2.
 *  -dial response [bN] [accept/decline]    | Sends a response from b1/b2 to b0.
 *  -dial confirm [2/3] b0 [b1/b2]          | Outlines # of callers and destChoice
 *  -dial remove [b0/b1/b2]                 | Sent on a 'leave', removes a caller
 *  -dial add    [b0/b1/b2]                 | Informs devices to add an IP to TX.
 */
void runDial(char *input) {

    char   *xmitbuf = Global.Buffers.msgBuff;
    char   *loc;
    int     ipsParsed;
    char    ipTempString[16];

    loc = getNextInp(input, true);


    /*  -dial               | Displays whether a call is active and the callers if so. */
    if (!loc) {
        if (Global.Dial.callThreeWay == 1) {
            strcpy(xmitbuf,  " Phone call is ACTIVE!");
            puts(xmitbuf);
            sprintf(xmitbuf, "     Caller 1: %s", Global.Dial.ip1String);
            puts(xmitbuf);
            sprintf(xmitbuf, "     Caller 2: %s", Global.Dial.ip2String);
            puts(xmitbuf);
        }
        else if (Global.Dial.callTwoWay == CALL_ACTIVE) {
            strcpy(xmitbuf,  " Phone call is ACTIVE!");
            puts(xmitbuf);
            sprintf(xmitbuf, "     Caller 1: %s", Global.Dial.ip1String);
            puts(xmitbuf);
        }
        else {
            strcpy(xmitbuf,  " Phone call is NOT active!");
            puts(xmitbuf);
        }
        return;
    }


    /* If the user enters -dial local or -dial self does the following: */
    else if ( (strncmpi(loc, "local", sizeof("local")) == 0) || (strncmpi(loc, "self", sizeof("self")) == 0) ) {
        runStream(" 0");
        runStream(" 1");
        runStream(" 2");
        strcpy(xmitbuf, " Beginning local audio session!");
        puts(xmitbuf);
    }


    /* If the user enters "-dial accept", do the following: */
    else if (strncmpi(loc, "accept", sizeof("accept")) == 0) {

        /* If a request never occurred to accept/decline the call, inform the user that a request must be made before declining/accepting */
        if (Global.Dial.callPing == false) {
            addError(NULL, ERR_NOT_PINGED);
            return;
        }

        /* If NOT in a two-way or three-way call AND a ping HAS been received, then send a response to the requestor! */
        if (Global.Dial.callThreeWay == CALL_INACTIVE || Global.Dial.callTwoWay == CALL_INACTIVE) {
            sprintf(xmitbuf, "-netudp %s -dial response %s accept", Global.Dial.ip1String, Global.Dial.ip0String);
            runNETUDP(xmitbuf, 0);
        }

        /* Otherwise the accept fails and error out! */
        else {
            addError(NULL, ERR_ACCEPT_FAILED);
            Global.Dial.callPing = false;
            return;
        }

        Global.Dial.callPing = false;

    }


    /* If the user enters -dial decline, do the following: */
    else if (strncmpi(loc, "decline", sizeof("decline")) == 0) {

        /* If a request never occurred to accept/decline the call, inform the user that a request must be made before declining/accepting */
        if (Global.Dial.callPing == false) {
            addError(NULL, ERR_NOT_PINGED);
            return;
        }

        /* If NOT in a two-way or three-way call AND a ping HAS been received, then send a response to the requestor! */
        if (Global.Dial.callThreeWay == 0 || Global.Dial.callTwoWay == 0) {
            sprintf(xmitbuf, "-netudp %s -dial response %s decline", Global.Dial.ip1String, Global.Dial.ip0String);
            runNETUDP(xmitbuf, 0);
        }

        /* Otherwise the decline fails and error out! */
        else {
            addError(NULL, ERR_DECLINE_FAILED);
            Global.Dial.callPing = false;
            return;
        }

        Global.Dial.callPing = false;

    }


//    if (strncmpi(loc, "leave", sizeof("leave")) == 0) {
//        /* netudp the leave sequence to the other two boards! */
//    }
//
//    if (strncmpi(loc, "join", sizeof("join")) == 0) {
//        /* netudp that this board would like to join an ongoing call. Add error condition if other boards say
//         * they're not in a call */
//    }


    /* If the baord sees "-dial request (another board has requested that this board join a call), then it will do the following: */
    /* -dial request b0    | Sends a dial request from b0 to b1 and/or b2. */
    else if (strncmpi(loc, "request", sizeof("request")) == 0) {

        /* Sets the callPing variable to true to indicate to system that a request to join a call has been received */
        Global.Dial.callPing = true;


        /* If a request is received, store the ip of the requestor into ip1String */
        /* IPs at this point should be: ip0String (myself), ip1String (requestor), ip2String (empty) */
        loc = getNextInp(loc, true);
        if (!loc) {
            addError(NULL, ERR_REQ_FAILED);
            return;
        }
        if (sscanf(loc, "%15s", Global.Dial.ip1String) != 1) {
            addError(NULL, ERR_REQ_FAILED);
            return;
        }

        /* Prompt user to acecpt or decline the phone call */
        strcpy(xmitbuf, " Accept (-dial accept) or Decline (-dial decline) phone call?");
        puts(xmitbuf);

    }


    /* If the board sees "-dial response", then it will perform the following: */
    /* -dial response [bN] [accept/decline]    | Sends a response from b1/b2 to b0. */
    /* THIS IS THE FINAL STEP FOR BOARD0, IT WILL BE ABLE TO ACCEPT TXs AT THIS POINT! */
    else if (strncmpi(loc, "response", sizeof("response")) == 0) {

        /* If not expecting a call but a response is received, error out! */
        if      (Global.Dial.callThreeWay == 0 && Global.Dial.callTwoWay == CALL_INACTIVE) {
            addError(NULL, ERR_UNPROMPTED_RESP);
            return;
        }

        /* If already in a three way call OR already in a two-way call and NOT expecting a three way call, error out */
        else if ( (Global.Dial.callThreeWay == 1) || ( (Global.Dial.callTwoWay == CALL_ACTIVE) && (Global.Dial.callThreeWay != 2) ) ) {
            addError(NULL, ERR_ALREADY_IN_CALL);
            return;
        }

        /* If expecting EITHER a two-way OR a three-way call, then confirm dial response and assign TX appropriately  */
        else if ( (Global.Dial.callTwoWay == CALL_EXPECTING) ) {

            /* Expects to find the ip of the responder here */
            loc = getNextInp(loc, true);
            if (!loc) {
                putB("loc Null");
                addError(NULL, ERR_RESP_FAILED);
                return;
            }
            else if (sscanf(loc, "%15s", Global.Dial.ip1String) != 1) {
                putB("IP scan bad");
                addError(NULL, ERR_RESP_FAILED);
                return;
            }

            /* Expects to find "accept" or "decline" here */
            loc = getNextInp(loc, true);
            if (!loc) {
                putB("loc Null for accept/decline");
                addError(NULL, ERR_RESP_FAILED);
                return;
            }
            /* If user types "accept"
             *  + Change callTwoWay to "in-call" or 1
             *  + Change ipAddr1 to the entered ip1StringAddress which will then begin audio transmission! */
            else if (strncmpi(loc, "accept", sizeof("accept")) == 0) {
                Global.Dial.callTwoWay = CALL_ACTIVE;
                Global.Dial.ipAddr1 = 1/* Assignment of ipAddr1 in the proper format! */;

                runStream(" 0");
                runStream(" 1");
                runStream(" 2");

                /* Send the "-dial" confirmation to the responder board!
                 * Confirms to "responder" board that it is:
                 *   a two-way call and to set destinationChoice to THIS BOARD (ip0String) */
                sprintf(xmitbuf, "-netudp %s -dial confirm 2 %s", Global.Dial.ip1String, Global.Dial.ip0String);
                runNETUDP(xmitbuf, 0);
            }

            else {
                Global.Dial.callThreeWay = CALL_INACTIVE;
                memset(Global.Dial.ip1String, 0, sizeof(Global.Dial.ip1String));
                Global.Dial.ipAddr1 = 0;
            }
        }

        /* If IN a two-way call AND expecting a three-way call, then confirm SECOND dial response and assign TX appropriately */
        else if ( (Global.Dial.callTwoWay == CALL_ACTIVE) && (Global.Dial.callThreeWay == CALL_EXPECTING) ) {

            /* Expects to find the ip of the responder here */
            loc = getNextInp(loc, true);
            if (!loc) {
                addError(NULL, ERR_RESP_FAILED);
                return;
            }
            if (sscanf(loc, "%15s", Global.Dial.ip2String) != 1) {
                addError(NULL, ERR_RESP_FAILED);
                return;
            }

            /* Expects to find "accept" or "decline" here */
            loc = getNextInp(loc, true);
            if (!loc) {
                addError(NULL, ERR_RESP_FAILED);
                return;
            }
            /* If user types "accept"
             *  + Change callTwoWay to "in-call" or 1
             *  + Change ipAddr1 to the entered ip1StringAddress which will then begin audio transmission! */
            if (strncmpi(loc, "accept", sizeof("accept")) == 0) {
                Global.Dial.callThreeWay = 1;
                Global.Dial.ipAddr2 = 1;

                runStream(" 0");
                runStream(" 1");
                runStream(" 2");

                /* Send the "-dial" confirmation to the responder board!
                 * Confirms to "responder" (which must be board 2 at this point) AND "board 1" that it is:
                 *   a three-way call and to set destinationChoice to THIS BOARD (ip0String) and BOARD 1 (ip1String) for responder AND
                 *   a three-way call and to set destinationChoice to THIS BOARD (ip0String) and BOARD 2 (ip2String) for board 1 (ip1String) */
                sprintf(xmitbuf, "-netudp %s -dial confirm 3 %s %s", Global.Dial.ip1String, Global.Dial.ip0String, Global.Dial.ip2String);
                runNETUDP(xmitbuf, 0);
                sprintf(xmitbuf, "-netudp %s -dial confirm 3 %s %s", Global.Dial.ip2String, Global.Dial.ip1String, Global.Dial.ip0String);
                runNETUDP(xmitbuf, 0);

                strcpy(ipTempString, Global.Dial.ip2String);
                strcpy(Global.Dial.ip2String, Global.Dial.ip1String);
                strcpy(Global.Dial.ip1String, ipTempString);

            }
            else {
                Global.Dial.callThreeWay = 1;
                memset(Global.Dial.ip2String, 0, sizeof(Global.Dial.ip2String));
                Global.Dial.ipAddr2 = 0;
            }
        }

        /* Error out if it does not fall into any of the above categories: */
        else {

            addError(NULL, ERR_RESP_FAILED);
            return;
        }


    }


    /* If the board sees "-dial confirm", then it will perform the following */
    /*  -dial confirm [2/3] b0 [b1/b2]          | Outlines # of callers and destChoice */
    else if (strncmpi(loc, "confirm", sizeof("confirm")) == 0) {

        /*   */
        loc = getNextInp(loc, true);
        if (!loc) {
            addError(NULL, ERR_CONFIRM_FAILED);
            return;
        }

        else if (*loc == '2') {

            loc = getNextInp(loc, true);
            if (!loc) {
                addError(NULL, ERR_CONFIRM_FAILED);
                return;
            }
            if (sscanf(loc, "%15s", Global.Dial.ip1String) != 1) {
                addError(NULL, ERR_CONFIRM_FAILED);
                return;
            }

            Global.Dial.callTwoWay = CALL_ACTIVE;
            Global.Dial.callThreeWay = CALL_INACTIVE;
            Global.Dial.ipAddr1 = 1;

            runStream(" 0");
            runStream(" 1");
            runStream(" 2");

        }

        else if (*loc == '3') {

            loc = getNextInp(loc, true);
            if (!loc) {
                addError(NULL, ERR_CONFIRM_FAILED);
                return;
            }
            if (sscanf(loc, "%15s %15s", Global.Dial.ip1String, Global.Dial.ip2String) != 2) {
                addError(NULL, ERR_CONFIRM_FAILED);
                return;
            }

            Global.Dial.callTwoWay = CALL_ACTIVE;
            Global.Dial.callThreeWay = CALL_ACTIVE;
            Global.Dial.ipAddr1 = 1;
            Global.Dial.ipAddr2 = 1;

            runStream(" 0");
            runStream(" 1");
            runStream(" 2");

        }

        else {
            addError(NULL, ERR_CONFIRM_FAILED);
            return;
        }
    }

    /* POSSIBLE FUTURE IMPLEMENTATION */
//    if (strncmpi(loc, "remove", sizeof("remove")) == 0) {
//        /*   */
//    }
//
//    if (strncmpi(loc, "add", sizeof("add")) == 0) {
//        /*
//         *
//         */
//    }



    else if (isdigit(*loc)) {

        /* Check if the user is already in call: */
        if (Global.Dial.callThreeWay == CALL_ACTIVE || Global.Dial.callTwoWay == CALL_ACTIVE) {
            addError(NULL, ERR_ALREADY_IN_CALL);
            return;
        }

        /* Store the first and second IP addresses into their respective variables: */
        ipsParsed = sscanf(loc, "%15s %15s", Global.Dial.ip1String, Global.Dial.ip2String);

        /* switch-case which determines whether to EXPECT a 3 way call, EXPECT a 2 way call, or no call. */
        switch (ipsParsed) {
        case 0:
            Global.Dial.callThreeWay = CALL_INACTIVE;
            Global.Dial.callTwoWay = CALL_INACTIVE;
            break;
        case 1:
            Global.Dial.callThreeWay = CALL_INACTIVE;
            Global.Dial.callTwoWay = CALL_EXPECTING;
            break;
        case 2: /* Has to allow both for three-way because the three-way call sequence involves a two-way call at some point */
            Global.Dial.callThreeWay = CALL_EXPECTING;
            Global.Dial.callTwoWay = CALL_EXPECTING;
            break;
        default:
            Global.Dial.callThreeWay = CALL_INACTIVE;
            Global.Dial.callTwoWay = CALL_INACTIVE;
            break;
        }

        if (Global.Dial.callThreeWay == CALL_EXPECTING) {

            /* Send a netudp message to ip1 that ip0 is requesting a call: */
            sprintf(xmitbuf, "-netudp %s -dial request %s", Global.Dial.ip1String, Global.Dial.ip0String);
            runNETUDP(xmitbuf, 0);

            /* Send a netudp message to ip2 that ip0 is requesting a call: */
            sprintf(xmitbuf, "-netudp %s -dial request %s", Global.Dial.ip2String, Global.Dial.ip0String);
            runNETUDP(xmitbuf, 0);

            return;
        }

        /* If a two-way call is expected do the following: */
        if (Global.Dial.callTwoWay == CALL_EXPECTING) {

            /* Send a netudp message to ip1 that ip0 is requesting a call: */
            sprintf(xmitbuf, "-netudp %s -dial request %s", Global.Dial.ip1String, Global.Dial.ip0String);
            runNETUDP(xmitbuf, 0);

            return;
        }

        else {
            addError(NULL, ERR_DIAL_REQ_FAILED);
            return;
        }
    }

    return;

} // void runDial(char *input);
/* ================================================================================ */





/* ================================================================================
 *      RUN NETUDP
 * --------------------------------------------------------------------------------
 *
 */
void runNETUDP(char *input, int32_t binaryCount) {

    char       *loc;
    uint32_t    gateKey;
    int32_t     payloadNext;

    loc = getNextInp(input, true);
    if (!loc) {
        putB("No payload attached to message!");
        return;
    }

    /* Enter NETUDP GateSwi so as to allow the netudpQ to be updated! */
    gateKey = GateSwi_enter(Global.Bios.NETUDPGateSwi);

    /* Increment through the NETUDP circular buffer to add the instruction to the payload buffer! */
    payloadNext = Global.netudpQueue.netudpWriting + 1;
    if (payloadNext >= MAX_NETUDP_COUNT) {
        payloadNext = 0;
    }

    /* If the next payload is equal to the index of the payload reading, then overflow occurs! */
    if (payloadNext == Global.netudpQueue.netudpReading) {
        GateSwi_leave(Global.Bios.NETUDPGateSwi, gateKey);
        puts("Network Queue Overflow");
        return;
    }

    /* After both error cases are checked, largely the same addPayload logic is followed! */
    memcpy(Global.netudpQueue.netudpPayloads[Global.netudpQueue.netudpWriting], loc, strlen(loc) + binaryCount + 1);
    Global.netudpQueue.netudpBinaryCount[Global.netudpQueue.netudpWriting] = binaryCount; // binaryCount used for transmitting voice
    Global.netudpQueue.netudpWriting = payloadNext;
    GateSwi_leave(Global.Bios.NETUDPGateSwi, gateKey);

    Semaphore_post(Global.Bios.NETUDPSem);

    return;

} // void runNETUDP(char *input);
/* ================================================================================ */






/* ================================================================================
 *      HELP MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help" command
 *   -about
 *   -adc
 *   -audio
 *   -callback
 *   -clear
 *   -dial
 *   -gpio
 *   -help
 *   -if
 *   -memr
 *   -print
 *   -reg
 *   -script
 *   -sine
 *   -stream
 *   -ticker
 *   -timer
 *   -uart
 *   -voice
 *
 */
void msgHelp() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, "                         Help / List of Commands");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "--------------------------------------------------------------------------------");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -about");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -audio");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -callback");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -clear");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -dial");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -error");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -gpio");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -help");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -if");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -memr");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -print");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -reg");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -rem");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -script");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -sine");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -stream");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -ticker");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -timer");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -uart");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -voice");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "--------------------------------------------------------------------------------");
    puts    (xmitbuf);

} // void msgHelp();
/* ================================================================================ */





/* ================================================================================
 *      HELP HELP MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help help" command
 */
void msgHelpHelp() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, " -help             :  Displays a list of supported commands");
    puts(xmitbuf);
    strcpy(xmitbuf, "                      Type -help [command] for details about that command");
    puts(xmitbuf);

} // void msgHelpHelp();
/* ================================================================================ */





/* ================================================================================
 *      HELP ABOUT MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help about" command
 */
void msgHelpAbout() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, " -about            :  Name, assignment #, current version, date & time");
    puts(xmitbuf);

} // void msgHelpAbout();
/* ================================================================================ */





/* ================================================================================
 *      HELP PRINT MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help print" command
 */
void msgHelpPrint() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, " -print [param]    :  Prints any characters after the print statement");
    puts(xmitbuf);

} // void msgHelpPrint();
/* ================================================================================ */





/* ================================================================================
 *      HELP MEMR
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help memr" command
 */
void msgHelpMemr() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, " -memr  [addr]     :  Read a memory location and print contents");
    puts(xmitbuf);
    strcpy(xmitbuf, "                       + Shows 4 quads of memory contents from 0xMEMADDR");
    puts(xmitbuf);
    strcpy(xmitbuf, "                       + FLASH: 0x00000000 to 0x000FFFFF");
    puts(xmitbuf);
    strcpy(xmitbuf, "                       +  SRAM: 0x20000000 to 0x2003FFFF");
    puts(xmitbuf);

} // void msgHelpMemr();
/* ================================================================================ */





/* ================================================================================
 *      HELP GPIO MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help gpio" command
 */
void msgHelpGPIO() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " GPIO DETAILS    :");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 0  |   Corresponds to LED D1  on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 1  |   Corresponds to LED D2  on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 2  |   Corresponds to LED D3  on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 3  |   Corresponds to LED D4  on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 4  |   Corresponds to pin PK5 on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 5  |   Corresponds to pin PD4 on the board [r/w/t] [Out, Std, Med, Low]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 6  |   Corresponds to USR_SW1 on the board [r]     [In,  PU, Fall Edge]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " GPIO 7  |   Corresponds to USR_SW2 on the board [r]     [In,  PU, Fall Edge]");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -gpio           :   Displays all of the GPIO and their states");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -gpio #         :   Displays the info for that GPIO index (on, off, etc.)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -gpio # t       :   Toggles that specific GPIO index if it can be toggled");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -gpio # r/w     :   Read or write a value from/to a GPIO");
    puts(xmitbuf);

    return;

} // void msgHelpGPIO();
/* ================================================================================ */





/* ================================================================================
 *      HELP ERROR MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help error" command
 */
void msgHelpError() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -error          :   Displays a list of all errors and their counts.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -error [code]   :   Displays details for a specific error code and its count.");
    puts(xmitbuf);

    return;

} // void msgHelpError();
/* ================================================================================ */





/* ================================================================================
 *      HELP TIMER MESSAGE
 * --------------------------------------------------------------------------------
 *  Contains the output sequence for the "-help error" command:
 *      -timer           | print current timer period (in us) to perform CALLBACK 0
 *      -timer 0         | turn timer off
 *      -timer VAL       | set timer period to VAL (in us)
 *      -timer VAL m     | set timer period to VAL (in ms)
 *      -timer VAL s     | set timer period to VAL (in s )
 *      -timer VAL Unit  | set timer period to VAL (in TI=RTOS "enum-UNITs")
 *                       | timer period must be >= 100 us or 0
 *                       | timer period must be < 35.7 s
 */
void msgHelpTimer() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -timer           | print current timer period (in us) to perform CALLBACK 0");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -timer 0         | turn timer off");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -timer VAL       | set timer period to VAL (in us)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -timer VAL s     | set timer period to VAL (in s )");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -timer VAL Unit  | set timer period to VAL (in TI=RTOS \"enum-UNITs\")");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                  | timer period must be >= 100 us or 0");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                  | timer period must be < 35.7 s");
    puts(xmitbuf);

    return;

} // void msgHelpTimer();
/* ================================================================================ */






/* ================================================================================
 *      HELP CALLBACK MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help callback(s)"
 *  -callback                    :   Displays all callbacks, counts, and functions
 *  -callback clr                :   Clears ALL callbacks
 *  -callback [idx]              :   Displays details for a callback.
 *  -callback [idx] clr          :   Clears a callback at that specific index.
 *  -callback [idx] [cnt] [func] :   CB_idx will execute func \"cnt\" times.
 *
 */
void msgHelpCallback() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -callback                    :   Displays all callbacks, counts, and functions");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -callback clr                :   Clears ALL callbacks");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -callback [idx]              :   Displays details for a callback.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -callback [idx] clr          :   Clears a callback at that specific index.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -callback [idx] [cnt] [func] :   CB_idx will execute func \"cnt\" times.");
    puts(xmitbuf);

    return;

} // void msgHelpCallback();
/* ================================================================================ */





/* ================================================================================
 *      HELP TICKER MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help ticker(s)"
 * -ticker       :  Displays a list of the all the ticker details and ticker status
 *                  also outlines their delays, periods, count, and payload.
 * -ticker 'k'   :  Ticker kill - Clears the entire ticker table.
 * -ticker 'p'   :  Pause all tickers.
 * -ticker 'r'   :  Run/Resume all tickers.
 * -ticker [idx] :  Shows details of the ticker at the specified index.
 *
 * -ticker [idx] [del] [per] [cnt] [payload] : Sets up ticker_idx
 *
 *  idx     |   index    ('u' specifies next open ticker slot)
 *  del     |   delay    (between 1 - 3750)
 *  per     |   period   (between 1 - 3750)
 *  cnt     |   count    (-1 for unlimited)
 *  payload |   payload  (payload to run on ticker activation)
 */
void msgHelpTicker() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -ticker       :  Displays a list of ticker details and ticker status");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                  also outlines their delays, periods, count, and payload.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -ticker 'k'   :  Ticker kill - Clears the entire ticker table.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -ticker 'p'   :  Pause all tickers.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -ticker 'r'   :  Run/Resume all tickers.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -ticker [idx] :  Shows details of the ticker at the specified index.");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -ticker [idx] [del] [per] [cnt] [payload] : Sets up ticker_idx");
    puts(xmitbuf);
    strcpy  (xmitbuf, "  idx     |   index    ('u' specifies next open ticker slot)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "  del     |   delay    (between 1 - 3750)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "  per     |   period   (between 1 - 3750)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "  cnt     |   count    (-1 for unlimited)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "  payload |   payload  (payload to run on ticker activation)");
    puts(xmitbuf);

    return;

} // void msgHelpTicker();
/* ================================================================================ */





/* ================================================================================
 *      HELP REGISTER MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help reg(s)"
 * -reg                 | show all registers and contents
 * -reg [idx]           | show contents of register at index
 * -reg (0-31) OP (0-31, #) (0-31, #)
 * -reg  DST   OP    SA        SB
 *                      | reg DST <= reg SA OP reg SB
 * -reg   4    ^    5         #666
 *                      | reg 4 <= reg 5 XOR #666
 *                      | reg DST will be modified using contents of SA and SB
 *                      | OPCODES:
 *                      | OP: ?(READ)   =(MOV)  x(XCG)
 *                      | OP: +(ADD)   ++(INC)
 *                      | OP: -(SUB)   --(DEC)
 *                      | OP: ~(NOT)    _(NEG)
 *                      | OP: &(AND)    |(IOR)  ^(XOR)
 *                      | OP: *(MUL)    /(DIV)  %(REM)
 *                      | OP: >(MAX)    <(MIN)  @(MEM)
 *                      | #  is IMMEDIATE DECIMAL
 *                      | #x is IMMEDIATE HEX
 *                      | If #SA or #SB, operand OP be immediate (DEC)
 *                      | If #xSA or #xSB, operand OP be immediate (HEX)
 * - reg DST @ SRC      | reg DST is set to data at address in reg SRC
 * - reg DST @ #SRC     | reg DST is set to data at address in #SRC (dec)
 * - reg DST @ #xSRC    | reg DST is set to data at address in #SRC (hex)
 * - reg  13 @ #x200    | reg 13 is set to the data at address 0x00000200
 *                      | POS / 0 = MAX POS ; NEG / 0 = MAX NEG
 */
void msgHelpReg() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -reg                 | show all registers and contents");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -reg [idx]           | show contents of register at index");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -reg (0-31) OP (0-31, #) (0-31, #)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -reg  DST   OP    SA        SB");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | reg DST <= reg SA OP reg SB");
    puts(xmitbuf);
    strcpy  (xmitbuf, " -reg   4    ^    5         #666");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | reg 4 <= reg 5 XOR #666");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | reg DST will be modified using contents of SA and SB");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OPCODES:");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: ?(READ)   =(MOV)  x(XCG)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: +(ADD)   ++(INC)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: -(SUB)   --(DEC)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: ~(NOT)    _(NEG)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: &(AND)    |(IOR)  ^(XOR)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | OP: *(MUL)    /(DIV)  %(REM)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | #  is IMMEDIATE DECIMAL");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | #x is IMMEDIATE HEX");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | If #SA or #SB, operand OP be immediate (DEC)");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | If #xSA or #xSB, operand OP be immediate (HEX)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " - reg DST @ SRC      | reg DST is set to data at address in reg SRC");
    puts(xmitbuf);
    strcpy  (xmitbuf, " - reg DST @ #SRC     | reg DST is set to data at address in #SRC (dec)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " - reg DST @ #xSRC    | reg DST is set to data at address in #SRC (hex)");
    puts(xmitbuf);
    strcpy  (xmitbuf, " - reg  13 @ #x200    | reg 13 is set to the data at address 0x00000200");
    puts(xmitbuf);
    strcpy  (xmitbuf, "                      | POS / 0 = MAX POS ; NEG / 0 = MAX NEG");
    puts(xmitbuf);

    return;

} // void msgHelpReg();
/* ================================================================================ */





/* ================================================================================
 *      HELP SCRIPT MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help callback(s)"
 * -script                      displays the entire script table
 * -script [index]              loads the entry at that script line
 * -script clr all              clears out entire script table
 * -script [index] clr          clears out a line of the script.
 * -script [index] clr all      clears out index and all lines under it.
 * -script [index] r            reads from a line of the script.
 * -script [index] w [payload]  writes into the script at that index
 * -script [index] x            executes from that index to the next blank line.
 *
 * FUTURE IMPLEMENTATION
 * -script l                    displays a list of scripts that can be loaded in
 * -script l [index]            loads a pre-defined script of specified index.
 *
 * Use "Semaphore_getCount([Semaphore Handle])" to get the length of the Payload queue at any given time.
 * Make sure to never pull "script[64]" as WE DON"T KNOW ITS CONTENTS!
 *
 * Create a "rom" version of some scripts that did not fit.
 *
 */
void msgHelpScript() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf,  " -script                      displays the entire script table");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index]              loads the entry at that script line.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script clr                  clears out the entire script table.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index] clr          clears out a line of the script.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index] clr all      clears out all lines under a given index.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index] r            reads from a line of the script.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index] w [payload]  writes into the script at that index.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -script [index] x            executes from that index to the next blank line.");
    puts    (xmitbuf);

    return;

} // void msgHelpScript();
/* ================================================================================ */





/* ================================================================================
 *      HELP CONDITIONAL MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help conditional(s)"
 * - if [reg_a] (>, <, =) [reg_b]  ?   [PayloaD]
 *   IF   VAL   CONDITION   VAL   THEN   CMD
 *          | [reg_a] (SA) and [reg_b] (SB) are register contents
 *          | Only valid conditions are (>, = , <)
 *          | This conditional command will only queue payload on CONDITION
 * - if   [SA]  (>, <, =)   [SB]   ?   [PD-T]   :   [PD-F]
 *   IF   VAL   CONDITION   VAL   THEN   CMD    ELSE  CMD
 *          | This conditional will queue PD-T on true or PD-F on false
 *          |  RSA and  RSB  are REGISTER  contents
 *          |  #SA and  #SB  are IMMEDIATE decimal values
 *          | #xSA and #xSB  are IMMEDIATE hex values
 *          |  @SA and  @SB  are MEMORY ADDRESS contents
 *          | @xSA and @xSB  are HEX MEM ADDRESS contents
 *          | @RSA and @RSB  are INDIRECT MEM ADDRESS contents
 *          | >=, <=, and != can be made with >, <, = ...
 * - if   R0        >       240    ?  -print abc : -print 123
 *          | If R0 is greater than 240, then print 'abc', else print '123'
 *          | ':' is a delimiter and must not be used inside of a
 *          | conditional payload; if one must be used, use a script.
 */
void msgHelpConditional() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf,  " - if [reg_a] (>, <, =) [reg_b]  ?   [PayloaD]");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "   IF   VAL   CONDITION   VAL   THEN   CMD");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | [reg_a] (SA) and [reg_b] (SB) are register contents");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | Only valid conditions are (>, = , <)");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | This conditional command will only queue payload on CONDITION");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " - if   [SA]  (>, <, =)   [SB]   ?   [PD-T]   :   [PD-F]");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "   IF   VAL   CONDITION   VAL   THEN   CMD    ELSE  CMD");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | This conditional will queue PD-T on true or PD-F on false");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          |  RSA and  RSB  are REGISTER  contents");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          |  #SA and  #SB  are IMMEDIATE decimal values");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | #xSA and #xSB  are IMMEDIATE hex values");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          |  @SA and  @SB  are MEMORY ADDRESS contents");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | @xSA and @xSB  are HEX MEM ADDRESS contents");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | @RSA and @RSB  are INDIRECT MEM ADDRESS contents");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | >=, <=, and != can be made with >, <, = ...");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " - if   R0        >       240    ?  -print abc : -print 123");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | If R0 is greater than 240, then print 'abc', else print '123' ");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | IMPORTANT ':' is a delimiter and must not be used inside of a");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | conditional payload; if one must be used, use a script.");
    puts    (xmitbuf);

} // void msgHelpConditional();
/* ================================================================================ */




/* ================================================================================
 *      HELP UART7 MESSAGE
 * --------------------------------------------------------------------------------
 *  Outputs the message for the command "-help uart"
 * CONFIGURATION:
 *          | TX: Pin PC5/4
 *          | RX: Pin PC4/3
 *          | Recall that TX--RX and RX--TX between the two boards
 * -uart [payload]
 *              | Transmits a payload to another device.
 *              | Payload transmits "as-is"; make sure it's correct!
 */
void msgHelpUART7() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf,  " CONFIGURATION:");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | TX: Pin PC5/4");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | RX: Pin PC4/3");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | Recall that TX--RX and RX--TX between the two boards");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  " -uart [payload]");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | Transmits a payload to another device.");
    puts    (xmitbuf);
    strcpy  (xmitbuf,  "          | Payload transmits \"as-is\"; make sure it's correct!");
    puts    (xmitbuf);

    return;

} // void msgHelpUART7();
/* ================================================================================ */





/* ================================================================================
 *      HELP CLEAR MESSAGE
 * --------------------------------------------------------------------------------
 *  -clear       | Clears the PuTTY console.
 */
void msgHelpClear() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -clear       | Clears the PuTTY console.");
    puts    (xmitbuf);

    return;

} // void msgHelpClear();
/* ================================================================================ */





/* ================================================================================
 *      HELP CLEAR MESSAGE
 * --------------------------------------------------------------------------------
 *  -clear       | Clears the PuTTY console.
 */
void msgHelpRem() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -rem [remark]  | Allows the user to add comments to a script.");
    puts    (xmitbuf);

    return;

} // void msgHelpRem();
/* ================================================================================ */





/* ================================================================================
 *      HELP SINE MESSAGE
 * --------------------------------------------------------------------------------
 *  -sine           | Shows details of the current sine-wave audio output.
 *  -sine [freq]    | Output a sine-wave at the user-specified frequency.
 *                  | Sine waves may only output at a frequency up to 3999 Hz.
 *                  | Speakers have minimal low-frequency response.
 *                  |   + Human ear is also largely incapable of hearing <20 Hz.
 *                  | It is suggested that only frequencies >20 Hz are entered.
 *                  | Interface details:
 *                  |   + For this to operate, move R6 to R8 on BOOSTXL board.
 *                  |   + Make note of the audio amp pin! (PK5 must be zero)
 */
void msgHelpSine() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -sine           | Shows details of the current sine-wave audio output.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -sine [freq]    | Output a sine-wave at the user-specified frequency.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 | Sine waves may only output at a frequency up to 3999 Hz.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 | Speakers have minimal low-frequency response.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 |   + Human ear is also largely incapable of hearing <20 Hz.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 | It is suggested that only frequencies >20 Hz are entered.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 | Interface details:");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 |   + For this to operate, move R6 to R8 on BOOSTXL board.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "                 |   + Make note of the audio amp pin! (PK5 must be zero)");
    puts    (xmitbuf);

    return;

} // void msgHelpSine();
/* ================================================================================ */





/* ================================================================================
 *      HELP AUDIO MESSAGE
 * --------------------------------------------------------------------------------
 *
 */
void msgHelpAudio() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " - audio     | This function is used only in the background!");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "             | It processes the audio /'long loads/' from local");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "             | or network calls and SPI tranfers it to THIS devices's DAC.");
    puts    (xmitbuf);

    return;

} // void msgHelpAudio();
/* ================================================================================ */





/* ================================================================================
 *      HELP STREAM MESSAGE
 * --------------------------------------------------------------------------------
 *  - stream 0 | This step in the stream sequence clears timers and callbacks
 *             | the necessary timers and callbacks to operate audio.
 *  - stream 1 | Sets up all the necessary components for receiving and
 *             | transmitting audio on the device.
 *  - stream 2 | Called after some delay to finally begin ADC conversion.
 *             | Once ADC conversion is successful, stream sequence ends.
 */
void msgHelpStream() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " - stream 0 | This step in the stream sequence clears timers and callbacks");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "            | the necessary timers and callbacks to operate audio.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " - stream 1 | Sets up all the necessary components for receiving and");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "            | transmitting audio on the device.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " - stream 2 | Called after some delay to finally begin ADC conversion.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "            | Once ADC conversion is successful, stream sequence ends.");
    puts    (xmitbuf);

    return;

} // void msgHelpStream();
/* ================================================================================ */





/* ================================================================================
 *      HELP VOICE MESSAGE
 * --------------------------------------------------------------------------------
 *  Allows the user to investigate the voice command though the user will not be
 *  able to enter this as a command.
 *
 */
void msgHelpVoice() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -voice  | This function is used in the background.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "         | Used to direct voice messages to local audio or");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "         | to different devices via NETUDP.");
    puts    (xmitbuf);

    return;

} // void msgHelpVoice();
/* ================================================================================ */





/* ================================================================================
 *      HELP DIAL MESSAGE
 * --------------------------------------------------------------------------------
 * Frontend -dial commands:
 *  -dial               | Displays whether a call is active and the callers if so.
 *  -dial local/slef    | Engages in a local audio call. NO NETWORKING!
 *  -dial IP1           | Begins a call with 'IP1' on default port 1000.
 *  -dial IP1 IP2       | Begins a call with 'IP1' and 'IP2' on default port 1000.
 *  -dial accept        | Accepts an incoming dial request.
 *  -dial decline       | Declines an incoming dial request.
 *  -dial leave         | Leaves an active call.
 *  -dial join          | Joins an ongoing call.
 *
 * Backend -dial commands:
 *  -dial request b0    | Sends a dial request from b0 to b1 and/or b2.
 *  -dial response [bN] [accept/decline]    | Sends a response from b1/b2 to b0.
 *  -dial confirm [2/3] b0 [b1/b2]          | Outlines # of callers and destChoice
 *  -dial remove [b0/b1/b2]                 | Sent on a 'leave', removes a caller
 *  -dial add    [b0/b1/b2]                 | Informs devices to add an IP to TX.
 */
void msgHelpDial() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " Frontend -dial commands:");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial               | Displays whether a call is active and the callers if so.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial local/self    | Engages in a local audio call. NO NETWORKING!");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial self          | Engages in a local 'call' via local network.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial IP            | Begins a call with 'IP' on default port 1000.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial IP1 IP2       | Begins a call with 'IP1' and 'IP2' on default port 1000.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial accept        | Accepts an incoming dial request.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial decline       | Declines an incoming dial request.");
    puts    (xmitbuf);
//    strcpy  (xmitbuf, "  -dial leave         | Leaves an active call.");
//    puts    (xmitbuf);
//    strcpy  (xmitbuf, "  -dial join          | Joins an ongoing call.");
//    puts    (xmitbuf);
    strcpy  (xmitbuf, " Backend -dial commands:");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial request b0    | Sends a dial request from b0 to b1 and/or b2.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial response [bN] [accept/decline]    | Sends a response from b1/b2 to b0.");
    puts    (xmitbuf);
    strcpy  (xmitbuf, "  -dial confirm [2/3] b0 [b1/b2]          | Outlines # of callers and destChoice");
    puts    (xmitbuf);
//    strcpy  (xmitbuf, "  -dial remove [b0/b1/b2]                 | Sent on a 'leave', removes a caller.");
//    puts    (xmitbuf);
//    strcpy  (xmitbuf, "  -dial add    [b0/b1/b2]                 | Informs devices to add an IP to TX.");
//    puts    (xmitbuf);

    return;

} // void msgHelpDial();
/* ================================================================================ */





/* ================================================================================
 *      HELP NETUDP MESSAGE
 * --------------------------------------------------------------------------------
 *  -netudp 0.0.0.0         [PAYLOAD] | Sends PAYLOAD to nobody
 *  -netudp nobody          [PAYLOAD] | Sends PAYLOAD to nobody
 *  -netudp 127.0.0.1       [PAYLOAD] | Sends PAYLOAD to localhost/myself
 *  -netudp localhost       [PAYLOAD] | Sends PAYLOAD to localhost/myself
 *  -netudp 255.255.255.255 [PAYLOAD] | Broadcasts PAYLOAD
 *  -netudp broadcast       [PAYLOAD] | Broadcasts PAYLOAD
 *  -netudp 239.255.255.1   [PAYLOAD] | Multicasts PAYLOAD
 *  -netudp multicast       [PAYLOAD] | Multicasts PAYLOAD
 *  -netudp [IP_ADDRESS]    [PAYLOAD] | Sends PAYLOAD to specified IP address
 */
void msgHelpNETUDP() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy  (xmitbuf, " -netudp 0.0.0.0         [PAYLOAD] | Sends PAYLOAD to nobody");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp nobody          [PAYLOAD] | Sends PAYLOAD to nobody");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp 127.0.0.1       [PAYLOAD] | Sends PAYLOAD to localhost/myself");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp localhost       [PAYLOAD] | Sends PAYLOAD to localhost/myself");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp 255.255.255.255 [PAYLOAD] | Broadcasts PAYLOAD");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp broadcast       [PAYLOAD] | Broadcasts PAYLOAD");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp 239.255.255.1   [PAYLOAD] | Multicasts PAYLOAD");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp multicast       [PAYLOAD] | Multicasts PAYLOAD");
    puts    (xmitbuf);
    strcpy  (xmitbuf, " -netudp [IP_ADDRESS]    [PAYLOAD] | Sends PAYLOAD to specified IP address");
    puts    (xmitbuf);

    return;

} // void msgHelpNETUDP();
/* ================================================================================ */





/* ================================================================================
 *      ABOUT MESSAGE
 * --------------------------------------------------------------------------------
 *  This function contains the code to output the "-about" message.
 */
void msgAbout() {

    char *xmitbuf = Global.Buffers.msgBuff;

    strcpy(xmitbuf, "                            About this Program");
    puts(xmitbuf);
    strcpy(xmitbuf, "--------------------------------------------------------------------------------");
    puts(xmitbuf);
    strcpy(xmitbuf, " Jonathan Masley     R11827104");
    puts(xmitbuf);
    strcpy(xmitbuf, " HW13 - 3-Way Voice");
    puts(xmitbuf);
    strcpy(xmitbuf, " Version 3.2");
    puts(xmitbuf);
    snprintf(xmitbuf, BUFFER_SIZE, " %s  ,  %s", __DATE__, __TIME__);
    puts(xmitbuf);
    strcpy(xmitbuf, "--------------------------------------------------------------------------------");
    puts(xmitbuf);

    return;

} // void msgAbout();
/* ================================================================================ */





/* ================================================================================
 *      PRINT MESSAGE
 * --------------------------------------------------------------------------------
 *  This function contains the code to output the "-print [output]" message.
 *
 *  This function is used to print whatever the user determines after the command
 *  "-print [statement]"
 */
void msgPrint(char *input) {

    char   *xmitbuf = Global.Buffers.msgBuff;
    char   *loc;

    loc = getNextInp(input, false);

    if (!loc) {
        addError(NULL, ERR_LOC_NULL);
    }
    else {
        strcpy(xmitbuf, loc);
        puts(xmitbuf);
    }

    return;

} // void msgPrint(char *input);
/* ================================================================================ */





/* ================================================================================
 *      ERROR MESSAGE
 * --------------------------------------------------------------------------------
 *  This function contains the code to output the "-error" message.
 */
void msgError(char *input) {
    char *xmitbuf = Global.Buffers.msgBuff;

    /* Wish I could do a switch-case statement here, but I also really like organizing my errors as "0a", "1b" and whatnot
     * (I couldn't be bothered to switch these over to integer for comparison, lol) */

    // Error 0a : ERR_WRITE_UNSUCCESSFUL
    if      (strstr(input, ERR_WRITE_UNSUCCESSFUL)  != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: UART_W Error      | prot_write unsuccessful.", ERR_WRITE_UNSUCCESSFUL, Global.Errors.error0aCount);
        puts(xmitbuf);
    }

    // Error 0b : ERR_LOC_NULL
    else if (strstr(input, ERR_LOC_NULL)            != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Parse Error       | a NULL loc was returned.", ERR_LOC_NULL, Global.Errors.error0bCount);
        puts(xmitbuf);
    }

    // Error 0c : ERR_PARSE
    else if (strstr(input, ERR_PARSE)               != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: User Error        | invalid command returned.", ERR_PARSE, Global.Errors.error0cCount);
        puts(xmitbuf);
    }

    // Error 0d : ERR_BUFF_OVERFLOW
    else if (strstr(input, ERR_BUFF_OVERFLOW)       != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Buffer Overflow   | a buffer overflowed", ERR_BUFF_OVERFLOW, Global.Errors.error0dCount);
        puts(xmitbuf);
    }

    // Error 1a : ERR_HELP
    else if (strstr(input, ERR_HELP)                != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Help Error        | help for an unrecognized command.", ERR_HELP, Global.Errors.error1aCount);
        puts(xmitbuf);
    }

    // Error 2a : ERR_MEMR_OUT_OF_RANGE
    else if (strstr(input, ERR_MEMR_OUT_OF_RANGE)   != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Addr Out of Range | MEMR address is out of range.", ERR_MEMR_OUT_OF_RANGE, Global.Errors.error2aCount);
        puts(xmitbuf);
    }

    // Error 2b : ERR_MEMR_INVALID_INP
    else if (strstr(input, ERR_MEMR_INVALID_INP)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad MEMR Input    | invalid inp entered in MEMR func.", ERR_MEMR_INVALID_INP, Global.Errors.error2bCount);
        puts(xmitbuf);
    }

    // Error 3a : ERR_INVALID_GPIO_IDX
    else if (strstr(input, ERR_INVALID_GPIO_IDX)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO index    | invalid GPIO index.", ERR_INVALID_GPIO_IDX, Global.Errors.error3aCount);
        puts(xmitbuf);
    }

    // Error 3b : ERR_INVALID_GPIO_OP
    else if (strstr(input, ERR_INVALID_GPIO_OP)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO index    | invalid GPIO index.", ERR_INVALID_GPIO_OP, Global.Errors.error3bCount);
        puts(xmitbuf);
    }

    // Error 3c : ERR_INVALID_GPIO_VAL
    else if (strstr(input, ERR_INVALID_GPIO_VAL)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO value    | invalid or no GPIO value.", ERR_INVALID_GPIO_VAL, Global.Errors.error3cCount);
        puts(xmitbuf);
    }

    // Error 3d : ERR_INVALID_GPIO_WT
    else if (strstr(input, ERR_INVALID_GPIO_WT)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO w/t      | invalid index for GPIO w/t.", ERR_INVALID_GPIO_WT, Global.Errors.error3dCount);
        puts(xmitbuf);
    }

    // Error 4a : ERR_BIOS
    else if (strstr(input, ERR_BIOS)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bios Error        | an error occurred w the bios.", ERR_BIOS, Global.Errors.error4aCount);
        puts(xmitbuf);
    }

    // Error 4b : ERR_PAYLOAD_Q_OF
    else if (strstr(input, ERR_PAYLOAD_Q_OF)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Payload OF        | payload queue overflowed.", ERR_PAYLOAD_Q_OF, Global.Errors.error4bCount);
        puts(xmitbuf);
    }

    // Error 4c : ERR_MSG_Q_OF
    else if (strstr(input, ERR_MSG_Q_OF)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: output msg OF     | message queue overflowed.", ERR_MSG_Q_OF, Global.Errors.error4cCount);
        puts(xmitbuf);
    }

    // Error 5a : ERR_INVALID_TIMER_PER
   else if (strstr(input, ERR_INVALID_TIMER_PER)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid Timer Per | User entered a bad timer period.", ERR_INVALID_TIMER_PER, Global.Errors.error5aCount);
        puts(xmitbuf);
    }

    // Error 5b : ERR_INVALID_TIMER_UNITS
    else if (strstr(input, ERR_INVALID_TIMER_UNITS)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid Time Unit | Units specified unrecognized", ERR_INVALID_TIMER_UNITS, Global.Errors.error5bCount);
        puts(xmitbuf);
    }

    // Error 5c : ERR_MIN_TIMER_THRESH
    else if (strstr(input, ERR_MIN_TIMER_THRESH)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Timer per <min    | Specified period under min.", ERR_MIN_TIMER_THRESH, Global.Errors.error5cCount);
        puts(xmitbuf);
    }

    // Error 5d : ERR_MAX_TIMER_THRESH
    else if (strstr(input, ERR_MAX_TIMER_THRESH)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Timer per >max    | Specified period above max.", ERR_MAX_TIMER_THRESH, Global.Errors.error5dCount);
        puts(xmitbuf);
    }

    // Error 6a : ERR_INVALID_CB_IDX
    else if (strstr(input, ERR_INVALID_CB_IDX)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid CB index  | Invalid CB index specified.", ERR_INVALID_CB_IDX, Global.Errors.error6aCount);
        puts(xmitbuf);
    }

    // Error 6b : ERR_INVALID_CB_COUNT
    else if (strstr(input, ERR_INVALID_CB_COUNT)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid CB count  | Invalid CB count specified.", ERR_INVALID_CB_COUNT, Global.Errors.error6bCount);
        puts(xmitbuf);
    }

    // Error 6c : ERR_UNSPEC_CB_FUNC
    else if (strstr(input, ERR_UNSPEC_CB_FUNC)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: No CB payload     | No CB payload was specified.", ERR_UNSPEC_CB_FUNC, Global.Errors.error6cCount);
        puts(xmitbuf);
    }

    // Error 7a : ERR_NO_FREE_TKR
    else if (strstr(input, ERR_NO_FREE_TKR)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: No free Tkr       | No free tkr available.", ERR_NO_FREE_TKR, Global.Errors.error7aCount);
        puts(xmitbuf);
    }

    // Error 7b : ERR_TKR_INVALID_INDEX
    else if (strstr(input, ERR_TKR_INVALID_INDEX)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid Tkr idx   | Invalid ticker index specified.", ERR_TKR_INVALID_INDEX, Global.Errors.error7bCount);
        puts(xmitbuf);
    }

    // Error 7c : ERR_TKR_OUT_OF_BOUNDS
    else if (strstr(input, ERR_TKR_OUT_OF_BOUNDS)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Tkr del/per bad   | Ticker period/delay invalid.", ERR_TKR_OUT_OF_BOUNDS, Global.Errors.error7cCount);
        puts(xmitbuf);
    }

    // Error 7d : ERR_INVALID_TKR_COUNT
    else if (strstr(input, ERR_INVALID_TKR_COUNT)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid Tkr count | Ticker count invalid.", ERR_INVALID_TKR_COUNT, Global.Errors.error7dCount);
        puts(xmitbuf);
    }

    // Error 7e : ERR_INVALID_TKR_PAYLOAD
    else if (strstr(input, ERR_UNSPEC_CB_FUNC)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad Tkr payload   | Ticker payload invalid.", ERR_INVALID_TKR_PAYLOAD, Global.Errors.error7eCount);
        puts(xmitbuf);
    }

    // Error 7f : ERR_TKR_ADD_FAILED
    else if (strstr(input, ERR_TKR_ADD_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: addTkr fxn failed | addTicker() function failed.", ERR_TKR_ADD_FAILED, Global.Errors.error7fCount);
        puts(xmitbuf);
    }

    // Error 8a : ERR_INVALID_REG_IDX
    else if (strstr(input, ERR_INVALID_REG_IDX)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad reg idx       | Invalid/unspecified reg dest idx.", ERR_INVALID_REG_IDX, Global.Errors.error8aCount);
        puts(xmitbuf);
    }

    // Error 8b : ERR_INVALID_OP_CODE
    else if (strstr(input, ERR_INVALID_OP_CODE)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad reg op code   | Invalid/unspecified reg op code.", ERR_INVALID_OP_CODE, Global.Errors.error8bCount);
        puts(xmitbuf);
    }

    // Error 8c : ERR_UNSPEC_INVALID_SRCA
    else if (strstr(input, ERR_UNSPEC_INVALID_SRCA)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad reg srcA      | Invalid/unspecified reg src A.", ERR_UNSPEC_INVALID_SRCA, Global.Errors.error8cCount);
        puts(xmitbuf);
    }

    // Error 8d : ERR_UNSPEC_INVALID_SRCB
    else if (strstr(input, ERR_UNSPEC_INVALID_SRCB)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad reg srcB      | Invalid/unspecified reg src B.", ERR_UNSPEC_INVALID_SRCB, Global.Errors.error8dCount);
        puts(xmitbuf);
    }

    // Error 8e : ERR_REG_REM_ZERO
    else if (strstr(input, ERR_REG_REM_ZERO)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Div by 0 in REM   | Attempted to div by 0 for REM.", ERR_REG_REM_ZERO, Global.Errors.error8eCount);
        puts(xmitbuf);
    }

    // Error 9a: ERR_INV_SCRIPT_IDX
     else if (strstr(input, ERR_INV_SCRIPT_IDX)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad Script idx    | Invalid or unspecified script index.", ERR_INV_SCRIPT_IDX, Global.Errors.error9aCount);
        puts(xmitbuf);
    }

    // Error 9b : ERR_INV_SCRIPT_PAYLOAD
    else if (strstr(input, ERR_INV_SCRIPT_PAYLOAD)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad Script pd     | Invalid of unspecified script payload.", ERR_INV_SCRIPT_PAYLOAD, Global.Errors.error9bCount);
        puts(xmitbuf);
    }

    // Error 10a : ERR_COND_SA_INVALID
    else if (strstr(input, ERR_COND_SA_INVALID)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad -if srcA      | Invalid of unspecified conditional srcA.", ERR_COND_SA_INVALID, Global.Errors.error10aCount);
        puts(xmitbuf);
    }

    // Error 10b : ERR_COND_SB_INVALID
    else if (strstr(input, ERR_COND_SB_INVALID)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad -if srcB      | Invalid of unspecified conditional srcB.", ERR_COND_SB_INVALID, Global.Errors.error10bCount);
        puts(xmitbuf);
    }

    // Error 10c : ERR_COND_OP_INVALID
    else if (strstr(input, ERR_COND_OP_INVALID)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad -if Op        | Invalid of unspecified conditional operator.", ERR_COND_OP_INVALID, Global.Errors.error10cCount);
        puts(xmitbuf);
    }

    // Error 10d : ERR_COND_PD_INVALID
    else if (strstr(input, ERR_COND_PD_INVALID)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad -if PD        | Invalid of unspecified conditional payload.", ERR_COND_PD_INVALID, Global.Errors.error10dCount);
        puts(xmitbuf);
    }

    // Error 10e : ERR_UNSPEC_DELIM
    else if (strstr(input, ERR_UNSPEC_DELIM)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad -if delimiter | Invalid of unspecified conditional delimiter.", ERR_UNSPEC_DELIM, Global.Errors.error10eCount);
        puts(xmitbuf);
    }

    // Error 11a : ERR_INVALID_UART7
    else if (strstr(input, ERR_INVALID_UART7)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad or no UART PD | Invalid or unspecified UART7 payload.", ERR_INVALID_UART7, Global.Errors.error11aCount);
        puts(xmitbuf);
    }

    // Error 12a : ERR_INVALID_FREQ
    else if (strstr(input, ERR_INVALID_FREQ)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Invalid Freq Err  | Invalid frequency specified.", ERR_INVALID_FREQ, Global.Errors.error12aCount);
        puts(xmitbuf);
    }

    // Error 12b : ERR_FREQ_OUT_OF_RANGE
    else if (strstr(input, ERR_FREQ_OUT_OF_RANGE)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Freq Out of Range | User-input frequency out of range.", ERR_FREQ_OUT_OF_RANGE, Global.Errors.error12bCount);
        puts(xmitbuf);
    }

    // Error 12c : ERR_VOICE_BUF
    else if (strstr(input, ERR_VOICE_BUF)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: SPI Voice Buff    | SPI voice buffer/transaction bad.", ERR_VOICE_BUF, Global.Errors.error12cCount);
        puts(xmitbuf);
    }

    // Error 14a : ERR_ADC_BUF_INVALID
    else if (strstr(input, ERR_ADC_BUF_INVALID)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: ADCBuf Error      | Bad ADCBuf during ADCBuf callback.", ERR_ADC_BUF_INVALID, Global.Errors.error14aCount);
        puts(xmitbuf);
    }

    // Error 14b : ERR_UNKNOWN_RX_BUF
    else if (strstr(input, ERR_UNKNOWN_RX_BUF)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: ADC Ping Pong Bad | Bad ADCBuf from Ping/Pong.", ERR_UNKNOWN_RX_BUF, Global.Errors.error14bCount);
        puts(xmitbuf);
    }

    // Error 16a : ERR_NOT_PINGED
    else if (strstr(input, ERR_NOT_PINGED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Acc/Dec W/O Ping  | Attempted to accept/decline w/o ping.", ERR_NOT_PINGED, Global.Errors.error16aCount);
        puts(xmitbuf);
    }

    // Error 16b : ERR_ACCEPT_FAILED
    else if (strstr(input, ERR_ACCEPT_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: -dial accept fail | -dial accept failed or misformatted.", ERR_ACCEPT_FAILED, Global.Errors.error16bCount);
        puts(xmitbuf);
    }

    // Error 16c : ERR_DECLINE_FAILED
    else if (strstr(input, ERR_DECLINE_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: -dial decline bad | -dial decline failed or misformatted.", ERR_DECLINE_FAILED, Global.Errors.error16cCount);
        puts(xmitbuf);
    }

    // Error 16d : ERR_REQ_FAILED
    else if (strstr(input, ERR_REQ_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: -dial request bad | -dial request failed or misformatted.", ERR_REQ_FAILED, Global.Errors.error16dCount);
        puts(xmitbuf);
    }

    // Error 16e : ERR_UNPROMPTED_RESP
    else if (strstr(input, ERR_UNPROMPTED_RESP)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Unexp -dial resp  | Unexpected -dial response.", ERR_UNPROMPTED_RESP, Global.Errors.error16eCount);
        puts(xmitbuf);
    }

    // Error 16f : ERR_ALREADY_IN_CALL
    else if (strstr(input, ERR_ALREADY_IN_CALL)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Already in a Call | Improper -dial action performed while in call.", ERR_ALREADY_IN_CALL, Global.Errors.error16fCount);
        puts(xmitbuf);
    }

    // Error 16g : ERR_RESP_FAILED
    else if (strstr(input, ERR_RESP_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: -dial resp failed | -dial response failed or was misformatted", ERR_RESP_FAILED, Global.Errors.error16gCount);
        puts(xmitbuf);
    }

    // Error 16h : ERR_CONFIRM_FAILED
    else if (strstr(input, ERR_CONFIRM_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: -dial confirm bad | -dial confirm failed. CRITICAL error.", ERR_CONFIRM_FAILED, Global.Errors.error16hCount);
        puts(xmitbuf);
    }

    // Error 16i : ERR_DIAL_REQ_FAILED
    else if (strstr(input, ERR_DIAL_REQ_FAILED)    != NULL) {
        sprintf(xmitbuf, " ERR %s - %d: Bad Usr -dial req | User's -dial b1/b2 request was bad!.", ERR_DIAL_REQ_FAILED, Global.Errors.error16iCount);
        puts(xmitbuf);
    }


    // List of all the errors and their codes.
    else {
        sprintf(xmitbuf, " ERR %s - %d: UART_W Error      | prot_write unsuccessful.", ERR_WRITE_UNSUCCESSFUL, Global.Errors.error0aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Parse Error       | a NULL loc was returned.", ERR_LOC_NULL, Global.Errors.error0bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: User Error        | invalid command returned.", ERR_PARSE, Global.Errors.error0cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Buffer Overflow   | a buffer overflowed", ERR_BUFF_OVERFLOW, Global.Errors.error0dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Help Error        | help for an unrecognized command.", ERR_HELP, Global.Errors.error1aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Addr Out of Range | MEMR address is out of range.", ERR_MEMR_OUT_OF_RANGE, Global.Errors.error2aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad MEMR Input    | invalid inp entered in MEMR func.", ERR_MEMR_INVALID_INP, Global.Errors.error2bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO index    | invalid GPIO index.", ERR_INVALID_GPIO_IDX, Global.Errors.error3aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO Op       | invalid GPIO operation specified.", ERR_INVALID_GPIO_OP, Global.Errors.error3bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO value    | invalid or no GPIO value.", ERR_INVALID_GPIO_VAL, Global.Errors.error3cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad GPIO w/t      | invalid index for GPIO w/t.", ERR_INVALID_GPIO_WT, Global.Errors.error3dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: BIOS_ERR          | an error occurred w the bios.", ERR_BIOS, Global.Errors.error4aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Payload OF        | payload queue overflowed.", ERR_PAYLOAD_Q_OF, Global.Errors.error4bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: output msg OF     | message queue overflowed.", ERR_MSG_Q_OF, Global.Errors.error4cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid Timer Per | User entered a bad timer period.", ERR_INVALID_TIMER_PER, Global.Errors.error5aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid Time Unit | Units specified unrecognized", ERR_INVALID_TIMER_UNITS, Global.Errors.error5bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Timer per <min    | Specified period under min.", ERR_MIN_TIMER_THRESH, Global.Errors.error5cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Timer per >max    | Specified period above max.", ERR_MAX_TIMER_THRESH, Global.Errors.error5dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid CB index  | Invalid CB index specified.", ERR_INVALID_CB_IDX, Global.Errors.error6aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid CB count  | Invalid CB count specified.", ERR_INVALID_CB_COUNT, Global.Errors.error6bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: No CB payload     | No CB payload was specified.", ERR_UNSPEC_CB_FUNC, Global.Errors.error6cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: No free Tkr       | No free tkr available.", ERR_NO_FREE_TKR, Global.Errors.error7aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid Tkr idx   | Invalid ticker index specified.", ERR_TKR_INVALID_INDEX, Global.Errors.error7bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Tkr del/per bad   | Ticker period/delay invalid.", ERR_TKR_OUT_OF_BOUNDS, Global.Errors.error7cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid Tkr count | Ticker count invalid.", ERR_INVALID_TKR_COUNT, Global.Errors.error7dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad Tkr payload   | Ticker payload invalid.", ERR_INVALID_TKR_PAYLOAD, Global.Errors.error7eCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: addTkr fxn failed | addTicker() function failed.", ERR_TKR_ADD_FAILED, Global.Errors.error7fCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad reg idx       | Invalid/unspecified reg dest idx.", ERR_INVALID_REG_IDX, Global.Errors.error8aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad reg op code   | Invalid/unspecified reg op code.", ERR_INVALID_OP_CODE, Global.Errors.error8bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad reg srcA      | Invalid/unspecified reg src A.", ERR_UNSPEC_INVALID_SRCA, Global.Errors.error8cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad reg srcB      | Invalid/unspecified reg src B.", ERR_UNSPEC_INVALID_SRCB, Global.Errors.error8dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Div by 0 in REM   | Attempted to div by 0 for REM.", ERR_REG_REM_ZERO, Global.Errors.error8eCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad Script idx    | Invalid or unspecified script index.", ERR_INV_SCRIPT_IDX, Global.Errors.error9aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad Script pd     | Invalid of unspecified script payload.", ERR_INV_SCRIPT_PAYLOAD, Global.Errors.error9bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad -if srcA      | Invalid of unspecified conditional srcA.", ERR_COND_SA_INVALID, Global.Errors.error10aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad -if srcB      | Invalid of unspecified conditional srcB.", ERR_COND_SB_INVALID, Global.Errors.error10bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad -if Op        | Invalid of unspecified conditional operator.", ERR_COND_OP_INVALID, Global.Errors.error10cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad -if PD        | Invalid of unspecified conditional payload.", ERR_COND_PD_INVALID, Global.Errors.error10dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad -if delimiter | Invalid of unspecified conditional delimiter.", ERR_UNSPEC_DELIM, Global.Errors.error10eCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad or no UART PD | Invalid or unspecified UART7 payload.", ERR_INVALID_UART7, Global.Errors.error11aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Invalid Freq Err  | Invalid frequency specified.", ERR_INVALID_FREQ, Global.Errors.error12aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Freq Out of Range | User-input frequency out of range.", ERR_FREQ_OUT_OF_RANGE, Global.Errors.error12bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: SPI Voice Buff    | SPI voice buffer/transaction bad.", ERR_VOICE_BUF, Global.Errors.error12cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: ADCBuf Error      | Bad ADCBuf during ADCBuf callback!.", ERR_ADC_BUF_INVALID, Global.Errors.error14aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: ADC Ping Pong Bad | Bad ADCBuf from Ping/Pong.", ERR_UNKNOWN_RX_BUF, Global.Errors.error14bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Acc/Dec W/O Ping  | Attempted to accept/decline w/o ping.", ERR_NOT_PINGED, Global.Errors.error16aCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: -dial accept fail | -dial accept failed or misformatted.", ERR_ACCEPT_FAILED, Global.Errors.error16bCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: -dial decline bad | -dial decline failed or misformatted.", ERR_DECLINE_FAILED, Global.Errors.error16cCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: -dial request bad | -dial request failed or misformatted.", ERR_REQ_FAILED, Global.Errors.error16dCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Unexp -dial resp  | Unexpected -dial response.", ERR_UNPROMPTED_RESP, Global.Errors.error16eCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Already in a Call | Improper -dial action performed while in call.", ERR_ALREADY_IN_CALL, Global.Errors.error16fCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: -dial resp failed | -dial response failed or was misformatted", ERR_RESP_FAILED, Global.Errors.error16gCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: -dial confirm bad | -dial confirm failed. CRITICAL error.", ERR_CONFIRM_FAILED, Global.Errors.error16hCount);
        puts(xmitbuf);
        sprintf(xmitbuf, " ERR %s - %d: Bad Usr -dial req | User's -dial b1/b2 request was bad!.", ERR_DIAL_REQ_FAILED, Global.Errors.error16iCount);
        puts(xmitbuf);

    }

    return;

} // void msgError(char *input);
/* ================================================================================ */





/* ================================================================================
 *      CHARACTER COMPARISON FUNCTION
 * --------------------------------------------------------------------------------
 *
 *  Returns a true if the characters are the same and false if the characters are different,
 *  irrespective of case; user-defined parameter (oftentimes b) must be lower-case!
 */
bool charCmp(char a, char b) {

    return tolower((unsigned char)a) == tolower((unsigned char)b);

} // bool charCmp(char a, char b);
/* ================================================================================ */





/* ================================================================================
 *      STRNCMPI FUNCTION
 * --------------------------------------------------------------------------------
 *
 *  Returns a true if the characters are the same and false if the characters are different,
 *  irrespective of case; user-defined parameter (oftentimes b) must be lower-case!
 *
 *  Returns a 0 if two strings are the same irrespective of case. Idk why this version of
 *  C doesn't have strncmpi, but now it does :D
 */
int strncmpi(const char *s1, const char *s2, size_t n) {

    while (n-- && *s1 && *s2) {
        char c1 = *s1++;
        char c2 = *s2++;
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) return c1 - c2;
    }

    return 0;

} // int strncmpi(const char *s1, const char *s2, size_t n);
/* ================================================================================ */






