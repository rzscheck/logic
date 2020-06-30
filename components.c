#include <stdlib.h>

#include "gates.h"
#include "arithmetic.h"
#include "components.h"

//
// Mux
//

void initMux(Mux* mux) {
	int i;
	mux->store = '0';
	for (i = 0; i < 2; i++) mux->data[i] = '0';
	initNot(&mux->not);
	for (i = 0; i < 3; i++) initNand(&mux->nand[i]);
	doMux(mux);
}

void doMux(Mux* mux) {
	mux->nand[0].in[0] = mux->store;
	mux->nand[0].in[1] = mux->data[0];
	doNand(&mux->nand[0]);
	mux->not.in = mux->store;
	doNot(&mux->not);
	mux->nand[1].in[0] = mux->not.out;
	mux->nand[1].in[1] = mux->data[1];
	doNand(&mux->nand[1]);
	mux->nand[2].in[0] = mux->nand[0].out;
	mux->nand[2].in[1] = mux->nand[1].out;
	doNand(&mux->nand[2]);
	mux->out = mux->nand[2].out;
}

Mux* newMux() {
	Mux* mux = (Mux*)malloc(sizeof(Mux));
	initMux(mux);
	return mux;
}

//
// Mux8
//

void initMux8(Mux8* mux8) {
	int i, j;
	mux8->store = '0';
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			mux8->data[i][j] = '0';
		}
	}
	for (i = 0; i < 8; i++) initMux(&mux8->mux[i]);
	doMux8(mux8);
}

void doMux8(Mux8* mux8) {
	int i, j;
	for (i = 0; i < 8; i++) {
		mux8->mux[i].store = mux8->store;
		for (j = 0; j < 2; j++) mux8->mux[i].data[j] = mux8->data[j][i];
		doMux(&mux8->mux[i]);
		mux8->out[i] = mux8->mux[i].out;
	}
}

Mux8* newMux8() {
	Mux8* mux8 = (Mux8*)malloc(sizeof(Mux8));
	initMux8(mux8);
	return mux8;
}

//
// DMux
//

void initDMux(DMux* dmux) {
	int i;
	dmux->store = '0';
	dmux->data = '0';
	for (i = 0; i < 2; i++) initAnd(&dmux->and[i]);
	initNot(&dmux->not);
	doDMux(dmux);
}

void doDMux(DMux* dmux) {
	dmux->and[0].in[0] = dmux->store;
	dmux->and[0].in[1] = dmux->data;
	doAnd(&dmux->and[0]);
	dmux->not.in = dmux->store;
	doNot(&dmux->not);
	dmux->and[1].in[0] = dmux->not.out;
	dmux->and[1].in[1] = dmux->data;
	doAnd(&dmux->and[1]);
	dmux->out[0] = dmux->and[0].out;
	dmux->out[1] = dmux->and[1].out;
}

DMux* newDMux() {
	DMux* dmux = (DMux*)malloc(sizeof(DMux));
	initDMux(dmux);
	return dmux;
}

//
// Latch
//

void initLatch(Latch* latch) {
	latch->store = '0';
	latch->data = '0';
	initMux(&latch->mux);
	doLatch(latch);
}

void doLatch(Latch* latch) {
	latch->mux.store = latch->store;
	latch->mux.data[0] = latch->data;
	latch->mux.data[1] = latch->mux.out;
	doMux(&latch->mux);
	latch->out = latch->mux.out;
}

Latch* newLatch() {
	Latch* latch = (Latch*)malloc(sizeof(Latch));
	initLatch(latch);
	return latch;
}

//
// DFF
//

void initDFF(DFF* dff) {
	int i;
	dff->store = '0';
	dff->data = '0';
	dff->clock = '0';
	for (i = 0; i < 2; i++) {
		initNand(&dff->nand[i]);
		initNot(&dff->not[i]);
		initLatch(&dff->latch[i]);
	}
	doDFF(dff);
}

void doDFF(DFF* dff) {
	dff->nand[0].in[0] = dff->store;
	dff->nand[0].in[1] = dff->clock;
	doNand(&dff->nand[0]);
	dff->nand[1].in[0] = dff->store;
	dff->nand[1].in[1] = dff->nand[0].out;
	doNand(&dff->nand[1]);
	dff->not[0].in = dff->nand[0].out;
	doNot(&dff->not[0]);
	dff->not[1].in = dff->nand[1].out;
	doNot(&dff->not[1]);
	dff->latch[0].store = dff->not[1].out;
	dff->latch[0].data = dff->data;
	doLatch(&dff->latch[0]);
	dff->latch[1].store = dff->not[0].out;
	dff->latch[1].data = dff->latch[0].out;
	doLatch(&dff->latch[1]);
	dff->out = dff->latch[1].out;
}

DFF* newDFF() {
	DFF* dff = (DFF*)malloc(sizeof(DFF));
	initDFF(dff);
	return dff;
}

//
// Register
//

void initRegister(Register* reg) {
	int i;
	reg->store = '0';
	reg->clock = '0';
	for (i = 0; i < 8; i++) {
		reg->data[i] = '0';
		initDFF(&reg->dff[i]);
	}
	doRegister(reg);
}

void doRegister(Register* reg) {
	int i;
	for (i = 0; i < 8; i++) {
		reg->dff[i].store = reg->store;
		reg->dff[i].data = reg->data[i];
		reg->dff[i].clock = reg->clock;
		doDFF(&reg->dff[i]);
		reg->out[i] = reg->dff[i].out;
	}
}

Register* newRegister() {
	Register* reg = (Register*)malloc(sizeof(Register));
	initRegister(reg);
	return reg;
}

//
// Counter
//

void initCounter(Counter* counter) {
	int i;
	counter->store = '0';
	counter->clock = '0';
	for (i = 0; i < 8; i++) counter->data[i] = '0';
	initMux8(&counter->mux8);
	initNot(&counter->not);
	initIncrement(&counter->increment);
	initRegister(&counter->reg);
	counter->reg.store = counter->not.out;
	doCounter(counter);
}

void doCounter(Counter* counter) {
	int i;
	counter->mux8.store = counter->store;
	counter->reg.clock = counter->clock;

	for (i = 0; i < 8; i++) {
		counter->mux8.data[0][i] = counter->data[i];
		counter->increment.in[i] = counter->reg.out[i];
	}
	doIncrement(&counter->increment);
	
	for (i = 0; i < 8; i++) counter->mux8.data[1][i] = counter->increment.out[i];
	doMux8(&counter->mux8);
	for (i = 0; i < 8; i++) counter->reg.data[i] = counter->mux8.out[i];
	doRegister(&counter->reg);
	for (i = 0; i < 8; i++) counter->out[i] = counter->reg.out[i];
}

Counter* newCounter() {
	Counter* counter = (Counter*)malloc(sizeof(Counter));
	initCounter(counter);
	return counter;
}
