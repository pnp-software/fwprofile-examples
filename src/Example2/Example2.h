/**
 * @file
 * This header file declares the function to create one instance of the Example2 state machine.
 * The state machine is configured with a set of function pointers representing the non-default
 * actions and guards of the state machine. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the state machine in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The state machine created by this file is shown in the figure below.
 *
 * <b>Note for state Initial State</b>
 * Embedded initial state creates an embedded state machine.
 *
 * <b>Note for state Initial State</b>
 * Initial state
 *
 * <b>Note for state CPS1</b>
 * Choice pseudo state
 *
 * <b>Note for state Final State</b>
 * Final state
 *
 * @image html Example2.png
 *
 * @author FW Profile code generator version 5.02
 * @date Created on: Dec 22 2016 11:47:56
 */

/** Make sure to include this header file only once */
#ifndef EXAMPLE2_H_
#define EXAMPLE2_H_

/** FW Profile function definitions */
#include "FwSmConstants.h"

/** State identifiers */
#define Example2_STATE_ES1 (1)		/* The identifier of state STATE_ES1 in State Machine Example2 */
#define Example2_STATE_ES2 (2)		/* The identifier of state STATE_ES2 in State Machine Example2 */
#define Example2_STATE_S1 (1)		/* The identifier of state STATE_S1 in State Machine Example2 */
#define Example2_STATE_S2 (2)		/* The identifier of state STATE_S2 in State Machine Example2 */

/** The identifiers of transition commands (triggers) */
// #define FW_TR_EXECUTE (0)
#define Trigger1 (1)
#define Trigger2 (2)
#define Trigger3 (3)
#define TRIGGER_NUM (4)

/**
 * Create a new state machine descriptor.
 * This interface creates the state machine descriptor directally.
 * @param smData the pointer to the state machine data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the state machine data when the state machine is created is NULL).
 * @return the pointer to the state machine descriptor
 */
FwSmDesc_t Example2Create(void* smData);

/**
 * Action Action5
 * @param smDesc the state machine descriptor
 */
void Action5(FwSmDesc_t smDesc);

/**
 * Action Action6
 * @param smDesc the state machine descriptor
 */
void Action6(FwSmDesc_t smDesc);

/**
 * Action Action2
 * @param smDesc the state machine descriptor
 */
void Action2(FwSmDesc_t smDesc);

/**
 * Action Action4
 * @param smDesc the state machine descriptor
 */
void Action4(FwSmDesc_t smDesc);

/**
 * Action Action3
 * @param smDesc the state machine descriptor
 */
void Action3(FwSmDesc_t smDesc);

/**
 * Action Action1
 * @param smDesc the state machine descriptor
 */
void Action1(FwSmDesc_t smDesc);

/**
 * Guard Guard2
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t Guard2(FwSmDesc_t smDesc);

/**
 * Guard Guard1
 * @param smDesc the state machine descriptor
 * @return 1 if the guard is fulfilled, otherwise 0.
 */
FwSmBool_t Guard1(FwSmDesc_t smDesc);

#endif /* Example2_H_ */