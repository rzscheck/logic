#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gates.h"
#include "arithmetic.h"
#include "components.h"
#include "ram.h"
#include "alu.h"
#include "memory.h"
#include "test.h"

void testNand() {
	Bit i, j;
	Nand* nand = newNand();
	
	puts("Testing nand");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			nand->in[0] = i; nand->in[1] = j;
			doNand(nand);
			printf("%c nand %c = %c\n", i, j, nand->out);
		}
	}
	
	puts("");
	
	free(nand);
}

void testNot() {
	Bit i;
	Not* not = newNot();
	
	puts("Testing not");
	
	for (i = '0'; i < '2'; i++) {
		not->in = i;
		doNot(not);
		printf("not %c = %c\n", i, not->out);
	}
	
	puts("");
	
	free(not);
}

void testAnd() {
	Bit i, j;
	And* and = newAnd();
	
	puts("Testing and");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			and->in[0] = i; and->in[1] = j;
			doAnd(and);
			printf("%c and %c = %c\n", i, j, and->out);
		}
	}
	
	puts("");
	
	free(and);
}

void testOr() {
	Bit i, j;
	Or* or = newOr();
	
	puts("Testing or");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			or->in[0] = i; or->in[1] = j;
			doOr(or);
			printf("%c or %c = %c\n", i, j, or->out);
		}
	}
	
	puts("");
	
	free(or);
}

void testXor() {
	Bit i, j;
	Xor* xor = newXor();
	
	puts("Testing xor");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			xor->in[0] = i; xor->in[1] = j;
			doXor(xor);
			printf("%c xor %c = %c\n", i, j, xor->out);
		}
	}
	
	puts("");
	
	free(xor);
}

void testHalfAdd() {
	Bit i, j;
	HalfAdd* halfAdd = (HalfAdd*)malloc(sizeof(HalfAdd));
	initHalfAdd(halfAdd);
	
	puts("Testing half add");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			halfAdd->in[0] = i; halfAdd->in[1] = j;
			doHalfAdd(halfAdd);
			printf("%c + %c = %s\n", i, j, halfAdd->out);
		}
	}
	
	puts("");
	
	free(halfAdd);
}

void testFullAdd() {
	Bit i, j, k;
	FullAdd* fullAdd = (FullAdd*)malloc(sizeof(FullAdd));
	initFullAdd(fullAdd);
	
	puts("Testing full add");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			for (k = '0'; k < '2'; k++) {
				fullAdd->in[0] = i; fullAdd->in[1] = j; fullAdd->in[2] = k;
				doFullAdd(fullAdd);
				printf("%c + %c + %c = %c%c\n", i, j, k, fullAdd->out[0], fullAdd->out[1]);
			}
		}
	}
	
	puts("");
	
	free(fullAdd);
}

void testAdd() {
	int i, j;
	Add* add = (Add*)malloc(sizeof(Add));
	initAdd(add);
	
	puts("testing 8-bit add");
	
	Bit in[2][8] = { "00000111", "00000001" };
	
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			add->in[i][j] = in[i][j];
		}
	}
	
	add->carryIn = '0';
	doAdd(add);
	
	for (i = 0; i < 8; i++) printf("%c", add->in[0][i]);
	printf(" + ");
	for (i = 0; i < 8; i++) printf("%c", add->in[1][i]);
	printf(" + %c = [%c]", add->carryIn, add->carryOut);
	for (i = 0; i < 8; i++) printf("%c", add->out[i]);
	puts("");
		
	free(add);
}

void testIncrement() {
	int i;
	Increment* increment = (Increment*)malloc(sizeof(Increment));
	initIncrement(increment);
	
	puts("Testing increment");
	
	increment->in[7] = '1';
	
	doIncrement(increment);
	
	printf("increment(");
	for (i = 0; i < 8; i++) printf("%c", increment->in[i]);
	printf(") = ");
	for (i = 0; i < 8; i++) printf("%c", increment->out[i]);
	
	puts("");
	
	free(increment);
}

void testSubtract() {
	int i;
	Subtract* subtract = (Subtract*)malloc(sizeof(Subtract));
	initSubtract(subtract);
	
	puts("Testing subtract");
	
	
	subtract->in[1][7] = '1';
	doSubtract(subtract);
	
	for (i = 0; i < 8; i++) printf("%c", subtract->in[0][i]);
	printf(" - ");
	for (i = 0; i < 8; i++) printf("%c", subtract->in[1][i]);
	printf(" = ");
	for (i = 0; i < 8; i++) printf("%c", subtract->out[i]);
	puts("");
	
	free(subtract);
}

