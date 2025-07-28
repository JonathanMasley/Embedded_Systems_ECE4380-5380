
/*
 * --------------------------------------------------------------------------------
 *      C-Tasks File
 * --------------------------------------------------------------------------------
 *  +
 *  +
 *  +
 *
 */

#include "c_header.h"

#ifdef glo
extern glo Global;
#endif





/* ================================================================================
 *      AAA FIRST TASK
 * --------------------------------------------------------------------------------
 *  This task will always run first but is currently not populated with anything!
 */
void taskAAA() {
    /* This task runs first as the top priority! */
    return;
}
/* ================================================================================ */





/* ================================================================================
 *      UART0 READ TASK
 * --------------------------------------------------------------------------------
 *  This function handles the reading from UART0 (adjacent to reset switch/upside down)
 *  It contains handling for the following:
 *      - EMERGENCY STOP ('`')
 *      - UP-ARROW ("\x1b[A")
 *      - DOWN-ARROW ("\x1b[B")
 *      - CARRIAGE RETURN ("\r\n" or '\r' or '\n')
 *          + PAYLOAD DELIVERY
 *      - BUFFER OVERFLOW
 *      - BACKSPACE ('\b')
 *      - CHARACTER ECHO
 */
void taskUART0Read() {

    char     inpChar;
    char    *input =      Global.Buffers.inpBuff;
    char    *xmitbuf =    Global.Buffers.msgBuff;
    int      i;
    int      histIdx;

    histIdx = 0;

    for (;;) {  // ever

        if (Global.Buffers.inpIndex >= 0) {
            UART_read(Global.Devices.uart0, &inpChar, 1);   /* This specifically is the task in this code */
        }

        /* Handles the emergency stop condition; CLEARS callbacks, tickers, scripts! */
        if (inpChar == '`') {

            /* Clears the callback table */
            for (i = 0; i < CALLBACK_COUNT; i++) {
                memset(Global.Callback.callbacks[i].payload, 0, BUFFER_SIZE);
                Global.Callback.callbacks[i].count = 0;
            }

            /* Clears the ticker table */
            for (i = 0; i < TICKER_COUNT; i++) {
                addTicker(i, 0, 0, 0, NULL);
            }

            /* Clears the script count */
            for (i = 0; i < SCRIPT_COUNT; i++) {
                addScript(i, NULL);
            }

            /* Prints EMERGENCY STOP in bold */
            strcpy(xmitbuf, "EMERGENCY STOP");
            putB(xmitbuf);
        }

        /* Handles escape sequences */
        else if (inpChar == '\033' || inpChar == '\x1b') {
            /* Store up to 3-char escape sequences, does not handle F1-F12 :( */
            char inp0;
            char inp1;
            UART_read(Global.Devices.uart0, &inp0, 1);
            UART_read(Global.Devices.uart0, &inp1, 1);

            /* Check for an up  arrow */
            if      ( (inp0 == '[') && (inp1 == 'A') ) {
                /* If histIdx is valid and the inpArrowBuffer has been populated, then perform the up arrow action */
                if  ( (histIdx < INP_HISTORY_COUNT - 1) && (Global.Buffers.inpArrowBuffer[histIdx+1][0] != NULL)) {
                    histIdx++;
                    /* Copies necessary buffer information (user should still be able to interact and add/del to/from populated text */
                    Global.Buffers.inpIndex = strlen(Global.Buffers.inpArrowBuffer[histIdx]);
                    memset(input, 0, BUFFER_SIZE);
                    strcpy(input, Global.Buffers.inpArrowBuffer[histIdx]);
                    /* Only after the input buffer has been properly written does it output to the console */
                    putSL(CLEAR_LINE_RESET);
                    putSL(Global.Buffers.inpArrowBuffer[histIdx]);
                }
                else {
                    continue;
                }
            }

            /* Check for a down arrow */
            else if ( (inp0 == '[') && (inp1 == 'B') ) {

                /* If the user returns back to the "original" space then clear line and reset buffer */
                if  (histIdx == 0) {
                    putSL(CLEAR_LINE_RESET);
                    memset(input, 0, BUFFER_SIZE);                      /* Reset entire buffer to empty string */
                    Global.Buffers.inpIndex = 0;                        /* Set inpIndex to zero to allow user to write to current buffer */
                    continue;
                }

                /* If the user wants to move back down the arrow buffer, pull from lower in the buffer */
                else if  (histIdx > 0) {
                    /* Decrement index */
                    histIdx--;
                    /* Set the buffer to the new arrow-buffer information */
                    Global.Buffers.inpIndex = strlen(Global.Buffers.inpArrowBuffer[histIdx]) - 1;
                    memset(input, 0, BUFFER_SIZE);
                    strcpy(input, Global.Buffers.inpArrowBuffer[histIdx]);
                    /* Only after the new arrow-buffer information has updated the buffer, will it output new text to the console */
                    putSL(CLEAR_LINE_RESET);
                    putSL(Global.Buffers.inpArrowBuffer[histIdx]);
                }

                else {
                    continue;
                }
            }

            else {
                continue;
            }

            continue;
        }

        /* Enter this block of if-statements once the user presses return */
        /* Not sure if PuTTY uses \r or \n so both were included */
        else if (inpChar == '\r' || inpChar == '\n') {

            puts(NEW_LINE);                                     /* Echoes the return line that the user input */

            input[Global.Buffers.inpIndex] = '\0';              /* Add a null terminator to the end of the buffer */

            /* If user just pressed '\n', don't add NULL to the queue T_T */
            if (Global.Buffers.inpIndex > 0) {

                /* Pushes every element in the array forward one (loses the last element) so as to make space for the newest input */
                for (i = INP_HISTORY_COUNT-1; i > 1; i--) {
                    strcpy(Global.Buffers.inpArrowBuffer[i], Global.Buffers.inpArrowBuffer[i-1]);
                }
                /* Stores the newest inpBuffer into the first index */
                strcpy(Global.Buffers.inpArrowBuffer[1], input);
                histIdx = 0;

                addPayload(input);
            }

            /* RESET THE BUFFER AFTER DELIVERY OF THE PAYLOAD */
            memset(input, 0, BUFFER_SIZE);                      /* Reset entire buffer to empty string */
            Global.Buffers.inpIndex = 0;                        /* Set inpIndex to zero for assessment of future payloads */
        }


        /* Until the user sends the command, store each character into a string, "input" */
        else {

            /* OVERFLOW Handler */
            if (Global.Buffers.inpIndex >= BUFFER_SIZE - 1) {
                addError(NULL, ERR_BUFF_OVERFLOW);
                memset(input, 0, sizeof(input));
                Global.Buffers.inpIndex = 0;
            }

            /* Backspace Handler */
            else if ((inpChar == '\b' || inpChar == 127) && (Global.Buffers.inpIndex > 0)) {
                Global.Buffers.inpIndex--;
                input[Global.Buffers.inpIndex] = '\0';
                putSL(BACKSPACE_SEQ);
            }

            /* Updates the input string for each user-input characters on the console */
            else if ( (isprint((unsigned char)inpChar)) && !((inpChar == '\b' || inpChar == 127) && Global.Buffers.inpIndex == 0) ) {
                char echoBuf[2] = {inpChar, '\0'};
                putSL(echoBuf);
                input[Global.Buffers.inpIndex] = inpChar;
                Global.Buffers.inpIndex++;
            }
        }
    }
} // void taskReadEcho();
/* ================================================================================ */





