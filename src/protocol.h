//
// Created by Alexander on 12.05.2015.
//
#include "api.hpp"
#ifndef DIPLOM_PROTOCOL_H
#define DIPLOM_PROTOCOL_H

class protocol {

public:
	protocol(const std::vector<Block> &bl, const Code &code) : bl(bl), code(code) {
		protocol::blSize = (UINT) protocol::bl.begin()->size();
		protocol::blocks = (UINT) protocol::bl.size();
	}
	virtual ~protocol() { }

	const std::string &getResults() const {
		return results;
	}

	const Plot &getPlot() const {
		return plot;
	}
	const Plot &getDelProbPlot() const{
		return delProbPlot;
	}
	void work(UINT type, UINT pkSize);
private:
	std::vector<Block>bl;
	std::vector<Packet>pl;
	std::string results;
	Code code;
	Plot plot, delProbPlot;
	double speed = 0.0, delProbability = 0.0, singleTime = 0.0;
	UINT blSize, blocks, pkSize, RecivedPackets = 0, SentPackets = 0;
	UINT blErrors = 0, packetSize;

	void datagramm();
	void latency();
	void Nstep();

	bool isCorectable(Packet packet);
	bool checkPacket(Packet packet);
	UINT checkBlockErrors(Block bl);
	bool isCorrectiableBlock(Block block);
};


#endif //DIPLOM_PROTOCOL_H
