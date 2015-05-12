//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"

void protocol::work(UINT type) {
    UINT param = 0;
    switch (type){
        case 1:
            datagramm();
            break;
        case 2:
            setparam(param, "Set max latency:");
            latency(param);
            break;
        case 3:
            setparam(param, "Set max steps:");
            Nstep(param);
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
void protocol::latency(UINT latency) { 
//TODO need hard fix
    for(auto i = 0; i < bl.size(); i++){
        auto errors = checkBlockErrors(bl.at(i));
        if( errors > 0 ){
            if( errors > code.errorsCorrection ){
                unsuc+=1;
                OverallBits += (unsuc)*blSize*(code.errorsCorrection*code.codeLegth);
            }
            else{
                suc+=1;
                PolBits += suc*blSize;
            }
        }
        else{
            suc+=1;
            PolBits += suc*blSize;
        }
	}
    OverallBits = unsuc*ATTEMS*blSize*code.codeLegth;
    PolBits = suc*blSize;
    speed = 1200;
    std::cout << "Blocks transmited = " << blocks << std::endl <<
                 "Blocks succeful = " << suc << std::endl <<
                 "Blocks unsucceful = " << unsuc << std::endl <<
                 "Percent succeful = " << percent << "%" << std::endl <<
                 "Speed = " << speed << " bt/s" << std::endl <<
                 "Attems = " << attems << std::endl;
    std::cout << "Single time = " << OverallBits/speed << std::endl;
}
void protocol::Nstep(UINT step) { 
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

    for(auto block : packet) checkBlockErrors(block) > code.errorsCorrection ? corupted+=1 : correct+=1;
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
Block protocol::mlSingleBlock() {
    Block block;
    for(auto i = 0; i < blSize; i++) block.emplace_back(0);
    return block;
}
Packet protocol::mkSinglePacket() {
    Packet packet;
    for(auto i = 0; i < pkSize; i++) packet.emplace_back(mlSingleBlock());
    return packet;
}