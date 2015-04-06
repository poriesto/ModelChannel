#include "api.hpp"

class pa
{
public:
	pa(UINT SessionSize, UINT BlockSize, UINT PacketSize)
	{
		this->SessionSize = SessionSize;
		this->BlockSize = BlockSize;
		this->PacketSize = PacketSize;
		this->Blocks = this->SessionSize / this->BlockSize;
		this->Packets = this->Blocks / this->PacketSize;
	}
	~pa();
	void work()
	{
		std::vector<UINT>bytes = makeSession(SessionSize);
		/*
			Apply erors to bytes stream
			Encode and decode bytes stream
		*/
		std::vector<Block> bl = makeBlocks(Blocks, BlockSize, bytes);
		std::vector<Packet> pl = makePackets(PacketSize, Packets, bl);

		std::cout << "Analyze packets:" << std::endl;
		UINT Succeful = 0, UnSucceful = 0;
		for(auto value : pl)
		{
			checkPacket(value) ? Succeful += 1 : UnSucceful += 1;
		}
		double R = ((Succeful*PacketSize) * BlockSize)/SessionSize;

		std::cout << "Packets in session: " << pl.capacity() << std::endl;
		std::cout << "Succeful transmited packets: " << Succeful << std::endl;
		std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
		std::cout << "Result speed: " << R << std::endl;
	}
	void setP(double p)
	{
		this->p = p;
	}
	void setA(double a)
	{
		this->a = a;
	}
	double getP()
	{
		return this->p;
	}
	double getA()
	{
		return this->a;
	}
	UINT getBlockSize()
	{
		return this->BlockSize;
	}
	UINT getPacketSize()
	{
		return this->PacketSize;
	}
	UINT getSessionSize()
	{
		return this->SessionSize;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets;
	double p, a;
};