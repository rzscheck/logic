#ifndef logic_components_h
#define logic_components_h

typedef struct MuxComp {
	Bit store;
	Bit data[2];
	Nand nand[3];
	Not not;
	Bit out;
} MuxComp;

typedef struct Mux8Comp {
	Bit store;
	Bit data[2][8];
	MuxComp mux[8];
	Bit out[8];
} Mux8Comp;

typedef struct DMuxComp {
	Bit store, data;
	And and[2];
	Not not;
	Bit out[2];
} DMuxComp;

typedef struct LatchComp {
	Bit store, data;
	MuxComp mux;
	Bit out;
} LatchComp;

typedef struct DFFComp {
	Bit store, data, clock;
	Nand nand[2];
	Not not[2];
	LatchComp latch[2];
	Bit out;
} DFFComp;

typedef struct RegisterComp {
	Bit store, clock;
	Bit data[8];
	DFFComp dff[8];
	Bit out[8];
} RegisterComp;

typedef struct CounterComp {
	Bit store, clock;
	Bit data[8];
	Mux8Comp mux8;
	Not not;
	IncrementComp increment;
	RegisterComp reg;
	Bit out[8];
} CounterComp;

// typedef struct RAMComp {
	// Bit store, clock;
	// Bit address[8], data[8];
	
	// RegisterComp reg[256];
// }

void initMux(MuxComp* mux);
void Mux(MuxComp* mux);

void initMux8(Mux8Comp* mux8);
void Mux8(Mux8Comp* mux8);

void initDMux(DMuxComp* dmux);
void DMux(DMuxComp* dmux);

void initLatch(LatchComp* latch);
void Latch(LatchComp* latch);

void initDFF(DFFComp* dff);
void DFF(DFFComp* dff);

void initRegister(RegisterComp* reg);
void Register(RegisterComp* reg);

void initCounter(CounterComp* counter);
void Counter(CounterComp* counter);

#endif
