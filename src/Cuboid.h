//
// Created by Alexander on 07.06.2015.
//

#ifndef DIPLOM_CUBOID_H
#define DIPLOM_CUBOID_H
#include "api.hpp"
typedef  std::vector<Packet> SpisokPaketov;
typedef  std::vector<std::vector <Packet> > Matrisa;
typedef  std::vector<Matrisa> Cub;

class Cuboid {

public:
    Cuboid(int size, SpisokPaketov &pl) : size(size), pl(pl)
    {
        begin = 0;
        end  = size;
    }

    const Cub &getData() const {
        return data;
    }

    void print1();
    void printtcrc();
   virtual ~Cuboid() { }
   void MakeCube();
private:
    std::vector<int> CRC_row;
    std::vector<std::vector<int>> CRC_r;
    std::vector<std::vector<int>> CRC_c;
    std::vector<int> CRC_coll;//
    // int crcsum = 0;
    int size;
    int begin, end;
    SpisokPaketov pl;
    Matrisa matrix;
    Cub data;

    SpisokPaketov makespisok (void);
    Matrisa makematrix (void);
    int summPacket(Packet cur);
    int summRow(SpisokPaketov cur);
};


#endif //DIPLOM_CUBOID_H