void testEqualsZero() {
	int i;
	EqualsZero* equalsZero = (EqualsZero*)malloc(sizeof(EqualsZero));
	
	puts("Testing equals zero");
	
	for (i = 0; i < 8; i++) equalsZero->in[i] = '0';
	doEqualsZero(equalsZero);
	
	for (i = 0; i < 8; i++) printf("%c", equalsZero->in[i]);
	printf(" = 0 ? %c\n", equalsZero->out);
	
	equalsZero->in[7] = '1';
	doEqualsZero(equalsZero);
	
	for (i = 0; i < 8; i++) printf("%c", equalsZero->in[i]);
	printf(" = 0 ? %c\n", equalsZero->out);
	
	free(equalsZero);
}

void testLessThanZero() {
	int i;
	LessThanZero* lessThanZero = (LessThanZero*)malloc(sizeof(LessThanZero*));
	initLessThanZero(lessThanZero);
	
	puts("Testing less than zero");
	
	for (i = 0; i < 8; i++) lessThanZero->in[i] = '1';
	
	doLessThanZero(lessThanZero);
	
	printf("-1 < 0 ? %c\n", lessThanZero->out);
	
	free(lessThanZero);
}

void testMux() {
	Bit i, j, k;
	MuxComp* mux = (MuxComp*)malloc(sizeof(MuxComp));
	initMux(mux);
	
	puts("Testing mux");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			for (k = '0'; k < '2'; k++) {
				mux->store = i; mux->data[0] = j; mux->data[1] = k;
				Mux(mux);
				printf("%c %c %c = %c\n", i, j, k, mux->out);
			}
		}
	}
	
	puts("");
	
	free(mux);
}

void testMux8() {
	int i;
	Mux8Comp* mux8 = (Mux8Comp*)malloc(sizeof(Mux8Comp));
	initMux8(mux8);
	
	printf("Testing 8-bit mux\n");
	
	printf("store: %c\n", mux8->store);
	printf("byte 0: ");
	for (i = 0; i < 8; i++) printf("%c", mux8->data[0][i]);
	printf("\nbyte 1: ");
	for (i = 0; i < 8; i++) printf("%c", mux8->data[1][i]);
	printf("\nmuxs:\n");
	for (i = 0; i < 8; i++) {
		printf("%d: store: %c in: %c%c out: %c\n", i, mux8->mux[i].store, mux8->mux[i].data[0], mux8->mux[i].data[1], mux8->mux[i].out);
	}
	printf("\noutput: ");
	for (i = 0; i < 8; i++) printf("%c", mux8->out[i]);
	printf("\n");
	// initMux(mux);
	for (i = 0; i < 8; i++) printf("%c\n", mux8->out[i]);
	puts("Testing 8-bit mux");
	
	mux8->data[0][7] = '1';
	Mux8(mux8);
	for (i = 0; i < 8; i++) printf("%c", mux8->out[i]);
	puts("");
	mux8->store = '1';
	Mux8(mux8);
	for (i = 0; i < 8; i++) printf("%c", mux8->out[i]);
	puts("");
}

void testDMux() {
	Bit i, j;
	DMuxComp* dmux = (DMuxComp*)malloc(sizeof(DMuxComp));
	initDMux(dmux);
	
	puts("Testing dmux");
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			dmux->store = i; dmux->data = j;
			DMux(dmux);
			printf("%c %c = %c%c\n", i, j, dmux->out[0], dmux->out[1]);
		}
	}
	
	puts("");
	
	free(dmux);
}

void testLatch() {
	Bit i, j;
	LatchComp* latch = (LatchComp*)malloc(sizeof(LatchComp));
	initLatch(latch);
	
	puts("Testing latch");
	
	for (i = '1'; i > '0' - 1; --i) {
		for (j = '0'; j < '2'; j++) {
			latch->store = i; latch->data = j;
			Latch(latch);
			printf("%c %c = %c\n", i, j, latch->out);
		}
	}
	
	puts("");
	
	free(latch);
}

void testDFF() {
	Bit i, j, k;
	DFFComp* dff = (DFFComp*)malloc(sizeof(DFFComp));
	initDFF(dff);
	
	puts("Testing flip flop");
	
	for (i = '1'; i > '0' - 1; --i) {
		for (j = '0'; j < '2'; j++) {
			for (k = '0'; k < '2'; k++) {
				dff->store = i; dff->data = j; dff->clock = k;
				DFF(dff);
				printf("%c %c %c = %c\n", i, j, k, dff->out);
			}
		}
	}
	
	puts("");
	
	free(dff);
}

