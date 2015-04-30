#ifndef DIPLOM_API_HPP
#define DIPLOM_API_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

typedef unsigned int UINT;
const UINT STRING_LENGHT = 40;
typedef std::vector<UINT> Block;
typedef std::vector<Block> Packet;
struct Code{
	UINT errorsCorrection;
	UINT codeLegth;
};

void print(std::vector<UINT> cont);
void printDb(std::vector<std::vector<UINT>> cont);
bool checkPacket(Packet pk);
std::vector<UINT> makeSession(UINT SessionLenght);
std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes);
std::vector<Packet> makePackets(UINT PacketSize, UINT Packets, std::vector<Block> v);
void checkPacketStream(std::vector<Packet> ps, UINT& Succeful, UINT& Unsucceful);
void generator(double a, double b, double& num);
std::vector<UINT> decodeBMA(std::vector<UINT>bytes);
void datagrammProtocol(std::vector<Block>bl, Code code);
void backNsteps(std::vector<Block>bl, Code code, UINT steps);
void latencyProtocol(std::vector<Block>bl, Code code, UINT latency);
void setNsteps(UINT& steps);
void setLatency(UINT& latency);
template <typename T>
void set2params(T& param1, T& param2, std::string message){
	std::cout << message << std::endl;
	std::cin >> param1;
	std::cin >> param2;
}
template <typename T>
void setparam(T& param, std::string message){
	std::cout << message << std::endl;
	std::cin >> param;
}
#endif //DIPLOM_API_HPP
