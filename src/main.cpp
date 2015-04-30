//
// Created by Alexander on 28.04.2015.
//
#include "main.h"

int main(){
    unsigned int SessionLenght = 0, PacketSize = 0, BlockSize = 0, model = 0, protocol = 0;
	unsigned int codeLenght = 0, errorsCorrection = 0;
	double A = 0, V = 0, p = 0.0, a = 0.0;

	setparam(protocol, "Chose protocol type\n"
			"Enter 1 - datagramm, 2 - with latency, 3 - backNstep");
	setparam(model, "Chose channel model\n"
			"Enter 1 - dsk, 2 - PA, 3 - OPP");
	std::cout << "Enter SessionLenght" << std::endl;
	std::cin >> SessionLenght;
	std::cout << "Enter BlockSize" << std::endl;
	std::cin >> BlockSize;
	std::cout << "Enter PacketSize" << std::endl;
	std::cin >> PacketSize;

	dsk* dk = new dsk(SessionLenght, BlockSize, PacketSize);
	pa* pk = new pa(SessionLenght, BlockSize, PacketSize);
	opp* op = new opp(BlockSize, SessionLenght);

	switch(model)
	{
		case 1:
			std::cout << "Enter P" << std::endl;
			std::cin >> p;
			set2params(codeLenght, errorsCorrection, "Set code parametrs:\nEnter length and"
					" errors correction");
			dk->setP(p);
			dk->setCode(codeLenght, errorsCorrection);
			dk->setProtocol(protocol);
			dk->work();
			break;
		case 2:
			set2params(p, a, "Set p and a:");
			set2params(codeLenght, errorsCorrection, "Set code parametrs\nEnter length and"
					" errors correction");
			pk->setCode(codeLenght, errorsCorrection);
			pk->setProtocol(protocol);
			pk->setParams(a,p);
			pk->work();
			break;
		case 3:
			set2params(A, V, "Set A and V:");
			set2params(codeLenght, errorsCorrection, "Set code parametrs\nEnter length and"
					" errors correction");
			op->setProtocolType(protocol);
			op->setCode(errorsCorrection, codeLenght);
			op->setParams(A, V);
			op->work();
			break;
		default:
			std::cout << "Enter correct params" << std::endl;
			break;
	}
    return EXIT_SUCCESS;
}
