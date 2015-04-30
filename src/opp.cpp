//
// Created by Alexander on 28.04.2015.
//
#include "opp.h"

UINT opp::GenOppPos(){
		double R, a = 0, b = 1;
		generator(a,b,R);
		double X = (A/pow(R,(1/V))) - A;
		return static_cast<int>(X);
}
void opp::work()
{
	std::cout << "======Begin OPP model======" << std::endl;
	int Pos = GenOppPos();

	for(auto i = 0; i < bytes.capacity(); i++)	{
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

	switch (ProtocolType){
		case 1:
			datagrammProtocol(bl, code);
			break;
		case 2:
			UINT latency;
			setLatency(latency);
			latencyProtocol(bl, code, latency);
			break;
		case 3:
			UINT steps;
			setNsteps(steps);
			backNsteps(bl, code, steps);
			break;
	}
	std::cout << "======End OPP model======" << std::endl;
}
