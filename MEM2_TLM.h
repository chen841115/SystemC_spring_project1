#ifndef MEM2_TLM_H
#define MEM2_TLM_H

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include<systemc.h>
#include<tlm.h>
#include<tlm_utils/simple_target_socket.h>
using namespace sc_core;
using namespace sc_dt;
using namespace std;
using namespace tlm;

SC_MODULE(Memory2)
{
    tlm_utils::simple_target_socket<Memory2> socket_m2;
    void mem2_do();
    virtual void mem2_do(tlm::tlm_generic_payload& trans, sc_time& delay);
    int mem[1024];
    SC_CTOR(Memory2):socket_m2("socket_m2")
    {
        socket_m2.register_b_transport(this, &Memory2::mem2_do);
        for(int i=0;i<1024;i++)
            mem[i] = 256;
    }
};
#endif
