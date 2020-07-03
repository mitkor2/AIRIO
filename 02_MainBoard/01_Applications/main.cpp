/*
 *  ======== main.cpp ========
 *  MT wiring Task framework
 */
#include <stddef.h>
//#include <oslib/osi.h>

/* XDC Header files */
#include <xdc/cfg/global.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <xdc/runtime/System.h>

/* Board Support Header files (from configuration closure) */
#include "Arduino.h"

/* magic insertion point 769d20fcd7a0eedaf64270f591438b01 */
extern void setup();
extern void loop();

#define NUM_SKETCHES 1
void (*func_ptr[NUM_SKETCHES][2])(void) = {
	{setup, loop}
};
const char *taskNames[] = {
	"loop"
};

Void the_task(UArg _task_setup, UArg _task_loop);

/* set priority of simple link callbacks
 * must be >= 0 and < Task_numPriorities
 * where Task_numPriorities is set by
 * TI-RTOS config
 */

/*
 *  ======== main task ========
 */
Void the_task(UArg _task_setup, UArg _task_loop)
{
	/* Call setup once */
	(*(void(*)()) _task_setup)();

	/* Call loop repeatedly */
	for(;;) {
		(*(void(*)()) _task_loop)();
		System_flush();
		Task_yield();
	}
}
/*
 *  ======== main ========
 */
int main()
{
	/* initialize all device/board specific peripherals */
	Board_init();  /* this function is generated as part of TI-RTOS config */

	/* The SimpleLink Host Driver requires a mechanism to allow functions to
	 * execute in task context.  The SpawnTask is created to handle such
	 * situations.  This task will remain blocked until the host driver
	 * posts a function.  If the SpawnTask priority is higher than other
	 * tasks, it will immediately execute that function and return to a
	 * blocked state.  Otherwise, it will remain ready until it has
	 * the highest priority of any ready function.
	*/

	Task_Params taskParams;

	/* initialize taskParams and set to default */
	Task_Params_init(&taskParams);

	/* All tasks have the same priority */
	taskParams.priority = Task_numPriorities - 2;
	taskParams.stackSize = 0x800;

	uint8_t i = 0;
	for(i = 0; i < NUM_SKETCHES; i++) {
		/* Set arg0 to setup() */
		taskParams.arg0 = (xdc_UArg)func_ptr[i][0];
		/* Set ar1 to loop */
		taskParams.arg1 = (xdc_UArg)func_ptr[i][1];
		/* Set the task name */
		taskParams.instance->name = (xdc_String) taskNames[i];
		/* Create the task */
		Task_create(the_task, &taskParams, NULL);
	}

	/* does not return */
	BIOS_start();

	return (0); /* should never get here, but just in case ... */
}