/* ================================================================================
 *      UART0 WRITE TASK
 * --------------------------------------------------------------------------------
 *  This function operates the UART_write, it handles increment of the OUTMSG queue
 *  and determining how a message should be printed on the console (directing msg
 *  to the proper UART_write_prot
 */
void taskUART0Write(UArg arg0, UArg arg1) {

    int32_t         msgNext;
    int32_t         index;
    char           *msg;
    outMsgTypeList  type;
    uint32_t        gateKey;

    for (;;) { // ever

        /* Because this is a 2nd highest priority forever loop, a semaphore governs its operation */
        Semaphore_pend(Global.Bios.UARTWriteSem, BIOS_WAIT_FOREVER);

        /* Queue handingling for the circular buffer OutMSGQ */
        index = Global.OutMsgQ.msgReading;
        msg = Global.OutMsgQ.msgs[index].msg;
        type = Global.OutMsgQ.msgs[index].type;

        /* If msg is NULL, don't bother going as far as UART_write */
        if(!msg) {
            return;
        }

        /* This determines which type of UART_write_prot_XX to send msg to (UART_write_prot is where it actually outputs to console! */
        switch (type) {
            case OUTMSG_N:
                UART_write_prot(msg);
                break;
            case OUTMSG_SL:
                UART_write_prot_sl(msg);
                break;
            case OUTMSG_BOLD:
                UART_write_prot_bold(msg);
                break;
            default:
                UART_write_prot(msg);
                break;
        }

        /* This GateSwi handles iteration through the circular buffer queue (increments to next message)
         * DO NOT MISTAKE THIS FOR SEMAPHORE_POST from addOutMsg() which actually posts a semaphore for
         * entering this task and outputting to the console! */
        gateKey = GateSwi_enter(Global.Bios.OutMsgGateSwi);
        msgNext = index + 1;
        msgNext = (Global.OutMsgQ.msgReading + 1) % MAX_MSG_COUNT;
        Global.OutMsgQ.msgReading = msgNext;
        GateSwi_leave(Global.Bios.OutMsgGateSwi, gateKey);

    }
} // void taskUART0Write(UArg arg0, UArg arg1);
/* ================================================================================ */





