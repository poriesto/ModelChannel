//
// Created by Alexander on 28.04.2015.
//
#include "api.hpp"
#ifndef DIPLOM_OPP_H
#define DIPLOM_OPP_H


class opp {
public:
    opp(UINT BlockSize, UINT SessionSize):BlockSize(BlockSize), SessionSize(SessionSize) {
        opp::Blocks = opp::SessionSize / opp::BlockSize;
		opp::bytes = makeSession(opp::SessionSize);
    }
    virtual ~opp() { }
    void setCode(UINT codeLength, UINT errosCor) {
        opp::code.errorsCorrection = errosCor;
        opp::code.codeLegth = codeLength;
    }
    void setCode(Code code){
        opp::code = code;
    }
    void setParams(double A, double V) {
        opp::A = A;
        opp::V = V;
    }
    void setProtocolType(UINT ProtocolType) {
        opp::ProtocolType = ProtocolType;
    }
    void work();

private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType;
    double A,V;
    Code code;
    std::vector<UINT> bytes, errorsPos;
    std::vector<Block> bl;

    UINT GenOppPos();
};


#endif //DIPLOM_OPP_H
