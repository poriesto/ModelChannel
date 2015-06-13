//
// Created by Alexander on 26.05.2015.
//

#include "opp.h"
#include "Graph.h"
#include "UnitTestsApi.h"

int main() {
    UINT BlockSize = 250, SessionLenght = 100000;
    opp* op = new opp(BlockSize, SessionLenght);
    std::list<Code>codeList;
    std::list<TwoParamModels> OPPmdl;
    init(codeList, OPPmdl);
    std::list<Plot>spdlist;
    std::list<Plot>delProbList;
    Plot plot, plotDelProb;
    for(auto P : OPPmdl){
        std::cout << P.param1 << " " << P.param2 << std::endl;
        op->setParams(P.param1, P.param2);
        op->genBitArray();
        for(auto codeTest : codeList){
            op->setProtocolType(2,16);
            op->setCode(codeTest);
            op->work();
            plot = op->getPlot();
            plotDelProb = op->getDelProbPlot();
            spdlist.emplace_back(plot);
            delProbList.emplace_back(plotDelProb);
        }
    }
    sf::RenderWindow window(sf::VideoMode(600*2, 400*2), "SFML plot", sf::Style::Default);
    Graph google_com("Transfer Rate", sf::Vector2i(0,0), spdlist);
    Graph google_ru("Deleviry Probality", sf::Vector2i(1,0), delProbList);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        // Each 200 ms, a new random value is add to the random curve
        google_com.update();
        google_ru.update();
        window.clear();
       window.draw(google_com);
        window.draw(google_ru);

        window.display();
    }
   return EXIT_SUCCESS;
}
