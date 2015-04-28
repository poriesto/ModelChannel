#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	std::vector<UINT>bytes = makeSession(SessionSize);
	UINT Count = 0;
	double a = 0, b = 1;
	double r;
	for(UINT i = 0; i < this->SessionSize; i++){
		generator(a,b, r);
		r < this->p ? bytes.at(i) = 1 : bytes.at(i) = 0;
		Count++;

		if(Count >= this->SessionSize){
			break;
		}
	}
	print(bytes);
	std::vector<Block> bl = makeBlocks(Blocks, BlockSize, bytes);
	std::vector<Packet> pl = makePackets(PacketSize, Packets, bl);

	std::cout << "Analyze packets:" << std::endl;
	UINT Succeful = 0, UnSucceful = 0;
	checkPacketStream(pl, Succeful, UnSucceful);

	double Pb = 0.807, Pt;
	double l = (Succeful * PacketSize) * BlockSize;
	double L = SessionSize;
	double R = l * Pb/L;

	std::cout << "Packets in session: " << pl.capacity() << std::endl;
	std::cout << "Succeful transmited packets: " << Succeful << std::endl;
	std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
	std::cout << "Result speed: " << R << std::endl;
	std::cout << "======End dsk model======" << std::endl;
}
