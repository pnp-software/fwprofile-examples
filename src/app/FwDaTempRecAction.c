/**
 * @file
 * @ingroup daGroup
 * Implementation of Temperature Recovery Action.
 *
 * @author V. Cechticky and A. Pasetti
 * @copyright P&P Software GmbH, 2011
 */

#include <stdlib.h>
#include "FwDaTempRecAction.h"
#include "FwDaHwDev.h"
#include "FwDaCurCheck.h"
#include "FwPrCore.h"
#include "FwPrConfig.h"
#include "FwPrDCreate.h"

/* --------------------------------------------------------------------- */
/**
 * Switch Off Hardware Device.
 * The Hardware Device is switch off by sending it command TR_HW_DEV_OFF.
 * @param prDesc the procedure descriptor
 */
static void HwDevSwitchOff(FwPrDesc_t prDesc);

/* --------------------------------------------------------------------- */
/**
 * Command Hardware Device to Stand-By.
 * The Hardware Device is commanded to Stand-By by sending it command
 * TR_HW_DEV_SBY.
 * @param prDesc the procedure descriptor
 */
static void HwDevToStandBy(FwPrDesc_t prDesc);

/* --------------------------------------------------------------------- */
/**
 * Command Hardware Device into Operational Mode.
 * The Hardware Device is commanded into operational mode by sending
 * it command TR_HW_DEV_OPER.
 * @param prDesc the procedure descriptor
 */
static void HwDevOperational(FwPrDesc_t prDesc);

/* --------------------------------------------------------------------- */
/**
 * Wait TEMP_REC_ACTION_N1 cycles.
 * This function is used as a guard in the procedure.
 * @param prDesc the procedure descriptor
 */
static FwPrBool_t WaitN1Cycle(FwPrDesc_t prDesc);

/* --------------------------------------------------------------------- */
/**
 * Check whether the HW Device temperature is below TEMP_REC_ACTION_T1.
 * This function is used as a guard in the procedure.
 * @param prDesc the procedure descriptor
 */
static FwPrBool_t TempBelowT1(FwPrDesc_t prDesc);

/* --------------------------------------------------------------------- */
FwPrDesc_t GetTempRecActionPr() {
	static FwPrDesc_t tempRecAction = NULL;
	const FwPrCounterS1_t nOfANodes = 3;	/* Number of action nodes */
	const FwPrCounterS1_t nOfDNodes = 1;	/* Number of decision nodes */
	const FwPrCounterS1_t nOfFlows = 6;		/* Number of control flows */
	const FwPrCounterS1_t nOfActions = 3;	/* Number of actions */
	const FwPrCounterS1_t nOfGuards = 2;	/* Number of guards */

	if (tempRecAction != NULL)	/* Temperature Recovery Action was already created */
		return tempRecAction;

	/* Create and configure the procedure */
	tempRecAction = FwPrCreate(nOfANodes,nOfDNodes,nOfFlows,nOfActions,nOfGuards);

	FwPrAddActionNode(tempRecAction, 1, &HwDevToStandBy);
	FwPrAddActionNode(tempRecAction, 2, &HwDevOperational);
	FwPrAddActionNode(tempRecAction, 3, &HwDevSwitchOff);

	FwPrAddDecisionNode(tempRecAction, 1, 2);

	FwPrAddFlowIniToAct(tempRecAction, 1, NULL);
	FwPrAddFlowActToDec(tempRecAction, 1, 1, &WaitN1Cycle);
	FwPrAddFlowDecToAct(tempRecAction, 1, 2, &TempBelowT1);
	FwPrAddFlowDecToAct(tempRecAction, 1, 3, NULL);	/* This acts as an "Else" guard */
	FwPrAddFlowActToFin(tempRecAction, 2, NULL);
	FwPrAddFlowActToFin(tempRecAction, 3, NULL);

	return tempRecAction;
}

/* --------------------------------------------------------------------- */
static void HwDevSwitchOff(FwPrDesc_t prDesc) {
	FwSmMakeTrans(GetHwDevSm(), TR_HW_DEV_OFF);
}

/* --------------------------------------------------------------------- */
static void HwDevToStandBy(FwPrDesc_t prDesc) {
	FwSmMakeTrans(GetHwDevSm(), TR_HW_DEV_SBY);
}

/* --------------------------------------------------------------------- */
static void HwDevOperational(FwPrDesc_t prDesc) {
	FwSmMakeTrans(GetHwDevSm(), TR_HW_DEV_OPER);
}

/* --------------------------------------------------------------------- */
static FwPrBool_t WaitN1Cycle(FwPrDesc_t prDesc) {
	if (FwPrGetNodeExecCnt(prDesc) >= TEMP_REC_ACTION_N1)
		return 1;
	else
		return 0;
}

/* --------------------------------------------------------------------- */
static FwPrBool_t TempBelowT1(FwPrDesc_t prDesc) {
	if (GetHwDevTemp() < TEMP_REC_ACTION_T1)
		return 1;
	else
		return 0;
}
