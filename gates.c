#include "gates.h"

// Each logic gate and circuit is a struct, defined in a header file
// There's an initialization function for each gate/circuit that sets its inputs to zero and does the same to any subcomponents it might have
// The logic gates are all pretty self-explanatory

void Nand(NandGate* nand);

void initNand(NandGate* nand) {
	for (int i = 0; i < 2; i++) nand->in[i] = '0';
	Nand(nand);
}

void Nand(NandGate* nand) {
	if ((nand->in[0] == nand->in[1]) && (nand->in[0] == '1')) nand->out = '0';
	else nand->out = '1';
}

void Not(NotGate* not);

void initNot(NotGate* not) {
	not->in = '0';
	initNand(&not->nand);
	Not(not);
}

void Not(NotGate* not) {
	not->nand.in[0] = not->in;
	not->nand.in[1] = not->in;
	Nand(&not->nand);
	not->out = not->nand.out;
}

void And(AndGate* and);

void initAnd(AndGate* and) {
	for (int i = 0; i < 2; i++) and->in[i] = '0';
	initNand(&and->nand);
	initNot(&and->not);
	And(and);
}

void And(AndGate* and) {
	and->nand.in[0] = and->in[0];
	and->nand.in[1] = and->in[1];
	Nand(&and->nand);
	and->not.in = and->nand.out;
	Not(&and->not);
	and->out = and->not.out;
}

void Or(OrGate* or);

void initOr(OrGate* or) {
	for (int i = 0; i < 2; i++) {
		or->in[i] = '0';
		initNot(&or->not[i]);
	}
	initNand(&or->nand);
	Or(or);
}

void Or(OrGate* or) {
	or->not[0].in = or->in[0];
	or->not[1].in = or->in[1];
	Not(&or->not[0]);
	Not(&or->not[1]);
	or->nand.in[0] = or->not[0].out;
	or->nand.in[1] = or->not[1].out;
	Nand(&or->nand);
	or->out = or->nand.out;
}

void Xor(XorGate* xor);

void initXor(XorGate* xor) {
	for (int i = 0; i < 2; i++) xor->in[i] = '0';
	for (int i = 0; i < 4; i++) initNand(&xor->nand[i]);
	Xor(xor);
}

void Xor(XorGate* xor) {
	xor->nand[0].in[0] = xor->in[0];
	xor->nand[0].in[1] = xor->in[1];
	Nand(&xor->nand[0]);
	xor->nand[1].in[0] = xor->in[0];
	xor->nand[1].in[1] = xor->nand[0].out;
	Nand(&xor->nand[1]);
	xor->nand[2].in[0] = xor->in[1];
	xor->nand[2].in[1] = xor->nand[0].out;
	Nand(&xor->nand[2]);
	xor->nand[3].in[0] = xor->nand[1].out;
	xor->nand[3].in[1] = xor->nand[2].out;
	Nand(&xor->nand[3]);
	xor->out = xor->nand[3].out;
}
