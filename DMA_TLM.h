#ifndef DMA_TLM_H
#define DMA_TLM_H

#include<systemc.h>
#include "MEM1_TLM.h"
#include "MEM2_TLM.h"

#include<tlm.h>
#include<tlm_utils/simple_initiator_socket.h>

SC_MODULE(DMA_TLM_READ) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<sc_uint<32> >DMA_data;
    sc_in<sc_uint<32> > DMA_addr;
    void READ_do();

    sc_uint<32> r_addr;

    int data;
    tlm_utils::simple_initiator_socket<DMA_TLM_READ> socket_r;

	// Constructor
	SC_CTOR(DMA_TLM_READ) : socket_r("socket_r")
    {
	    SC_CTHREAD(READ_do,clk.pos());
        async_reset_signal_is(rst,true);
	}
};

SC_MODULE(DMA_TLM_WRITE) {
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<sc_uint<32> >DMA_data;
    sc_in<sc_uint<32> > DMA_addr;
    void WRITE_do();

    sc_uint<32> w_addr;

    int data;
    tlm_utils::simple_initiator_socket<DMA_TLM_WRITE> socket_w;

	// Constructor
	SC_CTOR(DMA_TLM_WRITE) : socket_w("socket_w")
    {
	    SC_CTHREAD(WRITE_do,clk.pos());
        async_reset_signal_is(rst,true);
	}
};

#endif
