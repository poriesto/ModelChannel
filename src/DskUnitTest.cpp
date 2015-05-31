//
// Created by Alexander on 26.05.2015.
//

#include "dsk.hpp"
#include "UnitTestsApi.h"
#include "Graph.h"

int main(){
    UINT BlockSize = 150, SessionLenght = 10000000;
	dsk* dk = new dsk(BlockSize, SessionLenght);

    std::list<Code>codeList;
    std::list<double>Plist;
    std::list<Plot>plots, delProb;
    Plot curPlot;
    init(codeList, Plist);

    for(auto codeTest : codeList){
        for(auto P : Plist){
            dk->setP(P);
            dk->setCode(codeTest);
            dk->setProtocol(2,16);
            dk->work();
            curPlot = dk->getPlot();
            plots.emplace_back(curPlot);
            curPlot = dk->getProbPlot();
            delProb.emplace_back(curPlot);
        }
    }
    std::stringstream name;
    name << "DSK model with params:" << "P = " << to_str(*(Plist.begin()));
    Graph* gr = new Graph();
    gr->setname(name.str());
    gr->setPls(plots);
    gr->setinitPosition(0,0);
    gr->setwidthheight(1024, 768);
    gr->show();
}
