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
    codeList.emplace_back(setCode(31,20,2,1));
    codeList.emplace_back(setCode(31,26,3,1));
    codeList.emplace_back(setCode(63,51,2,1));

    codeList.emplace_back(setCode(23,17,3,8));
    codeList.emplace_back(setCode(31,21,2,8));
    codeList.emplace_back(setCode(30,20,4,8));

    codeList.emplace_back(setCode(1,1,0,0));

    //OPPmodel.emplace_back(setModel2(100, 1.094));
    OPPmodel.emplace_back(setModel2(125, 1.1));
    //OPPmodel.emplace_back(setModel2(95, 1.125));
}
void initPA(std::list<Code>& codeList, std::list<TwoParamModels>& OPPmodel){
    codeList.emplace_back(setCode(31,20,2,1));
    codeList.emplace_back(setCode(31,26,3,1));
    codeList.emplace_back(setCode(63,51,2,1));

    codeList.emplace_back(setCode(23,17,3,8));
    codeList.emplace_back(setCode(31,21,2,8));
    codeList.emplace_back(setCode(30,20,4,8));

    codeList.emplace_back(setCode(1,1,0,0));

    OPPmodel.emplace_back(setModel2(100, 1.094));
    OPPmodel.emplace_back(setModel2(125, 1.1));
    OPPmodel.emplace_back(setModel2(95, 1.125));
}
void init(std::list<Code>& codeList, std::list<double>& DSKmodel){
    codeList.emplace_back(setCode(31,20,2,1));
    codeList.emplace_back(setCode(31,26,3,1));
    codeList.emplace_back(setCode(63,51,2,1));

    codeList.emplace_back(setCode(1,1,0,0));

    codeList.emplace_back(setCode(23,17,3,8));
    codeList.emplace_back(setCode(31,21,2,8));
    codeList.emplace_back(setCode(30,20,4,8));

    codeList.emplace_back(setCode(1,1,0,0));


    DSKmodel.emplace_back(0.005); DSKmodel.emplace_back(0.01); DSKmodel.emplace_back(0.001);
}