void testRegister() {
	int i;
	RegisterComp* reg = (RegisterComp*)malloc(sizeof(RegisterComp));
	initRegister(reg);
	puts("Testing register");
	reg->store = '1';
	for (i = 0; i < 8; i++) {
		reg->data[i] = (i % 2)+'0';
		printf("%c", reg->out[i]);
	}
	Register(reg);
	reg->clock = '1';
	Register(reg);
	puts("");
	for (i = 0; i < 8; i++) printf("%c", reg->out[i]);
	puts("");
}

void testCounter() {
	int i, j;
	CounterComp* counter = (CounterComp*)malloc(sizeof(CounterComp));
	initCounter(counter);
	
	puts("Testing counter");
	i = 0;
	for (;;) {
		if (counter->clock == '1') {
			for (j = 0; j < 8; j++) printf("%c", counter->out[j]);
			puts("");
		}
		counter->clock = (i % 2) + '0';
		Counter(counter);
		sleep(1);
		i++;
	}
	free(counter);
}

void testRAM() {
	int i;
	RAM* ram = (RAM*)malloc(sizeof(RAM));
	initRAM(ram);
	
	for (i = 0; i < 8; i++) ram->data[i] = '1';
	doRAM(ram);
	puts("Testing RAM");
	
	// ram->address = '1';
	ram->store = '1';
	doRAM(ram);
	ram->clock = '1';
	doRAM(ram);
	ram->store = '0';
	doRAM(ram);
	ram->clock = '0';
	doRAM(ram);
	
	printf("RAM out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->out[i]);
	printf("\nReg 0 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[0].out[i]);
	printf("\nReg 1 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[1].out[i]);
	
	
	for (i = 0; i < 8; i++) ram->data[i] = (i % 2) + '0';
	doRAM(ram);
	ram->address = '1';
	doRAM(ram);
	ram->store = '1';
	doRAM(ram);
	ram->clock = '1';
	doRAM(ram);
	ram->store = '0';
	doRAM(ram);
	ram->clock = '0';
	doRAM(ram);
	printf("\n\nRAM out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->out[i]);
	printf("\nReg 0 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[0].out[i]);
	printf("\nReg 1 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[1].out[i]);
	
	ram->address = '0';
	doRAM(ram);
	
	printf("\n\nRAM out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->out[i]);
	printf("\nReg 0 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[0].out[i]);
	printf("\nReg 1 out: ");
	for (i = 0; i < 8; i++) printf("%c", ram->reg[1].out[i]);
	puts("");
	free(ram);
}

void testUnary() {
	int i, j, k;
	Unary* unary = (Unary*)malloc(sizeof(Unary));
	initUnary(unary);
	
	for (i = 0; i < 8; i++) unary->data[i] = (i % 2) + '0';
	
	for (i = '0'; i < '2'; i++) {
		for (j = '0'; j < '2'; j++) {
			unary->zero = i;
			unary->negate = j;
			doUnary(unary);
			printf("z: %c n: %c out: ", i, j);
			for (k = 0; k < 8; k++) printf("%c", unary->out[k]);
			puts("");
		}
	}
	free(unary);
}

void testMemory() {
	int i, j;
	Memory* mem = (Memory*)malloc(sizeof(Memory));
	initMemory(mem);
	
	mem->store[0] = '1';
	
	for (i = 0; i < 8; i++) mem->data[i] = '1';
	doMemory(mem);
	mem->clock = '1';
	doMemory(mem);
	// mem->store[0] = '1';
	mem->store[3] = '0';
	for (i = 0; i < 8; i++) mem->data[i] = '0';
	doMemory(mem);
	mem->clock = '0';
	doMemory(mem);
	mem->store[0] = '0';
	doMemory(mem);
	mem->clock = '0';
	doMemory(mem);
		
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 8; j++) printf("%c", mem->out[i][j]);
		puts("");
	}

	free(mem);
}

void test() {
	testNand();
	testNot();
	testAnd();
	testOr();
	testXor();
	testHalfAdd();
	testFullAdd();
	testAdd();
	testIncrement();
	testSubtract();
	testEqualsZero();
	testLessThanZero();
	// testMux();
	// testMux8();
	// testDMux();
	// testLatch();
	// testDFF();
	// testRegister();
	// testCounter();
	// testRAM();
	// testUnary();
	// testMemory();
}
