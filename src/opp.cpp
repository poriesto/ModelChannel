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
			datagrammPr();
			break;
		case 2:
			lantecyPr();
			break;
		case 3:
			UINT steps;
			std::cout << "Enter steps for protocol" << std::endl;
			std::cin >> steps;
			backNsteps(steps);
			break;
	}
	std::cout << "======End OPP model======" << std::endl;
}

void opp::backNsteps(UINT steps) {
	UINT Succeful = 0, Unsucceful = 0, errCounter = 0;
	std::vector<Block>ble;
	std::cout << "!******backNsteps Protocol begin******!" << std::endl;
	for(auto value : bl){
	}

	std::cout << "Blocks in session: " << bl.capacity() << std::endl;
	std::cout << "Succeful blocks: " << Succeful << std::endl;
	std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
	std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
	std::cout << "!******backNsteps Protocol end******!" << std::endl;
}

void opp::lantecyPr() {
	UINT Succeful, Unsucceful;
	Succeful = Unsucceful = 0;
	std::cout << "!******Latency protocol begin******!" << std::endl;
	for(auto value : bl){

	}

	std::cout << "Blocks in session: " << bl.capacity() << std::endl;
	std::cout << "Succeful blocks: " << Succeful << std::endl;
	std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
	std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
	std::cout << "!******Latency protocol end******!" << std::endl;
}

void opp::datagrammPr() {
	UINT Succeful, Unsucceful, errCounter;
	Succeful = Unsucceful = errCounter = 0;
	std::vector<Block> ble;
	std::cout << "!******Datagramm protocol begin******!" << std::endl;

	//TODO Need deep check for correction work
	for(auto value : bl){
		for(auto val : value){
			if (val == 1) {
				errCounter++;
			}
		}
		if(errCounter > errosCor){
			Unsucceful ++;
			ble.emplace_back(value);
		}
		else{
			Succeful++;
		}
		errCounter = 0;
	}

		std::cout << "Blocks with errors:" << std::endl;
		printDb(ble);

		double speed = (Succeful*BlockSize)/SessionSize;
		std::cout << "Blocks in session: " << bl.capacity() << std::endl;
		std::cout << "Succeful blocks: " << Succeful << std::endl;
		std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
		std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
		std::cout << "Result speed: " << speed << std::endl;
		std::cout << "!******Datagramm protocol end******!" << std::endl;
}
