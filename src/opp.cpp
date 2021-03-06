//
// Created by Alexander on 28.04.2015.
//
#include "opp.h"
UINT opp::GenOppPos(){
		double R, a = 0, b = 1;
		generator(a,b,R);
		double X = (A/pow(R,(1/V))) - A;
		return static_cast<UINT>(X);
}
void opp::work()
{
	std::cout << "======Begin OPP model======" << std::endl;
	Pos = GenOppPos();
	for(auto i = 0; i < bytes.capacity(); i++)	{
		if(Pos == i){
			bytes[i] = 1;
			errorsPos.emplace_back(Pos);
			Pos = i + 1 + GenOppPos();
		}
		else if( Pos != i){
			bytes[i] = 0;
		}
	}

    bl = makeBlocks(Blocks, BlockSize, bytes);
    pr = new protocol(bl,code);
	std::stringstream res;
	for(UINT i = 1; i <= PacketSize; i+=2){
		pr->work(ProtocolType, i);
		res << pr->getResults() << "\n";
	}
	saveToFile(res.str());
	opp::plot = pr->getPlot();
	opp::delProbPlot = pr->getDelProbPlot();
    std::cout << "======End OPP model======" << std::endl;
    std::stringstream bits;
    for(auto value : bytes){
    	bits << value << " ";
    }
    std::string bitsName = "ErrorsStreamOPP.txt";
    std::ofstream f;
    f.open(bitsName);
    f.write(bits.str().c_str(), sizeof(char)*bits.str().size()); 
    f.close();
}
void opp::saveToFile(std::string str) {
	std::stringstream ostr;
	ostr << "Модель канала ОПП с параметрами A = " << A << ", V = " << V <<"\n"
		<< str << "\n";
	std::cout << ostr.str() << std::endl;
	std::ofstream fout;
	std::stringstream fname;
	fname << "OPP_model A = " << A << ", V = " << V  << " code(" << code.codeLength << ", " << code.DataLength <<
	", " << code.errorsCorrection << ", " << code.bitsWord << ")" <<".txt";
	fout.open(fname.str());
	fout.write(ostr.str().c_str(), sizeof(char)*ostr.str().size());
	fout.close();
}