/* ================================================================================
 *      ADC TASK
 * --------------------------------------------------------------------------------
 *  - This task manages the ADC Buffer, audio source, and "destinationChoice".
 *  - destinationChoice is one of the most important, and confusing, components of this task.
 *      + destinationChoice determines where the audio should be sent and how it should work.
 *      + destinationChoice = 0 (Audio will come from RX_Ping to be "sent out"/"received" on channel 0)
 *      + destinationChoice = 1 (Audio will come from RX_Pong to be "sent out"/"received" on channel 1)
 *      + Local Audio will only ever employ destChoice 0 and 1
 *      + dialIP0 will be the only one to ever employ destChoice 0 and 1 (takes the place of the local voice)
 *      + THINK OF LOCAL AUDIO AS A PHONE CALL W/ YOURSELF! You still need to transmit this 0 and 1 destinationChoice
 *        to yourself just as you would receive from another caller!
 *
 *      + destinationChoice = 2 (Audio is coming from RX_Ping to be "sent out"/"received" on channel 2)
 *      + destinationChoice = 3 (Audio is coming from RX_Pong to be "sent out"/"received" on channel 3)
 *      + dialIP1 will be the only one to ever employ destChoice 2 and 3 (new channels for second device handing audio)!
 *
 */
void taskADCStream() {

    uint16_t   *source;
    char        longLoad[512]; /* 256-byte data block size doubled for overhead */
    int32_t     destinationChoice;
    int32_t     hdrLength;

    for (;;) { //ever
        /* Because this is a 3rd highest priority forever loop, a semaphore governs its operation */
        Semaphore_pend(Global.Bios.ADCSem, BIOS_WAIT_FOREVER);

        /* Test RX_Completed for ping, all this does is set destChoice and increment pingCount */
        if      (Global.audioControl.rxBuf.RX_Completed == Global.audioControl.rxBuf.RX_Ping) {
            source = Global.audioControl.rxBuf.RX_Completed;
            destinationChoice = 0;
            Global.audioControl.rxBuf.pingCount++;
            runGPIO(" 0 t");
        }
        /* Test RX_Completed for pong, all this does is set destChoice and increments pongCount */
        else if (Global.audioControl.rxBuf.RX_Completed == Global.audioControl.rxBuf.RX_Pong) {
            source = Global.audioControl.rxBuf.RX_Completed;
            destinationChoice = 1;
            Global.audioControl.rxBuf.pongCount++;
            runGPIO(" 1 t");
        }
        else {
            addError(NULL, ERR_UNKNOWN_RX_BUF);
            continue;
        }

        Global.audioControl.local = true;  /* Set to true at first and then test IPs != 0 to determine networking*/

        /* If IP1 != 0 then source buffer needs to navigate to transmission via network to IP1 on
         * destinationChoice 0, 1 and IP2 on destinationChoice 2, 3. */
        if (Global.Dial.callThreeWay == 1 || Global.Dial.callTwoWay == 1) {

            if (Global.Dial.ipAddr1 == 1) {
                sprintf(longLoad, "-netudp %s -voice %d 128  ",
                        Global.Dial.ip1String, destinationChoice);
                hdrLength = (int32_t)(strlen(longLoad) + 1);
                memcpy(&longLoad[hdrLength], source, sizeof(uint16_t)*DATA_BLOCK_SIZE);
                runNETUDP(longLoad, sizeof(uint16_t)*DATA_BLOCK_SIZE);
                Global.audioControl.local = false;
            }

            if (Global.Dial.ipAddr2 == 1) {
                sprintf(longLoad, "-netudp %s -voice %d 128  ",
                        Global.Dial.ip2String, destinationChoice + 2);
                hdrLength = (int32_t)(strlen(longLoad) + 1);
                memcpy(&longLoad[hdrLength], source, sizeof(uint16_t)*DATA_BLOCK_SIZE);
                runNETUDP(longLoad, sizeof(uint16_t)*DATA_BLOCK_SIZE);
                Global.audioControl.local = false;
            }
        }
    }
} // void taskADCStream();
/* ================================================================================ */





