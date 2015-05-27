//Created by Alexander

#include "pa.h"
#include <list>
struct params{
	double a;
	double p;
};

int main(){
	UINT SesionSize = 10000000, BlockSize = 150;
	pa* pk = new pa(SesionSize, BlockSize);

    std::list<Code>codeList;
    Code code;
    code.codeLength = 31; code.DataLength = 11; code.errorsCorrection = 5; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 16; code.errorsCorrection = 3; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 23; code.DataLength = 17; code.errorsCorrection = 3; code.bitsWord = 8;
    codeList.emplace_back(code);

    code.codeLength = 63; code.DataLength = 57; code.errorsCorrection = 1; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 26; code.errorsCorrection = 1; code.bitsWord = 1;
    codeList.emplace_back(code);

    code.codeLength = 31; code.DataLength = 21; code.errorsCorrection = 2; code.bitsWord = 1;
    codeList.emplace_back(code);
	
	params P;
	std::list<params>pList;
	
	P.a = 1.1; P.p = 0.9;
	pList.emplace_back(P);
	
	P.a = 1.1; P.p = 0.9;
	pList.emplace_back(P);
	
	P.a = 1.1; P.p = 0.9;
	pList.emplace_back(P);
	
	for(auto codeTst : codeList){
		for(auto param : pList){
			pk->setCode(codeTst);
			pk->setProtocol(2, 16);
			pk->setParams(param.a, param.p);
			pk->work();
		}
	}

	return 0;
}

