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
    }

    virtual ~opp() { }


    void setCode(UINT codeLength, UINT errosCor) {
        opp::codeLength = codeLength;
        opp::errosCor = errosCor;
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
    UINT BlockSize, SessionSize;
    UINT Blocks, ProtocolType;
    UINT errosCor, codeLength;
    std::vector<UINT> bytes, errorsPos;
    std::vector<Block> bl;
    double A,V;

    UINT GenOppPos();
    void datagrammPr();
    void lantecyPr();
    void backNsteps(UINT steps);
};


#endif //DIPLOM_OPP_H
