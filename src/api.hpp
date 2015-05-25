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
	UINT codeLength;
	UINT DataLength;
	UINT errorsCorrection;
    UINT bitsWord;
};
template<typename T>
void print(T cont){
	UINT conter = 0;
	for(auto value : cont){
		if(conter == STRING_LENGHT){
			std::cout << std::endl;
			conter = 0;
		}
		std::cout << value << " ";
		conter++;
	}
	std::cout << std::endl;
}
std::vector<UINT> makeSession(UINT SessionLenght);
std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes);
std::vector<Packet> makePackets(UINT PacketSize, UINT Packets, std::vector<Block> v);
void generator(double a, double b, double& num);
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
