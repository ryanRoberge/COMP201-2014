// Ryan Roberge
// Professor Lawrance
// 2-11-2015
// Lab 3 - Concentration

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

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
    void flip(int row, int column, Model * model);
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
        model = new Model(8,8);
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
	lastRows.push_back(-1); // Initializes the lastRows vector to something that isn't empty
    lastColumns.push_back(-1); // Initializes the lastColumns vector to something that isn't empty
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

// TODO: If everything is visible, then it's game over
bool Model::gameOver(Model * model) {
    for(int r = 0; r < model->getHeight(); r++)
	{
		for(int c = 0; c < model->getWidth(); c++)
		{
			if(visible[r][c] == '*')
				return false;
		}
	}
	return true;
}

char Model::get(int row, int col) {
    return visible[row][col];
}
// TODO: Is the row/column valid?
// That is, is the row within the height, and is the column within the width?
// Return whether it is or isn't.
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

    return true;
}

// TODO: Flip a cell
void Model::flip(int row, int column, Model * model) {
		
    // If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
	// Ensures the row and column given this time is not the same as the previous set
	else if(row == lastRows.back() && column == lastColumns.back())
	{
		cout << endl << "Please enter a different row and column than the previous." << endl << endl;
		return;
	}
	// Ensures the row and column given is not an already flipped cell
	else if(visible[row][column] != '*')
	{
		cout << endl << "Please pick cells that haven't already been flipped." << endl << endl;
		return;	
	}
    // If the last selected row and column are invalid,
        // It means we're selecting the first "cell" to flip
		else if(lastRows.back() == -1 && lastColumns.back() == -1)
		{
			visible[row][column] = grid[row][column];
			lastRows.push_back(row);
			lastColumns.push_back(column);
			return;
		}
    // Otherwise, we are selecting the next "cell" to flip
        // If the last cell and the current cell match, great!
		else if(grid[row][column] == grid[lastRows.back()][lastColumns.back()])
		{
			cout << endl << "[MATCH]"  << endl << endl;
			visible[row][column] = grid[row][column];
			lastRows.push_back(-1);
			lastColumns.push_back(-1);
			return;
		}			
        // Otherwise, make the last cell invisible (set it to *)
		// No match case
		else if(grid[row][column] != grid[lastRows.back()][lastColumns.back()])
		{
			visible[row][column] = grid [row][column];
			
			// Copied show() function code, needed because view is not defined in this scope
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
				
			cout << endl << "[NO MATCH]"  << endl << endl;
			
			visible[row][column] = '*';
			visible[lastRows.back()][lastColumns.back()] = '*';
			lastRows.push_back(-1);
			lastColumns.push_back(-1);
			return;
		} 
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
}

// Show the board
// Read in coordinates
// Until we're done
void Controller::loop() {
    int row, col;
    while (!model->gameOver(model)) {
        view->show(model);
        cout << endl << "Enter row:    ";
        cin >> row;
		// Handy break out of game case for ease of testing
		if(row == -1)
		{
			delete model;
			delete view;
			exit(0);
		}
        cout << "Enter column: ";
		// Handy break out of game case for ease of testing
        cin >> col;
		if(col == -1) 
		{
			delete model;
			delete view;
			exit(0);
		}
        model->flip(row, col, model);
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