#include <stdio.h>
#include <stdlib.h>

#include "gates.h"
#include "arithmetic.h"

//
// HalfAdd
//

void initHalfAdd(HalfAdd* halfAdd) {
	int i;
	for (i = 0; i < 2; i++) halfAdd->in[i] = '0';
	for (i = 0; i < 4; i++) initNand(&halfAdd->nand[i]);
	initNot(&halfAdd->not);
	doHalfAdd(halfAdd);
}

void doHalfAdd(HalfAdd* halfAdd) {
	halfAdd->nand[0].in[0] = halfAdd->in[0];
	halfAdd->nand[0].in[1] = halfAdd->in[1];
	doNand(&halfAdd->nand[0]);
	halfAdd->nand[1].in[0] = halfAdd->in[0];
	halfAdd->nand[1].in[1] = halfAdd->nand[0].out;
	doNand(&halfAdd->nand[1]);
	halfAdd->nand[2].in[0] = halfAdd->in[1];
	halfAdd->nand[2].in[1] = halfAdd->nand[0].out;
	doNand(&halfAdd->nand[2]);
	halfAdd->nand[3].in[0] = halfAdd->nand[1].out;
	halfAdd->nand[3].in[1] = halfAdd->nand[2].out;
	doNand(&halfAdd->nand[3]);
	halfAdd->not.in = halfAdd->nand[0].out;
	doNot(&halfAdd->not);
	halfAdd->out[0] = halfAdd->not.out;
	halfAdd->out[1] = halfAdd->nand[3].out;
}

HalfAdd* newHalfAdd() {
	HalfAdd* halfAdd = (HalfAdd*)malloc(sizeof(HalfAdd));
	initHalfAdd(halfAdd);
	return halfAdd;
}

//
// Full add
//

void initFullAdd(FullAdd* fullAdd) {
	int i;
	for (i = 0; i < 3; i++) fullAdd->in[i] = '0';
	for (i = 0; i < 8; i++) initNand(&fullAdd->nand[i]);
	doFullAdd(fullAdd);
}

void doFullAdd(FullAdd* fullAdd) {
	fullAdd->nand[0].in[0] = fullAdd->in[0];
	fullAdd->nand[0].in[1] = fullAdd->in[1];
	doNand(&fullAdd->nand[0]);
	fullAdd->nand[1].in[0] = fullAdd->in[0];
	fullAdd->nand[1].in[1] = fullAdd->nand[0].out;
	doNand(&fullAdd->nand[1]);
	fullAdd->nand[2].in[0] = fullAdd->in[1];
	fullAdd->nand[2].in[1] = fullAdd->nand[0].out;
	doNand(&fullAdd->nand[2]);
	fullAdd->nand[3].in[0] = fullAdd->nand[1].out;
	fullAdd->nand[3].in[1] = fullAdd->nand[2].out;
	doNand(&fullAdd->nand[3]);
	fullAdd->nand[4].in[0] = fullAdd->in[2];
	fullAdd->nand[4].in[1] = fullAdd->nand[3].out;
	doNand(&fullAdd->nand[4]);
	fullAdd->nand[5].in[0] = fullAdd->nand[3].out;
	fullAdd->nand[5].in[1] = fullAdd->nand[4].out;
	doNand(&fullAdd->nand[5]);
	fullAdd->nand[6].in[0] = fullAdd->in[2];
	fullAdd->nand[6].in[1] = fullAdd->nand[4].out;
	doNand(&fullAdd->nand[6]);
	fullAdd->nand[7].in[0] = fullAdd->nand[5].out;
	fullAdd->nand[7].in[1] = fullAdd->nand[6].out;
	doNand(&fullAdd->nand[7]);
	fullAdd->nand[8].in[0] = fullAdd->nand[0].out;
	fullAdd->nand[8].in[1] = fullAdd->nand[4].out;
	doNand(&fullAdd->nand[8]);
	fullAdd->out[0] = fullAdd->nand[8].out;
	fullAdd->out[1] = fullAdd->nand[7].out;
}

FullAdd* newFullAdd() {
	FullAdd* fullAdd = (FullAdd*)malloc(sizeof(FullAdd));
	initFullAdd(fullAdd);
	return fullAdd;
}

//
// Add
//

void initAdd(Add* add) {
	int i, j;
	add->carryIn = '0';
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			add->in[i][j] = '0';
		}
	}
	for (i = 0; i < 8; i++) initFullAdd(&add->fullAdd[i]);
	doAdd(add);
}

void doAdd(Add* add) {
	int i;
	add->fullAdd[0].in[2] = add->carryIn;
	for (i = 0; i < 8; i++) {
		add->fullAdd[i].in[0] = add->in[0][7-i];
		add->fullAdd[i].in[1] = add->in[1][7-i];
		doFullAdd(&add->fullAdd[i]);
		add->out[7-i] = add->fullAdd[i].out[1];
		if (i < 7) add->fullAdd[i + 1].in[2] = add->fullAdd[i].out[0];
	}
	add->carryOut = add->fullAdd[7].out[0];
}

