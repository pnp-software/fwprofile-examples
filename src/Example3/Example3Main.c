/**
 * @file Example3Main.c
 *
 * @author FW Profile code generator version 5.02
 * @date Created on: Dec 22 2016 12:12:41
 */

/** Example3 function definitions */
#include "Example3.h"

/** FW Profile function definitions */
#include "FwPrConstants.h"
#include "FwPrPrivate.h"
#include "FwPrConfig.h"
#include "FwPrCore.h"

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

FwPrBool_t hasNext()
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

FwPrBool_t nextGuard(char* callee)
{
	return (FwPrBool_t)getNext(callee) % 2;
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

/** Action Action1 */
void Action1(FwPrDesc_t prDesc)
{
	printf("  Action Action1\n");
}

/** Action Action2 */
void Action2(FwPrDesc_t prDesc)
{
	printf("  Action Action2\n");
}

/** Guard Guard1 */
FwPrBool_t Guard1(FwPrDesc_t prDesc)
{
	int guard = nextGuard("Guard Guard1");
	printf("  Guard Guard1(%d)\n", guard);
	return guard;
}

/** Guard Guard2 */
FwPrBool_t Guard2(FwPrDesc_t prDesc)
{
	int guard = nextGuard("Guard Guard2");
	printf("  Guard Guard2(%d)\n", guard);
	return guard;
}

/** Guard wait */
FwPrBool_t wait(FwPrDesc_t prDesc)
{
	int guard = nextGuard("Guard wait");
	printf("  Guard wait(%d)\n", guard);
	return guard;
}

/* ----------------------------------------------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{
	int i;

	setArgs(argc, argv);

	/** Define the procedure descriptor (PRD) */
	FwPrDesc_t prDesc = Example3Create(NULL);

	/** Check that the procedure is properly configured */
	if (FwPrCheck(prDesc) != prSuccess) {
		printf("The procedure Example3 is NOT properly configured ... FAILURE\n");
		return EXIT_FAILURE;
	}

	printf("The procedure Example3 is properly configured ... SUCCESS\n");

	/** Start the procedure, and execute it */
	FwPrStart(prDesc);
	for (i = 0; hasNext() && FwPrGetCurNode(prDesc) != 0; i++) {
		printf("[%03d]\n", i++);
		FwPrExecute(prDesc);
	}

	close();
	return EXIT_SUCCESS;
}