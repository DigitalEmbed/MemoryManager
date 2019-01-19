BIN_NAME=main

all: $(BIN_NAME)

eMemoryPool: main.c LinkedList.o DataBank.o MemoryPool.o
	gcc -ggdb -o main main.c LinkedList.o DataBank.o MemoryPool.o

LinkedList.o: LinkedList/LinkedList.c LinkedList/LinkedList.h
	gcc -ggdb -c LinkedList/LinkedList.c

DataBank.o: DataBank/DataBank.c DataBank/DataBank.h
	gcc -ggdb -c DataBank/DataBank.c

MemoryPool.o: MemoryPool/MemoryPool.c MemoryPool/MemoryPool.h
	gcc -ggdb -c MemoryPool/MemoryPool.c


