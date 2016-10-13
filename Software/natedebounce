/*
 * Sample debouncing code
 *
 * Copyright 2010 Dean Hall.
 * This code snippet is offered under the MIT license:
 * http://www.opensource.org/licenses/mit-license.html
 */
 
/*
 * The hardware is an AVR with a switch connected to the INT0 input.
 * The firmware uses:
 *
 * - AVR Libc: http://www.nongnu.org/avr-libc/
 * - The AvrX microkernel: http://www.barello.net/avrx/
 *
 * This sample code performs debouncing on the INT0 input.
 * Here is the expected sequence of actions:
 *
 * - The AVR can be doing anything (awake or asleep) when the button is pressed
 * - The button press produces a low-going signal and bounces for a time
 * - The low-going signal activates the INT0 interrupt
 * - The INT0 service routine:
 *     - Disables the INT0 interrupt so bouncing doesn't cause multiple IRQs
 *     - Puts an AvrX message in the event queue of the inputs task
 * - The event in the queue causes the inputs_task to be scheduled, which:
 *     - Performs the action that the INT0 button is supposed to invoke
 *     - Starts an AvrX delay timer to allow for the button to stop bouncing
 *       During this delay, other AvrX tasks may run.
 *     - After the delay, the INT0 interrupt is re-enabled for the next input.
 *
 * In this design, the delay is especially long (1s) due to a very cheap button
 * and no need to respond to fast button presses.
 *
 * The downside of this software design is that no other input events are
 * processed while a button is debounced, although their press-messages are
 * queued up and handled after the debounce period.  This behavior was
 * acceptable for this immediate design, but may not be for all situations.
 */
 
#include <avr/interrupt.h>
#include "avrx.h"
 
#define DEBOUNCE_DELAY (uint16_t)(1000 / MILLISECONDS_PER_TIC)
 
static MessageControlBlock remote_ctrl_pressed_msg;
 
/* Remote Control button press interrupt service routine */
AVRX_SIGINT(INT0_vect)
{
   IntProlog();
 
   /* Disable INT0/RemoteCtrl interrupt */
   GICR &= ~_BV(INT0);
 
   AvrXIntSendMessage(&inputs_msg_queue, &remote_ctrl_pressed_msg);
   Epilog();
}
 
AVRX_GCC_TASKDEF(inputs_task, TASK_STACK_SIZE, 3)
{
   TimerControlBlock debounce_timer;
   MessageControlBlock *pmsg;
 
   /* Set INT0/RemoteCtrl and INT1/OpTest to trigger on falling edge */
   GICR &= ~(_BV(INT0) | _BV(INT1));
   MCUCR &= ~(_BV(ISC00) | _BV(ISC10));
   MCUCR |= (_BV(ISC01) | _BV(ISC11));
   GICR |= (_BV(INT0) | _BV(INT1));
 
   /* ... other initialization stuff removed */
 
   for (;;)
   {
       /* Wait for a message that an input was pressed or timer expired */
       pmsg = AvrXWaitMessage(&inputs_msg_queue);
 
       /* ... removed if-cases for other unrelated input messages */
 
       else if (pmsg == &remote_ctrl_pressed_msg)
       {
           DEBUG_PRINT(VERBOSITY_LOW, "RmtCtrl pressed.\n");
 
           /* ... removed code that performs the action the button invokes */
 
           /* Debounce delay for RemoteCtrl button; lets other threads run */
           AvrXDelay(&debounce_timer, DEBOUNCE_DELAY);
 
           /* Clear flag and enable interrupt */
           GIFR |= _BV(INTF0);
           GICR |= _BV(INT0);
       }
   }
}