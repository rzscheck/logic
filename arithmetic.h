#ifndef logic_arithmetic_h
#define logic_arithmetic_h

typedef struct HalfAddComp {
	Bit in[2];
	NandGate nand[4];
	NotGate not;
	Bit out[2];
} HalfAddComp;

typedef struct FullAddComp {
	Bit in[3];
	NandGate nand[8];
	Bit out[2];
} FullAddComp;

typedef struct AddComp {
	Bit in[2][8];
	Bit carryIn;
	FullAddComp fullAdd[8];
	Bit out[8];
	Bit carryOut;
} AddComp;

typedef struct IncrementComp {
	Bit in[8];
	AddComp add;
	NotGate not;
	Bit out[8];
} IncrementComp;

typedef struct SubtractComp {
	Bit in[2][8];
	NotGate not[9];
	AddComp add;
	Bit out[8];
} SubtractComp;

typedef struct EqualsZeroComp {
	Bit in[8];
	OrGate or[7];
	NotGate not;
	Bit out;
} EqualsZeroComp;

typedef struct LessThanZeroComp {
	Bit in[8];
	Bit out;
} LessThanZeroComp;

void initHalfAdd(HalfAddComp* halfAdd);
void HalfAdd(HalfAddComp* halfAdd);

void initFullAdd(FullAddComp* fullAdd);
void FullAdd(FullAddComp* fullAdd);

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
