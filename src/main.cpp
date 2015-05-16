//
// Created by Alexander on 28.04.2015.
//
#include "main.h"

int main(){
    unsigned int SessionLenght = 0, BlockSize = 0, model = 0, protocol = 0, CRC;
	unsigned int codeLenght = 0, dataLength = 0, errorsCorrection = 0, PacketSize;
	double A = 0, V = 0, p = 0.0, a = 0.0;

	setparam(protocol, "Chose protocol type\n"
			"Enter 1 - datagramm, 2 - with latency, 3 - backNstep");
	setparam(model, "Chose channel model\n"
			"Enter 1 - dsk, 2 - PA, 3 - OPP");
	set2params(SessionLenght, BlockSize, "Set SessionLenght and BlockSize");
	set2params(CRC,PacketSize, "Set CRC length and Blocks in packet");
	BlockSize += CRC;

	dsk* dk = new dsk(BlockSize, SessionLenght);
	pa* pk = new pa(SessionLenght, BlockSize);
	opp* op = new opp(BlockSize, SessionLenght);

	switch(model)
	{
		case 1:
			setparam(p, "Enter p for single bit:");
			set2params(codeLenght, errorsCorrection, "Set code parametrs:\nEnter length and"
					" errors correction");
			setparam(dataLength, "Enter data length for code");
			dk->setP(p);
			dk->setCode(codeLenght, errorsCorrection, dataLength);
			dk->setProtocol(protocol, PacketSize);
			dk->work();
			break;
		case 2:
			set2params(p, a, "Set p and a:");
			set2params(codeLenght, errorsCorrection, "Set code parametrs\nEnter length and"
					" errors correction");
			setparam(dataLength, "Enter data length for code");
			pk->setCode(codeLenght, errorsCorrection, dataLength);
			pk->setProtocol(protocol, PacketSize);
			pk->setParams(a,p);
			pk->work();
			break;
		case 3:
			set2params(A, V, "Set A and V:");
			set2params(codeLenght, errorsCorrection, "Set code parametrs\nEnter length and"
					" errors correction");
			setparam(dataLength, "Enter data length for code");
			op->setProtocolType(protocol, PacketSize);
			op->setCode(codeLenght, errorsCorrection, dataLength);
			op->setParams(A, V);
			op->work();
			break;
		default:
			std::cout << "Enter correct params" << std::endl;
			break;
	}
    return EXIT_SUCCESS;
}
