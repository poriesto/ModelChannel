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

    void work();
private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType, PacketSize;
    double p;
    Code code;
    protocol* pr;
    std::vector<UINT>bytes, errors;
    std::vector<Block>bl;
};

#endif //DIPLOM_DSK_H