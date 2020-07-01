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

Nand* newNand();
void initNand(Nand* nand);
void doNand(Nand* nand);

Not* newNot();
void initNot(Not* not);
void doNot(Not* not);

And* newAnd();
void initAnd(And* and);
void doAnd(And* and);

Or* newOr();
void initOr(Or* or);
void doOr(Or* or);

Xor* newXor();
void initXor(Xor* xor);
void doXor(Xor* xor);

#endif
