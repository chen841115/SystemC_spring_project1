#ifndef MEM1_TLM_H
#define MEM1_TLM_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include<systemc.h>
#include<tlm.h>
#include<tlm_utils/simple_target_socket.h>
using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;

SC_MODULE(Memory1)
{
    tlm_utils::simple_target_socket<Memory1> socket_m1;
    void mem1_do();
    virtual void mem1_do(tlm::tlm_generic_payload& trans, sc_time& delay);
    int mem[1024];
    SC_CTOR(Memory1):socket_m1("socket_m1")
    {
        socket_m1.register_b_transport(this, &Memory1::mem1_do);
        for(int i=0;i<1024;i++)
            mem[i] = i;
    }

    
};
#endif
