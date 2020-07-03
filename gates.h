#ifndef logic_gates_h
#define logic_gates_h

typedef char Bit;

typedef struct Nand {
	Bit in[2];
	Bit out;
} Nand;

Nand *newNand();
void initNand(Nand *nand);
void doNand(Nand *nand);

typedef struct Not {
	Bit in;
	Nand nand;
	Bit out;
} Not;

Not *newNot();
void initNot(Not * not);
void doNot(Not * not);

typedef struct And {
	Bit in[2];
	Nand nand;
	Not not;
	Bit out;
} And;

And *newAnd();
void initAnd(And *and);
void doAnd(And *and);

typedef struct Or {
	Bit in[2];
	Nand nand;
	Not not[2];
	Bit out;
} Or;

Or *newOr();
void initOr(Or *or );
void doOr(Or *or );

typedef struct Xor {
	Bit in[2];
	Nand nand[4];
	Bit out;
} Xor;

Xor *newXor();
void initXor(Xor *xor);
void doXor(Xor *xor);

#endif
