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
    }
}
void protocol::datagramm() {
    std::cout << "!******Datagramm protocol begin******!" << std::endl;
    auto expr1 = [this](){ unsuc+=1; attems+=ATTEMS; };
    auto expr2 = [this](){ suc+=1; };

    for(auto value : bl){
        auto errors = checkBlockErrs(value);
        errors > 0 ? errors > code.errorsCorrection ? expr1() : expr2() : expr2();
    }
    results();
    std::cout << "!******Datagramm protocol end******!" << std::endl;
}
void protocol::latency(UINT latency) { 
//TODO need hard fix
    for(auto i = 0; i < bl.size(); i++){
        auto errors = checkBlockErrs(bl.at(i));
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
    std::cout << "Single time = " << OverallBits/speed << std::endl;
}
void protocol::Nstep(UINT step) { 
	auto expr1 = [this](){ unsuc+=1; attems+=ATTEMS; };
    auto expr2 = [this](){ suc+=1; };
    for(auto i = 0; i < bl.size(); i++){
    }
    results();
}
void protocol::results() {
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
}
