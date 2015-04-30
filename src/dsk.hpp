#include "api.hpp"

class dsk
{
private:
public:
    dsk(UINT BlockSize, UINT PacketSize, UINT SessionSize) : BlockSize(BlockSize), PacketSize(PacketSize),
                                                             SessionSize(SessionSize) {
        dsk::Blocks = dsk::SessionSize / dsk::BlockSize;
        dsk::Packets = dsk::Blocks / dsk::PacketSize;
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
    UINT BlockSize, PacketSize, SessionSize;
    UINT Blocks, Packets, protocol;
    Code code;
    std::vector<UINT>bytes;
    std::vector<Block>bl;
    std::vector<Packet>pl;
    double p;
};