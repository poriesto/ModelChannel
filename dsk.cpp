#include "dsk.hpp"

int main()
{
	unsigned int SessionLenght = 0, PacketSize = 0, BlockSize = 0, model;
	double p = 0.0, a = 0.0;
	std::cout << "Chose channel model" << std::endl;
	std::cout << "Enter 1 for DSK model, 2 - for PA model, 3 - for OPP model" << std::endl;
	std::cin >> model;
	std::cout << "Enter SessionLenght" << std::endl;
	std::cin >> SessionLenght;
	std::cout << "Enter BlockSize" << std::endl;
	std::cin >> BlockSize;
	std::cout << "Enter PacketSize" << std::endl;
	std::cin >> PacketSize;
	std::cout << "Enter P" << std::endl;
	std::cin >> p;
	/*std::cout << "Enter a" << std::endl;
	std::cin >> a;
*/
	std::cout << "Enter SessionLenght: " << SessionLenght << std::endl;
	std::cout << "Enter BlockSize" << BlockSize << std::endl;
	std::cout << "Enter PacketSize" << PacketSize << std::endl;

	dsk* dk = new dsk(SessionLenght, BlockSize, PacketSize);
	pa* pk = new pa(SessionLenght, BlockSize, PacketSize);
	opp* op = new opp(SessionLenght, BlockSize, PacketSize);

	switch(model)
	{
		case 1:
			dk->setP(p);
			dk->work();
			break;
		case 2:
			pk->setP(p);
			pk->setA(a);
			pk->work();
			break;
		case 3:
			op->setParams(12, 1.08);
			op->work();
			break;
		default:
			break;
	}

	return 0;
}
