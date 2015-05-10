//
// Created by Alexander on 28.04.2015.
//
#include "api.hpp"
void printDb(std::vector<std::vector<UINT>> cont){
	for(auto value : cont){
		print(value);
	}
	std::cout << std::endl;
}
bool checkPacket(Packet pk){
	bool result = false;
	UINT Succeful = 0, Unsucceful = 0;
	for(auto value : pk){
		for(auto val : value){
			val == 0 ? Succeful += 1 : Unsucceful += 1;
		}
	}
	result = Unsucceful == 0 ? true : false;
	return result;
}
std::vector<UINT> makeSession(UINT SessionLenght){
	std::vector<UINT> ve;
	ve.resize(SessionLenght);
	std::fill(ve.begin(), ve.end(), 0);
	std::cout << "Bytes in session: " << ve.capacity() << std::endl;
	return ve;
}
std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes){
	std::vector<Block> ve;
	UINT IPOS = 0, EPOS = BlockSize;
	ve.reserve(Blocks);
	for(UINT i = 0; i < Blocks; i++){
		Block bk;
		for(auto i = IPOS; i < EPOS; i++){
			bk.emplace_back(bytes.at(i));
		}
		ve.emplace_back(bk);
		IPOS += BlockSize;
		EPOS += BlockSize;
	}
	return ve;
}
std::vector<Packet> makePackets(UINT PacketSize, UINT Packets, std::vector<Block> v){
	std::vector<Packet>ve;
	UINT IPOS = 0, EPOS = PacketSize;
	ve.reserve(Packets);
	for(UINT i = 0; i < Packets; i++){
		Packet pk;
		for(auto i = IPOS; i < EPOS; i++){
			pk.emplace_back(v.at(i));
		}
		ve.emplace_back(pk);
		IPOS += PacketSize;
		EPOS += PacketSize;
	}
	std::cout << "Packets created: " << ve.capacity() << std::endl;
	return ve;
}
void checkPacketStream(std::vector<Packet> ps, UINT& Succeful, UINT& Unsucceful){
	for(auto value : ps){
		checkPacket(value) ? Succeful += 1 : Unsucceful += 1;
	}
}
void generator(double a, double b, double& num){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);
	num = dis(gen);
}
void generator(UINT a, UINT b, UINT& num){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a,b);
	num = dis(gen);
}
void setNsteps(UINT& steps){
	std::cout << "Enter steps:" << std::endl;
	std::cin >> steps;
}
void setLatency(UINT& latency){
	std::cout << "Enter latency" << std::endl;
	std::cin >> latency;
}
bool checkR(UINT r, UINT a){
	bool result = false;
	r == a ? result = false : result = true;
	return result;
}
/*
 * Protocols
*/
/*
void datagrammProtocol(std::vector<Block>bl, Code code){
	UINT BlockSize = bl.at(0).capacity();
	std::vector<Block>bls, blu;
	//TODO implement datagramm protocol
	std::cout << "!******Datagramm protocol begin******!" << std::endl;
    for(auto value : bl){
		checkBlockErrs(value) == 0 ? bls.emplace_back(value) : blu.emplace_back(value);
	}
	double speed = ((blu.size())*BlockSize)/bl.capacity();
	std::cout << "Blocks in session: " << bl.capacity() << std::endl <<
			"Succeful blocks: " << bls.size() << std::endl <<
			"Unsucceful blocks: " << blu.size() << std::endl <<
			"Percent succeful: " << ((bls.size())*100)/bl.capacity() << std::endl <<
			"Result speed: " << speed << std::endl;
	std::cout << "!******Datagramm protocol end******!" << std::endl;
}*/
void datagrammProtocol(std::vector<Block>bl, Code code){
	UINT BlockSize = bl.at(0).size(), Blocks = bl.size();
	UINT r = 0, attems = 0;
	std::vector<UINT> bls, ble, trams;
	std::cout << "Data start" << std::endl;
	while(true)	{
		generator(0, Blocks, r);
		if( checkBlockErrs(bl[r]) >  0){
			if( checkBlockErrs(bl[r]) > code.errorsCorrection ){
				attems += 1;
				ble.emplace_back(r);
			}
			else{
				bls.emplace_back(r);
			}
		}
		else{
			bls.emplace_back(r);
		}
		if(trams.size() > Blocks){
			break;
		}
		trams.emplace_back(r);
	}
    std::cout << "Transmitted" << std::endl;
	for(auto value : trams){
			std::cout << value << " ";
		}
	double PolBits = bls.size() * BlockSize;
	//double OverallBits = (bls.size() + attems + ble.size()) * BlockSize;
	double OverallBits = (Blocks + attems)*BlockSize; // or OverallBits = transm * BlockSize;
	double speed = PolBits / OverallBits;
	std::cout << "PolBits = " << PolBits << std::endl << "OverallBits = " << OverallBits << std::endl;
	std::cout << "Blocks in session: " << bl.capacity() << std::endl <<
			"Succeful blocks: " << bls.size() << std::endl <<
			"Unsucceful blocks: " << ble.size() << std::endl <<
			"Atems: " << attems << std::endl << 
			"Percent succeful: " << ((bls.size())*100)/bl.capacity() << std::endl <<
			"Result speed: " << speed << std::endl;
	std::cout << "Data end" << std::endl;
}
void backNsteps(std::vector<Block>bl, Code code, UINT steps){
	//TODO implement back n steps protocol
    UINT BlockSize = bl.at(0).capacity();
    std::vector<Block>bls, blu;
    std::cout << "!******BackNstep protocol begin******!" << std::endl;
	for(auto value : bl){
		checkBlockErrs(value) == 0 ? bls.emplace_back(value) : blu.emplace_back(value);
	}
    double speed = ((blu.size())*BlockSize)/bl.capacity();
	std::cout << "Blocks in session: " << bl.capacity() << std::endl <<
			"Succeful blocks: " << bls.size() << std::endl <<
			"Unsucceful blocks: " << blu.size() << std::endl <<
			"Percent succeful: " << ((bls.size())*100)/bl.capacity() << std::endl <<
			"Result speed: " << speed << std::endl;
    std::cout << "!******BackNstep protocol end******!" << std::endl;
}
void latencyProtocol(std::vector<Block>bl, Code code, UINT latency){
	//TODO implement protocol with latency
    std::vector<Block>bls, blu;
    UINT BlockSize = bl.at(0).capacity();
    std::cout << "!******Latency protocol begin******!" << std::endl;
	for(auto value : bl){
		checkBlockErrs(value) == 0 ? bls.emplace_back(value) : blu.emplace_back(value);
	}
    double speed = ((blu.size())*BlockSize)/bl.capacity();
	std::cout << "Blocks in session: " << bl.capacity() << std::endl <<
			"Succeful blocks: " << bls.size() << std::endl <<
			"Unsucceful blocks: " << blu.size() << std::endl <<
			"Percent succeful: " << ((bls.size())*100)/bl.capacity() << std::endl <<
			"Result speed: " << speed << std::endl;
    std::cout << "!******Latency protocol end******!" << std::endl;
}
UINT checkBlockErrs(Block bl){
	UINT errors = 0;
	for(auto value : bl){
		if(value == 1){
			errors+=1;
		}
	}
	return errors;
}
