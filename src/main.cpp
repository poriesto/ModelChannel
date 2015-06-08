//
// Created by Alexander on 28.04.2015.
//
#include "main.h"
#include "Graph.h"
#include <list>
int main(){
    unsigned int SessionLenght = 0, BlockSize = 0, model = 0, protocol = 0, CRC;
	unsigned int codeLenght = 0, dataLength = 0, errorsCorrection = 0, PacketSize = 0, bitsWord = 0;
	double A = 0, V = 0, p = 0.0, a = 0.0;
	Plot cur;
	std::list<Plot>spdpls, delprobpls;

	setparam(protocol, "Chose protocol type\n"
			"Enter 1 - datagramm, 2 - with latency, 3 - backNstep");
	setparam(model, "Выберите поток ошибок\n"
			"Enter 1 - ДСК,, 2 - PA, 3 - ОПП");
	set2params(SessionLenght, BlockSize, "Установите длину сеанса связи и размер криптоблока");
	set2params(CRC,PacketSize, "Установите длину CRC последовательности и количество криптоблоков в кадре");
	BlockSize += CRC;

	set2params(codeLenght, errorsCorrection, "Параметры кода:\nУстановите длину кода n(бит) и"
					" Количество исправляемых ошибок");
	set2params(dataLength, bitsWord, "Установите длину информационной последовательности k(бит) и длину слова(бит)");

	dsk* dk = new dsk(BlockSize, SessionLenght);
	pa* pk = new pa(SessionLenght, BlockSize);
	opp* op = new opp(BlockSize, SessionLenght);
	switch(model)
	{
		case 1:
			setparam(p, "Enter p for single bit:");
			dk->setP(p);
			dk->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			dk->setProtocol(protocol, PacketSize);
			dk->work();
			cur = dk->getPlot();
			spdpls.emplace_back(cur);
			cur = dk->getProbPlot();
			delprobpls.emplace_back(cur);
			break;
		case 2:
			set2params(p, a, "Установите p и a:");
			pk->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			pk->setProtocol(protocol, PacketSize);
			pk->setParams(a,p);
			pk->work();
			cur = pk->getSpeedPlot();
			spdpls.emplace_back(cur);
			cur = pk->getTimePlot();
			delprobpls.emplace_back(cur);
			break;
		case 3:
			set2params(A, V, "Установите A и V:");
			op->setProtocolType(protocol, PacketSize);
			op->setCode(codeLenght, errorsCorrection, dataLength, bitsWord);
			op->setParams(A, V);
			op->work();
			cur = op->getPlot();
			spdpls.emplace_back(cur);
			cur = op->getDelProbPlot();
			delprobpls.emplace_back(cur);
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
