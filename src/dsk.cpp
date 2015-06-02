#include "dsk.hpp"

void dsk::work() {
	std::cout << "======Begin dsk model======" << std::endl;
	double a = 0, b = 1, r;

    for(auto i = 0; i < bytes.size(); i++){
        generator(a,b,r);
		r >= p ? bytes.at(i) = 0:1;
    }

    bl = makeBlocks(Blocks, BlockSize, bytes);
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
