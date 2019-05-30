#include"MEM2_TLM.h"

void Memory2::mem2_do(tlm::tlm_generic_payload& trans, sc_time& delay)
{
    
    tlm_command     cmd = trans.get_command();
    uint32_t       tlm_addr = trans.get_address();
    unsigned char*  ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();
    
    if( cmd == TLM_WRITE_COMMAND)
        memcpy(&mem[tlm_addr],ptr,len);
    else if(cmd == TLM_READ_COMMAND)
        cout << "ERROR" << endl;
    
    /*cout << "ptr:"<<hex <<(sc_uint<32>)*ptr<<" ";
    cout << "mem[" << tlm_addr <<"] = " << hex << m[tlm_addr]<<endl;*/
    trans.set_response_status(tlm::TLM_OK_RESPONSE);

}

