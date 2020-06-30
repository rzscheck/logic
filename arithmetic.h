#ifndef logic_arithmetic_h
#define logic_arithmetic_h

typedef struct HalfAdd {
	Bit in[2];
	Nand nand[4];
	Not not;
	Bit out[2];
} HalfAdd;

typedef struct FullAdd {
	Bit in[3];
	Nand nand[8];
	Bit out[2];
} FullAdd;

typedef struct AddComp {
	Bit in[2][8];
	Bit carryIn;
	FullAdd fullAdd[8];
	Bit out[8];
	Bit carryOut;
} AddComp;

typedef struct IncrementComp {
	Bit in[8];
	AddComp add;
	Not not;
	Bit out[8];
} IncrementComp;

typedef struct SubtractComp {
	Bit in[2][8];
	Not not[9];
	AddComp add;
	Bit out[8];
} SubtractComp;

typedef struct EqualsZeroComp {
	Bit in[8];
	Or or[7];
	Not not;
	Bit out;
} EqualsZeroComp;

typedef struct LessThanZeroComp {
	Bit in[8];
	Bit out;
} LessThanZeroComp;

void initHalfAdd(HalfAdd* halfAdd);
void doHalfAdd(HalfAdd* halfAdd);
HalfAdd* newHalfAdd();

void initFullAdd(FullAdd* fullAdd);
void doFullAdd(FullAdd* fullAdd);
FullAdd* newFullAdd();

void initAdd(AddComp* add);
void Add(AddComp* add);

void initIncrement(IncrementComp* increment);
void Increment(IncrementComp* increment);

void initSubtract(SubtractComp* subtract);
void Subtract(SubtractComp* subtract);

void initEqualsZero(EqualsZeroComp* equalsZero);
void EqualsZero(EqualsZeroComp* equalsZero);

void initLessThanZero(LessThanZeroComp* lessThanZero);
void LessThanZero(LessThanZeroComp* lessThanZero);

#endif
