/**
 * @file Example1Main.c
 *
 * @author FW Profile code generator version 5.02
 * @date Created on: Dec 22 2016 11:44:35
 */

/** Example1 function definitions */
#include "Example1.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmDCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CMDS          (128)
#define MAX_RANDOM_CYCLES (1000)

/* ----------------------------------------------------------------------------------------------------------------- */

enum mode_t {EMODE_INTERACTIVE, EMODE_RANDOM, EMODE_COMMANDLINE};

static enum mode_t g_mode;
static char**      g_argv;
static int         g_argc;
static int         g_arg;
static int         g_cmds[MAX_CMDS];
static int         g_cmdn;
static int         g_cycles;

void setArgs(int argc, char** argv)
{
	if (argc < 2) {
		g_mode = EMODE_RANDOM;
		g_cycles = 0;
		srand(time(NULL));
	}
	else if (strcmp(argv[1], "--interactive") == 0 || 
	         strcmp(argv[1], "-i") == 0) {
		g_mode = EMODE_INTERACTIVE;
		g_cmdn = 0;
	}
	else {
		g_mode = EMODE_COMMANDLINE;
		g_arg = 1;
		g_argc = argc;
		g_argv = argv;
	}
}

FwSmBool_t hasNext()
{
	switch (g_mode)
	{
		case EMODE_COMMANDLINE:
		{
			return (g_arg < g_argc);
		}
		case EMODE_INTERACTIVE:
		{
			return 1;
		}
		case EMODE_RANDOM:
		default:
		{
			return g_cycles < MAX_RANDOM_CYCLES;
		}
	}
}

int getNext(char* callee)
{
	int cmd = 0;

	if (hasNext()) {
		switch (g_mode)
		{
			case EMODE_COMMANDLINE:
			{
				cmd = atoi(g_argv[g_arg++]);
				break;
			}
			case EMODE_INTERACTIVE:
			{
				printf("%s>", callee);
				scanf("%d", &cmd);
				if (g_cmdn < MAX_CMDS)
				{
					g_cmds[g_cmdn++] = cmd;
				}
				break;
			}
			case EMODE_RANDOM:
			default:
			{
				cmd = rand();
				g_cycles++;
				break;
			}
		}
	}
	return cmd;
}

FwSmCounterU2_t nextTrigger()
{
	return (FwSmCounterU2_t)getNext("Trigger") % TRIGGER_NUM;
}

FwSmBool_t nextGuard(char* callee)
{
	return (FwSmBool_t)getNext(callee) % 2;
}

void close(void)
{
	switch (g_mode)
	{
		case EMODE_INTERACTIVE:
		{
			printf("Entered commands:\n");
			for (int i = 0; i < g_cmdn; i++)
			{
				printf("%d ", g_cmds[i]);
			}
			printf("\n");
			break;
		}
		default:
		{
			break;
		}
	}
}

/** Action Action2 */
void Action2(FwSmDesc_t smDesc)
{
	printf("  Action Action2\n");
}

/** Action Action4 */
void Action4(FwSmDesc_t smDesc)
{
	printf("  Action Action4\n");
}

/** Action Action3 */
void Action3(FwSmDesc_t smDesc)
{
	printf("  Action Action3\n");
}

/** Action Action1 */
void Action1(FwSmDesc_t smDesc)
{
	printf("  Action Action1\n");
}

/** Guard Guard2 */
FwSmBool_t Guard2(FwSmDesc_t smDesc)
{
	int guard = nextGuard("Guard Guard2");
	printf("  Guard Guard2(%d)\n", guard);
	return guard;
}

/** Guard Guard1 */
FwSmBool_t Guard1(FwSmDesc_t smDesc)
{
	int guard = nextGuard("Guard Guard1");
	printf("  Guard Guard1(%d)\n", guard);
	return guard;
}

/* ----------------------------------------------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
	int i, trigger;

	setArgs(argc, argv);

	/** Define the state machine descriptor (SMD) */
	FwSmDesc_t smDesc = Example1Create(NULL);

	/** Check that the SM is properly configured */
	if (FwSmCheckRec(smDesc) != smSuccess) {
		printf("The state machine Example1 is NOT properly configured ... FAILURE\n");
		return EXIT_FAILURE;
	}

	printf("The state machine Example1 is properly configured ... SUCCESS\n");

	/** Start the SM, send a few transition commands to it, and execute it */
	FwSmStart(smDesc);
	for (i = 0; hasNext() && FwSmGetCurState(smDesc) != 0; i++) {
		trigger = nextTrigger();
		printf("[%03d] Trigger %d\n", i, trigger);
		FwSmMakeTrans(smDesc, trigger);
	}

	close();
	return EXIT_SUCCESS;
}