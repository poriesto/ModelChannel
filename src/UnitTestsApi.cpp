//
// Created by Alexander on 28.05.2015.
//
#include "UnitTestsApi.h"

Code setCode(UINT cl, UINT dl, UINT er, UINT bw){
    Code code;
    code.codeLength = cl; code.DataLength = dl;
    code.errorsCorrection = er; code.bitsWord = bw;
    return code;
}
TwoParamModels setModel2(double param1, double param2){
    TwoParamModels tw;
    tw.param1 = param1; tw.param2 =param2;
    return tw;
}
void init(std::list<Code>& codeList, std::list<TwoParamModels>& OPPmodel){
    codeList.emplace_back(setCode(31,11,5,1));
    codeList.emplace_back(setCode(31,16,3,1));
    codeList.emplace_back(setCode(23,17,3,8));
    codeList.emplace_back(setCode(63,57,1,1));
    codeList.emplace_back(setCode(31,26,1,1));
    codeList.emplace_back(setCode(31,21,2,1));
    codeList.emplace_back(setCode(1,1,0,0));
    OPPmodel.emplace_back(setModel2(1.0,0.98));
   // OPPmodel.emplace_back(setModel2(0.9,0.9));
   // OPPmodel.emplace_back(setModel2(0.9,0.8));
}
void init(std::list<Code>& codeList, std::list<double>& DSKmodel){
    codeList.emplace_back(setCode(31,11,5,1));
    codeList.emplace_back(setCode(31,16,3,1));
    codeList.emplace_back(setCode(23,17,3,8));
    codeList.emplace_back(setCode(63,57,1,1));
    codeList.emplace_back(setCode(31,26,1,1));
    codeList.emplace_back(setCode(31,21,2,1));
    DSKmodel.emplace_back(0.005); DSKmodel.emplace_back(0.01); DSKmodel.emplace_back(0.001);
}
