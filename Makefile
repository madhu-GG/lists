SRC=src
OBJ=obj
LIB=lib
INC=inc

ARR_SRC=$(SRC)/array_list

ARR_LIB=$(LIB)/libarraylist.a

arraylist: $(ARR_LIB)

$(ARR_LIB): $(ARR_SRC)/*.c
	gcc -o $@ -c $^ -I$(INC)

clean: .PHONY

.PHONY:
	rm -rf lib/*
	rm -rf obj/*
