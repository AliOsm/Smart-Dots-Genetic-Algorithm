#ifndef DOT
#define DOT

#include <cmath>

#include "position.cpp"
#include "brain.cpp"

class Dot {
private:
	static int factor;
	static int dx[];
	static int dy[];

	bool dead;
	bool reachedTarget;
	int width;
	int height;
	int fitness;
	Position position;
	Position target;
	Brain brain;

	bool outOfRange() {
		return position.x < 0 ||
					 position.x >= height ||
					 position.y < 0 ||
					 position.y >= width;
	}

public:
	Dot(int width, int height, int instructionsCount, Position target) :
		position(height - Dot::factor, width / 2),
		target(target),
		brain(instructionsCount, 5) {
		dead = false;
		reachedTarget = false;
		this->width = width;
		this->height = height;
		fitness = 0;
	}

	bool isDead() {
		return dead;
	}

	bool isReachedTarget() {
		return reachedTarget;
	}

	int getInstructionsCount() {
		return brain.getInstructionsCount();	
	}

	int getCurrent() {
		return brain.getCurrent();
	}

	int getFitness() {
		return fitness;
	}

	Position getPosition() {
		return position;
	}

	void kill() {
		dead = true;
	}

	void move() {
		if(!dead) {
			if(brain.getCurrent() >= getInstructionsCount()) {
				dead = true;
				return;
			}

			int current = brain.getInstruction();
			position.x += dx[current];
			position.y += dy[current];

			if(outOfRange()) {
				position.x -= dx[current];
				position.y -= dy[current];
				dead = true;
			}

			if(position.euclideanDistance(target) < 2.0)
				reachedTarget = true;
		}
	}

	void calculateFitness() {
		if(reachedTarget) {
			fitness = 10000 / brain.getCurrent();
		} else {
			double distance = position.euclideanDistance(target);
			fitness = 100 / (distance * distance);
		}
	}

	Dot clone() {
		Dot child(*this);

		child.dead = false;
		child.reachedTarget = false;
		child.fitness = 0;
		child.position = Position(height - Dot::factor, width / 2);
		child.brain.resetCurrent();
		
		return child;
	}

	void mutate() {
		if(!reachedTarget)
			brain.mutate(10);
	}
};

int Dot::factor = 4;
int Dot::dx[] = {-1, -1, -1, 0, 0};
int Dot::dy[] = {0, -1, 1, -1, 1};

#endif
