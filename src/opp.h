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

    void setCode(const Code &code) {
        opp::code = code;
    }

    const Plot &getPlot() const {
        return plot;
    }
    const Plot &getDelProbPlot() const{
        return delProbPlot;
    }
    void genBitArray();
private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType, PacketSize;
    double A,V;
    Code code;
    Plot plot, delProbPlot;
    std::vector<UINT> bytes;
    std::vector<Block> bl;
    protocol* pr;

    UINT GenOppPos();
    void saveToFile(std::string str);
    std::vector<UINT> toAsync(UINT size);
};


#endif //DIPLOM_OPP_H
