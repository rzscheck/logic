#include "gates.h"
#include "arithmetic.h"
#include "components.h"

//
// Mux
//

void initMux(MuxComp* mux) {
	int i;
	mux->store = '0';
	for (i = 0; i < 2; i++) mux->data[i] = '0';
	initNot(&mux->not);
	for (i = 0; i < 3; i++) initNand(&mux->nand[i]);
	Mux(mux);
}

void Mux(MuxComp* mux) {
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

//
// Mux8
//

void initMux8(Mux8Comp* mux8) {
	int i, j;
	mux8->store = '0';
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 8; j++) {
			mux8->data[i][j] = '0';
		}
	}
	for (i = 0; i < 8; i++) initMux(&mux8->mux[i]);
	Mux8(mux8);
}

void Mux8(Mux8Comp* mux8) {
	int i, j;
	for (i = 0; i < 8; i++) {
		mux8->mux[i].store = mux8->store;
		for (j = 0; j < 2; j++) mux8->mux[i].data[j] = mux8->data[j][i];
		Mux(&mux8->mux[i]);
		mux8->out[i] = mux8->mux[i].out;
	}
}

//
// DMux
//

void initDMux(DMuxComp* dmux) {
	int i;
	dmux->store = '0';
	dmux->data = '0';
	for (i = 0; i < 2; i++) initAnd(&dmux->and[i]);
	initNot(&dmux->not);
	DMux(dmux);
}

void DMux(DMuxComp* dmux) {
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

//
// Latch
//

void initLatch(LatchComp* latch) {
	latch->store = '0';
	latch->data = '0';
	initMux(&latch->mux);
	Latch(latch);
}

void Latch(LatchComp* latch) {
	latch->mux.store = latch->store;
	latch->mux.data[0] = latch->data;
	latch->mux.data[1] = latch->mux.out;
	Mux(&latch->mux);
	latch->out = latch->mux.out;
}

//
// DFF
//

void initDFF(DFFComp* dff) {
	int i;
	dff->store = '0';
	dff->data = '0';
	dff->clock = '0';
	for (i = 0; i < 2; i++) {
		initNand(&dff->nand[i]);
		initNot(&dff->not[i]);
		initLatch(&dff->latch[i]);
	}
	DFF(dff);
}

void DFF(DFFComp* dff) {
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
	Latch(&dff->latch[0]);
	dff->latch[1].store = dff->not[0].out;
	dff->latch[1].data = dff->latch[0].out;
	Latch(&dff->latch[1]);
	dff->out = dff->latch[1].out;
}

//
// Register
//

void initRegister(RegisterComp* reg) {
	int i;
	reg->store = '0';
	reg->clock = '0';
	for (i = 0; i < 8; i++) {
		reg->data[i] = '0';
		initDFF(&reg->dff[i]);
	}
	Register(reg);
}

void Register(RegisterComp* reg) {
	int i;
	for (i = 0; i < 8; i++) {
		reg->dff[i].store = reg->store;
		reg->dff[i].data = reg->data[i];
		reg->dff[i].clock = reg->clock;
		DFF(&reg->dff[i]);
		reg->out[i] = reg->dff[i].out;
	}
}

//
// Counter
//

void initCounter(CounterComp* counter) {
	int i;
	counter->store = '0';
	counter->clock = '0';
	for (i = 0; i < 8; i++) counter->data[i] = '0';
	initMux8(&counter->mux8);
	initNot(&counter->not);
	initIncrement(&counter->increment);
	initRegister(&counter->reg);
	counter->reg.store = counter->not.out;
	Counter(counter);
}

void Counter(CounterComp* counter) {
	int i;
	counter->mux8.store = counter->store;
	counter->reg.clock = counter->clock;

	for (i = 0; i < 8; i++) {
		counter->mux8.data[0][i] = counter->data[i];
		counter->increment.in[i] = counter->reg.out[i];
	}
	doIncrement(&counter->increment);
	
	for (i = 0; i < 8; i++) counter->mux8.data[1][i] = counter->increment.out[i];
	Mux8(&counter->mux8);
	for (i = 0; i < 8; i++) counter->reg.data[i] = counter->mux8.out[i];
	Register(&counter->reg);
	for (i = 0; i < 8; i++) counter->out[i] = counter->reg.out[i];
}
