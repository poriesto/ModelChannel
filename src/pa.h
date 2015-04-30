//
// Created by Alexander on 28.04.2015.
//

#ifndef DIPLOM_PA_H
#define DIPLOM_PA_H

#include "api.hpp"

class pa
{
public:
	pa(UINT SessionSize, UINT BlockSize, UINT PacketSize) : SessionSize(SessionSize), BlockSize(BlockSize),
															PacketSize(PacketSize) {
		pa::Blocks = pa::SessionSize / pa::BlockSize;
		pa::Packets = pa::Blocks / pa::PacketSize;
		pa::bytes = makeSession(pa::SessionSize);
	}
	virtual ~pa(){}
	void setParams(double a, double p){
		pa::a = a;
		pa::p = p;
	}
	void setCode(UINT codelenght, UINT correction){
		pa::code.codeLegth = codelenght;
		pa::code.errorsCorrection = correction;
	}
	void setCode(Code code){
		pa::code = code;
	}
	void setProtocol(UINT protocol)	{
		pa::protocol = protocol;
	}
	void work();
private:
	UINT SessionSize, BlockSize, PacketSize;
	UINT Blocks, Packets;
	UINT protocol;
	Code code;
	std::vector<UINT> bytes;
	std::vector<Block> bl;
	std::vector<Packet> pl;
	double p, a;
};

#endif //DIPLOM_PA_H
