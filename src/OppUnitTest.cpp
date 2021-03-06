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
    std::list<Plot>spdlist;
    std::list<Plot>delProbList;
    for(auto P : OPPmdl){
        std::cout << P.param1 << " " << P.param2 << std::endl;
        for(auto codeTest : codeList){
            Plot plot, plotDelProb;
            op->setProtocolType(2,16);
            op->setCode(codeTest);
            op->setParams(P.param1, P.param2);
            op->work();
            plot = op->getPlot();
            plotDelProb = op->getDelProbPlot();
            spdlist.emplace_back(plot);
            delProbList.emplace_back(plotDelProb);
        }
    }
    std::stringstream sname;
    sname << "OPP model with params:" << " A = " << to_str(OPPmdl.begin()->param1) << ", V = " << to_str(OPPmdl.begin()->param2);
    Graph* gr = new Graph();
    gr->setname(sname.str());
    gr->setPls(spdlist);
    gr->setinitPosition(0,0);
    gr->setwidthheight(1024,768);
    gr->show();
    return EXIT_SUCCESS;
}
