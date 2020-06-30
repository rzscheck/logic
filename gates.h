#ifndef logic_gates_h
#define logic_gates_h

typedef char Bit;

typedef struct Nand {
	Bit in[2];
	Bit out;
} Nand;

typedef struct Not {
	Bit in;
	Nand nand;
	Bit out;
} Not;

typedef struct And {
	Bit in[2];
	Nand nand;
	Not not;
	Bit out;
} And;

typedef struct Or {
	Bit in[2];
	Nand nand;
	Not not[2];
	Bit out;
} Or;

typedef struct Xor {
	Bit in[2];
	Nand nand[4];
	Bit out;
} Xor;

void initNand(Nand* nand);
void doNand(Nand* nand);
Nand* newNand();

void initNot(Not* not);
void doNot(Not* not);
Not* newNot();

void initAnd(And* and);
void doAnd(And* and);
And* newAnd();

void initOr(Or* or);
void doOr(Or* or);
Or* newOr();

void initXor(Xor* xor);
void doXor(Xor* xor);
Xor* newXor();

#endif
