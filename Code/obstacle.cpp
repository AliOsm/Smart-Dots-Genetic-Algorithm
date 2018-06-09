#ifndef OBSTACLES
#define OBSTACLES

#include "position.cpp"

class Obstacle {
private:
	Position topLeft;
	int width;
	int height;

public:
	Obstacle(Position position, int width, int height) :
		topLeft(position) {
		this->width = width;
		this->height = height;
	}

	bool collision(Position position) {
		return position.y >= topLeft.y &&
					 position.y < topLeft.y + width &&
					 position.x >= topLeft.x &&
					 position.x < topLeft.x + height;
	}
};

#endif
