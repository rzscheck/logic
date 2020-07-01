#ifndef logic_components_h
#define logic_components_h

typedef struct Mux {
	Bit store;
	Bit data[2];
	Nand nand[3];
	Not not;
	Bit out;
} Mux;

typedef struct Mux8 {
	Bit store;
	Bit data[2][8];
	Mux mux[8];
	Bit out[8];
} Mux8;

typedef struct DMux {
	Bit store, data;
	And and[2];
	Not not;
	Bit out[2];
} DMux;

typedef struct Latch {
	Bit store, data;
	Mux mux;
	Bit out;
} Latch;

typedef struct DFF {
	Bit store, data, clock;
	Nand nand[2];
	Not not[2];
	Latch latch[2];
	Bit out;
} DFF;

typedef struct Register {
	Bit store, clock;
	Bit data[8];
	DFF dff[8];
	Bit out[8];
} Register;

typedef struct Counter {
	Bit store, clock;
	Bit data[8];
	Mux8 mux8;
	Not not;
	Increment increment;
	Register reg;
	Bit out[8];
} Counter;

// typedef struct RAM {
	// Bit store, clock;
	// Bit address[8], data[8];
	
	// Register reg[256];
// }

Mux* newMux();
void initMux(Mux* mux);
void doMux(Mux* mux);

Mux8* newMux8();
void initMux8(Mux8* mux8);
void doMux8(Mux8* mux8);

DMux* newDMux();
void initDMux(DMux* dmux);
void doDMux(DMux* dmux);

Latch* newLatch();
void initLatch(Latch* latch);
void doLatch(Latch* latch);

DFF* newDFF();
void initDFF(DFF* dff);
void doDFF(DFF* dff);

Register* newRegister();
void initRegister(Register* reg);
void doRegister(Register* reg);

Counter* newCounter();
void initCounter(Counter* counter);
void doCounter(Counter* counter);

#endif
