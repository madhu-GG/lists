SRC=src
OBJ=obj
LIB=lib
INC=inc

TESTSRC=test
TESTBIN=test
TESTLIB=-lcriterion
TESTINC=

TEST_TYPE ?=simple_test

TEST_EXEC =$(TESTBIN)/$(TEST_TYPE).bin


MODE ?=release

ifeq ("$(MODE)","debug")
	CFLAGS += -g -Wall -Wextra
else
	CFLAGS += -O2
endif

ARR_SRC=$(SRC)/array_list

ARR_LIB=$(LIB)/libarraylist.a

$(ARR_LIB): $(OBJ)/arraylist.o
	mkdir -p $(LIB)
	$(AR) rcs $@ $^

$(OBJ)/arraylist.o: $(ARR_SRC)/*.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $^ -I$(INC)

LL_SRC=$(SRC)/linked_list

LL_LIB=$(LIB)/liblinkedlist.a

$(LL_LIB):$(OBJ)/linkedlist.o
	mkdir -p $(LIB)
	$(AR) rc $@ $^

$(OBJ)/linkedlist.o: $(LL_SRC)/*.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $^ -I$(INC)

.PHONY: clean linked array test

clean:
	rm -f $(OBJ)/*
	rm -f $(LIB)/*
	rm -f $(TEST_EXEC)

array: $(ARR_LIB)

linked: $(LL_LIB)

test: $(TEST_EXEC)

$(TEST_EXEC): $(TESTSRC)/$(TEST_TYPE).c $(LIB)/*.a
	$(CC) $(CFLAGS) -o $@ $^ -I$(INC) $(TESTINC) $(TESTLIB)
