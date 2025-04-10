#include <stdio.h>
#include <stdlib.h>
#include "resources.h"
#include "score.h"
#include <windows.h>
#include <mmsystem.h>

bool gameOver = false;
static int gravityInterval = 1000;

void playBGM() 
{
    char command[256];

    // Close any existing BGM (to avoid multiple loops)
    mciSendString("close bgm", NULL, 0, NULL);

    // Open and loop the background music
    sprintf(command, "open \"OST and SFX\\TetrisSoloModeOst.wav\" type waveaudio alias bgm");
    mciSendString(command, NULL, 0, NULL);
    
    sprintf(command, "play bgm repeat");
    mciSendString(command, NULL, 0, NULL);
}

void playSFX(const char* alias, const char* file) 
{
    char command[256];

    // Close the previous instance of the sound
    sprintf(command, "close %s", alias);
    mciSendString(command, NULL, 0, NULL);

    // Open sound file again
    sprintf(command, "open \"%s\" type waveaudio alias %s", file, alias);
    mciSendString(command, NULL, 0, NULL);

    // Play sound asynchronously
    sprintf(command, "play %s", alias);
    mciSendString(command, NULL, 0, NULL);
}

void gotoxy(int x, int y) 
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int generateRandomNumber() 
{
    static int lastNum = -1; 
    int min = 1, max = 7;
    int newNum;

    srand(time(NULL));

    do 
	{
        newNum = min + rand() % (max - min + 1);
    } while (newNum == lastNum); // Non repeating RNG

    lastNum = newNum;
    return newNum;
}

bool collision(Tetromino* t, int board[boardRows][boardCols], int dx, int dy)
{
	Block* temp = t->head;
	
	while (temp) 
    {
        int newX = temp->x;
        int newY = temp->y + dy;
        
        if (newY < 0 ||newY >= boardRows) 
        {
            return true;
        }

        if (newY >= 0 && board[newY][newX] == 1) 
        {
            return true;
        }
        
        temp = temp->next;
    }

    return false;
}

bool checkGameOver(int board[boardRows][boardCols]) 
{
    for (col = 0; col < boardCols; col++) 
    {
        if (board[3][col] == 1) // If any block is at row 3, game over
        {
            gotoxy(5, boardRows + 2);
            printf("GAME OVER!\n");

            // Clear the board
            for (row = 0; row < boardRows; row++) 
            {
                for (col = 0; col < boardCols; col++) 
                {
                    board[row][col] = 0;
                }
            }

            if (score > highScore) 
            {
                saveHighScore(score);
            }

            elapsedGameTime = 0;
            difficultyLevel = 0;
            gravityInterval = 1000;
            score = 0;
            gameOver = true;

            return true; // Game over
        }
    }
    return false; // Game continues
}


