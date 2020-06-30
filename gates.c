#include "gates.h"

#include <stdlib.h>

// Each logic gate and circuit is a struct, defined in a header file
// There's an initialization function for each gate/circuit that sets its inputs to zero and does the same to any subcomponents it might have
// The logic gates are all pretty self-explanatory

void initNand(Nand* nand) {
	for (int i = 0; i < 2; i++) nand->in[i] = '0';
	doNand(nand);
}

void doNand(Nand* nand) {
	if ((nand->in[0] == '1') && (nand->in[1] == '1')) nand->out = '0';
	else nand->out = '1';
}

Nand* newNand() {
	Nand* nand = (Nand*)malloc(sizeof(Nand));
	initNand(nand);
	return nand;
}

void initNot(Not* not) {
	not->in = '0';
	initNand(&not->nand);
	doNot(not);
}

void doNot(Not* not) {
	not->nand.in[0] = not->in;
	not->nand.in[1] = not->in;
	doNand(&not->nand);
	not->out = not->nand.out;
}

Not* newNot() {
	Not* not = (Not*)malloc(sizeof(Not));
	initNot(not);
	return not;
}

void initAnd(And* and) {
	for (int i = 0; i < 2; i++) and->in[i] = '0';
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

And* newAnd() {
	And* and = (And*)malloc(sizeof(And));
	initAnd(and);
	return and;
}

void initOr(Or* or) {
	for (int i = 0; i < 2; i++) {
		or->in[i] = '0';
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

Or* newOr() {
	Or* or = (Or*)malloc(sizeof(Or));
	initOr(or);
	return or;
}

void initXor(Xor* xor) {
	for (int i = 0; i < 2; i++) xor->in[i] = '0';
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

Xor* newXor() {
	Xor* xor = (Xor*)malloc(sizeof(Xor));
	initXor(xor);
	return xor;
}