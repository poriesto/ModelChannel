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

    for(auto P : Plist){
        dk->setP(P);
        dk->genBitsArray();
        for(auto codeTest : codeList){
            dk->setCode(codeTest);
            dk->setProtocol(2,16);
            dk->work();
            curPlot = dk->getPlot();
            plots.emplace_back(curPlot);
            curPlot = dk->getProbPlot();
            delProb.emplace_back(curPlot);
        }
    }
    sf::RenderWindow window(sf::VideoMode(600*2, 400*2), "SFML plot", sf::Style::Default);
    Graph google_com("Transfer Rate", sf::Vector2i(0,0), plots);
    Graph google_ru("Deleviry Probality", sf::Vector2i(1,0), delProb);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        google_com.update();
        google_ru.update();
        window.clear();
       window.draw(google_com);
        window.draw(google_ru);

        window.display();
    }

	return EXIT_SUCCESS;
}
