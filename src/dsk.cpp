#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	UINT Count = 0;
	double a = 0, b = 1, r;

    for(auto& value : bytes){
        generator(a,b, r);
        r < dsk::p ? value = 0 : value = 1;
    }
    for(auto i = 0; i < bytes.size(); i++){
        bytes.at(i) == 1 ? dsk::errors.emplace_back(i) : dsk::corElems.emplace_back(i);
    }

	bl = makeBlocks(Blocks, BlockSize, bytes);
	printDb(bl);
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
