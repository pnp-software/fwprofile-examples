/**
 * @file
 * @ingroup daGroup
 * Definition of the <i>Current Failure Recovery Action (RA)</i>.
 * This RA is encapsulated in a procedure which first commands
 * the Hardware Device into SBY and then switches it off (see
 * figure below).
 * @image html CurRecAction.png
 * @author Vaclav Cechticky, Alessandro Pasetti
 * @copyright P&P Software GmbH, 2011, All Rights Reserved
 */

#ifndef FWDACURRA_H_
#define FWDACURRA_H_

#include "FwPrConstants.h"
#include "FwPrCore.h"

/** Identifier of the Current Recovery Action. */
#define CUR_REC_ACTION_ID 1

/**
 * Number of wait cycles between the command sending the Hardware
 * Device to Stand-By and the command switching it off.
 */
#define CUR_REC_ACTION_N1 4

/**
 * Retrieve the descriptor of the Current Recovery Action Procedure.
 * The Current Recovery Action Procedure is a singleton.
 * The first time this function is called, it creates and configures
 * the procedure descriptor.
 * Subsequently, it always returns the same descriptor.
 * 
 * This procedure performs the following actions:
 * - It commands the Hardware Device into Stand-By Mode
 * - It waits CUR_REC_ACT_N1 cycles
 * - It switches off the Hardware Device.
 * .
 * @return the procedure descriptor or NULL
 * if the procedure could not be created.
 */
FwPrDesc_t GetCurRecActionPr();

#endif /* FWDACURRA_H_ */
