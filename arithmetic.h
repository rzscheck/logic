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

typedef struct Add {
	Bit in[2][8];
	Bit carryIn;
	FullAdd fullAdd[8];
	Bit out[8];
	Bit carryOut;
} Add;

typedef struct Increment {
	Bit in[8];
	Add add;
	Not not;
	Bit out[8];
} Increment;

typedef struct Subtract {
	Bit in[2][8];
	Not not[9];
	Add add;
	Bit out[8];
} Subtract;

typedef struct EqualsZero {
	Bit in[8];
	Or or[7];
	Not not;
	Bit out;
} EqualsZero;

typedef struct LessThanZero {
	Bit in[8];
	Bit out;
} LessThanZero;

void initHalfAdd(HalfAdd* halfAdd);
void doHalfAdd(HalfAdd* halfAdd);
HalfAdd* newHalfAdd();

void initFullAdd(FullAdd* fullAdd);
void doFullAdd(FullAdd* fullAdd);
FullAdd* newFullAdd();

void initAdd(Add* add);
void doAdd(Add* add);
Add* newAdd();

void initIncrement(Increment* increment);
void doIncrement(Increment* increment);
Increment* newIncrement();

void initSubtract(Subtract* subtract);
void doSubtract(Subtract* subtract);
Subtract* newSubtract();

void initEqualsZero(EqualsZero* equalsZero);
void doEqualsZero(EqualsZero* equalsZero);
EqualsZero* newEqualsZero();

void initLessThanZero(LessThanZero* lessThanZero);
void doLessThanZero(LessThanZero* lessThanZero);
LessThanZero* newLessThanZero();

#endif
