#include "gates.h"
#include "arithmetic.h"
#include "components.h"
#include "alu.h"

void Unary(UnaryComp* unary);

void initUnary(UnaryComp* unary) {
	int i;
	unary->zero = '0';
	unary->negate = '0';
	for (i = 0; i < 8; i++) {
		unary->data[i] = '0';
		initNot(&unary->not[i]);
	}
	for (i = 0; i < 2; i++) initMux8(&unary->mux8[i]);
	Unary(unary);
}

void Unary(UnaryComp* unary) {
	int i;
	unary->mux8[0].store = unary->zero;
	for (i = 0; i < 8; i++) {
		unary->mux8[0].data[0][i] = '0';
		unary->mux8[0].data[1][i] = unary->data[i];
	}
	Mux8(&unary->mux8[0]);
	unary->mux8[1].store = unary->negate;
	for (i = 0; i < 8; i++) {
		unary->not[i].in = unary->mux8[0].out[i];
		doNot(&unary->not[i]);
		unary->mux8[1].data[0][i] = unary->not[i].out;
		unary->mux8[1].data[1][i] = unary->mux8[0].out[i];
	}
	Mux8(&unary->mux8[1]);
	for (i = 0; i < 8; i++) unary->out[i] = unary->mux8[1].out[i];
}
