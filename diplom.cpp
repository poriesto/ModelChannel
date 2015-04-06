#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

template<typename T>
void print(T cont)
{
	for(auto value : cont)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;
}
typedef std::vector<unsigned int> Block;
typedef std::vector<Block> Packet;

bool checkPacket(Packet pk)
{
	bool result = false;
	unsigned int Succeful = 0, Unsucceful = 0;
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

int main()
{
	unsigned int SessionLenght = 0, PacketSize = 0, BlockSize = 0;
	unsigned int errRange = 5;
	std::cout << "Enter SessionLenght" << std::endl;
	std::cin >> SessionLenght;
	std::cout << "Enter BlockSize" << std::endl;
	std::cin >> BlockSize;
	std::cout << "Enter PacketSize" << std::endl;
	std::cin >> PacketSize;

	std::cout << "Enter SessionLenght: " << SessionLenght << std::endl;
	std::cout << "Enter BlockSize" << BlockSize << std::endl;
	std::cout << "Enter PacketSize" << PacketSize << std::endl;

	//allocate some bytes
	std::vector<unsigned int> bytes;
	bytes.resize(SessionLenght);
	std::cout << "Bytes in session: " << bytes.capacity() << std::endl;
	std::fill(bytes.begin(), bytes.end(), 0);

	// encode and apply some error stream
	//std::vector<unsigned int>errStream;
	//errStream.resize(SessionLenght);
	//std::srand(std::time(0));
	//std::generate(errStream.begin(), errStream.end(), [](){
	//			std::random_device rd;
	//			std::mt19937 gen(rd());
	//			std::uniform_int_distribution<> dis(0,1);
	//			return dis(gen);
	//		});
	
	//OPP
	//for(auto i = 0; i < bytes.capacity(); i++)
	//{
	//	if( i % errRange == 0)
	//	{
	//		bytes.at(i) += 1;
	//	}
	//}
	//print(bytes);

	//decode data
	/*
		this place for some code
	*/
	
	//create some blocks
	unsigned int Blocks = 0;
	Blocks = SessionLenght/BlockSize;
	std::vector<Block> bl;
	bl.reserve(Blocks);
	unsigned int IPos = 0, EPos = BlockSize;
	for(auto i = 0; i < Blocks; i++)
	{
		Block bk;
		for(auto i = IPos; i < EPos; i++)
		{
			bk.emplace_back(bytes.at(i));
		}
		bl.emplace_back(bk);
		IPos += BlockSize;
		EPos += BlockSize;
	}
	std::cout << "Blocks created " << bl.capacity() << std::endl;
	
	//create some packet
	unsigned int Packets = 0;
	Packets = Blocks/PacketSize;
	std::vector<Packet> ve; //or std::list<Packet> pe
	ve.reserve(Packets); //packet array
	//create some packets
	unsigned int InitPos = 0, EndPos = PacketSize;
	for(auto i = 0; i < Packets; i++)
	{
		Packet pk;
		for(auto i = InitPos; i < EndPos; i++)
		{
			pk.emplace_back(bl.at(i));
		}
		ve.emplace_back(pk);
		InitPos += PacketSize;
		EndPos += PacketSize;
	}
	std::cout << "Create packets" << std::endl;
	std::cout << "Packets created " << ve.capacity() << std::endl;
	
	//analyze some data
	//work only with packets
	unsigned int Succeful = 0, Unsucceful = 0;
	for(auto value : ve)
	{
		checkPacket(value) ? Succeful += 1 : Unsucceful += 1;
	}
	std::cout << "Packets in session: " << Succeful + Unsucceful << std::endl;
	std::cout << "Succeful transmited packets: " << Succeful << std::endl;
	std::cout << "Unsucceful transmited packets: " << Unsucceful << std::endl;

	return 0;
}
