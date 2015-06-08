//Created by Alexander

#include "pa.h"
#include "Graph.h"
#include "UnitTestsApi.h"

int main(){
	UINT SesionSize = 10000000, BlockSize = 150;
	pa* pk = new pa(SesionSize, BlockSize);
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

	return EXIT_SUCCESS;
}

