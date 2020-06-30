#ifndef logic_alu_h
#define logic_alu_h

typedef struct UnaryComp {
	Bit zero, negate;
	Bit data[8];
	Not not[8];
	Mux8Comp mux8[2];
	Bit out[8];
} UnaryComp;

void initUnary(UnaryComp* unary);
void Unary(UnaryComp* unary);

#endif
