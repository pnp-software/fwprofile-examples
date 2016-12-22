/**
 * @file Example2.c
 *
 * @author FW Profile code generator version 5.02
 * @date Created on: Dec 22 2016 11:47:56
 */

/** Example2 function definitions */
#include "Example2.h"

/** FW Profile function definitions */
#include "FwSmPrivate.h"
#include "FwSmConfig.h"

#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
static struct FwSmDesc EsmDesc1 = {
	.smBase = &(SmBaseDesc_t){
		.pStates = (SmPState_t[]) {
			{.outTransIndex = 1,
			 .nOfOutTrans = 1,
			 .iEntryAction = 1,
			 .iDoAction = 0,
			 .iExitAction = 0},
			{.outTransIndex = 2,
			 .nOfOutTrans = 0,
			 .iEntryAction = 0,
			 .iDoAction = 0,
			 .iExitAction = 2}},
		.cStates = NULL,
		.trans = (SmTrans_t[]) {
			{.dest = 1,
			 .id = 0,
			 .iTrAction = 0,
			 .iTrGuard = 0},
			{.dest = 2,
			 .id = Trigger3,
			 .iTrAction = 0,
			 .iTrGuard = 0}},
		.nOfPStates = 2,
		.nOfCStates = 0,
		.nOfTrans = 2},
	.smActions = (FwSmAction_t[]){
		&SmDummyAction,
		&Action5,
		&Action6},
	.smGuards = (FwSmGuard_t[]){
		&SmDummyGuard},
	.esmDesc = (struct FwSmDesc*[]) {
		NULL,
		NULL},
	.nOfActions = 3,
	.nOfGuards = 1,
	.transCnt = 2,
	.curState = 0,
	.smExecCnt = 0,
	.stateExecCnt = 0,
	.errCode = smSuccess,
	.smData = NULL
};

static struct FwSmDesc smDesc = {
	.smBase = &(SmBaseDesc_t){
		.pStates = (SmPState_t[]) {
			{.outTransIndex = 1,
			 .nOfOutTrans = 1,
			 .iEntryAction = 0,
			 .iDoAction = 0,
			 .iExitAction = 1},
			{.outTransIndex = 2,
			 .nOfOutTrans = 1,
			 .iEntryAction = 2,
			 .iDoAction = 3,
			 .iExitAction = 0}},
		.cStates = (SmCState_t[]) {
			{.outTransIndex = 3,
			 .nOfOutTrans = 2}},
		.trans = (SmTrans_t[]) {
			{.dest = 1,
			 .id = 0,
			 .iTrAction = 4,
			 .iTrGuard = 0},
			{.dest = -1,
			 .id = Trigger1,
			 .iTrAction = 0,
			 .iTrGuard = 0},
			{.dest = 0,
			 .id = Trigger2,
			 .iTrAction = 1,
			 .iTrGuard = 1},
			{.dest = 1,
			 .id = 0,
			 .iTrAction = 0,
			 .iTrGuard = 2},
			{.dest = 2,
			 .id = 0,
			 .iTrAction = 0,
			 .iTrGuard = 0}},
		.nOfPStates = 2,
		.nOfCStates = 1,
		.nOfTrans = 5},
	.smActions = (FwSmAction_t[]){
		&SmDummyAction,
		&Action2,
		&Action4,
		&Action3,
		&Action1},
	.smGuards = (FwSmGuard_t[]){
		&SmDummyGuard,
		&Guard2,
		&Guard1},
	.esmDesc = (struct FwSmDesc*[]) {
		NULL,
		&EsmDesc1},
	.nOfActions = 5,
	.nOfGuards = 3,
	.transCnt = 5,
	.curState = 0,
	.smExecCnt = 0,
	.stateExecCnt = 0,
	.errCode = smSuccess,
	.smData = NULL
};

FwSmDesc_t Example2Create(void* smData)
{
	FwSmSetData(&EsmDesc1, smData);
	FwSmSetData(&smDesc, smData);
	return &smDesc;
}