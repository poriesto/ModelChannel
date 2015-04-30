//
// Created by Alexander on 28.04.2015.
//

#include "pa.h"

void pa::work(){
    std::cout << "======Begin pa model======" << std::endl;
	bl = makeBlocks(Blocks, BlockSize, bytes);
	pl = makePackets(PacketSize, Packets, bl);

	switch(pa::protocol){
		case 1:
			datagrammProtocol(bl, code);
			break;
		case 2:
			UINT latency;
			setLatency(latency);
			latencyProtocol(bl, code , latency);
			break;
		case 3:
			UINT steps;
			setNsteps(steps);
			backNsteps(bl, code, steps);
			break;
	}

	std::cout << "End pa model" << std::endl;
}
