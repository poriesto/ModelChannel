//
// Created by Alexander on 28.04.2015.
//
#include "opp.h"
#include <future>

std::vector<UINT> opp::toAsync(UINT size) {
    std::vector<UINT> v(size);
    int Pos = GenOppPos();
    for (int i = 0; i < v.size(); i++) {
        if (Pos == i) {
            v.at(i) = 1;
            Pos = i + 1 + GenOppPos();
        }
        else {
            v.at(i);
        }
    }
    return v;
}

void opp::genBitArray() {
    int size = SessionSize / 4;
    std::vector<std::future<std::vector<UINT>>> ran;
    for (int i = 0; i < 4; i++) {
        ran.emplace_back(std::async(std::launch::async, &opp::toAsync, this, size));
    }
    for (auto it = ran.begin(); it < ran.end(); it++) {
        std::vector<UINT> cur = it->get();
        bytes.insert(bytes.end(), cur.begin(), cur.end());
        std::vector<UINT>().swap(cur);
    }
    std::cout << "Bits size = " << bytes.size();
    bl = makeBlocks(Blocks, BlockSize, bytes);
    std::vector<UINT>().swap(bytes);
    std::vector<std::future<std::vector<UINT>>>().swap(ran);
}

UINT opp::GenOppPos() {
    double R, a = 0, b = 1;
    generator(a, b, R);
    double X = (A / pow(R, (1 / V))) - A;
    return static_cast<UINT>(X);
}

void opp::work() {
    pr = new protocol(bl, code);
    std::stringstream res;
    for (UINT i = 1; i <= PacketSize; i += 1) {
        pr->work(ProtocolType, i);
        res << pr->getResults() << "\n";
    }
    saveToFile(res.str());
    opp::plot = pr->getPlot();
    opp::delProbPlot = pr->getDelProbPlot();
}

void opp::saveToFile(std::string str) {
    std::stringstream ostr;
    ostr << "Модель канала ОПП с параметрами A = " << A << ", V = " << V << "\n"
    << str << "\n";
    std::cout << ostr.str() << std::endl;
    std::ofstream fout;
    std::stringstream fname;
    fname << "OPP_model A = " << A << ", V = " << V << " code(" << code.codeLength << ", " << code.DataLength <<
    ", " << code.errorsCorrection << ", " << code.bitsWord << ")" << ".txt";
    fout.open(fname.str());
    fout.write(ostr.str().c_str(), sizeof(char) * ostr.str().size());
    fout.close();
}
