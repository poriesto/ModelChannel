#include "api.hpp"

class dsk
{
private:
public:
    dsk(UINT BlockSize, UINT PacketSize, UINT SessionSize) : BlockSize(BlockSize), PacketSize(PacketSize),
                                                             SessionSize(SessionSize) {
        dsk::Blocks = dsk::SessionSize / dsk::BlockSize;
        dsk::Packets = dsk::Blocks / dsk::PacketSize;
    }

    void setP(double p) {
        dsk::p = p;
    }
    void work();
private:
    UINT BlockSize, PacketSize, SessionSize;
    UINT Blocks, Packets;
    double p;
};