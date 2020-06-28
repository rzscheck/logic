logic: main.c gates.c gates.h arithmetic.c arithmetic.h components.c components.h ram.c ram.h memory.c memory.h alu.c alu.h test.c test.h
	gcc -o logic main.c gates.c arithmetic.c components.c ram.c memory.c alu.c test.c -g -Wall
