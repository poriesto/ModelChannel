#include "dsk.hpp"
#include <thread>

void dsk::toTHR(btsiter beg, btsiter end){
	for(auto current = beg; current < end; current++){
		double a=0,b=1,r;
		generator(a,b,r);
		r >= p ? *current = 0:1;
	}
}

void dsk::genBitsArray(){
	std::vector<std::thread> vth;
	btsiter beg,end;
	beg = bytes.begin();
	end = bytes.begin() + bytes.size()/4;
	for(int i = 0; i < 4; i++){
		vth.emplace_back(
				std::thread(&dsk::toTHR, this, beg, end));
		beg += bytes.size()/4;
		end += bytes.size()/4;
	}

	 for(auto &thr : vth){
		thr.join();
	}
}

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
    /*for(auto i = 0; i < bytes.size(); i++){
        generator(a,b,r);
		r >= p ? bytes.at(i) = 0:1;
    }*/

    bl = makeBlocks(Blocks, BlockSize, bytes);
	pr = new protocol(bl,code);
	pr->work(dsk::ProtocolType, dsk::PacketSize);
	std::stringstream res;
	/*for(UINT i = 1; i <= dsk::PacketSize; i+=5){
		pr->work(dsk::ProtocolType, i);
		res << pr->getResults() << "\n";
	}
	 */
    pr->work(dsk::ProtocolType, 1);
    res << pr->getResults() << "\n";
	saveToFile(res.str());
	dsk::plot = pr->getPlot();
	dsk::delProbPlot = pr->getDelProbPlot();
	std::cout << "======End dsk model======" << std::endl;
	std::stringstream bits;
    for(auto value : bytes){
    	bits << value << " ";
    }
	std::string bitsName = "ErrorsStreamDSK.txt";
    std::ofstream f;
    f.open(bitsName);
    f.write(bits.str().c_str(), sizeof(char)*bits.str().size()); 
    f.close();
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
