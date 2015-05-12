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
    void setCode(Code const &code) {
        dsk::code = code;
    }
    void setCode(UINT codeleght, UINT correction){
        dsk::code.codeLegth = codeleght;
        dsk::code.errorsCorrection = correction;
    }
    void setProtocol(UINT protocol) {
        dsk::ProtocolType = protocol;
    }

    void work();
private:
    UINT BlockSize, SessionSize, Blocks, ProtocolType;
    double p;
    Code code;
    protocol* pr;
    std::vector<UINT>bytes, errors;
    std::vector<Block>bl;
};

#endif //DIPLOM_DSK_H