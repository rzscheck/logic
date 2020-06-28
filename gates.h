#ifndef logic_gates_h
#define logic_gates_h

typedef char Bit;

typedef struct NandGate {
	Bit in[2];
	Bit out;
} NandGate;

typedef struct NotGate {
	Bit in;
	NandGate nand;
	Bit out;
} NotGate;

typedef struct AndGate {
	Bit in[2];
	NandGate nand;
	NotGate not;
	Bit out;
} AndGate;

typedef struct OrGate {
	Bit in[2];
	NandGate nand;
	NotGate not[2];
	Bit out;
} OrGate;

typedef struct XorGate {
	Bit in[2];
	NandGate nand[4];
	Bit out;
} XorGate;

void initNand(NandGate* nand);
void Nand(NandGate* nand);

void initNot(NotGate* not);
void Not(NotGate* not);

void initAnd(AndGate* and);
void And(AndGate* and);

void initOr(OrGate* or);
void Or(OrGate* or);

void initXor(XorGate* xor);
void Xor(XorGate* xor);

#endif
