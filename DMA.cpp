#include "DMA.h"

void DMA::DMA_do() {
	source_addr.write(0);
    target_addr.write(0);
    source_addr_origin.write(0);
    target_addr_origin.write(0);
    size.write(0);
    start.write(0);
    write_data.write(0);
    mem1_control.write(0);
    mem2_control.write(0);
    state.write(0);
    count = 1;
    Interrupt.write(0);

	while(true) {
		wait();
		if (control.read() == 1) {
		    if(addr.read()==0x0){
                source_addr_origin.write(data.read()/4);
            }
            else if(addr.read()==0x4){
                target_addr_origin.write(data.read()/4);
            }
            else if(addr.read()==0x8){
                size.write(data.read());
            }
            else if(addr.read()==0xC){
                start.write(data.read());
            }
	    }
        if(start.read()==1){
            if(state.read()==0){
                mem1_control.write(0);
                source_addr.write(source_addr_origin.read()+count);
                state.write(1);
                count++;
            }
            else if(state.read()==1){
                mem2_control.write(1);
                source_addr.write(source_addr_origin.read()+count);
                write_data.write(read_data.read());
                state.write(2);
                count++;
            }
            else if(state.read()==2){
                write_data.write(read_data.read());
                if(count<size.read())
                    source_addr.write(source_addr_origin.read()+count);
                if(count-2<size.read())
                    target_addr.write(target_addr_origin.read()+count-2);
                count++;
                if(count>size.read()+3)
                    Interrupt.write(1);
            }
            if(Clear.read()==1){
                source_addr.write(0);
                target_addr.write(0);
                size.write(0);
                start.write(0);
                write_data.write(0);
                mem1_control.write(0);
                mem2_control.write(0);
                state.write(0);
                count = 1;
                Interrupt.write(0);
            }      
        }
	}
}