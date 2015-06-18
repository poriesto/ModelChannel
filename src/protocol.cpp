//
// Created by Alexander on 12.05.2015.
//
#include "protocol.h"
#include <thread>
#include <future>
void protocol::work(UINT type, UINT pkSize) {
	protocol::pkSize = pkSize;
	UINT frames = blocks/pkSize;
	pl = makePackets(pkSize,frames, bl);
	packetSize = blSize*pkSize;
	switch (type){
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
	}
    std::vector<Packet>().swap(pl);
	RecivedPackets = 0; SentPackets = 0; delProbability = 0.0; speed = 0; singleTime = 0.0;
}
void protocol::datagramm() {
	for(auto packet : pl){
		if (checkPacket(packet)){
			if(isCorectable(packet)){
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
std::pair<UINT, UINT> protocol::toAsync(piter beg, piter end){
	std::pair<UINT, UINT>stat_;
	for(auto current = beg; current < end; current++){
		if(checkPacket(*current)){
			if(code.errorsCorrection > 0){
				if(isCorectable(*current)){
					stat_.first +=1;
				}
			}
		}
		else{
			stat_.first += 1;
		}
		stat_.second += 1;
	}
	return stat_;

}
void protocol::latency() {
	piter beg, end;
	beg = pl.begin();
	end = beg + pl.size()/4;
	std::vector<std::future<std::pair<UINT, UINT>>> ran;
	
	for(auto i = 0; i < 4; i++){
		ran.emplace_back(std::async(std::launch::async, &protocol::toAsync, this, beg,end));
		beg = end;
		end += pl.size()/4;
	}
	for(int i = 0; i < ran.size(); i++){
		std::pair<UINT, UINT>current = ran[i].get();
		RecivedPackets += current.first;
		SentPackets += current.second;
	}
    std::vector<std::future<std::pair<UINT,UINT>>>().swap(ran);
	UINT CodeBlockCount = packetSize/code.DataLength;
	double frameSize = blSize*pkSize + (code.DataLength*code.codeLength);
	delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
	speed = static_cast<double>(RecivedPackets*packetSize)/
			static_cast<double>(SentPackets*(blSize*pkSize+
					CodeBlockCount*(code.codeLength-code.DataLength)*code.bitsWord));
	singleTime = (SentPackets*SentPackets)/ (RecivedPackets*frameSize);
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
	int blErrors = 0;
	std::list<std::list<UINT> > words;
	for (auto i = 0; i < block.size() / code.bitsWord; i++) {
		std::list<UINT> word;
		for (auto j = ipos; j < epos; j++) {
			word.emplace_back(block.at(j));
		}
		words.emplace_back(word);
        std::list<UINT>().swap(word);
		ipos += code.bitsWord;
		epos += code.bitsWord;
	}
	int wordERR = 0;
	for (auto word : words) {
		for (auto value : word) {
			 if (value == 1) wordERR+=1;
		 }
		if(wordERR > 0) blErrors +=1;
	}
    std::list<std::list<UINT>>().swap(words);
	return blErrors <= code.errorsCorrection;
}
