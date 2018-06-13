#ifndef BRAIN
#define BRAIN

#include <vector>
#include <ctime>
#include <random>

class Brain {
private:
	int current;
	int mod;
	std::vector<int> instructions;

public:
	Brain(int instructionsCount, int mod) {
		current = 0;
		this->mod = mod;

		instructions.push_back(std::rand() % mod);
		for(int i = 1, rnd; i < instructionsCount; ++i) {
			do {
				rnd = std::rand() % mod;
			} while(rnd == instructions[i - 1]);
			instructions.push_back(rnd);
		}
	}

	int getCurrent() {
		return current;
	}

	int getInstructionsCount() {
		return instructions.size();
	}

	int getInstruction() {
		return instructions[current++];
	}

	void resetCurrent() {
		current = 0;
	}

	void mutate(double mutationRate) {
		int rnd;

		for(int i = 0; i < instructions.size(); ++i) {
			rnd = rand() % 100;
			if(rnd < mutationRate) {
				if(i == 0)
					instructions[i] = rand() % mod;
				else {
					do {
						instructions[i] = rand() % mod;
					} while(instructions[i] == instructions[i - 1]);
				}
			}
		}
	}
};

#endif
