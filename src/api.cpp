//
// Created by Alexander on 28.04.2015.
//
#include "api.hpp"

std::vector<UINT> makeSession(UINT SessionLenght){
	std::vector<UINT> ve;
	ve.resize(SessionLenght);
	std::fill(ve.begin(), ve.end(), 0);
	return ve;
}
std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes){
	std::vector<Block> ve;
	UINT IPOS = 0, EPOS = BlockSize;
	ve.reserve(Blocks);
	for(UINT i = 0; i < Blocks; i++){
		Block bk;
		for(auto j = IPOS; j < EPOS; j++){
			bk.emplace_back(bytes.at(j));
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
		for(auto j = IPOS; j < EPOS; j++){
			pk.emplace_back(v.at(i));
		}
		ve.emplace_back(pk);
		IPOS += PacketSize;
		EPOS += PacketSize;
	}
	return ve;
}
void generator(double a, double b, double& num){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);
	num = dis(gen);
}
std::string Code_toStr(Code code){
	std::stringstream str;
	str << "(" << code.DataLength << ", " << code.DataLength << ", "
	<< code.errorsCorrection << ", " << code.bitsWord << ")";
	return str.str();
}