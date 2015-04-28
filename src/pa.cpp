//
// Created by Alexander on 28.04.2015.
//

#include "pa.h"

void pa::work(){
    std::cout << "======Begin pa model======" << std::endl;
	bytes = makeSession(SessionSize);
	bl = makeBlocks(Blocks, BlockSize, bytes);
	pl = makePackets(PacketSize, Packets, bl);

	std::cout << "Analyze packets:" << std::endl;
	UINT Succeful = 0, UnSucceful = 0;
	checkPacketStream(pl, Succeful, UnSucceful);
	double R = ((Succeful*PacketSize) * BlockSize)/SessionSize;

	std::cout << "Packets in session: " << pl.capacity() << std::endl;
	std::cout << "Succeful transmited packets: " << Succeful << std::endl;
	std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
	std::cout << "Result speed: " << R << std::endl;
	std::cout << "End pa model" << std::endl;
}
