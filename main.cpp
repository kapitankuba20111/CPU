#include <stdio.h>

using u32 = unsigned int;

class Memory {
public:
	static constexpr u32 MAX_MEM = 64 * 512;
	char Data[MAX_MEM];

	void Init() {
		for (int i = 0; i < MAX_MEM; i++)
		{
			Data[i] = 0;
		}
	}

	char operator[](int Address) const
	{
		if (Address < MAX_MEM) {
			return Data[Address];
		}
	}

	/** write 1 byte */
	char& operator[](int Address)
	{
		if (Address < MAX_MEM) {
			return Data[Address];
		}
		else {
			printf("No memory left to write to\n");
		}
	}
};

class CPU {
	int FuturePos;
	int Pos;

	char inst;
public:

	void Reset(Memory& mem) {
		FuturePos = 0;
		Pos = 1;
		mem.Init();
	}

	void Advance(Memory& mem) {
		FuturePos++;
		Pos = FuturePos - 1;
		inst = mem.Data[Pos];
	}

	static constexpr char
		INS_JML = 0xAA,
		INS_SRE = 0xAB,
		INS_HRE = 0xAC,
		INS_NOP = 0xAD;

	void Execute(int InsToExec, Memory& mem) {
		while (InsToExec > 0 || InsToExec != 0) {
			Advance(mem);
			switch (inst) {
			case INS_HRE:
			{
				Reset(mem);
				InsToExec--;
			} break;
			case INS_SRE:
			{
				FuturePos = 0;
				Pos = 1;
				InsToExec--;
			} break;
			case INS_JML:
			{
				FuturePos = mem.Data[Pos + 2];
				InsToExec--;
			} break;
			case INS_NOP:
			{
				//Do nothing since the instruction name stands for "No OPeration"
			} break;
			;
			}
		}
	}
};

int main() {
	CPU cpu;
	Memory mem;
	cpu.Reset(mem);
	mem[0] = CPU::INS_NOP;
	mem[1] = CPU::INS_SRE;
	cpu.Execute(3, mem);
	return 0;
}