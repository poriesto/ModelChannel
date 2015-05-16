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

    for(auto i = 0; i < bytes.size(); i++){
        generator(a,b,r);
        r >= p ? expr1((UINT) i) : expr2((UINT) i);
    }

//    std::cout << "Errors:" << std::endl;
//    print(errors);

    bl = makeBlocks(Blocks, BlockSize, bytes);
	pr = new protocol(bl,code);
	pr->work(dsk::ProtocolType, dsk::PacketSize);
	std::cout << "======End dsk model======" << std::endl;
}
