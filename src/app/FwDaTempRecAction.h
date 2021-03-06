/**
 * @file
 * @ingroup daGroup
 * Definition of the <i>Temperature Failure Recovery Action (RA)</i>.
 * This RA is encapsulated in a procedure which first commands
 * the Hardware Device into SBY and then checks whether the
 * temperature is below a safe threshold. If this is so, the device
 * is commanded back into operational mode; otherwise it is switched
 * off(see figure below).
 * @image html TempRecAction.png
 * @author Vaclav Cechticky, Alessandro Pasetti
 * @copyright P&P Software GmbH, 2012, All Rights Reserved
 */

#ifndef FWDATEMPRA_H_
#define FWDATEMPRA_H_

#include "FwPrConstants.h"
#include "FwPrCore.h"

/** Identifier of the Temperature Recovery Action. */
#define TEMP_REC_ACTION_ID 1

/**
 * Number of wait cycles between the command sending the Hardware
 * Device to Stand-By and the check on the temperature.
 */
#define TEMP_REC_ACTION_N1 4

/**
 * Temperature threshold for the Temperature Recovery Action.
 * If the temperature of the HW Device is found to be below this
 * thresholds, the HW Device is commanded back into operational
 * mode; otherwise, it is switched off.
 */
#define TEMP_REC_ACTION_T1 50

/**
 * Retrieve the descriptor of the Temperature Recovery Action Procedure.
 * The Temperature Recovery Action Procedure is a singleton.
 * The first time this function is called, it creates and configures
 * the procedure descriptor.
 * Subsequently, it always returns the same descriptor.
 * 
 * This procedure performs the following actions:
 * - It commands the Hardware Device into Stand-By Mode
 * - It waits TEMP_REC_ACT_N1 cycles
 * - It checks the temperature and, if it finds that it is below
 *   TEMP_REC_ACTION_T1, it commands the HW Device back into
 *   operational mode; otherwise it switches it off.
 * .
 * @return the procedure descriptor or NULL
 * if the procedure could not be created.
 */
FwPrDesc_t GetTempRecActionPr();

#endif /* FWDACURRA_H_ */
