//
// Created by Alexander on 26.05.2015.
//

#include "opp.h"
#include <list>
struct OPPparams{
    double A;
    double V;
};

int main(){
    UINT BlockSize = 150, SessionLenght = 10000000;
    opp* op = new opp(BlockSize, SessionLenght);

    std::list<Code>codeList;
    Code code;
    code.codeLength = 31; code.DataLength = 11; code.errorsCorrection = 5; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 16; code.errorsCorrection = 3; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 23; code.DataLength = 17; code.errorsCorrection = 3; code.bitsWord = 8;
    codeList.emplace_back(code);

    code.codeLength = 63; code.DataLength = 57; code.errorsCorrection = 1; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 26; code.errorsCorrection = 1; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 21; code.errorsCorrection = 2; code.bitsWord = 1;
    codeList.emplace_back(code);

    OPPparams params;
    std::list<OPPparams>Plist;

    params.A = 1; params.V = 0.9;
    Plist.emplace_back(params);

    params.A = 0.9; params.V = 0.9;
    Plist.emplace_back(params);

    params.A = 0.9; params.V = 0.8;
    Plist.emplace_back(params);

    for(auto codeTest : codeList){
        for(auto P : Plist){
            op->setProtocolType(2, 16);
            op->setCode(codeTest);
            op->setParams(P.A, P.V);
            op->work();
        }
    }
}
