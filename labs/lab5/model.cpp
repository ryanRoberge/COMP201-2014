#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model(int w, int h) {
    width = w;
    height = h;
    Coordinate head;
    Coordinate tail;
    direction = RIGHT;
	lastDirection;
    head.x = 1;
    head.y = 0;
    tail.x = 0;
    tail.y = 0;
    food.x = 5;
    food.y = 10;
    snake.push_front(head);
    snake.push_back(tail);
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

bool Model::gameOver() {
    return snake.empty() || snake.size() == width * height;
}

// Which way should the snake face?
void Model::go(Direction d) {
    direction = d;
}

// Move foward
void Model::crawl() {
    Coordinate front = snake.front();
	
	if(lastDirection == DEAD)
		direction = DEAD;
	
	if(direction == UP && lastDirection == DOWN)
		direction = DOWN;
	
	if(direction == DOWN && lastDirection == UP)
		direction = UP;
	
	if(direction == LEFT && lastDirection == RIGHT)
		direction = RIGHT;
	
	if(direction == RIGHT && lastDirection == LEFT)
		direction = LEFT;
	
    switch(direction) {
    case UP: front.y--; lastDirection = UP;
	break;
    case DOWN: front.y++; lastDirection = DOWN;
	break;
    case LEFT: front.x--; lastDirection = LEFT;
	break;
    case RIGHT: front.x++; lastDirection = RIGHT; 
	break;
    }
    // TODO: Colliding with the perimeter of the screen should set direction to DEAD
    // When DEAD, the snake slowly shrinks down to nothing
    if(front.y >= ((height*8)-16) || front.y < 0 || front.x >= (width*8) || front.x < 0)
	{
		direction = DEAD;
		lastDirection = DEAD;		
	}
	
    if (direction != DEAD) {
        snake.push_front(front);
    }
	else
	{
		snake.pop_front();
		if(snake.empty())
			return;
	}

    // TODO: Colliding with food grows the snake (so don't pop_back in that case)
    // TODO: Also, colliding with food should cause us to place the food somewhere
    // else, but not anywhere on the snake.
	if(front.x != food.x || front.y != food.y && direction != DEAD)
		snake.pop_back();
	else
	{
		food.x = rand()%64;
		food.y = rand()%48;
	}
}
