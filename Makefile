SRC=src
OBJ=obj
LIB=lib
INC=inc

ARR_SRC=$(SRC)/array_list

ARR_LIB=$(LIB)/libarraylist.a

$(ARR_LIB): $(OBJ)/arraylist.o
	$(AR) rcs $@ $^

$(OBJ)/arraylist.o: $(ARR_SRC)/*.c
	gcc -o $@ -c $^ -I$(INC)

.PHONY: clean

clean:
	rm -f $(OBJ)/*
	rm -f $(LIB)/*
