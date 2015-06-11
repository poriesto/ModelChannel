//
// Created by Alexander on 07.06.2015.
//

#include "Cuboid.h"

SpisokPaketov Cuboid::makespisok(void) {

    SpisokPaketov V;
    for (int i = begin; i < end; i++) {
        V.push_back(pl[i]);
    }
    begin = end;
    if (end != pl.size()){
        end += size;
    } else {
        end = pl.size();
    }
    return V;
}

Matrisa Cuboid::makematrix(void) {
    Matrisa M;
     for (int i = 0; i < size; i ++){
        M.push_back(makespisok());
       CRC_row[i] = summRow(M.back());
    }
    CRC_r.push_back(CRC_row);
    return M;
}

void Cuboid::MakeCube() {
   CRC_coll.resize(size);
   CRC_row.resize(size);
    for (int i = 0; i < size; i++){
        data.push_back(makematrix());
    }
   for (auto cu : data){
        for (int j = 0; j < size; j++){
            SpisokPaketov col;
            for (int i = 0; i < size; i++){
                col.push_back(cu[j][i]);
            }
            CRC_coll[j] = summRow(col);
        }
       CRC_c.push_back(CRC_coll);
    }
}

int Cuboid::summPacket(Packet cur) {
    int crcsum = 0;
    for (auto block : cur){
        for (auto bit : block){
            crcsum ^= bit;
        }
    }
    return crcsum;
}

int Cuboid::summRow(SpisokPaketov cur) {
    int crc = 0;
    for (auto pk : cur){
        crc += summPacket(pk);
    }
    return crc;
}

void Cuboid::print1() {

    for (auto m : data){
        std::cout<<"gran'"<<std::endl;
        for (auto v : m){
            std::cout<<"stroka"<<std::endl;
            for (auto s : v){
                std::cout<<"packet";
                for (auto p :s ){
                    std::cout << "block:";
                    for(auto b : p){
                        std::cout << b;
                    }
                }
            }

        }
    }
    std::cout << std::endl;
    std::cout << "gshjkgfsjdfdsa"<< std::endl<< std::endl<< std::endl;
    printtcrc();
   // print(CRC_row);
    std::cout << "gshjkgfsjdfdsa"<< std::endl<< std::endl<< std::endl;
}

void Cuboid::printtcrc() {
    for (auto crc_v : CRC_r){
        print(crc_v);
    }
    std::cout<<std::endl;
    for (auto crc_v : CRC_c){
        print(crc_v);
    }
}
