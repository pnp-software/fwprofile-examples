/**
 * RT Container Example for C1 Implementation of the FW Profile.
 * This file contains a complete program to create, configure
 * and use a simple RT Container.
 * The RT Container wraps a thread which, at every notification,
 * writes a message to standard output.
 * The main program sends a sequence of notifications to the RT
 * Container. Each notification should wake up the internal
 * container's thread (the "Activation Thread"). Successive
 * notifications are separated by a 10 ms wait.
 * @author Vaclav Cechticky, Alessandro Pasetti
 * @copyright P&P Software GmbH, 2013, All Rights Reserved
 */

#include <stdio.h>
#include <stdlib.h>

/* Include FW Profile functions */
#include "FwRtConstants.h"
#include "FwRtConfig.h"
#include "FwRtCore.h"
#include <time.h>

/** This variable holds a time duration of 10 ms */
static struct timespec ten_ms = {0,10000000};

/* -------------------------------------------------------------------------*/
/**
 * Function implementing the user's functional behaviour.
 * In this example, this function prints a message and returns zero.
 * @param rtDesc the RT Container descriptor
 * @return always return zero
 */
FwRtOutcome_t UserFunctionalBehaviour(FwRtDesc_t rtDesc) {
	static int i = 1;
	printf("Activation Thread: Notification %i has been received!\n",i);
	i++;
	return 0;
}

/* -------------------------------------------------------------------------*/
/**
 * Main program for the RT Container Example.
 * This program creates and configures a sample RT Container then sends a few
 * notifications to it. Each notification should wake up the container's thread.
 * @return always returns EXIT_SUCCESS
 */
int main(void) {
	struct FwRtDesc rtDesc;		/* The RT Container Descriptor */
	int i;

	/* Reset the RT Container */
	FwRtReset(&rtDesc);

	/* Attach functional behaviour to RT Container */
	FwRtSetExecFuncBehaviour(&rtDesc,&UserFunctionalBehaviour);

	/* Initialize the RT Container */
	FwRtInit(&rtDesc);

	/* Start the RT Container and send a few notifications to it */
	FwRtStart(&rtDesc);
	for (i=0; i<10; i++) {
		printf("Sending notification %i to container ...\n",i+1);
		FwRtNotify(&rtDesc);
		nanosleep(&ten_ms,NULL);	/* wait ten ms */
	}

	/* Stop the RT Container */
	FwRtStop(&rtDesc);

	/* To ensure orderly shutdown: wait until container thread has terminated */
	FwRtWaitForTermination(&rtDesc);

	/* Shutdown the RT Container */
	FwRtShutdown(&rtDesc);

	return EXIT_SUCCESS;
}
