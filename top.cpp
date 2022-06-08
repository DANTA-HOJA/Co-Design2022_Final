#include "top.h"

void top::entry()
{
    if (reset.read()) {
	// port0i.write(0xFF);
	// port1i.write(0xFF);
	// port2i.write(0xFF);
	// port3i.write(0xFF);
    }
}

void top::mux_xram()
{
    unsigned short a = xram_addr.read();
	bool         a03 = true;
	xrambig_re       = a03 && xram_re.read();
	xrambig_we       = a03 && xram_we.read();
    xram_rd_data     = (a03) ? xrambig_rd_data.read() : sc_dt::sc_uint<8> (0x00);
    bool rdy         = (a03) ? xrambig_ready.read() : sc_dt::sc_uint<1> (true);
    xram_ready       = rdy;
    xram_addr8       = xram_addr.read() & 0xFF;
}
