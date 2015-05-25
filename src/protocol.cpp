//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"
#include <list>

void protocol::work(UINT type, UINT pkSize) {
    protocol::pkSize = pkSize;
    pl = makePackets(protocol::pkSize,blocks/protocol::pkSize, bl);
    packetSize = blSize*pkSize;
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
    bool CoruptedPacket, CorrectablePacket;
    for(auto packet : pl){
        CoruptedPacket = checkPacket(packet);
        if (CoruptedPacket){
            CorrectablePacket = isCorectable(packet);
            if(CorrectablePacket){
                RecivedPackets+=1;
            }
        }
        else{
            RecivedPackets+=1;
        }
        SentPackets+=1;
    }
    std::cout << "Sent Packets = " << SentPackets << " RecivedPackets = " << RecivedPackets << std::endl;
    delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
    speed = delProbability*RecivedPackets/SentPackets;
    speed = speed*packetSize;
    std::cout << "Deleviring probability: " << delProbability << std::endl <<
                 "Speed: " << speed << std::endl;
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
    speed = (static_cast<double>(RecivedPackets)/ static_cast<double>(SentPackets))*(static_cast<double>(blSize*pkSize));
    singleTime = static_cast<double>(SentPackets*SentPackets)/ static_cast<double>(RecivedPackets*packetSize);

    std::cout << "Deleviring probability: " << delProbability << std::endl <<
                 "Speed: " << speed << std::endl <<
                 "Time for work on single packet: " << singleTime << std::endl;
}
void protocol::Nstep() {
}

bool protocol::isCorectable(Packet packet) {
    UINT corupted = 0;
    for(auto block : packet) if(isCorrectiableBlock(block)) corupted += 1;
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
    UINT ipos = 0, epos = code.bitsWord;
    blErrors = 0;
    if(code.bitsWord > 1) {
        std::list<std::list<UINT> > words;
        for (auto i = 0; i < block.size() / code.bitsWord; i++) {
            std::list<UINT> word;
            for (auto j = ipos; j < epos; j++) {
                word.emplace_back(block.at(j));
            }
            words.emplace_back(word);
            ipos += code.bitsWord;
            epos += code.bitsWord;
        }
        for (auto word : words) {
            for (auto value : word) {
                if (value == 1) blErrors+=1;
            }
        }
    }
    else{
        blErrors = checkBlockErrors(block);
    }
    return blErrors <= code.errorsCorrection;
}
