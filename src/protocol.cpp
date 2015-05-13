//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"

void protocol::work(UINT type, UINT pkSize) {
    UINT param = 0;
    protocol::pkSize = pkSize;
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
            break;
    }
}
void protocol::datagramm() {
    std::cout << "!******Datagramm protocol begin******!" << std::endl;
    auto expr1 = [this](){ unsuc+=1; attems+=ATTEMS; };
    auto expr2 = [this](){ suc+=1; };

    for(auto value : bl){
        auto errors = checkBlockErrors(value);
        errors > 0 ? errors > code.errorsCorrection ? expr1() : expr2() : expr2();
    }
    PolBits = suc*blSize;
    OverallBits = (suc+unsuc+attems)*blSize;
    percent = (suc*100)/blocks;
    speed = PolBits / OverallBits;
    std::cout << "Blocks transmited = " << blocks << std::endl <<
                 "Blocks succeful = " << suc << std::endl <<
                 "Blocks unsucceful = " << unsuc << std::endl <<
                 "Percent succeful = " << percent << "%" << std::endl <<
                 "Speed = " << speed << " bt/s" << std::endl <<
                 "Attems = " << attems << std::endl;
    std::cout << "!******Datagramm protocol end******!" << std::endl;
}
void protocol::latency() {
//TODO need hard fix
    std::vector<Packet> pl= makePackets(pkSize, blocks/pkSize, bl);
    auto expr = [this](){unsuc+=1; attems+=1; suc+=1;};
    auto expr1 = [this](){suc+=1;};
    for(auto packet : pl){
        bool isCorupt = checkPacket(packet);
        isCorupt ? isCorectable(packet) ? expr1() : expr() : expr1();
    }
    PolBits = suc * pkSize * blSize;
    OverallBits = (((unsuc+attems)*pkSize)*blSize) + PolBits;
    percent = PolBits*100/OverallBits;
    speed = PolBits/OverallBits;
    std::cout << "Blocks transmited = " << blocks << std::endl <<
                 "Overall Bits = " << OverallBits << std::endl <<
                 "PolBits = " << PolBits << std::endl <<
                 "Percent succeful = " << percent << "%" << std::endl <<
                 "Speed = " << speed << " bt/s" << std::endl <<
                 "Attems = " << attems << std::endl;
    std::cout << "Single time = " << OverallBits/speed << std::endl;
}
void protocol::Nstep() {
	/*auto expr1 = [this](){ unsuc+=1; attems+=ATTEMS; };
    auto expr2 = [this](){ suc+=1; };
    for(auto i = 0; i < bl.size(); i++){
    }
    PolBits = suc*blSize;
    OverallBits = (suc+unsuc+attems)*blSize;
    percent = (suc*100)/blocks;
    speed = PolBits / OverallBits;
    std::cout << "Blocks transmited = " << blocks << std::endl <<
                 "Blocks succeful = " << suc << std::endl <<
                 "Blocks unsucceful = " << unsuc << std::endl <<
                 "Percent succeful = " << percent << "%" << std::endl <<
                 "Speed = " << speed << " bt/s" << std::endl <<
                 "Attems = " << attems << std::endl;*/
}

bool protocol::isCorectable(Packet packet) {
    bool result = false;
    UINT correct = 0, corupted = 0;

    //for(auto block : packet) checkBlockErrors(block) > code.errorsCorrection ? corupted+=1 : correct+=1;
    for(auto block : packet) isCorrectiableBlock(block) ? correct+=1 : corupted+=1;
    corupted == 0 ? result = true: result = false;
    return result;
}
bool protocol::checkPacket(Packet packet) {
    bool result = false;
    UINT correct = 0, corupted = 0;

    for(auto block : packet) checkBlockErrors(block) > 0 ? corupted+=1 : correct+=1;
    corupted > 0 ? result = false: result = true;
    return result;
}
UINT protocol::checkBlockErrors(Block bl) {
    UINT errors = 0;

    for(auto value : bl) if(value == 1) errors+=1;
    return errors;
}
bool protocol::isCorrectiableBlock(Block block) {
    bool result = false;
    auto errors = checkBlockErrors(block);
    errors <= code.errorsCorrection ? result = true : result = false;
    return result;
}
