#ifndef logic_alu_h
#define logic_alu_h

typedef struct Unary {
	Bit zero, negate;
	Bit data[8];
	Not not[8];
	Mux8Comp mux8[2];
	Bit out[8];
} Unary;

void initUnary(Unary* unary);
void doUnary(Unary* unary);
Unary* newUnary();

#endif
