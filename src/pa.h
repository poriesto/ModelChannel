//
// Created by Alexander on 28.04.2015.
//

#ifndef DIPLOM_PA_H
#define DIPLOM_PA_H

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

	~pa()
	{

	}
	void work();
	void setParams(double a, double p)
	{
		pa::a = a;
		pa::p = p;
	}
	void setCode(UINT codelenght, UINT correction)
	{
		pa::codelenght = codelenght;
		pa::correction = correction;
	}
	void setProtocol(UINT protocol)
	{
		this->protocol = protocol;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets;
	UINT codelenght, correction, protocol;
	std::vector<UINT> bytes;
	std::vector<Block> bl;
	std::vector<Packet> pl;
	double p, a;

	void datagrammProtocol();
	void latencyProtocol();
	void backNsteps(UINT steps);

};

#endif //DIPLOM_PA_H
