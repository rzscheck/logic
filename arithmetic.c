#include <stdio.h>

#include "gates.h"
#include "arithmetic.h"

void HalfAdd(HalfAddComp* halfAdd);

void initHalfAdd(HalfAddComp* halfAdd) {
	int i;
	for (i = 0; i < 2; i++) halfAdd->in[i] = '0';
	for (i = 0; i < 4; i++) initNand(&halfAdd->nand[i]);
	initNot(&halfAdd->not);
	HalfAdd(halfAdd);
}

void HalfAdd(HalfAddComp* halfAdd) {
	halfAdd->nand[0].in[0] = halfAdd->in[0];
	halfAdd->nand[0].in[1] = halfAdd->in[1];
	Nand(&halfAdd->nand[0]);
	halfAdd->nand[1].in[0] = halfAdd->in[0];
	halfAdd->nand[1].in[1] = halfAdd->nand[0].out;
	Nand(&halfAdd->nand[1]);
	halfAdd->nand[2].in[0] = halfAdd->in[1];
	halfAdd->nand[2].in[1] = halfAdd->nand[0].out;
	Nand(&halfAdd->nand[2]);
	halfAdd->nand[3].in[0] = halfAdd->nand[1].out;
	halfAdd->nand[3].in[1] = halfAdd->nand[2].out;
	Nand(&halfAdd->nand[3]);
	halfAdd->not.in = halfAdd->nand[0].out;
	Not(&halfAdd->not);
	halfAdd->out[0] = halfAdd->not.out;
	halfAdd->out[1] = halfAdd->nand[3].out;
}

void FullAdd(FullAddComp* fullAdd);

void initFullAdd(FullAddComp* fullAdd) {
	int i;
	for (i = 0; i < 3; i++) fullAdd->in[i] = '0';
	for (i = 0; i < 8; i++) initNand(&fullAdd->nand[i]);
	FullAdd(fullAdd);
}

void FullAdd(FullAddComp* fullAdd) {
	fullAdd->nand[0].in[0] = fullAdd->in[0];
	fullAdd->nand[0].in[1] = fullAdd->in[1];
	Nand(&fullAdd->nand[0]);
	fullAdd->nand[1].in[0] = fullAdd->in[0];
	fullAdd->nand[1].in[1] = fullAdd->nand[0].out;
	Nand(&fullAdd->nand[1]);
	fullAdd->nand[2].in[0] = fullAdd->in[1];
	fullAdd->nand[2].in[1] = fullAdd->nand[0].out;
	Nand(&fullAdd->nand[2]);
	fullAdd->nand[3].in[0] = fullAdd->nand[1].out;
	fullAdd->nand[3].in[1] = fullAdd->nand[2].out;
	Nand(&fullAdd->nand[3]);
	fullAdd->nand[4].in[0] = fullAdd->in[2];
	fullAdd->nand[4].in[1] = fullAdd->nand[3].out;
	Nand(&fullAdd->nand[4]);
	fullAdd->nand[5].in[0] = fullAdd->nand[3].out;
	fullAdd->nand[5].in[1] = fullAdd->nand[4].out;
	Nand(&fullAdd->nand[5]);
	fullAdd->nand[6].in[0] = fullAdd->in[2];
	fullAdd->nand[6].in[1] = fullAdd->nand[4].out;
	Nand(&fullAdd->nand[6]);
	fullAdd->nand[7].in[0] = fullAdd->nand[5].out;
	fullAdd->nand[7].in[1] = fullAdd->nand[6].out;
	Nand(&fullAdd->nand[7]);
	fullAdd->nand[8].in[0] = fullAdd->nand[0].out;
	fullAdd->nand[8].in[1] = fullAdd->nand[4].out;
	Nand(&fullAdd->nand[8]);
	fullAdd->out[0] = fullAdd->nand[8].out;
	fullAdd->out[1] = fullAdd->nand[7].out;
}

void Add(AddComp* add);

void initAdd(AddComp* add) {
	int i, j;
	add->carryIn = '0';
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			add->in[i][j] = '0';
		}
	}
	for (i = 0; i < 8; i++) initFullAdd(&add->fullAdd[i]);
	Add(add);
}

