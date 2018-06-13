#include <vector>
#include <ctime>
#include <thread>
#include <chrono>

#include "obstacle.cpp"
#include "position.cpp"
#include "population.cpp"
#include "grid.cpp"

int const width = 31;
int const height = 20;

int main() {
	std::srand(std::time(NULL));

	std::vector<Obstacle> obstacles;

	// One obstable
	// obstacles.push_back(Obstacle(Position(9, 7), 17, 2));

	// Two obstacles
	// obstacles.push_back(Obstacle(Position(7, 0), 16, 2));
	// obstacles.push_back(Obstacle(Position(13, 15), 16, 2));

	// Three obstacles
	obstacles.push_back(Obstacle(Position(5, 5), 8, 6));
	obstacles.push_back(Obstacle(Position(5, 18), 8, 6));
	obstacles.push_back(Obstacle(Position(12, 11), 9, 2));

	Position target(2, width / 2);
  Population population(1000, width, height, 100, target, obstacles);
  Grid grid(width, height, target, obstacles);

  while(true) {
	  for(int i = 0; i < population.getInstructionsCount(); ++i) {
	  	std::system("clear");
	  	grid.draw(population);
	  	population.move();
	  	if(population.countAlive() == 0) {
	  		population.calculateFitness();
	  		population.naturalSelection();
	  		population.mutation();
	  		population.resetReachedTarget();
	  		break;
	  	}
	  	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	  }
	}

  return 0;
}
