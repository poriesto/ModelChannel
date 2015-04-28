//
// Created by Alexander on 28.04.2015.
//
#include "opp.h"

UINT opp::GenOppPos()
	{
		double R, a = 0, b = 1;
		generator(a,b,R);
		double X = (A/pow(R,(1/V))) - A;
		std::cout << "X = " << X << " R = " << R << std::endl	;
		return static_cast<int>(X);
	}
void opp::work()
{
	std::cout << "======Begin OPP model======" << std::endl;
	bytes = makeSession(opp::SessionSize);
	int Pos = GenOppPos();

	for(int i = 0; i < bytes.capacity()-1; i++)	{
		if(Pos == i){
			bytes[i] = 1;
			errorsPos.emplace_back(Pos);
			Pos = i + 1 + GenOppPos();
		}
		else if( Pos != i){
			bytes[i] = 0;
		}
	}

	std::cout << std::endl << "Errors" << std::endl;
	print(errorsPos);
	bl = makeBlocks(Blocks, BlockSize, bytes);

	std::cout << "Blocks:" << std::endl;
	printDb(bl);
	switch (ProtocolType){
		case 1:
			datagrammProtocol(bl, code);
			break;
		case 2:
			UINT latency;
			std::cout << "Enter latency" << std::endl;
			std::cin >> latency;
			latencyProtocol(bl, code, latency);
			break;
		case 3:
			UINT steps;
			std::cout << "Enter steps for protocol" << std::endl;
			std::cin >> steps;
			backNsteps(bl, code, steps);
			break;
	}
	std::cout << "======End OPP model======" << std::endl;
}


