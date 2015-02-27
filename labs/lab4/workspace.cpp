    // If the row and column are not valid, break out and don't do anything
    if (!valid(row, column)) { return; }
	// Ensures the row and column given this time is not the same as the previous set
	else if(row == lastRows.back() && column == lastColumns.back())
	{
		return;
	}
	
	// Ensures the row and column given is not an already flipped cell
	/*
	else if(visible[row][column] != )
	{
		return;	
	}
	*/
	
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
			    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,
				0x03, 0x3A, 0x01));

				SDL_Rect dest;
				char letter;
				for (int i = 0; i < model->getHeight(); i++) {
					for (int j = 0; j < model->getWidth(); j++) {
						dest.x = j * 80;
						dest.y = i * 80;
						letter = model->get(i, j);
            
				 SDL_BlitSurface( letters[letter], NULL, screen, &dest );
					}
				}

			SDL_UpdateWindowSurface(window);
			
			visible[row][column] = '*';
			visible[lastRows.back()][lastColumns.back()] = '*';
			lastRows.push_back(-1);
			lastColumns.push_back(-1);
			return;
		} 