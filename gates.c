#include <stdlib.h>

#include "types.h"
#include "gates.h"

// Each logic gate and circuit is a struct, defined in a header file
// There's an initialization function for each gate/circuit that sets its inputs to zero and does the same to any subcomponents it might have
// The logic gates are all pretty self-explanatory

//
// Nand
//

Nand* newNand() {
	Nand* nand = (Nand*)malloc(sizeof(Nand));
	initNand(nand);
	return nand;
}

void initNand(Nand* nand) {
	for (int i = 0; i < 2; i++) nand->in[i] = BIT_0;
	doNand(nand);
}

void doNand(Nand* nand) {
	if ((nand->in[0] == BIT_1) && (nand->in[1] == BIT_1)) nand->out = BIT_0;
	else nand->out = BIT_1;
}

//
// Not
//

Not* newNot() {
	Not* not = (Not*)malloc(sizeof(Not));
	initNot(not);
	return not;
}

void initNot(Not* not) {
	not->in = BIT_0;
	initNand(&not->nand);
	doNot(not);
}

void doNot(Not* not) {
	not->nand.in[0] = not->in;
	not->nand.in[1] = not->in;
	doNand(&not->nand);
	not->out = not->nand.out;
}

//
// And
//

And* newAnd() {
	And* and = (And*)malloc(sizeof(And));
	initAnd(and);
	return and;
}

void initAnd(And* and) {
	for (int i = 0; i < 2; i++) and->in[i] = BIT_0;
	initNand(&and->nand);
	initNot(&and->not);
	doAnd(and);
}

void doAnd(And* and) {
	and->nand.in[0] = and->in[0];
	and->nand.in[1] = and->in[1];
	doNand(&and->nand);
	and->not.in = and->nand.out;
	doNot(&and->not);
	and->out = and->not.out;
}

//
// Or
//

Or* newOr() {
	Or* or = (Or*)malloc(sizeof(Or));
	initOr(or);
	return or;
}

void initOr(Or* or) {
	for (int i = 0; i < 2; i++) {
		or->in[i] = BIT_0;
		initNot(&or->not[i]);
	}
	initNand(&or->nand);
	doOr(or);
}

void doOr(Or* or) {
	or->not[0].in = or->in[0];
	or->not[1].in = or->in[1];
	doNot(&or->not[0]);
	doNot(&or->not[1]);
	or->nand.in[0] = or->not[0].out;
	or->nand.in[1] = or->not[1].out;
	doNand(&or->nand);
	or->out = or->nand.out;
}

//
// Xor
//

Xor* newXor() {
	Xor* xor = (Xor*)malloc(sizeof(Xor));
	initXor(xor);
	return xor;
}

void initXor(Xor* xor) {
	for (int i = 0; i < 2; i++) xor->in[i] = BIT_0;
	for (int i = 0; i < 4; i++) initNand(&xor->nand[i]);
	doXor(xor);
}

void doXor(Xor* xor) {
	xor->nand[0].in[0] = xor->in[0];
	xor->nand[0].in[1] = xor->in[1];
	doNand(&xor->nand[0]);
	xor->nand[1].in[0] = xor->in[0];
	xor->nand[1].in[1] = xor->nand[0].out;
	doNand(&xor->nand[1]);
	xor->nand[2].in[0] = xor->in[1];
	xor->nand[2].in[1] = xor->nand[0].out;
	doNand(&xor->nand[2]);
	xor->nand[3].in[0] = xor->nand[1].out;
	xor->nand[3].in[1] = xor->nand[2].out;
	doNand(&xor->nand[3]);
	xor->out = xor->nand[3].out;
}
