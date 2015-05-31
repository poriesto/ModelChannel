//Created by Alexander

#include "pa.h"
#include "Graph.h"
#include "UnitTestsApi.h"

int main(){
	UINT SesionSize = 10000000, BlockSize = 150;
	pa* pk = new pa(SesionSize, BlockSize);
	Graph* gr = new Graph();
	Plot cur;

    std::list<Code>codeList;
	std::list<Plot>plots;
	std::list<Plot>delPlots;
	std::list<TwoParamModels> paParams;
	init(codeList,paParams);

	for(auto codeTst : codeList){
		for(auto param : paParams){
			pk->setCode(codeTst);
			pk->setProtocol(2, 16);
			pk->setParams(param.param1, param.param2);
			pk->work();
			cur = pk->getSpeedPlot();
			plots.emplace_back( cur );
			cur = pk->getTimePlot();
			delPlots.emplace_back( cur );
		}
	}
	std::stringstream sname;
	 sname << "PA model with params:" << " P = " << to_str(paParams.begin()->param1)
	 << ", A = " << to_str(paParams.begin()->param2);
	gr->setname(sname.str());
	gr->setPls(plots);
	gr->setinitPosition(0,0);
	gr->setwidthheight(1024,768);
	gr->show();

	return EXIT_SUCCESS;
}

