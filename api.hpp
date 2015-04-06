#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

typedef unsigned int UINT;
typedef std::vector<UINT> Block;
typedef std::vector<Block> Packet;
template<typename T>
void print(T cont)
{
	for(auto value : cont)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;
}
bool checkPacket(Packet pk)
{
	bool result = false;
	UINT Succeful = 0, Unsucceful = 0;
	for(auto value : pk)
	{
		for(auto val : value)
		{
			val == 0 ? Succeful += 1 : Unsucceful += 1;
		}
	}
	result = Unsucceful == 0 ? true : false;
	return result;
}

std::vector<UINT> makeSession(UINT SessionLenght)
{
	std::vector<UINT> ve;
	ve.resize(SessionLenght);
	std::fill(ve.begin(), ve.end(), 0);
	std::cout << "Bytes in session: " << ve.capacity() << std::endl;
	return ve;	
}

std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes)
{
	std::vector<Block> ve;
	UINT IPOS = 0, EPOS = BlockSize;
	ve.reserve(Blocks);
	for(auto i = 0; i < Blocks; i++)
	{
		Block bk;
		for(auto i = IPOS; i < EPOS; i++)
		{
			bk.emplace_back(bytes.at(i));
		}
		ve.emplace_back(bk);
		IPOS += BlockSize;
		EPOS += BlockSize;
	}
	std::cout << "Blocks created: " << ve.capacity() << std::endl;
	return ve;
}
std::vector<Packet> makePackets(UINT PacketSize, UINT Packets, std::vector<Block> v)
{
	std::vector<Packet>ve;
	UINT IPOS = 0, EPOS = PacketSize;
	ve.reserve(Packets);
	for(auto i = 0; i < Packets; i++)
	{
		Packet pk;
		for(auto i = IPOS; i < EPOS; i++)
		{
			pk.emplace_back(v.at(i));
		}
		ve.emplace_back(pk);
		IPOS += PacketSize;
		EPOS += PacketSize;
	}
	std::cout << "Packets created: " << ve.capacity() << std::endl;
	return ve;
}