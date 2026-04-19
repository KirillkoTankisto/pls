SRC = src
INC = include
BUILD = build

SRC_FILES = args.c dirs.c display.c error.c filemeta.c genericmap.c io.c main.c
INC_FILES = args.h dirs.h display.h error.h filemeta.h genericmap.h io.h

CC ?= cc
TARGET ?=

CFLAGS = -O3 -pipe -std=c23 -Wall -Wextra -Werror -pedantic -D_POSIX_C_SOURCE=200809L $(TARGET)
DBGFLAGS = -O0 -g -std=c23 -Wall -Wextra -Werror -pedantic -D_POSIX_C_SOURCE=200809L

LDFLAGS = -Wl,--strip-all

PREFIX ?= /usr/local/bin

all: compile

compile: $(BUILD)/pls

debug: $(BUILD)/pls_debug

$(BUILD)/pls: $(addprefix $(SRC)/,$(SRC_FILES)) $(addprefix $(INC)/,$(INC_FILES)) $(BUILD)
	$(CC) -o $@ $(addprefix $(SRC)/,$(SRC_FILES)) $(CFLAGS) $(LDFLAGS)

$(BUILD)/pls_debug: $(addprefix $(SRC)/,$(SRC_FILES)) $(addprefix $(INC)/,$(INC_FILES)) $(BUILD)
	$(CC) -o $@ $(addprefix $(SRC)/,$(SRC_FILES)) $(DBGFLAGS)

$(BUILD):
	mkdir -p $@

clean: $(BUILD)
	rm -rf build

install: $(BUILD)/pls $(PREFIX)
	mkdir -p $(PREFIX)
	install $(BUILD)/pls $(PREFIX)

.PHONY: all compile debug clean install
