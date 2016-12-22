# Following line must stay on line 2, otherwise Release.sh will not work anymore.
C1_DIR = ./lib/fwprofile/src
C1_SRC_SM = $(shell find $(C1_DIR) -name 'FwSm*.c')
C1_SRC_PR = $(shell find $(C1_DIR) -name 'FwPr*.c')
C1_SRC_RT = $(shell find $(C1_DIR) -name 'FwRt*.c')
C1_SRC = $(C1_SRC_SM) $(C1_SRC_PR) $(C1_SRC_RT)

PR_DIR = ./src/pr_tutorials
RT_DIR = ./src/rt_tutorials
SM_DIR = ./src/sm_tutorials

DA_EXE = $(OUT)/sm_demo
E1_EXE = $(OUT)/Example1
E2_EXE = $(OUT)/Example2
E3_EXE = $(OUT)/Example3
RT_EXE = $(OUT)/RtExample1
PR_EXE = $(OUT)/PrExample1
SM_EXE = $(OUT)/SmExample1 $(OUT)/SmExample2 $(OUT)/SmExample3
EXE = $(DA_EXE) $(E1_EXE) $(E2_EXE) $(RT_EXE) $(PR_EXE) $(SM_EXE)

CC ?= gcc
CFLAGS = -std=c99 -O0 -g3 -Wall -fmessage-length=0 -fprofile-arcs -ftest-coverage -I$(C1_DIR)
LFLAGS = -Wl,-fprofile-arcs
LIBS = -lpthread
OUT = bin

.PHONY: all create_dir clean run-all

all: clean $(EXE)

run-all:
	$(patsubst %,./%;,$(EXE))

$(DA_EXE): create_dir $(shell find ./src/app -name 'FwDa*.c') $(C1_SRC)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^) $(LIBS)

$(E1_EXE): create_dir $(shell find ./src/Example1/ -name '*.c') $(C1_SRC_SM)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^)

$(E2_EXE): create_dir $(shell find ./src/Example2/ -name '*.c') $(C1_SRC_SM)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^)

$(E3_EXE): create_dir $(shell find ./src/Example3/ -name '*.c') $(C1_SRC_PR)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^)	

$(RT_EXE): $(OUT)/%: create_dir $(RT_DIR)/FwProfile_%.c $(C1_SRC_RT)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^) $(LIBS)

$(PR_EXE): $(OUT)/%: create_dir $(PR_DIR)/FwProfile_%.c $(C1_SRC_PR)	
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^)

$(SM_EXE): $(OUT)/%: create_dir $(SM_DIR)/FwProfile_%.c $(C1_SRC_SM)
	$(CC) $(CFLAGS) -o $@ $(filter-out $<,$^)

print-%:
	@echo $*=$($*)

create_dir:
	mkdir -p $(OUT)

clean:
	rm $(OUT) -rf
