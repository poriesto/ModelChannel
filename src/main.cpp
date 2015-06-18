//
// Created by Alexander on 28.04.2015.
//
#include "main.h"

int main(){
    unsigned int SessionLenght = 0, BlockSize = 0, model = 0, protocol = 0, CRC;
	unsigned int PacketSize = 0 ;
	double A = 0, V = 0, p = 0.0;
	Plot cur;
	std::list<Plot>spdpls, delprobpls;

	setparam(protocol, "Chose protocol type\n"
			"Enter 1 - datagramm, 2 - with latency, 3 - backNstep");
	setparam(model, "Выберите поток ошибок\n"
			"Enter 1 - ДСК,, 2 - PA, 3 - ОПП");
	set2params(SessionLenght, BlockSize, "Установите длину сеанса связи и размер криптоблока");
	set2params(CRC,PacketSize, "Установите длину CRC последовательности и количество криптоблоков в кадре");
	BlockSize += CRC;

    std::list<Code>cdl = loadFromFile("Codes.txt");
    for(auto va : cdl){
        std::string tmp = Code_toStr(va);
        std::cout << tmp << std::endl;
    }
	dsk* dk = new dsk(BlockSize, SessionLenght);
	opp* op = new opp(BlockSize, SessionLenght);
	switch(model) {
        case 1:
            setparam(p, "Enter p for single bit:");
            dk->setP(p);
            dk->genBitsArray();
            dk->setProtocol(protocol,PacketSize);
            for (auto code : cdl) {
                dk->setCode(code);
                dk->work();
                cur = dk->getPlot();
                spdpls.emplace_back(cur);
                cur = dk->getProbPlot();
                delprobpls.emplace_back(cur);
            }
			break;
		case 3:
			set2params(A, V, "Установите A и V:");
            op->setParams(A, V);
			op->genBitArray();
            op->setProtocolType(protocol, PacketSize);
            for(auto code : cdl){
                op->setCode(code);
                op->work();
                cur = op->getPlot();
                spdpls.emplace_back(cur);
                cur = op->getDelProbPlot();
                delprobpls.emplace_back(cur);
            }
			break;
		default:
			std::cout << "Введены некоректные параметры" << std::endl;
			break;
	}
	sf::RenderWindow window(sf::VideoMode(600*2, 400*2), "SFML plot", sf::Style::Default);
    Graph google_com("Transfer Rate", sf::Vector2i(0,0), spdpls);
    Graph google_ru("Deleviry Probality", sf::Vector2i(1,0), delprobpls);
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
