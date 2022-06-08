#ifndef	__ASIC_H
#define __ASIC_H
#include "systemc.h"
#include <stdio.h>


SC_MODULE(FIR_asic)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      A;  	// P0: 8051 -> FIR, Prepared value which needs calculate. (port0o)
	sc_in<sc_uint<8> >      B;  	// P3: 8051 -> FIR, Tell FIR can catch value. (port3o)
	sc_out<sc_uint<8> >     C;  	// P2: FIR -> 8051, FIR calculate complete or not. (port2i)
	sc_out<sc_uint<8> >     D;  	// P1: FIR -> 8051, FIR send result value back. (port1i)
	sc_signal<bool> rst;

	void FIR_1(); // 1 cycle ： use multi adders and multi multipliers
	void FIR_N(); // N cycle ： use one adder and one multiplier


	SC_CTOR(FIR_asic)
	{
		rst = true;
		/* switch 1-cycle or N-cycle. */
		SC_CTHREAD(FIR_1, clk.pos());
		// SC_CTHREAD(FIR_N, clk.pos());
	};
	
};

#endif