void storeTetromino(Tetromino* t, int board[boardRows][boardCols], int colorBoard[boardRows][boardCols]) 
{
    Block* temp = t->head;
    int row, col;
    int clearedLines = 0;
	static int comboCount = 0;

    // Store Tetromino in the board
    while (temp != NULL) 
	{
        board[temp->y][temp->x] = 1;          // Mark as occupied
        colorBoard[temp->y][temp->x] = t->bgColor; // Store color of the Tetromino
        temp = temp->next;
    }
    setColor(7);
    printBoard(t, board, colorBoard);  
    Sleep(10);
	gotoxy(13, 2);
	printf("             ");
    if (checkGameOver(board)) 
    {
        return; // Exit early if game over
    }

    for (row = 0; row < boardRows; row++) 
    {
        bool fullRow = true;

        for (col = 0; col < boardCols; col++) 
        {
            if (board[row][col] == 0) 
            {
                fullRow = false;
                break;
            }
        }

        if (fullRow) 
        {
            // Shift all rows down
            for (r = row; r > 0; r--) 
            {
                for (col = 0; col < boardCols; col++) 
                {
                    board[r][col] = board[r - 1][col];
                    colorBoard[r][col] = colorBoard[r - 1][col];
                    
                }
            }

            // Clear the top row
            for (col = 0; col < boardCols; col++) 
            {
                board[0][col] = 0;
            }
            clearedLines++;
        }  
    }
    
    if (clearedLines > 0) 
    {
    	playSFX("clear1", "OST and SFX\\clear1.wav");
    	comboCount = comboCount + clearedLines;// Increase combo multiplier
        score += (100 * clearedLines) + (100 * (comboCount - 1));  
        gotoxy(boardCols * 2 + 36, 13);
        if(comboCount == 2)
        {
        	playSFX("clear2", "OST and SFX\\clear2.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 3)
		{
			playSFX("clear3", "OST and SFX\\clear3.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 4)
		{
			playSFX("clear4", "OST and SFX\\clear4.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 5)
		{
			playSFX("clear5", "OST and SFX\\clear5.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 6)
		{
			playSFX("clear6", "OST and SFX\\clear6.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 7)
		{
			playSFX("clear7", "OST and SFX\\clear7.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 8)
		{
			playSFX("clear8", "OST and SFX\\clear8.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
        else if(comboCount == 9)
		{
			playSFX("clear9", "OST and SFX\\clear9.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 10)
		{
			playSFX("clear10", "OST and SFX\\clear10.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount == 11)
		{
			playSFX("clear11", "OST and SFX\\clear11.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
        else if(comboCount == 12)
		{
			playSFX("clear12", "OST and SFX\\clear12.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
		else if(comboCount > 12)
		{
			playSFX("clear13", "OST and SFX\\clear13.wav");
        	printf("COMBO x%d!!", comboCount);
        	gotoxy(boardCols * 2 + 36, 14);
        	printf("+%d pts!!", (comboCount - 1) * 100);
		}
    } 
    else 
    {
        comboCount = 0;  // Reset combo if no line is cleared
        gotoxy(boardCols * 2 + 36, 13);
        printf("            ");
        gotoxy(boardCols * 2 + 36, 14);
        printf("            ");
    }
    free(t);
}

Tetromino* generateTetromino(int choice, int x, int y) 
{
	Tetromino* t = NULL;

    switch(choice)
    {
        case 1: t = LineBlock(x, y); break;
        case 2: t = tBlock(x, y); break;
        case 3: t = lBlock(x, y); break;
        case 4: t = OBlock(x, y); break;
        case 5: t = JBlock(x, y); break;
        case 6: t = SBlock(x, y); break;
        case 7: t = ZBlock(x, y); break;
    }
    return t;
}

int getTetrominoIndex(const char* name) 
{
    if (strcmp(name, "Line") == 0) return 1;
    if (strcmp(name, "T") == 0) return 2;
    if (strcmp(name, "L") == 0) return 3;
    if (strcmp(name, "Square") == 0) return 4;
    if (strcmp(name, "J") == 0) return 5;
    if (strcmp(name, "S") == 0) return 6;
    if (strcmp(name, "Z") == 0) return 7;
    return 0; // Default case (should never happen)
}

void printTetrominoPreview(int choice, int x, int y) 
{
    if (choice < 1 || choice > 7) return; // Ensure choice is valid
  	
	setColor(WHITE);
    gotoxy(x, y);
    
    
    
    for (i = 0; i < 4; i++) 
    {
        gotoxy(x, y + i); // Move cursor to correct position
        for (j = 0; j < 4; j++) 
        {
            if (tetrominoShapes[choice - 1][i][j] == 'O') 
            {
            	switch(choice)
				{
					case 1: setColor(BG_BLUE); break;
					case 2: setColor(BG_GREEN); break;
					case 3: setColor(BG_LIGHT_RED); break;
					case 4: setColor(BG_BROWN); break;
					case 5: setColor(BG_LIGHT_MAGENTA); break;
					case 6: setColor(BG_CYAN); break;
					case 7: setColor(BG_RED); break;
				}
				printf("  ");
            }
            else 
            {
            	setColor(BG_BLACK);
                printf("  ");
            }
        }
        setColor(7);
    }
}

void printSideText() 
{
    gotoxy(14, 6);
    printf("Next Block:");
    printTetrominoPreview(nextChoice, 14, 7);

    gotoxy(14, 13);
    printf("Held Block:");
    if (heldTetromino) 
	{
        printTetrominoPreview(getTetrominoIndex(heldTetromino->type), 14, 14);
    }

     //Display Score and High Score
    gotoxy(boardCols * 2 + 33, 6);
    printf("Score: %d", score);
    gotoxy(boardCols * 2 + 33, 7);
    printf("High Score: %d", highScore);

    // Display Time & Level
    int elapsedMinutes = elapsedGameTime / 60000;  // Convert to minutes
    int elapsedSeconds = (elapsedGameTime % 60000) / 1000;  // Remaining seconds
    gotoxy(14, 20);
    printf("Time: %d:%02d", elapsedMinutes, elapsedSeconds);
    gotoxy(14, 22);
    printf("Level: %d", difficultyLevel + 1);
}


void printBoard(Tetromino* t, int BOARD[boardRows][boardCols], int colorBoard[boardRows][boardCols])
{
	gTetromino* g = createGhostTetromino(t);
	if (!g) return;
	ghostPos(g, BOARD);
    int gameOverFlag = 0;
    char board[boardRows][boardCols];
    
    gotoxy(28, 0);
    printf("[]====================[]");
    gotoxy(8, 0);
    printf("[]==================");
    for(i = 0; i < 24; i++)
    {
    	gotoxy(8, i+1);
    	printf("||");
	}
	gotoxy(8, 25);
	printf("[]==================");
	
	gotoxy(10 , 4);
	printf("==================");
	
	gotoxy(10 , 11);
	printf("==================");
	
	gotoxy(10 , 18);
	printf("==================");
	
	gotoxy(52, 25);
	printf("==================[]");
	gotoxy(52, 0);
	printf("==================[]");
	
	for(i = 0; i < 24; i++)
    {
    	gotoxy(70, i+1);
    	printf("||");
	}
	
	gotoxy(52 , 4);
	printf("==================");
	
	gotoxy(52 , 11);
	printf("==================");
	
	gotoxy(52 , 18);
	printf("==================");
    
    gotoxy(28, 1);
    
	
    // Copy stored blocks
    for (i = 0; i < boardRows; i++)
    {
    	
        for (j = 0; j < boardCols; j++)
        {
            if (BOARD[i][j] == 1)
                board[i][j] = '#';  // Stored blocks
            else
                board[i][j] = ' ';
        }
    }

	gBlock* gTemp = g->head;
    while (gTemp) 
	{
        board[gTemp->gy][gTemp->gx] = 'G';
        gTemp = gTemp->next;
    }
	
    // active Tetromino blocks
    Block* temp = t->head;
    while (temp)
    {
        if (temp->y >= 0 && temp->y < boardRows && temp->x >= 0 && temp->x < boardCols)
        {
            board[temp->y][temp->x] = '@';  // Active Tetromino symbol
        }
        temp = temp->next;
    }

    // Print the board boarders
    for (i = 0; i <= boardRows; i++)
    {
    	gotoxy(28, i+1);
        for (j = 0; j <= boardCols + 1; j++)
        {
            if (i == boardRows) 
            {
                // Bottom border
                if (j == 0 || j == boardCols + 1)
                {
                	setColor(WHITE);
                	printf("[]");
                	setColor(7);
				}
                    
                else
                {
                	setColor(WHITE);
                	printf("==");
                	setColor(7);
				}
                    
            }
            else if ((j == 0 && i ==  4) || (j == 11 && i ==  4))
            {
                // Left & Right Borders
                // Block spawn hub
                setColor(RED);
                printf("||");
                setColor(7);
            }
            else if (j == 0 || j == boardCols + 1)
            {
                // Side borders
                setColor(WHITE);
                printf("||");
                setColor(7);
            }
            else if (board[i][j - 1] == '#')
            {
                setColor(colorBoard[i][j - 1]); // Apply stored color
                printf("  ");
                setColor(7); // Reset to default color after printing
            }
            else if (board[i][j - 1] == '@')
            {
                // Active block
                setColor(t->bgColor);
                printf("  ");
                setColor(7);
            }
           	else if (board[i][j - 1] == 'G')
           	{
           		setColor(BG_DARK_GRAY);
                printf("  ");
                setColor(7);
			}
            else
            {
                // Empty space
                setColor(DARK_GRAY);
                printf("[]");
            }
        }
        printf("\n");
    }
    printSideText();
}

void swapTetromino(Tetromino** currentTetromino)  
{
    if (hasSwapped) 
	{
		playSFX("invalid", "OST and SFX\\invalid.wav");
		gotoxy(13, 2);
		printf("SWAP LOCKED!");
		return;
	} // Prevent multiple swaps per drop
	
	playSFX("notif", "OST and SFX\\notif.wav");
    if (!heldTetromino) 
    {
        // First time swapping: move CURRENT to HELD
        heldTetromino = *currentTetromino;
        *currentTetromino = generateTetromino(nextChoice, 5, 1); // Reset to x=5, y=1
        nextChoice = generateRandomNumber(); // Prepare new next piece
    } 
    else 
    {
        // Swap CURRENT and HELD block
        Tetromino* temp = heldTetromino;
        heldTetromino = *currentTetromino;  
        *currentTetromino = temp; // Bring back held block

        // Reset ALL blocks in the Tetromino to start at (x = 5, y = 1)
        Block* block = (*currentTetromino)->head;
        
        int minX = boardCols, minY = boardRows;
        
        // Find the top-leftmost block of the Tetromino
        while (block) {
            if (block->x < minX) minX = block->x;
            if (block->y < minY) minY = block->y;
            block = block->next;
        }

        // Calculate offsets to move the piece to (x=5, y=1)
        int xOffset = 5 - minX;
        int yOffset = 1 - minY;

        // Apply the offsets to all blocks
        block = (*currentTetromino)->head;
        while (block) {
            block->x += xOffset;
            block->y += yOffset;
            block = block->next;
        }
    }

    hasSwapped = true;  // Lock swapping for this drop
}

Tetromino* moveTetromino(Tetromino* t, int board[boardRows][boardCols], int dx, int dy) 
{
    Block* temp = t->head;
    
    while (temp) 
	{
		int newX = temp->x + dx;
		int newY = temp->y + dy;
		
		if (newX < 0 || newY < 0 || newX >= boardCols|| newY >= boardRows)
		{
			return t;
		}
        
        if (board[newY][newX] == 1)
        {
        	return t; // indicator for occupied space
		}
        temp = temp->next;
    }
    
    
    temp = t->head;
    while (temp)
    {
    	temp->x += dx;
        temp->y += dy;
        temp = temp->next;
	}
    	
    return t;
}

void ghostPos(gTetromino* g, int board[boardRows][boardCols])
{
    bool collide = false;
    
    while (collide == false) 
	{
        gBlock* temp = g->head;
        while (temp) 
		{
            if (temp->gy + 1 >= boardRows || board[temp->gy + 1][temp->gx] == 1) 
			{
                collide = true;
                break;
            }
            temp = temp->next;
        }

        if (collide == false) 
		{
            temp = g->head;
            while (temp) 
			{
                temp->gy += 1;
                temp = temp->next;
            }
        }
    }
}

void rotateTetromino(Tetromino* t, int clockwise)
{
    if (t->isOBlock) return;  // Ignore rotation for O-blocks

    Block* p = t->head->next; // Pivot point (2nd node)
    Block* temp = t->head;

    int newX[4], newY[4], i = 0;
    int minX = boardCols, maxX = 0, minY = boardRows, maxY = 0;
    
    Block* tempSim = t->head;
    while (tempSim)
    {
        int dx = tempSim->x - p->x;
    	int dy = tempSim->y - p->y;

        if (clockwise)
        {
            newX[i] = p->x + dy;
            newY[i] = p->y - dx;
        }
        else
        {
            newX[i] = p->x - dy;
            newY[i] = p->y + dx;
        }

        // Track boundaries
        if (newX[i] < minX) minX = newX[i];
        if (newX[i] > maxX) maxX = newX[i];
        if (newY[i] < minY) minY = newY[i];
        if (newY[i] > maxY) maxY = newY[i];
		
        tempSim = tempSim->next;
        i++;
    }
    
    // rotation collision checker
	for(j = 0; j < 4; j++)
	{
		if (board[newY[j]][newX[j]] == 1)
		{
			return; // Stop rotation if collision occurs
		}
	}
    int shiftX = 0, shiftY = 0;
    if (minX < 0) shiftX = -minX;  // Push right if out on the left
    if (maxX >= boardCols) shiftX = boardCols - 1 - maxX;  // Push left if out on the right
    if (minY < 0) shiftY = -minY;  // Push down if out at the top
    if (maxY >= boardRows) shiftY = boardRows - 1 - maxY;  // Push up if out at the bottom

    i = 0;
    temp = t->head;
    while (temp)
    {
        temp->x = newX[i] + shiftX;
        temp->y = newY[i] + shiftY;
        temp = temp->next;
        i++;
    }
}

void moveBlock(int choice)
{
    int x = 5, y = 1;
    char key;
    Tetromino* t = NULL;
    bool collide = true;
    highScore = loadHighScore();
    
    switch(choice)
    {
        case 1: t = LineBlock(x, y); break;
        case 2: t = tBlock(x, y); break;
        case 3: t = lBlock(x, y); break;
        case 4: t = OBlock(x, y); break;
        case 5: t = JBlock(x, y); break;
        case 6: t = SBlock(x, y); break;
        case 7: t = ZBlock(x, y); break;
    }

    // Hide cursor to avoid flickering
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Timer-based gravity
    static DWORD gameStartTime = 0;
    if (gameStartTime == 0) gameStartTime = GetTickCount();  // Start game timer once

    DWORD lastDropTime = GetTickCount(); // Track last drop time
    
	hasSwapped = false;
    do
    {
        gotoxy(10, 10);
        printBoard(t, board, colorBoard);  // Print the updated board

        // Handle player input
        if (_kbhit())  
        {
        	int dx = 0, dy = 0; 
            key = _getch();
            if(key == -32)
            {
            	key = _getch();
        	}
        		
            switch (key) 
            {
                case 'a': case 'A': case 75:
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					dx = -1; 
					break;
				}
                case 's': case 'S': case 80:
				{
					//playSFX("move", OST and SFX\\move_side.wav",;
					dy = 1; 
					break;
				}
                case 'd': case 'D': case 77:
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					dx = 1; 
					break;
				} 
                case 'q': case 'Q': case 72:
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					rotateTetromino(t, 1); 
					break;
				}
                case 'e': case 'E': 
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					rotateTetromino(t, 0); 
					break;
				}
                case ' ':
                    while (!collision(t, board, 0, 1)) 
                    {
                        moveTetromino(t, board, 0, 1);
                    }
                    storeTetromino(t, board, colorBoard);
                    playSFX("drop", "OST and SFX\\drop_impact.wav");
                    collide = false;
                    return;  // Block has landed, exit the function
                case 'x': case 'X':
                	swapTetromino(&t);
                    break;
                case '1': exit(0);
            }
            

            // Move if no collision
            if (!collision(t, board, dx, dy))
            {
                moveTetromino(t, board, dx, dy);
            }
            	
			
			
        }

        // Gravity logic: Drop based on current speed
        if (GetTickCount() - lastDropTime >= gravityInterval)  
        {
            lastDropTime = GetTickCount();  // Reset only the gravity timer
            
            if (!collision(t, board, 0, 1)) 
            {
                moveTetromino(t, board, 0, 1);  // Move down
            }
            else 
            {
                storeTetromino(t, board, colorBoard);  // Lock the piece when it hits the ground
                hasSwapped = false;
                collide = false;
            }
        }

        // Difficulty Increase Logic (Every 2 minutes)
        
        
        elapsedGameTime = GetTickCount() - gameStartTime;
        if (elapsedGameTime >= (difficultyLevel + 1) * 60000)  // Every 1 minute
        {
            difficultyLevel++;
            gravityInterval -= 200;  // Reduce drop speed

            if (gravityInterval < 175)  
            {
            	gravityInterval = 175;  // New minimum speed
			}
            
        }

    } while (collide == true);

    // Show the cursor again when done
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void soloMode() 
{

    int currentChoice = generateRandomNumber();
    nextChoice = generateRandomNumber();  
	PlaySound("OST and SFX\\TetrisSoloModeOst.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	gameOver = false;
	playSFX("notif", "OST and SFX\\notif.wav");
    while (gameOver == false) 
    {
        moveBlock(currentChoice);  
        currentChoice = nextChoice;  
        nextChoice = generateRandomNumber();  
    }
}



