/**
 * @file Example3.c
 *
 * @author FW Profile code generator version 5.02
 * @date Created on: Dec 22 2016 12:12:41
 */

/** Example3 function definitions */
#include "Example3.h"

/** FW Profile function definitions */
#include "FwPrPrivate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

#include <stdlib.h>

/** Global variables */
static int exec_counter = 1;

/* ----------------------------------------------------------------------------------------------------------------- */
static struct FwPrDesc prDesc = {
	.prBase = &(PrBaseDesc_t){
		.aNodes = (PrANode_t[]) {
				{.iFlow = 1,
				 .iAction = 0},
				{.iFlow = 4,
				 .iAction = 0},
				{.iFlow = 5,
				 .iAction = 1},
				{.iFlow = 6,
				 .iAction = 1}},
		.dNodes = (PrDNode_t[]) {
				{.outFlowIndex = 2,
				 .nOfOutTrans = 2}},
		.flows = (PrFlow_t[]) {
				{.dest = 1,
				 .iGuard = 0},
				{.dest = 3,
				 .iGuard = 1},
				{.dest = 2,
				 .iGuard = 1},
				{.dest = 4,
				 .iGuard = 2},
				{.dest = 0,
				 .iGuard = 0},
				{.dest = -1,
				 .iGuard = 3},
				{.dest = 0,
				 .iGuard = 0}},
		.nOfANodes = 4,
		.nOfDNodes = 1,
		.nOfFlows = 7},
	.prActions = (FwPrAction_t[]){
		&Action1,
		&Action2},
	.prGuards = (FwPrGuard_t[]){
		&PrDummyGuard,
		&Guard1,
		&Guard2,
		&wait},
	.nOfActions = 2,
	.nOfGuards = 4,
	.flowCnt = 7,
	.curNode = 0,
	.errCode = prSuccess,
	.prExecCnt = 0,
	.nodeExecCnt = 0,
	.prData = NULL
};

FwPrDesc_t Example3Create(void* prData)
{
	FwPrSetData(&prDesc, prData);
	return &prDesc;
}