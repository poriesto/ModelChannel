#include "dsk.hpp"
#include <thread>
#include <future>

std::vector<UINT> dsk::toAsync(int size) {
    std::vector<UINT>v(size);
    for(auto cur = v.begin(); cur < v.end(); cur++){
        double a = 0, b = 0, r;
        generator(a,b,r);
        r >= p ? *cur = 0:1;
    }
    return v;
}

void dsk::genBitsArray(){
    int size = SessionSize/4;
    std::vector<std::future<std::vector<UINT>>> ran;
    for(int i = 0; i < 4; i++){
        ran.emplace_back(std::async(std::launch::async, &dsk::toAsync, this, size));
    }
    for(auto it = ran.begin(); it < ran.end(); it++){
        std::vector<UINT> cur = it->get();
        bytes.insert(bytes.end(), cur.begin(), cur.end());
        std::vector<UINT>().swap(cur);
    }
    bl = makeBlocks(Blocks, BlockSize, bytes);
    std::vector<UINT>().swap(bytes);
    std::vector<std::future<std::vector<UINT>>>().swap(ran);
}

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	pr = new protocol(bl,code);
	pr->work(dsk::ProtocolType, dsk::PacketSize);
	std::stringstream res;
	for(UINT i = 1; i <= dsk::PacketSize; i+=5){
		pr->work(dsk::ProtocolType, i);
		res << pr->getResults() << "\n";
	}
	saveToFile(res.str());
	dsk::plot = pr->getPlot();
	dsk::delProbPlot = pr->getDelProbPlot();
	std::cout << "======End dsk model======" << std::endl;
}
void dsk::saveToFile(std::string str) {
std::stringstream ostr;
	ostr << "Модель канала ДСК p =  " << p <<"\n"
		<< str << "\n";
	std::cout << ostr.str() << std::endl;
	std::ofstream fout;
	std::stringstream fname;
	fname << "DSK_model p = " << p << " code(" << code.codeLength << ", " << code.DataLength <<
	", " << code.errorsCorrection << ", " << code.bitsWord << ")" << ".txt";
	fout.open(fname.str());
	fout.write(ostr.str().c_str(), sizeof(char)*ostr.str().size());
	fout.close();
}
