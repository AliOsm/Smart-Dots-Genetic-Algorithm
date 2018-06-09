#ifndef POPULATION
#define POPULATION

#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#include "dot.cpp"
#include "obstacle.cpp"

class Population {
private:
	int instructionsCount;
	int generation;
	int alive;
	int reachedTarget;
	int minimumCurrent;
	double fitnessSum;
	Position target;
	std::vector<Dot> dots;
	std::vector<Obstacle> obstacles;

	bool isOnObstacle(Position position) {
		for(int i = 0; i < obstacles.size(); ++i)
			if(obstacles[i].collision(position))
				return true;
		return false;
	}

	void calculateFitnessSum() {
		fitnessSum = 0;
		for(int i = 0; i < dots.size(); ++i)
			fitnessSum += dots[i].getFitness();
	}

	Dot selectParent() {
		std::uniform_real_distribution<double> urd(0.0, fitnessSum);
		std::default_random_engine dre(std::time(NULL));
		double rnd = urd(dre);
		double currentSum = 0;

		for(int i = 0; i < dots.size(); ++i) {
			currentSum += dots[i].getFitness();

			if(currentSum > rnd)
				return dots[i];
		}
	}

	Dot getBestDot() {
		double bestFitness = 0;
		double bestIndex;
		for(int i = 0; i < dots.size(); ++i) {
			if(dots[i].getFitness() > bestFitness) {
				bestFitness = dots[i].getFitness();
				bestIndex = i;
			}
		}

		if(dots[bestIndex].isReachedTarget())
			minimumCurrent = std::min(minimumCurrent, dots[bestIndex].getCurrent() + 25);

		return dots[bestIndex];
	}

public:
	Population(int populationSize, int width, int height, int instructionsCount, Position target, std::vector<Obstacle> obstacles) :
		target(target),
		obstacles(obstacles) {
		this->instructionsCount = instructionsCount;
		generation = 1;
		alive = 0;
		reachedTarget = 0;
		fitnessSum = 0;
		minimumCurrent = instructionsCount;
		for(int i = 0; i < populationSize; ++i)
			dots.push_back(Dot(width, height, instructionsCount, target));
	}

	int getSize() {
		return dots.size();
	}

	int getInstructionsCount() {
		return instructionsCount;	
	}

	int getGeneration() {
		return generation;
	}

	int getAlive() {
		return alive;
	}

	int getReachedTarget() {
		return reachedTarget;
	}

	Dot getDot(int idx) {
		return dots[idx];
	}

	void resetReachedTarget() {
		reachedTarget = 0;
	}

	int countAlive() {
		alive = 0;
		for(int i = 0; i < dots.size(); ++i)
			if(!dots[i].isDead() && !dots[i].isReachedTarget())
				++alive;
		return alive;
	}

	void move() {
		for(int i = 0; i < dots.size(); ++i) {
			if(dots[i].isReachedTarget())
				continue;

			dots[i].move();
			
			if(dots[i].getCurrent() > minimumCurrent ||
				 isOnObstacle(dots[i].getPosition()))
				dots[i].kill();
			
			if(dots[i].isReachedTarget())
				++reachedTarget;
		}
	}

	void calculateFitness() {
		for(int i = 0; i < dots.size(); ++i)
			dots[i].calculateFitness();
	}

	void naturalSelection() {
		calculateFitnessSum();
		
		std::vector<Dot> newDots;
		newDots.push_back(getBestDot().reset());
		for(int i = 1; i < dots.size(); ++i) {
			Dot parent = selectParent();
			newDots.push_back(parent.clone());
		}

		dots.swap(newDots);
		++generation;
	}

	void mutation() {
		for(int i = 0; i < dots.size(); ++i)
			dots[i].mutate();
	}
};

#endif