void Add(AddComp* add) {
	int i;
	add->fullAdd[0].in[2] = add->carryIn;
	for (i = 0; i < 8; i++) {
		add->fullAdd[i].in[0] = add->in[0][7-i];
		add->fullAdd[i].in[1] = add->in[1][7-i];
		FullAdd(&add->fullAdd[i]);
		add->out[7-i] = add->fullAdd[i].out[1];
		if (i < 7) add->fullAdd[i + 1].in[2] = add->fullAdd[i].out[0];
	}
	add->carryOut = add->fullAdd[7].out[0];
}

void Increment(IncrementComp* increment);

void initIncrement(IncrementComp* increment) {
	int i;
	for (i = 0; i < 8; i++) increment->in[i] = '0';
	initAdd(&increment->add);
	initNot(&increment->not);
	Increment(increment);
}

void Increment(IncrementComp* increment) {
	int i;
	for (i = 0; i < 8; i++) {
		increment->add.in[0][i] = increment->in[i];
		increment->add.in[1][i] = '0';
	}
	//~ increment->not.in = '0'; // Shouldn't need this if it's initialized
	Not(&increment->not);
	increment->add.carryIn = increment->not.out;
	Add(&increment->add);
	for (i = 0; i < 8; i++) {
		increment->out[i] = increment->add.out[i];
	}
}

void Subtract(SubtractComp* subtract);

void initSubtract(SubtractComp* subtract) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			subtract->in[i][j] = '0';
		}
	}
	for (i = 0; i < 9; i++) initNot(&subtract->not[i]);
	initAdd(&subtract->add);
	Subtract(subtract);
}

void Subtract(SubtractComp* subtract) {
	int i;
	for (i = 0; i < 8; i++) {
		subtract->not[i].in = subtract->in[1][i];
		Not(&subtract->not[i]);
		subtract->add.in[0][i] = subtract->in[0][i];
		subtract->add.in[1][i] = subtract->not[i].out;
	}
	//~ subtract->not[8].in = '0'; // not needed if initialized
	Not(&subtract->not[8]);
	subtract->add.carryIn = subtract->not[8].out;
	Add(&subtract->add);
	for (i = 0; i < 8; i++) {
		subtract->out[i] = subtract->add.out[i];
	}
}

void EqualsZero(EqualsZeroComp* equalsZero);

void initEqualsZero(EqualsZeroComp* equalsZero) {
	int i;
	for (i = 0; i < 8; i++) equalsZero->in[i] = '0';
	for (i = 0; i < 7; i++) initOr(&equalsZero->or[i]);
	initNot(&equalsZero->not);
	EqualsZero(equalsZero);
}

void EqualsZero(EqualsZeroComp* equalsZero) {
	equalsZero->or[0].in[0] = equalsZero->in[0];
	equalsZero->or[0].in[1] = equalsZero->in[1];
	Or(&equalsZero->or[0]);
	equalsZero->or[1].in[0] = equalsZero->in[2];
	equalsZero->or[1].in[1] = equalsZero->or[0].out;
	Or(&equalsZero->or[1]);
	equalsZero->or[2].in[0] = equalsZero->in[3];
	equalsZero->or[2].in[1] = equalsZero->or[1].out;
	Or(&equalsZero->or[2]);
	equalsZero->or[3].in[0] = equalsZero->in[4];
	equalsZero->or[3].in[1] = equalsZero->or[2].out;
	Or(&equalsZero->or[3]);
	equalsZero->or[4].in[0] = equalsZero->in[5];
	equalsZero->or[4].in[1] = equalsZero->or[3].out;
	Or(&equalsZero->or[4]);
	equalsZero->or[5].in[0] = equalsZero->in[6];
	equalsZero->or[5].in[1] = equalsZero->or[4].out;
	Or(&equalsZero->or[5]);
	equalsZero->or[6].in[0] = equalsZero->in[7];
	equalsZero->or[6].in[1] = equalsZero->or[5].out;
	Or(&equalsZero->or[6]);
	equalsZero->not.in = equalsZero->or[6].out;
	Not(&equalsZero->not);
	equalsZero->out = equalsZero->not.out;
}

void LessThanZero(LessThanZeroComp* lessThanZero);

void initLessThanZero(LessThanZeroComp* lessThanZero) {
	int i;
	for (i = 0; i < 8; i++) lessThanZero->in[i] = '0';
	LessThanZero(lessThanZero);
}

void LessThanZero(LessThanZeroComp* lessThanZero) {
	lessThanZero->out = lessThanZero->in[0];
}
