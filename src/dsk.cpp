#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	double a = 0, b = 1, r;

    for(auto& value : bytes){
        generator(a,b, r);
        r < dsk::p ? value = 0 : value = 1;
    }
/*    for(auto i = 0; i < bytes.size(); i++){
        bytes.at(i) == 1 ? dsk::errors.emplace_back(i) : dsk::corElems.emplace_back(i);
    }
*/
	bl = makeBlocks(Blocks, BlockSize, bytes);
	pr = new protocol(bl,code);
	pr->work(dsk::ProtocolType);
	std::cout << "======End dsk model======" << std::endl;
}
