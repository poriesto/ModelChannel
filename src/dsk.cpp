#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	UINT Count = 0;
	double a = 0, b = 1;
	double r;
	for(UINT i = 0; i < SessionSize; i++){
		generator(a,b, r);
		r < this->p ? bytes.at(i) = 1 : bytes.at(i) = 0;
		Count++;
		if(Count >= SessionSize){
			break;
		}
	}
	print(bytes);
	bl = makeBlocks(Blocks, BlockSize, bytes);
	pl = makePackets(PacketSize, Packets, bl);

	switch (dsk::protocol){
		case 1:
			datagrammProtocol(bl, code);
			break;
		case 2:
			UINT latency;
			setLatency(latency);
			latencyProtocol(bl, code, latency);
			break;
		case 3:
			UINT steps;
			setNsteps(steps);
			backNsteps(bl, code, steps);
			break;
	}
	std::cout << "======End dsk model======" << std::endl;
}
