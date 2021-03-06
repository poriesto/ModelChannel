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
	pa(UINT SessionSize, UINT BlockSize) : SessionSize(SessionSize), BlockSize(BlockSize), PacketSize(PacketSize){
		pa::Blocks = pa::SessionSize / pa::BlockSize;
		pa::bytes = makeSession(pa::SessionSize);
	}
	virtual ~pa(){}
	void setParams(double a, double p){
		pa::a = a;
		pa::p = p;
	}
	void setCode(UINT codelenght, UINT correction, UINT data, UINT bitsWord){
		pa::code.codeLength = codelenght;
		pa::code.DataLength = data;
		pa::code.errorsCorrection = correction;
		pa::code.bitsWord = bitsWord;
	}
	void setCode(const Code &code){
		pa::code = code;
	}
	void setProtocol(UINT protocol, UINT PacketSize)	{
		pa::ProtocolType = protocol;
		pa::PacketSize = PacketSize;
	}
	void work();

	const Plot &getSpeedPlot() const {
		return speedPlot;
	}

	const Plot &getTimePlot() const {
		return timePlot;
	}

private:
	UINT SessionSize, BlockSize, Blocks, ProtocolType, PacketSize;
	Code code;
	Plot speedPlot, timePlot;
	protocol* pr;
    std::vector<UINT> bytes;
	std::vector<Block> bl;
	double p, a;
};

#endif //DIPLOM_PA_H
