//
// Created by Alexander on 28.04.2015.
//
#include "api.hpp"
#include "protocol.h"
#ifndef DIPLOM_OPP_H
#define DIPLOM_OPP_H


class opp {
public:
    opp(UINT BlockSize, UINT SessionSize):BlockSize(BlockSize), SessionSize(SessionSize) {
        opp::Blocks = opp::SessionSize / opp::BlockSize;
		opp::bytes = makeSession(opp::SessionSize);
    }
    virtual ~opp() { }
    void setCode(UINT codeLength, UINT errosCor, UINT dataLength, UINT bitsWord) {
        opp::code.errorsCorrection = errosCor;
        opp::code.codeLength = codeLength;
        opp::code.DataLength = dataLength;
        opp::code.bitsWord = bitsWord;
    }
    void setParams(double A, double V) {
        opp::A = A;
        opp::V = V;
    }
    void setProtocolType(UINT ProtocolType, UINT PacketSize) {
        opp::ProtocolType = ProtocolType;
        opp::PacketSize = PacketSize;
    }
    void work();

private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType, PacketSize;
    double A,V;
    Code code;
    std::vector<UINT> bytes, errorsPos;
    std::vector<Block> bl;
    protocol* pr;

    UINT GenOppPos();
    void saveToFile(std::string str);
};


#endif //DIPLOM_OPP_H
