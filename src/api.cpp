//
// Created by Alexander on 28.04.2015.
//
#include "api.hpp"

void print(std::vector<UINT> cont)
{
	UINT counter = 0;
	for(auto value : cont)
	{
		if (counter == STRING_LENGHT)
		{
			std::cout << std::endl;
			counter = 0;
		}
		std::cout << value << " ";
		counter++;
	}
	std::cout << std::endl;
}
void printDb(std::vector<std::vector<UINT>> cont)
{
	for(auto value : cont)
	{
		print(value);
	}
	std::cout << std::endl;
}

bool checkPacket(Packet pk)
{
	bool result = false;
	UINT Succeful = 0, Unsucceful = 0;
	for(auto value : pk)
	{
		for(auto val : value)
		{
			val == 0 ? Succeful += 1 : Unsucceful += 1;
		}
	}
	result = Unsucceful == 0 ? true : false;
	return result;
}

std::vector<UINT> makeSession(UINT SessionLenght)
{
	std::vector<UINT> ve;
	ve.resize(SessionLenght);
	std::fill(ve.begin(), ve.end(), 0);
	std::cout << "Bytes in session: " << ve.capacity() << std::endl;
	return ve;
}

std::vector<Block> makeBlocks(UINT Blocks, UINT BlockSize, std::vector<UINT>bytes)
{
	std::vector<Block> ve;
	UINT IPOS = 0, EPOS = BlockSize;
	ve.reserve(Blocks);
	for(UINT i = 0; i < Blocks; i++)
	{
		Block bk;
		for(auto i = IPOS; i < EPOS; i++)
		{
			bk.emplace_back(bytes.at(i));
		}
		ve.emplace_back(bk);
		IPOS += BlockSize;
		EPOS += BlockSize;
	}
	return ve;
}

std::vector<Packet> makePackets(UINT PacketSize, UINT Packets, std::vector<Block> v)
{
	std::vector<Packet>ve;
	UINT IPOS = 0, EPOS = PacketSize;
	ve.reserve(Packets);
	for(UINT i = 0; i < Packets; i++)
	{
		Packet pk;
		for(auto i = IPOS; i < EPOS; i++)
		{
			pk.emplace_back(v.at(i));
		}
		ve.emplace_back(pk);
		IPOS += PacketSize;
		EPOS += PacketSize;
	}
	std::cout << "Packets created: " << ve.capacity() << std::endl;
	return ve;
}

void checkPacketStream(std::vector<Packet> ps, UINT& Succeful, UINT& Unsucceful)
{
	for(auto value : ps)
	{
		checkPacket(value) ? Succeful += 1 : Unsucceful += 1;
	}
}

void generator(double a, double b, double& num)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);
	num = dis(gen);
}

std::vector<UINT> decodeBMA(std::vector<UINT>bytes)
{
	std::vector<UINT> b,c,t,s;
	int N, L, m, d;

	b.resize(bytes.capacity());
	t.resize(bytes.capacity());
	c.resize(bytes.capacity());
	s.resize(bytes.capacity());

	std::fill(b.begin(), b.end(), 0);
	std::fill(t.begin(), t.end(), 0);
	std::fill(c.begin(), c.end(), 0);
	std::fill(s.begin(), s.end(), 0);

	b[0] = c[0] = 1;
	N = L = 0;
	m = -1;

	while(N < (int)s.capacity())
	{
		d = 0;
		for(int i = 0; i <= L; i++)
		{
			d += s[N-i] * c[i];
		}
		d = d % 2;
		if (d != 0)
		{
			t = c;
			for(int i = 0; i <= s.capacity() + m - 1 - N; i++)
			{
				c[N - m + i] = c[N - m + i] ^ b[i];
			}
			if( L <= (N/2))
			{
				L = N + 1 - L;
				m = N;
				b = t;
			}
		}
		N++;
	}
	return c;
}

void datagrammProtocol(std::vector<Block>bl, Code code){
	UINT Succeful = 0, Unsucceful = 0, errsCounter = 0;
	UINT BlockSize = bl.at(0).capacity();
	std::vector<Block>ble;
	//TODO implement datagramm protocol
	std::cout << "!******Datagramm protocol begin******!" << std::endl;
	for(auto value : bl){
		for(auto val : value){
			if(val == 1){
				errsCounter++;
			}
		}
		if(errsCounter > code.errorsCorrection)	{
			Unsucceful++;
			ble.emplace_back(value);
		}
		else{
			Succeful++;
		}
		errsCounter = 0;
	}
	std::cout << "Blocks with errors" << std::endl;
	printDb(ble);

	double speed = (Succeful*BlockSize)/bl.capacity();
	std::cout << "Blocks in session: " << bl.capacity() << std::endl <<
			"Succeful blocks: " << Succeful << std::endl <<
			"Unsucceful blocks: " << Unsucceful << std::endl <<
			"Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl <<
			"Result speed: " << speed << std::endl;
	std::cout << "!******Datagramm protocol end******!" << std::endl;
}
void backNsteps(std::vector<Block>bl, Code code, UINT steps){
	//TODO implement back n steps protocol
}
void latencyProtocol(std::vector<Block>bl, Code code, UINT latency){
	//TODO implement protocol with latency
}
