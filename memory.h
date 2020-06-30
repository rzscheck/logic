#ifndef logic_memory_h
#define logic_memory_h

typedef struct Memory {
	Bit store[4]; // address, data, ALU, RAM;
	Bit clock;
	Bit data[8];
	Register reg[3]; // address, data, ALU;
	RAM256 ram;
	Bit out[4][8]; // address, data, ALU, RAM;
} Memory;

void initMemory(Memory* mem);
void doMemory(Memory* mem);
Memory* newMemory();

#endif
