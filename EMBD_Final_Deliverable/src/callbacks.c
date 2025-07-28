/*
 * callbacks.c
 *
 *  Created on: Jun 16, 2025
 *      Author: jonat
 */

#include "c_header.h"

#ifdef glo
extern glo Global;
#endif





/* ================================================================================
 *   ADC BUFFER CALLBACK
 * --------------------------------------------------------------------------------
 *  ...
 */
void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t var) {

    if (buffer != Global.audioControl.rxBuf.RX_Ping && buffer != Global.audioControl.rxBuf.RX_Pong) { // Buffer should be ping or pong (use a SWI to trigger error)
        Swi_post(Global.Bios.ADC_ErrorSwi);                // lower priority of the error throw, never throw an error on a HWI
        return;
    }

    Global.audioControl.rxBuf.RX_Completed = buffer;

    Semaphore_post(Global.Bios.ADCSem);

    return;
} // void adcBufCallback(ADCBuf_Handle handle, ADCBuf_Conversion *conversion, void *buffer, uint32_t channel, int_fast16_t var);
/* ================================================================================ */





/* ================================================================================
 *   ADC ERROR CALLBACK
 * --------------------------------------------------------------------------------
 *  ...
 */
void adcErrorSWI(UArg arg0, UArg arg1) {

    addError(NULL, ERR_ADC_BUF_INVALID);
    return;

} // void adcErrorSWI(UArg arg0, UArg arg1);
/* ================================================================================ */





/* ================================================================================
 *   TIMER0 CALLBACK
 * --------------------------------------------------------------------------------
 *  ...
 */
void timer0Callback(Timer_Handle handle, int_fast16_t status) {

    Global.Callback.Hwi_flag = false;

    if (strncmpi(Global.Callback.callbacks[0].payload, "-sine", strlen("-sine")) == 0) {
        Global.Callback.Hwi_flag = true;
        runSine(Global.Callback.callbacks[0].payload);
        return;
    }

    else if (strncmpi(Global.Callback.callbacks[0].payload, "-audio", strlen("-audio")) == 0) {
        Global.Callback.Hwi_flag = true;
        runAudio();
        return;
    }
    else {
        Swi_post(Global.Bios.Timer0Swi);
        return;
    }

} // void timer0Callback(Timer_Handle handle, int_fast16_t status);
/* ================================================================================ */






/* ================================================================================
 *   TIMER0 SWI
 * --------------------------------------------------------------------------------
 *  ...
 */
void timer0SWI(UArg arg0, UArg arg1) {

    int32_t     i = 0;      // This corresponds to the timer0 callback

    if (Global.Callback.callbacks[i].count != 0 && Global.Callback.callbacks[i].payload[0] != '\0') {

        addPayload(Global.Callback.callbacks[i].payload);

        uint16_t gateKey = GateSwi_enter(Global.Bios.CallbackGateSwi);
        if (Global.Callback.callbacks[i].count > 0) {
            Global.Callback.callbacks[i].count--;
            if (Global.Callback.callbacks[i].count == 0) {
                Global.Callback.callbacks[i].payload[0] = '\0';
            }
        }

        GateSwi_leave(Global.Bios.CallbackGateSwi, gateKey);
    }

    return;

}
/* ================================================================================ */






/* ================================================================================
 *   TIMER1 CALLBACK
 * --------------------------------------------------------------------------------
 *  ...
 */
void timer1Callback(Timer_Handle handle, int_fast16_t status) {

    Swi_post(Global.Bios.Timer1Swi);
    return;

} // void timer1Callback(Timer_Handle handle, int_fast16_t status);
/* ================================================================================ */






/* ================================================================================
 *   TIMER1 SWI
 * --------------------------------------------------------------------------------
 *  ...
 */
