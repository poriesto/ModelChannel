//
// Created by Alexander on 28.04.2015.
//
#ifndef DIPLOM_PA_H
#define DIPLOM_PA_H
#include "api.hpp"
#include "protocol.h"
//TODO work later
class pa
{
public:
	pa(UINT SessionSize, UINT BlockSize) : SessionSize(SessionSize), BlockSize(BlockSize){
		pa::Blocks = pa::SessionSize / pa::BlockSize;
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
		pa::ProtocolType = protocol;
	}
	void work();
private:
	UINT SessionSize, BlockSize, Blocks, ProtocolType;
	Code code;
	protocol* pr;
    std::vector<UINT> bytes;
	std::vector<Block> bl;
	double p, a;
};

#endif //DIPLOM_PA_H
