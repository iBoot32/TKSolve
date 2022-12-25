CC=gcc
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
BASE_NAME=cube_solver
SRC_C=$(BASE_NAME).c
TEST_C=test_$(BASE_NAME).c
EXECUTABLE=test_$(BASE_NAME)
EXECUTABLE_GCOV=$(EXECUTABLE)_gcov
SRC_H=$(BASE_NAME).h miniunit.h
SUBMIT_FILES=$(EXECUTABLE).c $(SRC_H) Makefile $(SRC_C)
SHELL=/bin/bash

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

coverage: $(SRC_C) $(TEST_C)
	$(CC) -o $(BASE_NAME) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(BASE_NAME)
	gcov -f $(BASE_NAME)
	
clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

.PHONY: test clean coverage

