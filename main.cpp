#include "DMA.h"

int sc_main(int argc, char* argv[]){

    
    sc_time clkprd(20, SC_NS);
    sc_clock clk("clk",clkprd);
    sc_signal<bool> rst;
    sc_signal<sc_uint<32> > addr;
    sc_signal<sc_uint<32> > data;
    sc_signal<sc_uint<1> > control;
    sc_signal<sc_uint<1> > Interrupt;
    sc_signal<sc_uint<1> > Clear;
    sc_signal<sc_uint<32> > source_addr;
    sc_signal<sc_uint<32> > target_addr;
    sc_signal<sc_uint<32> > read_data;
    sc_signal<sc_uint<32> > write_data;
    sc_signal<sc_uint<1> >  mem1_control;
    sc_signal<sc_uint<1> >  mem2_control;

    DMA uDMA("DMA");
    Memory1 *MEM1;
    Memory2 *MEM2;
    //Memory2 MEM2("mem2");
    DMA_TLM_READ  *uDMA_R;
    DMA_TLM_WRITE  *uDMA_W;

    MEM1 = new Memory1("mem1");
    MEM2 = new Memory2("mem2");
    uDMA_R = new DMA_TLM_READ("DMA_TLM_READ");
    uDMA_W = new DMA_TLM_WRITE("DMA_TLM_WRITE");


    uDMA_R->socket_r.bind(MEM1->socket_m1);
    uDMA_W->socket_w.bind(MEM2->socket_m2);

    uDMA.data(data);
    uDMA.addr(addr);
    uDMA.control(control);
    uDMA.clk(clk);
    uDMA.rst(rst);
    uDMA.Interrupt(Interrupt);
    uDMA.Clear(Clear);
    uDMA.mem2_control(mem2_control);
    uDMA.mem1_control(mem1_control);
    uDMA.source_addr(source_addr);
    uDMA.target_addr(target_addr);
    uDMA.read_data(read_data);
    uDMA.write_data(write_data);

    uDMA_R->clk(clk);
    uDMA_R->rst(rst);
    uDMA_R->DMA_data(read_data);
    uDMA_R->DMA_addr(source_addr);

    uDMA_W->clk(clk);
    uDMA_W->rst(rst);
    uDMA_W->DMA_data(write_data);
    uDMA_W->DMA_addr(target_addr);
    

    sc_trace_file *tf = sc_create_vcd_trace_file("RESULT");
    sc_trace(tf, clk, "clk");
	sc_trace(tf, rst, "rst");
	sc_trace(tf, addr, "addr");
	sc_trace(tf, data, "data");
	sc_trace(tf, control, "control");

    sc_trace(tf, uDMA.addr, "uDMA.addr");
    sc_trace(tf, uDMA.data, "uDMA.data");
    sc_trace(tf, uDMA.source_addr, "uDMA.source_addr");
    sc_trace(tf, uDMA.target_addr, "uDMA.target_addr");
    sc_trace(tf, uDMA.size, "uDMA.size");
    sc_trace(tf, uDMA.start, "uDMA.start");
    sc_trace(tf, uDMA.read_data, "uDMA.read_data");
    sc_trace(tf, uDMA.write_data, "uDMA.write_data");
    sc_trace(tf, uDMA.Clear, "uDMA.Clear");
    sc_trace(tf, uDMA.Interrupt, "uDMA.Interrupt");
    sc_trace(tf, uDMA.mem1_control, "uDMA.mem1_control");
    sc_trace(tf, uDMA.mem2_control, "uDMA.mem2_control");
    sc_trace(tf, uDMA.state, "uDMA.state");
    sc_trace(tf, uDMA.source_addr_origin, "uDMA.source_addr_origin");
    sc_trace(tf, uDMA.target_addr_origin, "uDMA.target_addr_origin");

    sc_trace(tf, uDMA_R->clk, "uDMA_R->clk");
    sc_trace(tf, uDMA_R->rst, "uDMA_R->rst");
    sc_trace(tf, uDMA_R->DMA_data, "uDMA_R->DMA_data");
    sc_trace(tf, uDMA_R->DMA_addr, "uDMA_R->DMA_addr");

    sc_trace(tf, uDMA_W->clk, "uDMA_W->clk");
    sc_trace(tf, uDMA_W->rst, "uDMA_W->rst");
    sc_trace(tf, uDMA_W->DMA_data, "uDMA_W->DMA_data");
    sc_trace(tf, uDMA_W->DMA_addr, "uDMA_W->DMA_addr");



    sc_trace(tf, MEM1->mem[0], "MEM1.mem0");
    sc_trace(tf, MEM1->mem[1], "MEM1.mem1");
    sc_trace(tf, MEM1->mem[2], "MEM1.mem2");
    sc_trace(tf, MEM1->mem[3], "MEM1.mem3");
    sc_trace(tf, MEM1->mem[4], "MEM1.mem4");
    sc_trace(tf, MEM1->mem[5], "MEM1.mem5");
    sc_trace(tf, MEM1->mem[6], "MEM1.mem6");

    sc_trace(tf, MEM2->mem[0], "MEM2.mem0");
    sc_trace(tf, MEM2->mem[1], "MEM2.mem1");
    sc_trace(tf, MEM2->mem[2], "MEM2.mem2");
    sc_trace(tf, MEM2->mem[3], "MEM2.mem3");
    sc_trace(tf, MEM2->mem[4], "MEM2.mem4");
    sc_trace(tf, MEM2->mem[5], "MEM2.mem5");
    sc_trace(tf, MEM2->mem[6], "MEM2.mem6");

    rst.write(true);
    sc_start(15,SC_NS);
    rst.write(false);

    control.write(1);
    addr.write(0x0);
    data.write(0);
    sc_start(20,SC_NS);
    addr.write(0x4);
    data.write(0);
    sc_start(20,SC_NS);
    addr.write(0x8);
    data.write(10);
    sc_start(20,SC_NS);
    addr.write(0xC);
    data.write(1);
    sc_start(20,SC_NS);
    control.write(0);

    sc_start(260,SC_NS);
    Clear.write(1);
    sc_start(20,SC_NS);

    sc_close_vcd_trace_file(tf);

    

    /*
    

    sc_trace(tf, uDMA.addr, "uDMA.addr");
    sc_trace(tf, uDMA.data, "uDMA.data");
    sc_trace(tf, uDMA.source_addr, "uDMA.source_addr");
    sc_trace(tf, uDMA.target_addr, "uDMA.target_addr");
    sc_trace(tf, uDMA.size, "uDMA.size");
    sc_trace(tf, uDMA.start, "uDMA.start");
    sc_trace(tf, uDMA.read_data, "uDMA.read_data");
    sc_trace(tf, uDMA.write_data, "uDMA.write_data");
    sc_trace(tf, uDMA.Clear, "uDMA.Clear");
    sc_trace(tf, uDMA.Interrupt, "uDMA.Interrupt");
    sc_trace(tf, uDMA.mem1_control, "uDMA.mem1_control");
    sc_trace(tf, uDMA.mem2_control, "uDMA.mem2_control");
    sc_trace(tf, uDMA.state, "uDMA.state");

    sc_trace(tf, uDMA.source_addr_origin, "uDMA.source_addr_origin");
    sc_trace(tf, uDMA.target_addr_origin, "uDMA.target_addr_origin");

    sc_trace(tf, MEM1.mem[0], "MEM1.mem0");
    sc_trace(tf, MEM1.mem[1], "MEM1.mem1");
    sc_trace(tf, MEM1.mem[2], "MEM1.mem2");
    sc_trace(tf, MEM1.mem[3], "MEM1.mem3");
    sc_trace(tf, MEM1.mem[4], "MEM1.mem4");
    sc_trace(tf, MEM1.mem[5], "MEM1.mem5");
    sc_trace(tf, MEM1.mem[6], "MEM1.mem6");
    sc_trace(tf, MEM1.mem[7], "MEM1.mem7");
    sc_trace(tf, MEM1.mem[8], "MEM1.mem8");
    sc_trace(tf, MEM1.mem[9], "MEM1.mem9");
    sc_trace(tf, MEM1.mem[10], "MEM1.mem10");
    sc_trace(tf, MEM1.addr, "MEM1.addr");
    sc_trace(tf, MEM1.control, "MEM1.control");
    sc_trace(tf, MEM1.indata, "MEM1.indata");
    sc_trace(tf, MEM1.outdata, "MEM1.outdata");

    sc_trace(tf, MEM2.mem[0], "MEM2.mem0");
    sc_trace(tf, MEM2.mem[1], "MEM2.mem1");
    sc_trace(tf, MEM2.mem[2], "MEM2.mem2");
    sc_trace(tf, MEM2.mem[3], "MEM2.mem3");
    sc_trace(tf, MEM2.mem[4], "MEM2.mem4");
    sc_trace(tf, MEM2.mem[5], "MEM2.mem5");
    sc_trace(tf, MEM2.mem[6], "MEM2.mem6");
    sc_trace(tf, MEM2.mem[7], "MEM2.mem7");
    sc_trace(tf, MEM2.mem[8], "MEM2.mem8");
    sc_trace(tf, MEM2.mem[9], "MEM2.mem9");
    sc_trace(tf, MEM2.mem[10], "MEM2.mem10");
    sc_trace(tf, MEM2.addr, "MEM2.addr");
    sc_trace(tf, MEM2.control, "MEM2.control");
    sc_trace(tf, MEM2.indata, "MEM2.indata");
    sc_trace(tf, MEM2.outdata, "MEM2.outdata");

    rst.write(true);
    sc_start(15,SC_NS);
    rst.write(false);

    control.write(1);
    addr.write(0x0);
    data.write(0);
    sc_start(20,SC_NS);
    addr.write(0x4);
    data.write(0);
    sc_start(20,SC_NS);
    addr.write(0x8);
    data.write(10);
    sc_start(20,SC_NS);
    addr.write(0xC);
    data.write(1);
    sc_start(20,SC_NS);
    control.write(0);*/

    /*while(Interrupt.read()==0){
        ;
    }*/
    /*sc_start(260,SC_NS);
    Clear.write(1);
    sc_start(20,SC_NS);

    sc_close_vcd_trace_file(tf);*/
    return 0;
}
