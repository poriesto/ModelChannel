#include "dsk.hpp"

int main()
{
	unsigned int SessionLenght = 0, PacketSize = 0, BlockSize = 0;
	double p = 0.0, a = 0.0;
	std::cout << "Enter SessionLenght" << std::endl;
	std::cin >> SessionLenght;
	std::cout << "Enter BlockSize" << std::endl;
	std::cin >> BlockSize;
	std::cout << "Enter PacketSize" << std::endl;
	std::cin >> PacketSize;
	std::cout << "Enter P" << std::endl;
	std::cin >> p;
	std::cout << "Enter a" << std::endl;
	std::cin >> a;

	std::cout << "Enter SessionLenght: " << SessionLenght << std::endl;
	std::cout << "Enter BlockSize" << BlockSize << std::endl;
	std::cout << "Enter PacketSize" << PacketSize << std::endl;

	dsk* dk = new dsk(SessionLenght, BlockSize, PacketSize);
	dk->setP(p);
	dk->work();

	pa* pk = new pa(SessionLenght, BlockSize, PacketSize);
	pk->setP(p);
	pk->setA(a);
	pk->work();
	
	opp* op = new opp(SessionLenght, BlockSize, PacketSize);
	op->work();

	return 0;
}