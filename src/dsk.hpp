#include "api.hpp"
#include "protocol.h"
#ifndef DIPLOM_DSK_H
#define DIPLOM_DSK_H

class dsk
{
private:
public:
    dsk(UINT BlockSize, UINT SessionSize) : BlockSize(BlockSize), SessionSize(SessionSize) {
        dsk::Blocks = dsk::SessionSize / dsk::BlockSize;
        dsk::bytes = makeSession(dsk::SessionSize);
    }
    virtual ~dsk() { }
    void setP(double p) {
        dsk::p = p;
    }
    void genBitsArray();
    void setCode(UINT codeleght, UINT correction, UINT data, UINT bitsWord){
        dsk::code.codeLength = codeleght;
        dsk::code.DataLength = data;
        dsk::code.errorsCorrection = correction;
        dsk::code.bitsWord = bitsWord;
    }
    void setProtocol(UINT protocol, UINT PacketSize) {
        dsk::ProtocolType = protocol;
        dsk::PacketSize = PacketSize;
    }

    void setCode(const Code &code) {
        dsk::code = code;
    }
    const Plot &getPlot() const{
        return plot;
    }
    const Plot &getProbPlot() const{
        return delProbPlot;
    }
    void work();
private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType, PacketSize;
    double p;
    Code code;
    Plot plot, delProbPlot;
    protocol* pr;
    std::vector<UINT>bytes;
    std::vector<Block>bl;
    void saveToFile(std::string str);
    std::vector<UINT> toAsync(int size);
};

#endif //DIPLOM_DSK_H
