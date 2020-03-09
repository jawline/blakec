BINDIR=./bin/
TEST_BIN=$(BINDIR)/test

.PHONY: all

all: build

build:
	mkdir -p ${BINDIR}

test: build
	@echo "Building Tests"
	${CC} -o ${TEST_BIN} -Isrc/ test/test.c
	@echo "Running Tests"
	${TEST_BIN}
