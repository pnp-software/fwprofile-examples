
C1_DIR = ./lib/fwprofile/src
C1_SRC = $(shell find $(C1_DIR) -name '*.c')
C1_OBJ = $(patsubst $(C1_DIR)/%.c,$(OUT)/%.o,$(C1_SRC))

DA_DIR = ./src
DA_SRC = $(shell find $(DA_DIR) -name 'FwDa*.c')
DA_OBJ = $(patsubst $(DA_DIR)/%c,$(OUT)/%o,$(DA_SRC))

CC ?= gcc
CFLAGS = -O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -I$(C1_DIR)
LFLAGS = -fprofile-arcs
LIBS = -lpthread
OUT = bin

.PHONY: all create_dir clean C1 run-all

all: create_dir C1 $(OUT)/sm_demo $(OUT)/RtExample1 $(OUT)/PrExample1 $(OUT)/SmExample1 $(OUT)/SmExample2 $(OUT)/SmExample3

run-all:
	./$(OUT)/sm_demo
	./$(OUT)/RtExample1
	./$(OUT)/PrExample1
	./$(OUT)/SmExample1
	./$(OUT)/SmExample2
	./$(OUT)/SmExample3

C1: $(C1_OBJ)

$(OUT)/%: bin/FwProfile_%.o $(C1_OBJ)
	$(CC) $(LFLAGS) -o $@ $? $(LIBS)

$(OUT)/sm_demo: $(DA_OBJ) $(C1_OBJ)
	$(CC) $(LFLAGS) -o $@ $? $(LIBS)

$(OUT)/%.o: $(DA_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(OUT)/%.o: $(C1_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

print-%: ; @echo $*=$($*)

create_dir:
	mkdir -p $(OUT)

clean:
	rm $(OUT) -rdf
