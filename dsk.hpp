#include "api.hpp"

class dsk
{
public:
	dsk(UINT SessionSize, UINT BlockSize, UINT PacketSize)
	{
		this->SessionSize = SessionSize;
		this->BlockSize = BlockSize;
		this->PacketSize = PacketSize;
		this->Blocks = this->SessionSize / this->BlockSize;
		this->Packets = this->Blocks / this->PacketSize;
	}
	~dsk();
	void setP(double p)
	{
		this->p = p;
	}
	double getP()
	{
		return this->p;
	}
	UINT getBlockSize()
	{
		return this->BlockSize;
	}
	UINT getdskcketSize()
	{
		return this->PacketSize;
	}
	UINT getSessionSize()
	{
		return this->SessionSize;
	}
	void work()
	{
		std::cout << "======Begin dsk model======" << std::endl;
		std::vector<UINT>bytes = makeSession(SessionSize);
		/*
			Apply erors to bytes stream
			Encode and decode bytes stream
		*/
		std::vector<Block> bl = makeBlocks(Blocks, BlockSize, bytes);
		std::vector<Packet> pl = makePackets(PacketSize, Packets, bl);
		
		/*std::cout << "Bytes start" << std::endl;
		print(bytes);
		std::cout << "Bytes end" << std::endl;
		std::cout << "Blocks start" << std::endl;
		for(auto value : bl)
		{
			print(value);
		}
		std::cout << "Blocks end" << std::endl;
		std::cout << "Packets start" << std::endl;
		for(auto value : pl)
		{
			for(auto valBK : value)
			{
				print(valBK);
			}
		}*/
		//Bernuli
		
		std::cout << "Analyze packets:" << std::endl;
		UINT Succeful = 0, UnSucceful = 0;
		checkPacketStream(pl, Succeful, UnSucceful);
		
		double Pb = 0.807, Pt;
		double l = (Succeful * PacketSize) * BlockSize;
		double L = SessionSize;
		double R = l * Pb/L;

		std::cout << "Packets in session: " << pl.capacity() << std::endl;
		std::cout << "Succeful transmited packets: " << Succeful << std::endl;
		std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
		std::cout << "Result speed: " << R << std::endl;
		std::cout << "======End dsk model======" << std::endl;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets;
	double p;
};

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
	~pa();
	void work()
	{
		std::cout << "======Begin pa model======" << std::endl;
		std::vector<UINT>bytes = makeSession(SessionSize);
		/*
			Apply erors to bytes stream
			Encode and decode bytes stream
		*/
		std::vector<Block> bl = makeBlocks(Blocks, BlockSize, bytes);
		std::vector<Packet> pl = makePackets(PacketSize, Packets, bl);

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
	double getP()
	{
		return this->p;
	}
	double getA()
	{
		return this->a;
	}
	UINT getBlockSize()
	{
		return this->BlockSize;
	}
	UINT getPacketSize()
	{
		return this->PacketSize;
	}
	UINT getSessionSize()
	{
		return this->SessionSize;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets;
	double p, a;
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
	~opp();
	void work()
	{
		std::cout << "======Begin OPP model======" << std::endl;
		std::vector<UINT>bytes = makeSession(SessionSize);
		/*
			Apply erors to bytes stream
			Encode and decode bytes stream
		*/
		for(int i = 0; i < bytes.capacity(); i++)
		{
			gen:
			int Pos = GenOppPos(this->A, this->V);
			std::cout << Pos << std::endl;
			Count == Pos ? bytes[Pos] = 1 : bytes[Pos] = 0;
			Pos = SessionSize + 1 + GenOppPos(this->A, this->V);
			Count ++;
			if(Count >= SessionSize)
			{
				goto gen;
			}
		}

		std::vector<Block> bl = makeBlocks(Blocks, BlockSize, bytes);
		std::vector<Packet> pl = makePackets(PacketSize, Packets, bl);

		std::cout << "Analyze packets:" << std::endl;
		UINT Succeful = 0, UnSucceful = 0;
		checkPacketStream(pl, Succeful, UnSucceful);
		double R = ((Succeful*PacketSize) * BlockSize)/SessionSize;

		std::cout << "Packets in session: " << pl.capacity() << std::endl;
		std::cout << "Succeful transmited packets: " << Succeful << std::endl;
		std::cout << "Unsucceful transmited packets: " << UnSucceful << std::endl;
		std::cout << "Result speed: " << R << std::endl;
		std::cout << "======End OPP model======" << std::endl;
	}
	void setParams(double A, double V)
	{
		this->A = A; this->V = V;
	}
private:
	UINT BlockSize, PacketSize, SessionSize;
	UINT Blocks, Packets, Count;
	double A,V, a, v;
	UINT GenOppPos(double A, double V)
	{
		/*double R = generator(0,1);
		double y = generator(0,1);*/
		double R,y, a = 0, b = 1;
		generator(a,b,R);
		generator(a,b,y);
		std::cout << "R = " << R << " y = " << y << std::endl;
		double X = (A/pow(y,(1/V))) - a;
		std::cout << "X = "<< X << std::endl; 
		return static_cast<int>(X);
	}

};