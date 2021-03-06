//
// Created by Alexander on 28.04.2015.
//

#include "pa.h"

void pa::work(){
    std::cout << "======Begin pa model======" << std::endl;
	bl = makeBlocks(Blocks, BlockSize, bytes);

	pr = new protocol(bl,code);
	pr->work(pa::ProtocolType, PacketSize);

	pa::speedPlot = pr->getPlot();
	pa::timePlot = pr->getDelProbPlot();
	std::cout << "End pa model" << std::endl;
}