Add* newAdd() {
	Add* add = (Add*)malloc(sizeof(Add));
	initAdd(add);
	return add;
}

//
// Increment
//

void initIncrement(Increment* increment) {
	int i;
	for (i = 0; i < 8; i++) increment->in[i] = '0';
	initAdd(&increment->add);
	initNot(&increment->not);
	doIncrement(increment);
}

void doIncrement(Increment* increment) {
	int i;
	for (i = 0; i < 8; i++) {
		increment->add.in[0][i] = increment->in[i];
		increment->add.in[1][i] = '0';
	}
	// increment->not.in = '0'; // Shouldn't need this if it's initialized
	doNot(&increment->not);
	increment->add.carryIn = increment->not.out;
	doAdd(&increment->add);
	for (i = 0; i < 8; i++) {
		increment->out[i] = increment->add.out[i];
	}
}

Increment* newIncrement() {
	Increment* increment = (Increment*)malloc(sizeof(Increment));
	initIncrement(increment);
	return increment;
}

//
// Subtract
//

void initSubtract(Subtract* subtract) {
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			subtract->in[i][j] = '0';
		}
	}
	for (i = 0; i < 9; i++) initNot(&subtract->not[i]);
	initAdd(&subtract->add);
	doSubtract(subtract);
}

void doSubtract(Subtract* subtract) {
	int i;
	for (i = 0; i < 8; i++) {
		subtract->not[i].in = subtract->in[1][i];
		doNot(&subtract->not[i]);
		subtract->add.in[0][i] = subtract->in[0][i];
		subtract->add.in[1][i] = subtract->not[i].out;
	}
	// subtract->not[8].in = '0'; // not needed if initialized
	doNot(&subtract->not[8]);
	subtract->add.carryIn = subtract->not[8].out;
	doAdd(&subtract->add);
	for (i = 0; i < 8; i++) {
		subtract->out[i] = subtract->add.out[i];
	}
}

Subtract* newSubtract() {
	Subtract* subtract = (Subtract*)malloc(sizeof(Subtract));
	initSubtract(subtract);
	return subtract;
}

//
// EqualsZero
//

void initEqualsZero(EqualsZero* equalsZero) {
	int i;
	for (i = 0; i < 8; i++) equalsZero->in[i] = '0';
	for (i = 0; i < 7; i++) initOr(&equalsZero->or[i]);
	initNot(&equalsZero->not);
	doEqualsZero(equalsZero);
}

void doEqualsZero(EqualsZero* equalsZero) {
	equalsZero->or[0].in[0] = equalsZero->in[0];
	equalsZero->or[0].in[1] = equalsZero->in[1];
	doOr(&equalsZero->or[0]);
	equalsZero->or[1].in[0] = equalsZero->in[2];
	equalsZero->or[1].in[1] = equalsZero->or[0].out;
	doOr(&equalsZero->or[1]);
	equalsZero->or[2].in[0] = equalsZero->in[3];
	equalsZero->or[2].in[1] = equalsZero->or[1].out;
	doOr(&equalsZero->or[2]);
	equalsZero->or[3].in[0] = equalsZero->in[4];
	equalsZero->or[3].in[1] = equalsZero->or[2].out;
	doOr(&equalsZero->or[3]);
	equalsZero->or[4].in[0] = equalsZero->in[5];
	equalsZero->or[4].in[1] = equalsZero->or[3].out;
	doOr(&equalsZero->or[4]);
	equalsZero->or[5].in[0] = equalsZero->in[6];
	equalsZero->or[5].in[1] = equalsZero->or[4].out;
	doOr(&equalsZero->or[5]);
	equalsZero->or[6].in[0] = equalsZero->in[7];
	equalsZero->or[6].in[1] = equalsZero->or[5].out;
	doOr(&equalsZero->or[6]);
	equalsZero->not.in = equalsZero->or[6].out;
	doNot(&equalsZero->not);
	equalsZero->out = equalsZero->not.out;
}

EqualsZero* newEqualsZero() {
	EqualsZero* equalsZero = (EqualsZero*)malloc(sizeof(EqualsZero));
	initEqualsZero(equalsZero);
	return equalsZero;
}

//
// LessThanZero
//

void initLessThanZero(LessThanZero* lessThanZero) {
	int i;
	for (i = 0; i < 8; i++) lessThanZero->in[i] = '0';
	doLessThanZero(lessThanZero);
}

void doLessThanZero(LessThanZero* lessThanZero) {
	lessThanZero->out = lessThanZero->in[0];
}

LessThanZero* newLessThanZero() {
	LessThanZero* lessThanZero = (LessThanZero*)malloc(sizeof(LessThanZero));
	initLessThanZero(lessThanZero);
	return lessThanZero;
}
