//
// Created by Alexander on 28.04.2015.
//
#include "main.h"
#include <list>
int main(){
    unsigned int SessionLenght = 0, BlockSize = 0, model = 0, protocol = 0, CRC;
	unsigned int codeLenght = 0, dataLength = 0, errorsCorrection = 0, PacketSize = 0, bitsWord = 0;
	double A = 0, V = 0, p = 0.0, a = 0.0;

	setparam(protocol, "Chose protocol type\n"
			"Enter 1 - datagramm, 2 - with latency, 3 - backNstep");
	setparam(model, "Выберите поток ошибок\n"
			"Enter 1 - ДСК,, 2 - PA, 3 - ОПП");
	set2params(SessionLenght, BlockSize, "Установите длину сеанса связи и размер криптоблока");
	set2params(CRC,PacketSize, "Установите длину CRC последовательности и количество криптоблоков в кадре");
	BlockSize += CRC;

	set2params(codeLenght, errorsCorrection, "Параметры кода:\nУстановите длину кода n(бит) и"
					" Количество исправляемых ошибок");
	set2params(dataLength, bitsWord, "Установите длину информационной последовательности k(бит) и длину слова(бит)");

	dsk* dk = new dsk(BlockSize, SessionLenght);
	pa* pk = new pa(SessionLenght, BlockSize);
	opp* op = new opp(BlockSize, SessionLenght);
	switch(model)
	{
		case 1:
			setparam(p, "Enter p for single bit:");
			dk->setP(p);
			dk->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			dk->setProtocol(protocol, PacketSize);
			dk->work();
			break;
		case 2:
			set2params(p, a, "Установите p и a:");
			pk->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			pk->setProtocol(protocol, PacketSize);
			pk->setParams(a,p);
			pk->work();
			break;
		case 3:
			set2params(A, V, "Установите A и V:");
			op->setProtocolType(protocol, PacketSize);
			op->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			op->setParams(A, V);
			op->work();
			break;
		default:
			std::cout << "Введены некоректные параметры" << std::endl;
			break;
	}
	return EXIT_SUCCESS;
}
