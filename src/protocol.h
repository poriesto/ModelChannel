//
// Created by Alexander on 12.05.2015.
//
#include "api.hpp"
#ifndef DIPLOM_PROTOCOL_H
#define DIPLOM_PROTOCOL_H

class protocol {

public:
    protocol(const std::vector<Block> &bl, const Code &code) : bl(bl), code(code) {
        protocol::attems = 0;
        protocol::blSize = protocol::bl.begin()->size();
        protocol::blocks = protocol::bl.size();
    }
    virtual ~protocol() { }

    void work(UINT type, UINT pkSize);
private:
    std::vector<Block>bl;
    Code code;
    double speed, PolBits, OverallBits, percent;
    UINT blSize, blocks, pkSize, suc, unsuc, attems;

    void datagramm();
    void latency();
    void Nstep();

    bool isCorectable(Packet packet);
    bool checkPacket(Packet packet);
    UINT checkBlockErrors(Block bl);
    bool isCorrectiableBlock(Block block);
};


#endif //DIPLOM_PROTOCOL_H
