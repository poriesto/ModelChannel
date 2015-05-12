#include "api.hpp"
//TODO implement Protocol models for all channel models
/*
pa model
*/
class pa
{
public:
	pa(UINT SessionSize, UINT BlockSize, UINT PacketSize)
	{
		this->SessionSize = SessionSize;
		this->BlockSize = BlockSize;
		this->PacketSize = PacketSize;
		this->Blocks = this->SessionSize / this->BlockSize;
		this->Packets = this->Blocks / this->PacketSize;
	}

	~pa()
	{

	}
	void work()
	{
		std::cout << "======Begin pa model======" << std::endl;
		bytes = makeSession(SessionSize);
		bl = makeBlocks(Blocks, BlockSize, bytes);
		pl = makePackets(PacketSize, Packets, bl);

		std::cout << "Analyze packets:" << std::endl;
		UINT Succeful = 0, UnSucceful = 0;
		checkPacketStream(pl, Succeful, UnSucceful);
		double R = ((Succeful*PacketSize) * BlockSize)/SessionSize;

		std::cout << "Packets in session: " << pl.capacity() << std::endl;
		std::cout << "Succeful transmited packets: " << Succeful << std::endl;
		std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
		std::cout << "Result speed: " << R << std::endl;
		std::cout << "End pa model" << std::endl;
	}
	void setP(double p)
	{
		this->p = p;
	}
	void setA(double a)
	{
		this->a = a;
	}
	void setCode(UINT codelenght, UINT correction)
	{
		this->codelenght = codelenght;
		this->correction = correction;
	}
	void setProtocol(UINT protocol)
	{
		this->protocol = protocol;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets;
	UINT codelenght, correction, protocol;
	std::vector<UINT> bytes;
	std::vector<Block> bl;
	std::vector<Packet> pl;
	double p, a;

	void datagrammProtocol()
	{
		std::cout << "!******Datagramm protocol begin******!" << std::endl;
		for(auto value : bl)
		{}
		std::cout << "!******Datagramm protocol end******!" << std::endl;
	}
	void latencyProtocol()
	{
		std::cout << "!******Latency protocol begin******!" << std::endl;
		for(auto value : bl)
		{}
		std::cout << "!******Latency protocol end******!" << std::endl;

	}
	void backNsteps(UINT steps)
	{
		std::cout << "!******backNsteps Protocol begin******!" << std::endl;
		for(auto value : bl)
		{}
		std::cout << "!******backNsteps Protocol end******!" << std::endl;

	}

};

/*
OPP model
*/
class opp
{
public:
	opp(UINT SessionSize, UINT BlockSize, UINT PacketSize)
	{
		this->SessionSize = SessionSize;
		this->BlockSize = BlockSize;
		this->PacketSize = PacketSize;
		this->Blocks = this->SessionSize / this->BlockSize;
		this->Packets = this->Blocks / this->PacketSize;
		this->Count = 0;
	}

	~opp()
	{}
	void work()
	{
		std::cout << "======Begin OPP model======" << std::endl;
		bytes = makeSession(SessionSize);
		int Pos = GenOppPos();
		for(int i = 0; i < bytes.capacity()-1; i++)
		{
			if(Pos == i)
			{
				bytes[i] = 1;
				errPOS.emplace_back(Pos);
				Pos = i + 1 + GenOppPos();
			}
			else if( Pos != i)
			{
				bytes[i] = 0;
			}
		}

		std::cout << std::endl << "Errors" << std::endl;
		print(errPOS);
		bl = makeBlocks(Blocks, BlockSize, bytes);

		std::cout << "Blocks:" << std::endl;
		printDb(bl);
		switch (ProtocolType)
		{
			case 1:
				datagrammProtocol();
				break;
			case 2:
				latencyProtocol();
				break;
			case 3:
				std::cout << "Enter steps for protocol" << std::endl;
				std::cin >> this->steps;
				backNsteps(this->steps);
				break;
		}
		std::cout << "======End OPP model======" << std::endl;
	}
	void setParams(double A, double V)
	{
		this->A = A; this->V = V;
	}
	void setCode(UINT errCor, UINT codeLenght)
	{
		this->errCor = errCor;
		this->errCor = codeLenght;
	}
	void setProtocolType(UINT type)
	{
		ProtocolType = type;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets, Count, ProtocolType;
	UINT errCor, codeLenght, steps;
	std::vector<UINT>bytes, errPOS;
	std::vector<Block> bl;
	double A,V;
	UINT GenOppPos()
	{
		double R, a = 0, b = 1;
		generator(a,b,R);
		double X = (A/pow(R,(1/V))) - A;
		std::cout << "X = " << X << " R = " << R << std::endl	;
		return static_cast<int>(X);
	}
	void datagrammProtocol()
	{
		UINT Succeful, Unsucceful, errCounter;
		Succeful = Unsucceful = errCounter = 0;
		std::vector<Block> ble;
		std::cout << "!******Datagramm protocol begin******!" << std::endl;

		//TODO Need deep check for correction work
		for(auto value : bl)
		{
			for(auto val : value)
			{
				if (val == 1) {
					errCounter++;
				}
				std::cout << errCounter << std::endl;
			}
			if(errCounter > errCor)
			{
				Unsucceful ++;
				ble.emplace_back(value);
			}
			else
			{
				Succeful++;
			}
			errCounter = 0;
		}

		std::cout << "Blocks with errors:" << std::endl;
		printDb(ble);

		double speed = (Succeful*BlockSize)/SessionSize;
		std::cout << "Blocks in session: " << bl.capacity() << std::endl;
		std::cout << "Succeful blocks: " << Succeful << std::endl;
		std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
		std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
		std::cout << "Result speed: " << speed << std::endl;
		std::cout << "!******Datagramm protocol end******!" << std::endl;
	}
	void latencyProtocol()
	{
		UINT Succeful, Unsucceful;
		Succeful = Unsucceful = 0;
		std::cout << "!******Latency protocol begin******!" << std::endl;
		for(auto value : bl)
		{}

		double speed = (Succeful*BlockSize)/SessionSize;
		std::cout << "Blocks in session: " << bl.capacity() << std::endl;
		std::cout << "Succeful blocks: " << Succeful << std::endl;
		std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
		std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
		std::cout << "Result speed: " << speed << std::endl;
		std::cout << "!******Latency protocol end******!" << std::endl;

	}
	void backNsteps(UINT steps)
	{
		UINT Succeful = 0, Unsucceful = 0, errCounter = 0;
		std::vector<Block>ble;
		std::cout << "!******backNsteps Protocol begin******!" << std::endl;
		for(auto value : bl)
		{
			for(auto val : value)
			{
				if (val > 0) {
					errCounter++;
				}
			}
			if (errCounter > errCor) {
				Unsucceful++;
				ble.emplace_back(value);
			}
			else {
				Succeful++;
			}
			errCounter = 0;
		}

		double speed = (Succeful*BlockSize)/SessionSize;
		std::cout << "Blocks in session: " << bl.capacity() << std::endl;
		std::cout << "Succeful blocks: " << Succeful << std::endl;
		std::cout << "Unsuccefl blocks: " << Unsucceful << std::endl;
		std::cout << "Percent succeful: " << (Succeful*100)/bl.capacity() << std::endl;
		std::cout << "Result speed: " << speed << std::endl;
		std::cout << "!******backNsteps Protocol end******!" << std::endl;

	}
};
