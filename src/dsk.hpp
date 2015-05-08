#include "api.hpp"
//TODO need work now
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
        dsk::protocol = protocol;
    }

    void work();
private:
    UINT BlockSize, SessionSize, Blocks, protocol;
    double p;
    Code code;
    std::vector<UINT>bytes, errors, corElems;
    std::vector<Block>bl;
};