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

//create Block from std::vector<UINT>
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

//create Packets from std::vector<Block>
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

//random generator from a to b
void generator(double a, double b, double& num){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);
	num = dis(gen);
}

//transform code to std::string
std::string Code_toStr(Code code){
	std::stringstream str;
	str << code.name << " (" << code.codeLength << ", " << code.DataLength << ", "
	<< code.errorsCorrection << ", " << code.bitsWord << ")";
	return str.str();
}

//read correction codes list from file
std::list<Code> loadFromFile(std::string file) {
    std::list<Code> codeList;
    std::ifstream ifile;
    std::string buf;
    Code tmp;

    ifile.open(file);
    if(ifile.is_open() && !ifile.fail()){
        while(!ifile.eof()) {
            std::getline(ifile, buf);
            tmp = CodeFromSTR(buf);
            codeList.emplace_back(tmp);
        }
        ifile.close();
    }
    else{
        throw(ifile.bad());
    }
    return codeList;
}

//Crearte correction code from std::string
Code CodeFromSTR(std::string str) {
    Code code;
    unsigned int pos = 0, cpos = 0;

    //find name in string
    cpos = (unsigned int) str.find(" ", pos);
    code.name = str.substr(pos, cpos - pos);
    //find in string code lenght
    pos = cpos+1; cpos = (unsigned int) str.find((" "), pos);
    code.codeLength = (UINT) atoi( str.substr(pos, cpos - pos).c_str() );
    //find in string data len
    pos = cpos+1; cpos = (unsigned int) str.find(" ", pos);
    code.DataLength = (UINT)atoi(str.substr(pos, cpos - pos).c_str());
    //find in string errors correction
    pos = cpos+1; cpos = (unsigned int) str.find(" ", pos);
    code.errorsCorrection = (UINT)atoi(str.substr(pos, cpos - pos).c_str());
    //find bits word
    pos = cpos+1; cpos = (unsigned int) str.find(" ", pos);
    code.bitsWord = (UINT)atoi(str.substr(pos, cpos-pos).c_str());

    return code;
}
