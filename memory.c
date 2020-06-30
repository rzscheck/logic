#include "gates.h"
#include "arithmetic.h"
#include "components.h"
#include "ram.h"
#include "memory.h"

//
// Memory
//

void initMemory(Memory* mem) {
	int i;
	mem->clock = '0';
	for (i = 0; i < 8; i++) mem->data[i] = '0';
	for (i = 0; i < 3; i++) {
		mem->store[i] = '0';
		initRegister(&mem->reg[i]);
	}
	initRAM256(&mem->ram);
	doMemory(mem);
}

void doMemory(Memory* mem) {
	int i, j;
	for (i = 0; i < 3; i++) {
		mem->reg[i].store = mem->store[i];
		mem->reg[i].clock = mem->clock;
		for (j = 0; j < 8; j++) mem->reg[i].data[j] = mem->data[j];
		Register(&mem->reg[i]);
	}
	
	mem->ram.store = mem->store[3];
	mem->ram.clock = mem->clock;
	for (i = 0; i < 8; i++) {
		mem->ram.data[i] = mem->data[i];
		mem->ram.address[i] = mem->reg[0].out[i];
	}
	doRAM256(&mem->ram);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 8; j++) mem->out[i][j] = mem->reg[i].out[j];
	}
	for (i = 0; i < 8; i++) mem->out[3][i] = mem->ram.out[i];
}

Memory* newMemory() {
	Memory* memory = (Memory*)malloc(sizeof(Memory));
	initMemory(memory);
	return memory;
}
