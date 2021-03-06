/**
 * @file
 * @ingroup daGroup
 * Definition of the <i>Temperature Failure Detection (FD)
 * Check</i>.
 * This FD Check is encapsulated in a state machine which is derived
 * from the FD Check State Machine.
 * The Temperature Check reports "anomaly detected" if the
 * temperature of the hardware device is above a certain
 * threshold.
 * if the Temperature Check declares a failure, it starts the
 * Temperature Recovery Action Procedure.
 * @author Vaclav Cechticky, Alessandro Pasetti
 * @copyright P&P Software GmbH, 2011, All Rights Reserved
 */

#ifndef FWDATEMPCHECK_H_
#define FWDATEMPCHECK_H_

/**
 * Maximum nominal temperature of the Hardware Device.
 * If the temperature of the Hardware Device exceeds this limit,
 * the Temperature FD Check declares an anomaly and if the
 * anomaly persists for longer than HW_DEV_TEMP_CNT_LIMIT
 * cycles, the Hardware Device must be switched off.
 */
#define HW_DEV_TEMP_MAX_NOM 90

/**
 * Counter limit for the Temperature FD Check.
 * If the temperature FD Check detects an anomaly for longer
 * than HW_DEV_TEMP_CNT_LIMIT cycles, then a failure is
 * declared and the Recovery Action associated to the check
 * is executed.
 */
#define HW_DEV_TEMP_CNT_LIMIT 2

/**
 * Retrieve the descriptor of the Temperature FD Check State Machine.
 * The Temperature FD Check State Machine is a singleton.
 * The first time this function is called, it creates and configures
 * the state machine descriptor.
 * Subsequently, it always returns the same descriptor.
 * 
 * The Temperature FD Check State Machine is built as an extension
 * of the generic FD Check State Machine
 * (see <code>FwDaFailDetCheck.h</code>) with the following changes:
 * - The Default Anomaly Detection Check (function
 *   <code>::DefAnomalyDetCheck</code>) is overridden to
 *   report "anomaly detected" if the temperature of the
 *   hardware device is above HW_DEV_TEMP_MAX_NOM.
 * - The Default Recovery Action (function
 *   <code>::DefRecoveryAction</code>) is overridden to
 *   start the Temperature Recovery Action Procedure.
 * - The counter limit <code>cntLimit</code> is set to
 *   HW_DEV_TEMP_CNT_LIMIT.
 * .
 * Thus, this FD Check monitors the temperature of the Hardware
 * Device and, if it finds that it is out-of-limits for more
 * than HW_DEV_TEMP_CNT_LIMIT consecutive cycles, it switches
 * off the Hardware Device.
 * @return the descriptor of the FD Check State Machine or NULL
 * if the state machine could not be created.
 */
FwSmDesc_t GetTempCheckSm();

#endif /* FWDATEMPCHECK_H_ */