/* ================================================================================
 *      NETUDP TASK
 * --------------------------------------------------------------------------------
 *  EMPTY FOR NOW!
 */
void taskNETUDP() {

    return;
}






/* ================================================================================
 *      UART7 READ TASK
 * --------------------------------------------------------------------------------
 *  SEE Global.Parameters.uartParams7 for specific details about the UART7 drivers.
 *      ^ (This will give a lot of insight into how this is set up!)
 *  UART_read reads an entire line (denoted by \r or \n or \r\n at the end of a tx) into the rxbuffer.
 *  If the length of the buffer is appropriate, add the UART7 input into the payload queue.
 */
void taskUART7Read() {

    char    rxBuffer[BUFFER_SIZE];
    size_t  len;

    for (;;) { //ever

        len = UART_read(Global.Devices.uart7, rxBuffer, sizeof(rxBuffer));

        if (len > 0 && len < BUFFER_SIZE) {

            rxBuffer[len-1] = '\0';
            putSL("UART 7 > ");
            puts(rxBuffer);

            addPayload(rxBuffer);

        } // if the rxBuffer is valid length

    } // End of forever loop

} // void taskUART7Read();
/* ================================================================================ */





/* ================================================================================
 *      PAYLOAD TASK
 * --------------------------------------------------------------------------------
 *  Handles incrementing through the circular buffer PAYLOAD QUEUE.
 *  Think about it this way:
 *
 *   -  It might look something like the following at first:
 *      +   (Context: 5 things have been added to the payload queue, that is the addPayload()
 *          function has been called 5x)
 *              INDEX: 0    VVVV
 *              QUEUE:     [PD0 ][PD1 ][PD2 ][PD3 ][PD4 ]
 *              SEMAPHORE: Count 5
 *      +   (NOTE: nothing has happened yet, since we haven't been able to enter this task yet; however,
 *                 all those semaphores ARE POSTED, we just haven't been able to enter the Semaphore pend yet)
 *
 *   -  Each time this lowest priority task is allowed to be entered (nothing else is happening), then:
 *      +   The Semaphore_pend looks for a Semaphore_post! If there is one, then it figures out which
 *          index of the circular buffer queue it should pull from!
 *      +   Then it EXECUTES this specific payload in the queue.
 *              INDEX: 0    VVVV
 *              QUEUE:     [PD0 ][PD1 ][PD2 ][PD3 ][PD4 ]
 *              SEMAPHORE: Count 4 (I'm not sure where exactly it happens, but after the semaphore_pend receives a
 *                                  semaphore, it will decrement its count)
 *
 *   -  After the "execPayload" then we will increment through the queue (because we edit our Global, we need a GateSwi for this)!
 *      +   INCREMENT THROUGH THE QUEUE!
 *              INDEX: 1          VVVV
 *              QUEUE:     [PD0 ][PD1 ][PD2 ][PD3 ][PD4 ]
 *              SEMAPHORE: Count 4
 *      +   It will continue to do all of the above for as many SEMAPHORES there are! You best hope your ass that
 *          the semaphores don't get misaligned with the queue as that means your execution will lag (and if it gets
 *          behind enough it will start to lose payloads; this shouldn't happen if it is properly configured).
 */
void taskPayload() {

    int32_t     payloadNext;
    int32_t     index;
    char       *payload;
    uint32_t    gateKey;

    for (;;) { // ever

        Semaphore_pend(Global.Bios.PayloadSem, BIOS_WAIT_FOREVER);  // Wait here for a queue entry!
        index = Global.PayloadQ.payloadReading;
        payload = Global.PayloadQ.payloads[index];

        execPayload(payload);

        gateKey = GateSwi_enter(Global.Bios.PayloadGateSwi);
        payloadNext = index + 1;
        payloadNext = (Global.PayloadQ.payloadReading + 1) % MAX_PAYLOAD_COUNT;
        Global.PayloadQ.payloadReading = payloadNext;
        GateSwi_leave(Global.Bios.PayloadGateSwi, gateKey);

    } // Do this forever!

} // void taskPayload();
/* ================================================================================ */




