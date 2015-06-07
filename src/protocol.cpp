//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"
#include <list>
#include "Cuboid.h"
#include <array>
void protocol::work(UINT type, UINT pkSize) {
	protocol::pkSize = pkSize;
	UINT frames = blocks/pkSize;
	pl = makePackets(pkSize,frames, bl);
	packetSize = blSize*pkSize;
    std::cout << "pl size = " << pl.size()<< std::endl;
    Cuboid *cub = new Cuboid(5, pl);
    cub->MakeCube();
    cub->print1();
	/*switch (type){
		case 1:
			datagramm();
			break;
		case 2:
			latency();
			break;
		case 3:
			Nstep();
			break;
		default:
			std::cout << "Set correct params" << std::endl;
			break;
	}*/
	pl.erase(pl.begin(), pl.end());
    //delete[] cub;
	RecivedPackets = 0; SentPackets = 0; delProbability = 0.0; speed = 0; singleTime = 0.0;
}
void protocol::datagramm() {
	bool CoruptedPacket, CorrectablePacket;
	for(auto packet : pl){
		CoruptedPacket = checkPacket(packet);
		if (CoruptedPacket){
			CorrectablePacket = isCorectable(packet);
			if(CorrectablePacket){
				RecivedPackets+=1;
			}
		}
		else{
			RecivedPackets+=1;
		}
		SentPackets+=1;
	}
	std::cout << "Sent Packets = " << SentPackets << " RecivedPackets = " << RecivedPackets << std::endl;
	delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
	speed = delProbability*RecivedPackets/SentPackets;
	speed = speed*packetSize;
	plot.speed.emplace_back(speed);
	plot.FrameSize.emplace_back(packetSize);
	plot.code = protocol::code;
	std::cout << "Deleviring probability: " << delProbability << std::endl <<
				 "Speed: " << speed << std::endl;
}
//TODO need hard fix
void protocol::latency() {
	bool CoruptedPacket, CorrectablePacket;

	for(auto packet : pl){
		CoruptedPacket = checkPacket(packet);
		if(CoruptedPacket){
			if(code.errorsCorrection > 0) {
				CorrectablePacket = isCorectable(packet);
				if (CorrectablePacket) {
					RecivedPackets += 1;
				}
			}
		}
		else{
			RecivedPackets += 1;
		}
		SentPackets += 1;
	}
	UINT CodeBlockCount = packetSize/code.DataLength;
	double frameSize = blSize*pkSize + (code.DataLength*code.codeLength);
	delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
	//speed = (static_cast<double>(RecivedPackets)/ static_cast<double>(SentPackets))*frameSize;
	speed = static_cast<double>(RecivedPackets*packetSize)/
			static_cast<double>(SentPackets*(blSize*pkSize+
					CodeBlockCount*(code.codeLength-code.DataLength)*code.bitsWord));
	singleTime = static_cast<double>(SentPackets*SentPackets)/ static_cast<double>(RecivedPackets*frameSize);
	std::stringstream ss;
	ss <<"Код (" << to_str(code.codeLength) << ", " << to_str(code.DataLength) << ", " << to_str(code.errorsCorrection) << ", " << to_str(code.bitsWord) << ")\n"
		<< "Размер блока, бит = " << blSize << "\nКоличество блоков в кадре = " << pkSize
		<< "\nОтправлено кадров = " << to_str(SentPackets)
		<< "\nПринято кадров = " << to_str(RecivedPackets)
		<< "\nСкорость передачи = " << to_str(speed)
		<< "\nВероятность доставки кадра = " << to_str(delProbability)
		<< " \nСреднее время задержки = " << to_str(singleTime);
	results = ss.str();
	plot.speed.emplace_back(speed);
	plot.FrameSize.emplace_back(packetSize);
	plot.code = protocol::code;
	delProbPlot.speed.emplace_back(delProbability);
	delProbPlot.FrameSize.emplace_back(packetSize);
	delProbPlot.code = protocol::code;
}
void protocol::Nstep() {
}

bool protocol::isCorectable(Packet packet) {
	UINT corupted = 0;
	for(auto block : packet) if(isCorrectiableBlock(block)) corupted += 1;
	return corupted == 0;
}
bool protocol::checkPacket(Packet packet) {
	UINT corupted = 0;
	for(auto block : packet) if (checkBlockErrors(block) > 0) corupted+=1;
	return corupted > 0;
}
UINT protocol::checkBlockErrors(Block bl) {
	UINT errors = 0;
	for(auto value : bl) if(value == 1) errors+=1;
	return errors;
}
bool protocol::isCorrectiableBlock(Block block) {
	UINT ipos = 0, epos = code.bitsWord;
	blErrors = 0;
	std::list<std::list<UINT> > words;
	for (auto i = 0; i < block.size() / code.bitsWord; i++) {
		std::list<UINT> word;
		for (auto j = ipos; j < epos; j++) {
			word.emplace_back(block.at(j));
		}
		words.emplace_back(word);
		ipos += code.bitsWord;
		epos += code.bitsWord;
	}
	for (auto word : words) {
		for (auto value : word) {
			 if (value == 1) blErrors+=1;
		 }
	}
	if (code.errorsCorrection == 0){
		return blErrors <= 0;
	}
	return blErrors <= code.errorsCorrection;
}
void protocol::makeCub(int size) {
   /* for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int e = 0; e < size; ++e) {
                cub1[i][j][e] = pl[e+i];
            }
        }
    }*/
    for(int i = 0; i < size; i++){
        cub1.push_back(
                genVecVecPac(size));
    }
}
void protocol::printcube(Cuboid cub) {
    for(auto vale : cub.getData()){
        for(auto ve : vale){
            for(auto v : vale){
                for(auto g : v){
                    for(auto h : g){
                        for(auto j : h){
                            std::cout << j;
                        }
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}