void timer1SWI(UArg arg0, UArg arg1) {

    int32_t     i;
    uint32_t    gateKey;

    gateKey = GateSwi_enter(Global.Bios.TickerGateSwi);

    for (i = 0; i < TICKER_COUNT; i++) {

        if (Global.Tickers[i].delay > 0) {
            Global.Tickers[i].delay--;

            if (Global.Tickers[i].delay <= 0) {
                addPayload(Global.Tickers[i].payload);

                if (Global.Tickers[i].count != 0) {
                    Global.Tickers[i].delay = Global.Tickers[i].period;

                    if (Global.Tickers[i].count > 0) {
                        Global.Tickers[i].count--;

                    } // decrement count
                } // reset delay
            } // add the payload to the queue
        } // decrement the delay: do nothing
    } // for loop

    GateSwi_leave(Global.Bios.TickerGateSwi, gateKey);

    return;
} // void timer1SWI(UArg arg0, UArg arg1);
/* ================================================================================ */





/* ================================================================================
 *   CALLBACK FOR SWITCH 1 BUTTON
 * --------------------------------------------------------------------------------
 *  This function services the Hardware interrupt that is triggered upon actuation of the switch.
 *  It will immediately post a SWI (software interrupt) to be serviced in BIOS!
 */
void gpioButtonSw1Callback(uint_least8_t index) {

    Swi_post(Global.Bios.SW1_Swi);
    return;

} // void gpioButtonSw1Callback(uint_least8_t index);
/* ================================================================================ */





/* ================================================================================
 *   SOFTWARE INTERRUPT FOR THE SWITCH 1 BUTTON
 * --------------------------------------------------------------------------------
 * This function is the user-defined SWI (software interrupt) function that the hardware interrupt steps into
 * This is crucial as we do not want to perform a function based on the HWI because there are likely more important
 *  things to consider at a given moment. This takes it a step further all the way down to the payload task!
 */
void SWIgpioButtonSw1(UArg arg0, UArg arg1) {

    int32_t    i = 1;   // for switch 1 (table entry number in call backs)
    uint32_t   gateKey;

    gateKey = GateSwi_enter(Global.Bios.CallbackGateSwi);
    if (Global.Callback.callbacks[i].count != 0 )           // Prevents writing to the callback table while being engaged (prevents more than one thing from modifying the callback table during a callback...)
    {

        addPayload(Global.Callback.callbacks[i].payload);   //
        if (Global.Callback.callbacks[i].count > 0)
            Global.Callback.callbacks[i].count--;
    }
    GateSwi_leave(Global.Bios.CallbackGateSwi, gateKey);
    //DON'T HAVE 2 PARSERS! EVERYTHING GOES THROUGH ONE QUEUE. The order you put something in the queue is the order they are serviced.

    return;

} // void SWIgpioButtonSw1(UArg arg0, UArg arg1);
/* ================================================================================ */





/* ================================================================================
 *   CALLBACK FOR SWITCH 1 BUTTON
 * --------------------------------------------------------------------------------
 *  Like for SW1, this function also takes the HWI and posts a SWI interrupt so as
 *  not to interrupt more important tasks for the duration of an entire HWI.
 */
void gpioButtonSw2Callback(uint_least8_t index) {

    Swi_post(Global.Bios.SW2_Swi);
    return;

} // void gpioButtonSw2Callback(uint_least8_t index);
/* ================================================================================ */




/* ================================================================================
 *   SOFTWARE INTERRUPT FOR THE SWITCH 2 BUTTON
 * --------------------------------------------------------------------------------
 *  Like SW1, this function responds directly to the SWI posted by the HWI.
 *  This SWI extrapolates the button press ANOTHER layer down to
 *  the payloadQ which is the lowest priority task!
 */
void SWIgpioButtonSw2(UArg arg0, UArg arg1) {

    int32_t    i = 2; // for switch 1 (table entry number in call backs)
    uint32_t   gateKey;

    gateKey = GateSwi_enter(Global.Bios.CallbackGateSwi);
    if (Global.Callback.callbacks[i].count != 0 ) // Prevents writing to the callback table while (prevents more than one thing from modifying the callback table)
    {

        addPayload(Global.Callback.callbacks[i].payload);
        if (Global.Callback.callbacks[i].count > 0)
            Global.Callback.callbacks[i].count--;
    }
    GateSwi_leave(Global.Bios.CallbackGateSwi, gateKey);
    //DON'T HAVE 2 PARSERS! EVERYTHING GOES THROUGH ONE QUEUE. The order you put something in the queue is the order they are serviced.

    return;

} // void SWIgpioButtonSw2(UArg arg0, UArg arg1);
/* ================================================================================ */








