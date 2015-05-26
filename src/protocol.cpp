//
// Created by Alexander on 12.05.2015.
//
//TODO need implement Nstep and latency protocol
#include "protocol.h"
#include <list>

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
	std::cout << "Deleviring probability: " << delProbability << std::endl <<
				 "Speed: " << speed << std::endl;
}
//TODO need hard fix
void protocol::latency() {
	bool CoruptedPacket, CorrectablePacket;

	for(auto packet : pl){
		CoruptedPacket = checkPacket(packet);
		if(CoruptedPacket){
			CorrectablePacket = isCorectable(packet);
			if(CorrectablePacket){
				RecivedPackets += 1;
			}
		}
		else{
			RecivedPackets += 1;
		}
		SentPackets += 1;
	}
	double frameSize = blSize*pkSize + (code.DataLength*code.codeLength);
	delProbability = static_cast<double >(RecivedPackets) / static_cast<double>(SentPackets);
	speed = (static_cast<double>(RecivedPackets)/ static_cast<double>(SentPackets))*frameSize;
	singleTime = static_cast<double>(SentPackets*SentPackets)/ static_cast<double>(RecivedPackets*frameSize);
	std::stringstream ss;
	ss <<"��� (" << to_str(code.codeLength) << ", " << to_str(code.DataLength) << ", " << to_str(code.errorsCorrection) << ", " << to_str(code.bitsWord) << ")\n"
		<< "������ �����, ��� = " << blSize << "\n���������� ������ � ����� = " << pkSize
		<< "\n���������� ������ = " << to_str(SentPackets)
		<< "\n������� ������ = " << to_str(RecivedPackets)
		<< "\n�������� �������� = " << to_str(speed)
		<< "\n����������� �������� ����� = " << to_str(delProbability)
		<< " \n������� ����� �������� = " << to_str(singleTime);
	results = ss.str();
	/*std::cout << results << std::endl;*/
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
/*
bool protocol::isCorrectiableBlock(Block block) {
	UINT ipos = 0, epos = code.bitsWord;
	blErrors = 0;
	if(code.bitsWord > 1) {
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
	}
	else{
		blErrors = checkBlockErrors(block);
	}
	return blErrors <= code.errorsCorrection;
}
*/
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
	return blErrors <= code.errorsCorrection;
}
