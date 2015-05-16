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
            break;
    }
}
void protocol::datagramm() {
    std::cout << "!******Datagramm protocol begin******!" << std::endl;
    auto expr1 = [this](){ unsuc+=1; attems+=1; };
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
//TODO need hard fix
void protocol::latency() {
    auto succsExpr = [this](){
        PolBits += blSize * pkSize;
        suc+=1;
        OverallBits += PolBits;
    };
    auto unsuccsExpr = [this](){
        OverallBits += blSize * pkSize;
        unsuc+=1;
        attems += 1;
        PolBits += blSize*(pkSize+attems);
    };
    bool Correct, Correctable;
    for(auto packet : pl){
        Correct = checkPacket(packet);
        if (Correct){
            Correctable = isCorectable(packet);
            if(Correctable){
                succsExpr();
            }
            else{
                unsuccsExpr();
            }
        }
        else{
            succsExpr();
        }
        attems = 0;
    }
    speed = PolBits/OverallBits;
    percent = (PolBits*100)/OverallBits;
    double singleTime = (OverallBits/speed)/(suc+unsuc+attems);
    std::cout << "Bits transmitted: " << OverallBits << std::endl <<
                 "Correct bits transmitted: " << PolBits << std::endl <<
                 "Percent corrects bits in session: " << percent << std::endl <<
                 "Speed: " << speed << std::endl <<
                 "Time for work on single packet: " << singleTime << std::endl;
}
void protocol::Nstep() {
}

bool protocol::isCorectable(Packet packet) {
    UINT correct = 0, corupted = 0;

    for(auto block : packet) isCorrectiableBlock(block) ? correct+=1 : corupted+=1;
    return corupted == 0;
}
bool protocol::checkPacket(Packet packet) {
    UINT correct = 0, corupted = 0;

    for(auto block : packet) checkBlockErrors(block) > 0 ? corupted+=1 : correct+=1;
    return corupted <= 0;
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
