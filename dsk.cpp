#include "dsk.hpp"

int main()
{
	unsigned int SessionLenght = 0, PacketSize = 0, BlockSize = 0, model;
	double A = 0, V = 0;
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

	dsk* dk = new dsk(SessionLenght, BlockSize, PacketSize);
	pa* pk = new pa(SessionLenght, BlockSize, PacketSize);
	opp* op = new opp(SessionLenght, BlockSize, PacketSize);

	switch(model)
	{
		case 1:
			std::cout << "Enter P" << std::endl;
			std::cin >> p;
			dk->setP(p);
			dk->work();
			break;
		case 2:
			std::cout << "Enter P" << std::endl;
			std::cin >> p;
			std::cout << "Enter a" << std::endl;
			std::cin >> a;
			pk->setP(p);
			pk->setA(a);
			pk->work();
			break;
		case 3:
			std::cout << "Enter A" << std::endl;
			std::cin >> A;
			std::cout << "Enter V" << std::endl;
			std::cin >> V;
			op->setParams(A, V);
			//op->setParams(12, 1.08);
			op->work();
			break;
		default:
			break;
	}

	return 0;
}
