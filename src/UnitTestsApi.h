//
// Created by Alexander on 28.05.2015.
//

#ifndef DIPLOM_UNITTESTSAPI_H
#define DIPLOM_UNITTESTSAPI_H

#include "api.hpp"
#include <list>
#include <thread>
struct TwoParamModels{
    double param1;
    double param2;
};
Code setCode(UINT cl, UINT dl, UINT er, UINT bw);
TwoParamModels setModel2(double param1, double param2);
void init(std::list<Code>&codeList, std::list<TwoParamModels>&OPPmodel);
void initPA(std::list<Code>&codeList, std::list<TwoParamModels>&OPPmodel);
void init(std::list<Code>&codeList, std::list<double>&OPPmodel);
#endif //DIPLOM_UNITTESTSAPI_H
