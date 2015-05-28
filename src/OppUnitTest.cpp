//
// Created by Alexander on 26.05.2015.
//

#include "opp.h"
#include "Graph.h"
#include "UnitTestsApi.h"

int main() {
    UINT BlockSize = 150, SessionLenght = 10000000;
    opp* op = new opp(BlockSize, SessionLenght);
    std::list<Code>codeList;
    std::list<TwoParamModels> OPPmdl;
    init(codeList, OPPmdl);
    std::list<Plot>plist;
    for(auto P : OPPmdl){
        std::cout << P.param1 << " " << P.param2 << std::endl;
        for(auto codeTest : codeList){
            Plot plot;
            op->setProtocolType(2,16);
            op->setCode(codeTest);
            op->setParams(P.param1, P.param2);
            op->work();
            plot = op->getPlot();
            plist.emplace_back(plot);
        }
    }
    std::string name = "Graph";
    Graph* gr = new Graph();
    gr->setname(name);
    gr->setPls(plist);
    gr->setinitPosition(0,0);
    gr->setwidthheight(1024,768);
    gr->show();
}
