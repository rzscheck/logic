#ifndef logic_ram_h
#define logic_ram_h

typedef struct RAMComp {
	Bit store, address, clock;
	Bit data[8];
	DMuxComp dmux;
	RegisterComp reg[2];
	Mux8Comp mux8;
	Bit out[8];
} RAMComp;

typedef struct RAM4Comp {
	Bit store, address[2], clock;
	Bit data[8];
	DMuxComp dmux;
	RAMComp ram[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM4Comp;

typedef struct RAM8Comp {
	Bit store, address[3], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM4Comp ram4[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM8Comp;

typedef struct RAM16Comp {
	Bit store, address[4], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM8Comp ram8[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM16Comp;

typedef struct RAM32Comp {
	Bit store, address[5], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM16Comp ram16[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM32Comp;

typedef struct RAM64Comp {
	Bit store, address[6], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM32Comp ram32[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM64Comp;

typedef struct RAM128Comp {
	Bit store, address[7], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM64Comp ram64[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM128Comp;

typedef struct RAM256Comp {
	Bit store, address[8], clock;
	Bit data[8];
	DMuxComp dmux;
	RAM128Comp ram128[2];
	Mux8Comp mux8;
	Bit out[8];
} RAM256Comp;

void initRAM(RAMComp* ram);
void RAM(RAMComp* ram);

void initRAM4(RAM4Comp* ram4);
void RAM4(RAM4Comp* ram4);

void initRAM8(RAM8Comp* ram8);
void RAM8(RAM8Comp* ram8);

void initRAM16(RAM16Comp* ram16);
void RAM16(RAM16Comp* ram16);

void initRAM32(RAM32Comp* ram32);
void RAM32(RAM32Comp* ram32);

void initRAM64(RAM64Comp* ram64);
void RAM64(RAM64Comp* ram64);

void initRAM128(RAM128Comp* ram128);
void RAM128(RAM128Comp* ram128);

void initRAM256(RAM256Comp* ram256);
void RAM256(RAM256Comp* ram256);

#endif
