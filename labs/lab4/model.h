#include <vector>

#ifndef _MODEL_H
#define _MODEL_H

<<<<<<< HEAD
enum State { FIRST_MOVE, CHECKING, NO_MATCH };

//State state = FIRST_MOVE; // When user first starts, he is flipping the first in a pair
=======
enum State { INIT, FIRST, NO_MATCH };
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78

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
    // Is the game over?
    bool gameOver();
<<<<<<< HEAD
	State currentState();
=======
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
private:
    // Is the row/column valid?
    bool valid(int row, int column);
    // Did the cell at current row/column match the cell at the last row/column 
    bool matched(int row, int column);
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
    std::vector<int> lastRow;
    std::vector<int> lastColumn;
<<<<<<< HEAD
    State state = FIRST_MOVE;
=======
    State state;
>>>>>>> cfd4033199ecfdbe958a674e52aee0233ac2fd78
};


#endif