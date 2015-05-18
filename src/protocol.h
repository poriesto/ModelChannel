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
        protocol::blSize = (UINT) protocol::bl.begin()->size();
        protocol::blocks = (UINT) protocol::bl.size();
    }
    virtual ~protocol() { }
    void setSpeed(double speed) {
        protocol::speed = speed;
    }

    void work(UINT type, UINT pkSize);
private:
    std::vector<Block>bl;
    std::vector<Packet>pl;
    Code code;
    double speed = 0.0, PolBits = 0.0, OverallBits = 0.0, percent = 0.0;
    double delProbability = 0.0;
    UINT blSize, blocks, pkSize, RecivedPackets = 0, SentPackets = 0, attems = 0;
    UINT blErrors;

    void datagramm();
    void latency();
    void Nstep();

    bool isCorectable(Packet packet);
    bool checkPacket(Packet packet);
    UINT checkBlockErrors(Block bl);
    bool isCorrectiableBlock(Block block);
};


#endif //DIPLOM_PROTOCOL_H
