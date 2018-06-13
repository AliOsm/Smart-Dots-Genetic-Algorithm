#ifndef GRID
#define GRID

#include <stdio.h>
#include <vector>
#include <set>

#include "dot.cpp"
#include "position.cpp"
#include "obstacle.cpp"

class Grid {
private:
	int width;
	int height;
	Position target;
	std::vector<Obstacle> obstacles;

	bool isOnObstacle(Position position) {
		for(int i = 0; i < obstacles.size(); ++i)
			if(obstacles[i].collision(position))
				return true;
		return false;
	}

public:
	Grid(int width, int height, Position target, std::vector<Obstacle> obstacles) :
		target(target),
		obstacles(obstacles) {
		this->width = width;
		this->height = height;
	}

	void draw(Population population) {
		std::printf("Generation #%d\n", population.getGeneration());
		std::printf("Number of alive dots: %d\n", population.getAlive());
		std::printf("Number of dead  dots: %d\n", population.getSize() - population.getAlive() - population.getReachedTarget());
		std::printf("Number of dots reached the target: %d\n", population.getReachedTarget());
		std::putchar('+');
		for(int i = 0; i < width; ++i)
			std::putchar('-');
		std::printf("+\n");

		std::set<Position> positions;
		for(int i = 0; i < population.getSize(); ++i)
			positions.insert(population.getDot(i).getPosition());

		for(int i = 0; i < height; ++i) {
			std::putchar('|');
			for(int j = 0; j < width; ++j)
				if(isOnObstacle(Position(i, j)))
					std::putchar('=');
				else if(Position(i, j).euclideanDistance(target) < 2.0)
					std::putchar('#');
				else if(positions.count(Position(i, j)))
					std::putchar('*');
				else
					std::putchar(' ');
			std::printf("|\n");
		}

		std::putchar('+');
		for(int i = 0; i < width; ++i)
			std::putchar('-');
		std::printf("+\n");
	}
};

#endif
