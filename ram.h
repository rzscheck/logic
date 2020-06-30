#ifndef logic_ram_h
#define logic_ram_h

typedef struct RAM {
	Bit store, address, clock;
	Bit data[8];
	DMux dmux;
	Register reg[2];
	Mux8 mux8;
	Bit out[8];
} RAM;

typedef struct RAM4 {
	Bit store, address[2], clock;
	Bit data[8];
	DMux dmux;
	RAM ram[2];
	Mux8 mux8;
	Bit out[8];
} RAM4;

typedef struct RAM8 {
	Bit store, address[3], clock;
	Bit data[8];
	DMux dmux;
	RAM4 ram4[2];
	Mux8 mux8;
	Bit out[8];
} RAM8;

typedef struct RAM16 {
	Bit store, address[4], clock;
	Bit data[8];
	DMux dmux;
	RAM8 ram8[2];
	Mux8 mux8;
	Bit out[8];
} RAM16;

typedef struct RAM32 {
	Bit store, address[5], clock;
	Bit data[8];
	DMux dmux;
	RAM16 ram16[2];
	Mux8 mux8;
	Bit out[8];
} RAM32;

typedef struct RAM64 {
	Bit store, address[6], clock;
	Bit data[8];
	DMux dmux;
	RAM32 ram32[2];
	Mux8 mux8;
	Bit out[8];
} RAM64;

typedef struct RAM128 {
	Bit store, address[7], clock;
	Bit data[8];
	DMux dmux;
	RAM64 ram64[2];
	Mux8 mux8;
	Bit out[8];
} RAM128;

typedef struct RAM256 {
	Bit store, address[8], clock;
	Bit data[8];
	DMux dmux;
	RAM128 ram128[2];
	Mux8 mux8;
	Bit out[8];
} RAM256;

void initRAM(RAM* ram);
void doRAM(RAM* ram);
RAM* newRAM();

void initRAM4(RAM4* ram4);
void doRAM4(RAM4* ram4);
RAM4* newRAM4();

void initRAM8(RAM8* ram8);
void doRAM8(RAM8* ram8);
RAM8* newRAM8();

void initRAM16(RAM16* ram16);
void doRAM16(RAM16* ram16);
RAM16* newRAM16();

void initRAM32(RAM32* ram32);
void doRAM32(RAM32* ram32);
RAM32* newRAM32();

void initRAM64(RAM64* ram64);
void doRAM64(RAM64* ram64);
RAM64* newRAM64();

void initRAM128(RAM128* ram128);
void doRAM128(RAM128* ram128);
RAM128* newRAM128();

void initRAM256(RAM256* ram256);
void doRAM256(RAM256* ram256);
RAM256* newRAM256();

#endif
