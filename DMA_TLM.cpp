#include<iostream>
#include"DMA_TLM.h"
using namespace tlm;
using namespace std;

void DMA_TLM_READ::READ_do()
{
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10,SC_NS);
    
    while(true)
    {

            r_addr = DMA_addr.read();
            tlm::tlm_command cmd = TLM_READ_COMMAND;
            trans->set_command(cmd);
            trans->set_address(r_addr);
            trans->set_data_ptr((unsigned char*)&data);
            trans->set_data_length( 4 );
            trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
            trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
            trans->set_dmi_allowed( false ); // Mandatory initial value
            trans->set_response_status( TLM_INCOMPLETE_RESPONSE );
            socket_r-> b_transport(*trans,delay);

            if(cmd == tlm::TLM_READ_COMMAND)
            {
                DMA_data.write(data);
                //cout << "m_r_data:" << m_r_data <<" "<< "temp_data:" << temp_data <<endl;
            } 


            cout << "trans = { " << (cmd ? 'W' : 'R') << ", " 
            << hex << r_addr << " } , DMA_data = " << hex 
            << DMA_data.read() << " data = " << hex 
            <<(sc_uint<32>)data << " at time " << sc_time_stamp()
            << " delay = " << delay << " " <<endl;


            if ( trans->is_response_error() )
                SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

        wait(delay);
        
    }
}

void DMA_TLM_WRITE::WRITE_do()
{
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10,SC_NS);
    
    while(true)
    {

            data = DMA_data.read();
            w_addr = DMA_addr.read();
            tlm::tlm_command cmd = TLM_WRITE_COMMAND;
            trans->set_command(cmd);
            trans->set_address(w_addr);
            trans->set_data_ptr((unsigned char*)&data);
            trans->set_data_length( 4 );
            trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
            trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
            trans->set_dmi_allowed( false ); // Mandatory initial value
            trans->set_response_status( TLM_INCOMPLETE_RESPONSE );
            socket_w-> b_transport(*trans,delay);

            /*if(cmd == tlm::TLM_READ_COMMAND)
            {
                DMA_data.write(data);
                //cout << "m_r_data:" << m_r_data <<" "<< "temp_data:" << temp_data <<endl;
            }*/


            cout << "trans = { " << (cmd ? 'W' : 'R') << ", " 
            << hex << w_addr << " } , DMA_data = " << hex 
            << DMA_data.read() << " data = " << hex 
            <<(sc_uint<32>)data << " at time " << sc_time_stamp()
            << " delay = " << delay << " " <<endl;


            if ( trans->is_response_error() )
                SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
        
        wait(delay);
    }
}