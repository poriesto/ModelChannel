//
// Created by Alexander on 26.05.2015.
//

#include "dsk.hpp"
#include <list>

int main(){
    UINT BlockSize = 150, SessionLenght = 10000000;
	dsk* dk = new dsk(BlockSize, SessionLenght);

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
    std::list<double>Plist{0.05, 0.01, 0.005};
    for(auto codeTest : codeList){
        for(auto P : Plist){
            dk->setP(P);
            dk->setCode(codeTest);
            dk->setProtocol(2,16);
            dk->work();
        }
    }
}
