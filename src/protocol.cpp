//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"

void protocol::work(UINT type, UINT pkSize) {
    protocol::pkSize = pkSize;
    pl = makePackets(protocol::pkSize,blocks/protocol::pkSize, bl);
    switch (type){
        case 1:
            datagramm();
            break;
        case 2:
            latency();
            break;
        case 3:
            Nstep();
            break;
        default:
            std::cout << "Set correct params" << std::endl;
            break;
    }
}
void protocol::datagramm() {
    std::cout << "!******Datagramm protocol begin******!" << std::endl;
    std::cout << "!******Datagramm protocol end******!" << std::endl;
}
//TODO need hard fix
void protocol::latency() {
    bool CoruptedPacket, CorrectablePacket;
    
    for(auto packet : pl){
        CoruptedPacket = checkPacket(packet);
        if(CoruptedPacket){
            CorrectablePacket = isCorectable(packet);
            if(CorrectablePacket){
                RecivedPackets += 1;
            }
        }
        else{
            RecivedPackets += 1;
        }
        SentPackets += 1;
    }
    std::cout << "Sent Packets = " << SentPackets << " RecivedPackets = " << RecivedPackets << std::endl;
    delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
    speed = (delProbability * (RecivedPackets*pkSize*blSize))/SentPackets*blSize*pkSize;
    double singleTime = RecivedPackets*pkSize*blSize / speed;
    std::cout << "Deleviring probability: " << delProbability << std::endl <<
                 "Speed: " << speed << std::endl <<
                 "Time for work on single packet: " << singleTime << std::endl;
}
void protocol::Nstep() {
}

bool protocol::isCorectable(Packet packet) {
    UINT corupted = 0;
    for(auto block : packet) if(!isCorrectiableBlock(block)) corupted += 1;
    return corupted == 0;
}
bool protocol::checkPacket(Packet packet) {
    UINT corupted = 0;
    for(auto block : packet) if (checkBlockErrors(block) > 0) corupted+=1;
    return corupted > 0;
}
UINT protocol::checkBlockErrors(Block bl) {
    UINT errors = 0;
    for(auto value : bl) if(value == 1) errors+=1;
    return errors;
}
bool protocol::isCorrectiableBlock(Block block) {
    auto errors = checkBlockErrors(block);
    blErrors += errors;
    return errors <= code.errorsCorrection;
}
