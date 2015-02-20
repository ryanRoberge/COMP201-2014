// Ryan Roberge
// Professor Lawrance
// 2-19-2015
// Lab 3 - Concentration

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

enum State { FIRST_MOVE, CHECKING, NO_MATCH };

State state = FIRST_MOVE; // When user first starts, he is flipping the first in a pair

int rowToWipe; // Storage variable used for remembering a row needed to show the board before that cell is overwritten
int colToWipe; // Storage variable used for remembering a column needed to show the board before that cell is overwritten

// To clear the screen, look up ANSI escape codes
// Concentration game model
// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    // Initialize a grid of letters randomly
    Model(int w, int h);
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Methods (member functions)
    // Return the width
    int getWidth();
    // Return the height
    int getHeight();
    // Return visible stuff (invisible stuff is shown with character *)
    char get(int row, int column);
    // Flip this row/column
    void flip(int row, int column);
	// Used to change the most recent cell and the cell before that to a '*'
	void wipe(int row, int col);
    // Is the game over?
    bool gameOver(Model * model);
private:
    // Is the row/column valid?
    bool valid(int row, int column);
    // Fields (member data)
    // Randomly generated grid. This has pairs of characters in it
    char ** grid;
    // What is visible to the user?
    char ** visible;
    // What's the width?
    int width;
    // What's the height?
    int height;
    // What'd we flip last?
    vector<int> lastRows;
    vector<int> lastColumns;
};

// Show (output) the state of the model
class View {
public:
    // Print out the visible stuff in the grid
    void show(Model * model);
};

// Handle input
class Controller {
public:
    Controller() {
        model = new Model(4,4); // 4x4 because it's easier to play
        view = new View;
    }
    ~Controller() {
        delete model;
        delete view;
    }
    // Event loop
    void loop();
private:
    Model * model;
    View * view;
};

// Constructor initializes the object
Model::Model(int w, int h) {
    width = w;
    height = h;
	lastRows.push_back(-1); // Initializes the previously void vector to something comparable
	lastColumns.push_back(-1); // Initializes the previously void vector to something comparable
    grid = new char*[height];
    visible = new char*[height];
    // For every row, create the array for that row
    for (int i = 0; i < height; i++) {
        grid[i] = new char[width];
        visible[i] = new char[width];
    }
    srand(time(0));
    // TODO: make this random-ish
    // Look at asciitable.com and do some stuff with rand() % number
    // Hint: insert characters in order, then shuffle later in a separate loop
    
	char letter = 'A';
	for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = letter;
            // Everything's invisible at first
            visible[i][j] = '*';
			if(j % 2 == 1)
				letter++;
			if(letter > 'Z')
				letter = 'A';
        }
    }
	
	int otheri, otherj;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			otheri = rand() % height;
			otherj = rand() % width;
			
			letter = grid[i][j];
			grid[i][j] = grid[otheri][otherj];
			grid[otheri][otherj] = letter;
			
		}
	}
//////////////////////////////////////////////////////
// Displays the contents of grid (cheat so we can see)
	    for (int j = 0; j < width; j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < h; i++) {
        cout << i;
        for (int j = 0; j < w; j++) {
            cout << "\t" << grid[i][j];
        }
        cout << endl;
    }
	cout << endl;
//////////////////////////////////////////////////////
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

int Model::getWidth() {
    return width;
}
int Model::getHeight() {
    return height;
}

// If everything is visible, then it's game over
bool Model::gameOver(Model * model) {
    for(int r = 0; r < model->getHeight(); r++)
	{
		for(int c = 0; c < model->getWidth(); c++)
		{
			if(visible[r][c] == '*')
				return false;
		}
	}
	return true; // If all the cells were filled with letters, user must have won
}

char Model::get(int row, int col) {
    return visible[row][col];
}
// Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
// Also check to make sure user isn't being silly
bool Model::valid(int row, int column) {
	
	if(row > getWidth()-1 || row < 0)
	{
		cout << endl << "Coordinates are out of range, please try again." << endl << endl;
		return false;
	}
	
	if(column > getHeight()-1 || column < 0)
	{
		cout << endl << "Coordinates are out of range, please try again." << endl << endl;
		return false;	
	}
	
	if(row == lastRows.back() && column == lastColumns.back() && visible[row][column] != '*')
	{
		cout << endl << "Please enter a different row and column than the previous." << endl << endl;
		return false;
	}
	
	if(visible[row][column] != '*')
	{
		cout << endl << "Please pick cells that haven't already been flipped." << endl << endl;
		return false;	
	}

    return true;
}
// Used to change the most recent cell and the cell before that to a '*'
void Model::wipe(int row, int col)
{
	visible[row][col] = '*';
	visible[rowToWipe][colToWipe] = '*';
	return;
}

// Flip a cell/change game state
void Model::flip(int row, int column) {
		
    // If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
	
	// First of two cells are to be flipped
	else if(state == FIRST_MOVE)
	{
		visible[row][column] = grid[row][column];
		lastRows.push_back(row);
		lastColumns.push_back(column);
		state = CHECKING;
		return;
	}
	
	// These two recently flipped cells need to be compared
	else if(state == CHECKING)
	{
        // Checks for a match, changes game state accordingly
		if(grid[row][column] == grid[lastRows.back()][lastColumns.back()])
		{
			cout << endl << "[MATCH]"  << endl << endl;
			visible[row][column] = grid[row][column];
			state = FIRST_MOVE;
			lastRows.push_back(row);
			lastColumns.push_back(column);
			return;
		}			
		// No match case, changes game state accordingly
		else if(grid[row][column] != grid[lastRows.back()][lastColumns.back()])
		{
			state = NO_MATCH;
			visible[row][column] = grid [row][column];
			cout << endl << "[NO MATCH]"  << endl << endl;
			rowToWipe = lastRows.back(); // Saves what is currently the lastRow
			colToWipe = lastColumns.back(); // Saves what is currently the lastColumn
			lastRows.push_back(row);
			lastColumns.push_back(column);
			return;
		} 
	}
	return;
}

// Show the model, one cell at a time
void View::show(Model * model) {
	
    for (int j = 0; j < model->getWidth(); j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < model->getHeight(); i++) {
        cout << i;
        for (int j = 0; j < model->getWidth(); j++) {
            cout << "\t" << model->get(i, j);
        }
        cout << endl;
    }
	cout << endl;
}

// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {
    int row, col;
    while (!model->gameOver(model)) {
        view->show(model);
        cout << "Enter row:    ";
        cin >> row;
		// Handy break out of game case for ease of testing
		if(row == -1)
		{
			delete model;
			delete view;
			exit(0);
		}
        cout << "Enter column: ";
        cin >> col;
		cout << endl;
        model->flip(row, col);
		if(state == NO_MATCH)
		{
			view->show(model);
			model->wipe(row, col);
			state = FIRST_MOVE;
		}
    }
    
	view->show(model);
	cout << endl << "Hooray, you win!"<< endl;
	return;

}

int main() {
    Controller c;
    c.loop();
	return 0;
}