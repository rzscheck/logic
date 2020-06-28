#ifndef logic_memory_h
#define logic_memory_h

typedef struct MemoryComp {
	Bit store[4]; // address, data, ALU, RAM;
	Bit clock;
	Bit data[8];
	RegisterComp reg[3]; // address, data, ALU;
	RAM256Comp ram;
	Bit out[4][8]; // address, data, ALU, RAM;
} MemoryComp;

void initMemory(MemoryComp* mem);
void Memory(MemoryComp* mem);

#endif
