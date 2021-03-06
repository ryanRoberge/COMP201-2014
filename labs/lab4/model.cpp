#include "model.h"
<<<<<<< HEAD
#include "controller.h"
=======
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
#include <cstdlib>
#include <ctime>

using namespace std;

<<<<<<< HEAD
int temprow, tempcol;

=======
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
// Constructor initializes the object
Model::Model(int w, int h) {
    width = w;
    height = h;
<<<<<<< HEAD
	lastRow.push_back(-1); // Initializes the previously void vector to something comparable
	lastColumn.push_back(-1); // Initializes the previously void vector to something comparable
    state = FIRST_MOVE;
=======
    state = INIT;
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
    grid = new char*[height];
    visible = new char*[height];
    // For every row, create the array for that row
    for (int i = 0; i < height; i++) {
        grid[i] = new char[width];
        visible[i] = new char[width];
    }
    char letter = 'A';
    // Guarantee pairs of characters in the grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = letter;
            // Everything's invisible at first
            visible[i][j] = '_';
            // Every other iteration...
            if (j % 2 == 1) {
                letter++;
                if (letter > 'Z') {
                    letter = 'A';
                }
            }
        }
    }
    // Seed random number generator with time
    srand(time(0));
    // Randomize
    int otheri, otherj;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Pick a random spot in the grid
            otheri = rand() % height;
            otherj = rand() % width;
            // Swap grid[i][j] with grid[otheri][otherj]
            letter = grid[i][j];
            grid[i][j] = grid[otheri][otherj];
            grid[otheri][otherj] = letter;
        }
    }
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
    for (int i = 0; i < height; i++) {
        delete grid[i];
        delete visible[i];
    }
    delete grid;
    delete visible;
}
// TODO: Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
bool Model::valid(int row, int column) {
<<<<<<< HEAD
	
	if(row > getWidth()-1 || row < 0)
	{
		return false;
	}
	
	if(column > getHeight()-1 || column < 0)
	{
		return false;	
	}
	
=======
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
    return true;
}
bool Model::matched(int row, int column) {
    return true;
}
<<<<<<< HEAD

// TODO: Flip a cell
void Model::flip(int row, int column) {

	// If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
	
	if(state == NO_MATCH)
	{
		visible[lastRow.back()][lastColumn.back()] = '_';
		visible[temprow][tempcol] = '_';
		state = FIRST_MOVE;
	}
	
	// First of two cells are to be flipped
	if(state == FIRST_MOVE)
	{
		visible[row][column] = grid[row][column];
		lastRow.push_back(row);
		lastColumn.push_back(column);
		state = CHECKING;
		return;
	}
	
	// These two recently flipped cells need to be compared
	else if(state == CHECKING)
	{
        // Checks for a match, changes game state accordingly
		if(grid[row][column] == grid[lastRow.back()][lastColumn.back()])
		{
			visible[row][column] = grid[row][column];
			state = FIRST_MOVE;
			lastRow.clear();
			lastColumn.clear();
			return;
		}			
		// No match case, changes game state accordingly
		else if(grid[row][column] != grid[lastRow.back()][lastColumn.back()])
		{
			state = NO_MATCH;
			visible[row][column] = grid [row][column];
			temprow = lastRow.back(); // Storage for removing
			tempcol = lastColumn.back(); // Storage for removing
			lastRow.push_back(row);
			lastColumn.push_back(column);
			return;
		} 
	}
	return;
=======
// TODO: Flip a cell
void Model::flip(int row, int column) {
    // If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
    visible[row][column] = grid[row][column];
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
}
// If everything is visible, then it's game over
bool Model::gameOver() {
    // Assume the game is over
    bool isOver = true;
    // Loop through the grid and see if any element is not visible
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (visible[i][j] == '_') {
                isOver = false;
            }
        }
    }
    
    if (isOver) {
        // Set a nice game over message
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                visible[i][j] = '_';
            }
        }
        visible[2][3] = 'Y';
        visible[2][4] = 'O';
        visible[2][5] = 'U';
        visible[4][3] = 'W';
        visible[4][4] = 'I';
        visible[4][5] = 'N';
    }
    return isOver;
}
int Model::getWidth() {
    return width;
}
int Model::getHeight() {
    return height;
}
char Model::get(int row, int col) {
    return visible[row][col];
}
