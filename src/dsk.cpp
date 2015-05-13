#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	double a = 0, b = 1, r;
    auto expr1 = [this](UINT index){
        bytes.at(index) = 0;
    };
    auto expr2 = [this](UINT index){
        bytes.at(index) = 1;
        errors.emplace_back(index);
    };
/*
    for(auto& value : bytes){
        generator(a,b, r);
        //r < dsk::p ? value = 0 : value = 1;
        r > p ? value = 0 : value = 1;
    }*/
    for(auto i = 0; i < bytes.size(); i++){
        generator(a,b,r);
        r > p ? expr1(i) : expr2(i);
    }

    std::cout << "Errors:" << std::endl;
    print(errors);
/*    for(auto i = 0; i < bytes.size(); i++){
        bytes.at(i) == 1 ? dsk::errors.emplace_back(i) : dsk::corElems.emplace_back(i);
    }
*/
	bl = makeBlocks(Blocks, BlockSize, bytes);
	pr = new protocol(bl,code);
	pr->work(dsk::ProtocolType, dsk::PacketSize);
	std::cout << "======End dsk model======" << std::endl;
}
