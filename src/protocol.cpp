//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"
#include <thread>
#include <list>
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
	pl.erase(pl.begin(), pl.end());
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
//for thread
void protocol::toTHR(piter begin, piter end){
	bool CoruptedPacket, CorrectablePacket;
	for(auto current = begin; current < end; current++){
		CoruptedPacket = checkPacket(*current);
		if(CoruptedPacket){
			if(code.errorsCorrection > 0){
				CorrectablePacket = isCorectable(*current);
				if(CorrectablePacket){
					RecivedPackets +=1;
				}
			}
		}
		else{
			RecivedPackets += 1;
		}
		SentPackets += 1;
	}
}
std::pair<UINT, UINT> protocol::toAsync(piter beg, piter end){
	std::pair<UINT, UINT>stat_;
	std::cout << "Start Async thread" << std::endl;
	bool CoruptedPacket, CorrectablePacket;
	for(auto current = beg; current < end; current++){
		CoruptedPacket = checkPacket(*current);
		if(CoruptedPacket){
			if(code.errorsCorrection > 0){
				CorrectablePacket = isCorectable(*current);
				if(CorrectablePacket){
					stat_.first +=1;
				}
			}
		}
		else{
			stat_.first += 1;
		}
		stat_.second += 1;
	}
	std::cout << "End async thread" << std::endl;
	/*std::cout << "Recursive call start" << std::endl;
	piter mid = beg + pl.size()/2;
	auto hnd = std::async(std::launch::async, &protocol::toAsync, this, mid, end);
	std::pair<UINT, UINT> stat__ = toAsync(beg, mid);
	stat__.first += hnd.get().first;
	stat__.second += hnd.get().second;
	std::cout << "Recursive call end" << std::endl;
	*/
	return stat_;

}
//TODO need hard fix
void protocol::latency() {
	/*piter beg, end;
	int offset = pl.size()/4;
	beg = pl.begin(); end = beg + offset;

	std::vector<std::thread>vth;
	for(int i = 0; i < 4; i++){
		vth.emplace_back(
				std::thread(&protocol::toTHR, this, beg, end));
		beg = end;
		end += offset;
	}
	for(auto &thr : vth){
		//thr.join();
		if(thr.joinable()){
			thr.join();
		}
	}*/
	//toTHR(pl.begin(), pl.end());
	std::cout << "Start protocol work" << std::endl;
	//toAsync(pl.begin(), pls.end());
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
	UINT CodeBlockCount = packetSize/code.DataLength;
	double frameSize = blSize*pkSize + (code.DataLength*code.codeLength);
	delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
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
	//vth.erase(vth.begin(), vth.end());
	results = ss.str();
	plot.speed.emplace_back(speed);
	plot.FrameSize.emplace_back(packetSize);
	plot.code = protocol::code;
	delProbPlot.speed.emplace_back(delProbability);
	delProbPlot.FrameSize.emplace_back(packetSize);
	delProbPlot.code = protocol::code;
	ran.erase(ran.begin(), ran.end());
	std::cout << "End protocol work" << std::endl;
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
	return blErrors <= code.errorsCorrection;
}
