#include "systemc.h"
#include "DMA_TLM.h"

SC_MODULE(DMA) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<sc_uint<32> > addr;
    sc_in<sc_uint<32> > data;
    sc_in<sc_uint<1 > > control; //1->cpu write
    sc_out<sc_uint<32> > source_addr;
    sc_out<sc_uint<32> > target_addr;
    sc_signal<sc_uint<32> > source_addr_origin;
    sc_signal<sc_uint<32> > target_addr_origin;
    sc_signal<sc_uint<1> >  start;
    sc_signal<sc_uint<32> > size;
	sc_in<sc_uint<32> > read_data;
	sc_out<sc_uint<32> > write_data;

    sc_in<sc_uint<1> >  Clear;
    sc_out<sc_uint<1> >  Interrupt;

    sc_out<sc_uint<1> >  mem1_control;
    sc_out<sc_uint<1> >  mem2_control;

    sc_signal<sc_uint<2> >  state;
    int count;

	void DMA_do();

	// Constructor
	SC_CTOR(DMA) {
	    SC_CTHREAD(DMA_do,clk.pos());
        async_reset_signal_is(rst,true);
	}
};