BINDIR=./bin/
TEST_BIN=$(BINDIR)/test

.PHONY: all

all: build

build:
	mkdir -p ${BINDIR}

test: build
	@echo "Building Tests"
	${CC} -o ${TEST_BIN}list -Isrc/ test/list.c
	${CC} -o ${TEST_BIN}progress -Isrc/ src/blprogress.c test/progress.c
	@echo "Running Tests"
	${TEST_BIN}list
	${TEST_BIN}progress
