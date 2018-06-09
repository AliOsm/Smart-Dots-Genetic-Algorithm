#ifndef POSITION
#define POSITION

#include <cmath>

class Position {
public:
	int x;
	int y;

	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int manhatanDistance(Position position) {
		return std::abs(x - position.x) + std::abs(y - position.y);
	}

	double euclideanDistance(Position position) {
		return std::sqrt(std::pow(x - position.x, 2.0) + std::pow(y - position.y, 2.0));
	}

	bool operator<(const Position &position) const {
		if(x != position.x)
			return x < position.x;
		return y < position.y;
	}

	bool operator==(const Position &position) const {
		return x == position.x && y == position.y;
	}
};

#endif
