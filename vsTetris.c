#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include "VSResources.h"

int boardOffset = 24;
int boardOffsetBoarder = 80;

static int gravityInterval = 1000;


void P2printBoard(P2Tetromino* t, int P2board[boardRows][boardCols], int P2colorBoard[boardRows][boardCols])
{
	P2gTetromino* g = P1createGhostTetromino(t);
	if (!g) return;
	P2ghostPos(g, P1board);
    int P2gameOverFlag = 0;
    char P2Cboard[boardRows][boardCols];
    
    gotoxy(28 + boardOffset, 0);
    printf("[]====================[]");
    gotoxy(8 + boardOffset, 0);
    printf("==================[]");
    for(i = 0; i < 24; i++)
    {
    	gotoxy(8 + boardOffsetBoarder, i+1);
    	printf("||");
	}
	gotoxy(8 + boardOffsetBoarder, 25);
	printf("==================[]");
	
	gotoxy(10 + boardOffsetBoarder, 4);
	printf("==================");
	
	gotoxy(10 + boardOffsetBoarder, 11);
	printf("==================");
	
	gotoxy(10 + boardOffsetBoarder, 18);
	printf("==================");
    
    gotoxy(28 + boardOffsetBoarder, 1);
    
	
    // Copy stored blocks
    for (i = 0; i < boardRows; i++)
    {
    	
        for (j = 0; j < boardCols; j++)
        {
            if (P2board[i][j] == 1)
                P2Cboard[i][j] = '#';  // Stored blocks
            else
                P2Cboard[i][j] = ' ';
        }
    }

	P2gBlock* gTemp = g->head;
    while (gTemp) 
	{
        P2Cboard[gTemp->gy][gTemp->gx] = 'G';
        gTemp = gTemp->next;
    }
	
    // active Tetromino blocks
    P2Block* temp = t->head;
    while (temp)
    {
        if (temp->y >= 0 && temp->y < boardRows && temp->x >= 0 && temp->x < boardCols)
        {
            P2Cboard[temp->y][temp->x] = '@';  // Active Tetromino symbol
        }
        temp = temp->next;
    }

    // Print the board boarders
    for (i = 0; i <= boardRows; i++)
    {
    	gotoxy(28 + boardOffset, i+1);
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
            else if (P2Cboard[i][j - 1] == '#')
            {
                setColor(P2colorBoard[i][j - 1]); // Apply stored color
                printf("  ");
                setColor(7); // Reset to default color after printing
            }
            else if (P2Cboard[i][j - 1] == '@')
            {
                // Active block
                setColor(t->bgColor);
                printf("  ");
                setColor(7);
            }
           	else if (P2Cboard[i][j - 1] == 'G')
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
    P2printSideText();
}

void P1printBoard(P1Tetromino* t, int P1board[boardRows][boardCols], int P1colorBoard[boardRows][boardCols])
{
	P1gTetromino* g = P1createGhostTetromino(t);
	if (!g) return;
	P1ghostPos(g, P1board);
    int P1gameOverFlag = 0;
    char P1Cboard[boardRows][boardCols];
    
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
    
    gotoxy(28, 1);
    
	
    // Copy stored blocks
    for (i = 0; i < boardRows; i++)
    {
    	
        for (j = 0; j < boardCols; j++)
        {
            if (P1board[i][j] == 1)
                P1Cboard[i][j] = '#';  // Stored blocks
            else
                P1Cboard[i][j] = ' ';
        }
    }

	P1gBlock* gTemp = g->head;
    while (gTemp) 
	{
        P1Cboard[gTemp->gy][gTemp->gx] = 'G';
        gTemp = gTemp->next;
    }
	
    // active Tetromino blocks
    P1Block* temp = t->head;
    while (temp)
    {
        if (temp->y >= 0 && temp->y < boardRows && temp->x >= 0 && temp->x < boardCols)
        {
            P1Cboard[temp->y][temp->x] = '@';  // Active Tetromino symbol
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
            else if (P1Cboard[i][j - 1] == '#')
            {
                setColor(P1colorBoard[i][j - 1]); // Apply stored color
                printf("  ");
                setColor(7); // Reset to default color after printing
            }
            else if (P1Cboard[i][j - 1] == '@')
            {
                // Active block
                setColor(t->bgColor);
                printf("  ");
                setColor(7);
            }
           	else if (P1Cboard[i][j - 1] == 'G')
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
    P1printSideText();
}

void P2printSideText() 
{
    gotoxy(14, 6);
    printf("Next Block:");
    printTetrominoPreview(P2nextChoice, 14, 7);

    gotoxy(14, 13);
    printf("Held Block:");
    if (P2heldTetromino) 
	{
        printTetrominoPreview(getTetrominoIndex(P2heldTetromino->type), 14, 14);
    }

    
    gotoxy(14, 22);
    printf("Score: %d", P2Score);
   
    // Display Time & Level
    int elapsedMinutes = elapsedGameTime / 60000;  // Convert to minutes
    int elapsedSeconds = (elapsedGameTime % 60000) / 1000;  // Remaining seconds
    gotoxy(14, 20);
    printf("Time: %d:%02d", elapsedMinutes, elapsedSeconds);
    gotoxy(14, 23);
    printf("Level: %d", difficultyLevel + 1);
}

void P1printSideText() 
{
    gotoxy(14, 6);
    printf("Next Block:");
    printTetrominoPreview(P1nextChoice, 14, 7);

    gotoxy(14, 13);
    printf("Held Block:");
    if (P1heldTetromino) 
	{
        printTetrominoPreview(getTetrominoIndex(P1heldTetromino->type), 14, 14);
    }

    
    gotoxy(14, 22);
    printf("Score: %d", P1Score);
   
    // Display Time & Level
    int elapsedMinutes = elapsedGameTime / 60000;  // Convert to minutes
    int elapsedSeconds = (elapsedGameTime % 60000) / 1000;  // Remaining seconds
    gotoxy(14, 20);
    printf("Time: %d:%02d", elapsedMinutes, elapsedSeconds);
    gotoxy(14, 23);
    printf("Level: %d", difficultyLevel + 1);
}

void P2ghostPos(P2gTetromino* g, int P2board[boardRows][boardCols])
{
    bool collide = false;
    
    while (collide == false) 
	{
        P2gBlock* temp = g->head;
        while (temp) 
		{
            if (temp->gy + 1 >= boardRows || P1board[temp->gy + 1][temp->gx] == 1) 
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

void P1ghostPos(P1gTetromino* g, int P1board[boardRows][boardCols])
{
    bool collide = false;
    
    while (collide == false) 
	{
        P1gBlock* temp = g->head;
        while (temp) 
		{
            if (temp->gy + 1 >= boardRows || P1board[temp->gy + 1][temp->gx] == 1) 
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

bool P2collision(P2Tetromino* t, int P2board[boardRows][boardCols], int dx, int dy)
{
	P2Block* temp = t->head;
	
	while (temp) 
    {
        int newX = temp->x;
        int newY = temp->y + dy;
        
        if (newY < 0 ||newY >= boardRows) 
        {
            return true;
        }

        if (newY >= 0 && P2board[newY][newX] == 1) 
        {
            return true;
        }
        
        temp = temp->next;
    }

    return false;
}

bool P1collision(P1Tetromino* t, int P1board[boardRows][boardCols], int dx, int dy)
{
	P1Block* temp = t->head;
	
	while (temp) 
    {
        int newX = temp->x;
        int newY = temp->y + dy;
        
        if (newY < 0 ||newY >= boardRows) 
        {
            return true;
        }

        if (newY >= 0 && P1board[newY][newX] == 1) 
        {
            return true;
        }
        
        temp = temp->next;
    }

    return false;
}

P2Tetromino* P2generateTetromino(int choice, int x, int y) 
{
	P2Tetromino* t = NULL;

    switch(choice)
    {
        case 1: t = P2LineBlock(x, y); break;
        case 2: t = P2tBlock(x, y); break;
        case 3: t = P2lBlock(x, y); break;
        case 4: t = P2OBlock(x, y); break;
        case 5: t = P2JBlock(x, y); break;
        case 6: t = P2SBlock(x, y); break;
        case 7: t = P2ZBlock(x, y); break;
    }
    return t;
}

P1Tetromino* P1generateTetromino(int choice, int x, int y) 
{
	P1Tetromino* t = NULL;

    switch(choice)
    {
        case 1: t = P1LineBlock(x, y); break;
        case 2: t = P1tBlock(x, y); break;
        case 3: t = P1lBlock(x, y); break;
        case 4: t = P1OBlock(x, y); break;
        case 5: t = P1JBlock(x, y); break;
        case 6: t = P1SBlock(x, y); break;
        case 7: t = P1ZBlock(x, y); break;
    }
    return t;
}

void P2storeTetromino(P2Tetromino* t, int P2board[boardRows][boardCols], int P2colorBoard[boardRows][boardCols])
{
	P2Block* temp = t->head;
    int row, col;
    int clearedLines = 0;
	static int comboCount = 0;

    // Store Tetromino in the board
    while (temp != NULL) 
	{
        P2board[temp->y][temp->x] = 1;          // Mark as occupied
        P2colorBoard[temp->y][temp->x] = t->bgColor; // Store color of the Tetromino
        temp = temp->next;
    }
    setColor(7);
    P2printBoard(t, P2board, P2colorBoard);  
    Sleep(10);
	gotoxy(13, 2);
	printf("             ");
	
	if (checkGameOver(P2board)) 
    {
    	P2gameOver = true;
        return; // Exit early if game over
    }
    
    for (row = 0; row < boardRows; row++) 
    {
        bool fullRow = true;

        for (col = 0; col < boardCols; col++) 
        {
            if (P2board[row][col] == 0) 
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
                    P2board[r][col] = P2board[r - 1][col];
                    P2colorBoard[r][col] = P2colorBoard[r - 1][col];
                    
                }
            }

            // Clear the top row
            for (col = 0; col < boardCols; col++) 
            {
                P2board[0][col] = 0;
            }
            clearedLines++;
        }  
    }
    
    if (clearedLines > 0) 
    {
    	playSFX("clear1", "OST and SFX\\clear1.wav");
    	comboCount = comboCount + clearedLines;// Increase combo multiplier
        P1Score += (100 * clearedLines) + (100 * (comboCount - 1));  
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

void P1storeTetromino(P1Tetromino* t, int P1board[boardRows][boardCols], int P1colorBoard[boardRows][boardCols])
{
	P1Block* temp = t->head;
    int row, col;
    int clearedLines = 0;
	static int comboCount = 0;

    // Store Tetromino in the board
    while (temp != NULL) 
	{
        P1board[temp->y][temp->x] = 1;          // Mark as occupied
        P1colorBoard[temp->y][temp->x] = t->bgColor; // Store color of the Tetromino
        temp = temp->next;
    }
    setColor(7);
    P1printBoard(t, P1board, P1colorBoard);  
    Sleep(10);
	gotoxy(13, 2);
	printf("             ");
	
	if (checkGameOver(P1board)) 
    {
    	P1gameOver = true;
        return; // Exit early if game over
    }
    
    for (row = 0; row < boardRows; row++) 
    {
        bool fullRow = true;

        for (col = 0; col < boardCols; col++) 
        {
            if (P1board[row][col] == 0) 
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
                    P1board[r][col] = P1board[r - 1][col];
                    P1colorBoard[r][col] = P1colorBoard[r - 1][col];
                    
                }
            }

            // Clear the top row
            for (col = 0; col < boardCols; col++) 
            {
                P1board[0][col] = 0;
            }
            clearedLines++;
        }  
    }
    
    if (clearedLines > 0) 
    {
    	playSFX("clear1", "OST and SFX\\clear1.wav");
    	comboCount = comboCount + clearedLines;// Increase combo multiplier
        P1Score += (100 * clearedLines) + (100 * (comboCount - 1));  
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

void P2swapTetromino(P2Tetromino** P2currentTetromino)  
{
    if (P2hasSwapped) 
	{
		playSFX("invalid", "OST and SFX\\invalid.wav");
		gotoxy(13, 2);
		printf("SWAP LOCKED!");
		return;
	} // Prevent multiple swaps per drop
	
	playSFX("notif", "OST and SFX\\notif.wav");
    if (!P2heldTetromino) 
    {
        // First time swapping: move CURRENT to HELD
        P2heldTetromino = *P2currentTetromino;
        *P2currentTetromino = P2generateTetromino(P2nextChoice, 5, 1); // Reset to x=5, y=1
        P2nextChoice = P2generateRandomNumber(); // Prepare new next piece
    } 
    else 
    {
        // Swap CURRENT and HELD block
        P2Tetromino* temp = P2heldTetromino;
        P2heldTetromino = *P2currentTetromino;  
        *P2currentTetromino = temp; // Bring back held block

        // Reset ALL blocks in the Tetromino to start at (x = 5, y = 1)
        P2Block* block = (*P2currentTetromino)->head;
        
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
        block = (*P2currentTetromino)->head;
        while (block) {
            block->x += xOffset;
            block->y += yOffset;
            block = block->next;
        }
    }

    P1hasSwapped = true;  // Lock swapping for this drop
}

void P1swapTetromino(P1Tetromino** P1currentTetromino)  
{
    if (P1hasSwapped) 
	{
		playSFX("invalid", "OST and SFX\\invalid.wav");
		gotoxy(13, 2);
		printf("SWAP LOCKED!");
		return;
	} // Prevent multiple swaps per drop
	
	playSFX("notif", "OST and SFX\\notif.wav");
    if (!P1heldTetromino) 
    {
        // First time swapping: move CURRENT to HELD
        P1heldTetromino = *P1currentTetromino;
        *P1currentTetromino = P1generateTetromino(P1nextChoice, 5, 1); // Reset to x=5, y=1
        P1nextChoice = P1generateRandomNumber(); // Prepare new next piece
    } 
    else 
    {
        // Swap CURRENT and HELD block
        P1Tetromino* temp = P1heldTetromino;
        P1heldTetromino = *P1currentTetromino;  
        *P1currentTetromino = temp; // Bring back held block

        // Reset ALL blocks in the Tetromino to start at (x = 5, y = 1)
        P1Block* block = (*P1currentTetromino)->head;
        
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
        block = (*P1currentTetromino)->head;
        while (block) {
            block->x += xOffset;
            block->y += yOffset;
            block = block->next;
        }
    }

    P1hasSwapped = true;  // Lock swapping for this drop
}

P2Tetromino* P2moveTetromino(P2Tetromino* t, int P2board[boardRows][boardCols], int dx, int dy) 
{
    P2Block* temp = t->head;
    
    while (temp) 
	{
		int newX = temp->x + dx;
		int newY = temp->y + dy;
		
		if (newX < 0 || newY < 0 || newX >= boardCols|| newY >= boardRows)
		{
			return t;
		}
        
        if (P2board[newY][newX] == 1)
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


P1Tetromino* P1moveTetromino(P1Tetromino* t, int P1board[boardRows][boardCols], int dx, int dy) 
{
    P1Block* temp = t->head;
    
    while (temp) 
	{
		int newX = temp->x + dx;
		int newY = temp->y + dy;
		
		if (newX < 0 || newY < 0 || newX >= boardCols|| newY >= boardRows)
		{
			return t;
		}
        
        if (P1board[newY][newX] == 1)
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

void P2rotateTetromino(P2Tetromino* t, int clockwise)
{
    if (t->isOBlock) return;  // Ignore rotation for O-blocks

    P2Block* p = t->head->next; // Pivot point (2nd node)
    P2Block* temp = t->head;

    int newX[4], newY[4], i = 0;
    int minX = boardCols, maxX = 0, minY = boardRows, maxY = 0;
    
    P2Block* tempSim = t->head;
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
		if (P2board[newY[j]][newX[j]] == 1)
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

void P1rotateTetromino(P1Tetromino* t, int clockwise)
{
    if (t->isOBlock) return;  // Ignore rotation for O-blocks

    P1Block* p = t->head->next; // Pivot point (2nd node)
    P1Block* temp = t->head;

    int newX[4], newY[4], i = 0;
    int minX = boardCols, maxX = 0, minY = boardRows, maxY = 0;
    
    P1Block* tempSim = t->head;
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
		if (P1board[newY[j]][newX[j]] == 1)
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

void VSmoveBlock(int P1choice, int P2choice)
{
    int x = 5, y = 1;
    char key;
    P1Tetromino* t1 = NULL;
    P2Tetromino* t2 = NULL;
    int P1nextChoice = P1generateRandomNumber();
    int P2nextChoice = P2generateRandomNumber();
    
    switch(P1choice)
    {
        case 1: t1 = P1LineBlock(x, y); break;
        case 2: t1 = P1tBlock(x, y); break;
        case 3: t1 = P1lBlock(x, y); break;
        case 4: t1 = P1OBlock(x, y); break;
        case 5: t1 = P1JBlock(x, y); break;
        case 6: t1 = P1SBlock(x, y); break;
        case 7: t1 = P1ZBlock(x, y); break;
    }
    
    switch(P2choice)
    {
        case 1: t2 = P2LineBlock(x, y); break;
        case 2: t2 = P2tBlock(x, y); break;
        case 3: t2 = P2lBlock(x, y); break;
        case 4: t2 = P2OBlock(x, y); break;
        case 5: t2 = P2JBlock(x, y); break;
        case 6: t2 = P2SBlock(x, y); break;
        case 7: t2 = P2ZBlock(x, y); break;
    }
    
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    static DWORD gameStartTime = 0;
    if (gameStartTime == 0) gameStartTime = GetTickCount(); // start timer

    DWORD lastDropTime = GetTickCount(); // Track last drop time
    
	P1hasSwapped = false;
    do
    {
        gotoxy(10, 10);
        P1printBoard(t1, P1board, P1colorBoard);
        P2printBoard(t2, P2board, P2colorBoard);

        
        if (_kbhit())  
        {
        	int p1x = 0, p1y = 0; 
        	int p2x = 0, p2y = 0; 
        	
            key = _getch();
            if(key == -32)
            {
            	key = _getch();
        	}
        		
            switch (key) 
            {
                case 'a': case 'A':
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					p1x = -1; 
					break;
				}
                case 's': case 'S':
				{
					//playSFX("move", OST and SFX\\move_side.wav",;
					p1y = 1; 
					break;
				}
                case 'd': case 'D':
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					p1x = 1; 
					break;
				} 
                case 'q': case 'Q':
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					P1rotateTetromino(t1, 1); 
					break;
				}
                case 'e': case 'E': 
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					P1rotateTetromino(t1, 0); 
					break;
				}
                case ' ':
                    while (!P1collision(t1, P1board, 0, 1)) 
                    {
                        P1moveTetromino(t1, P1board, 0, 1);
                    }
                    P1storeTetromino(t1, P1board, P1colorBoard);
                    //playSFX("drop", "OST and SFX\\drop_impact.wav");
                    
                    return;  // Block has landed, exit the function
                case 'x': case 'X':
                	P1swapTetromino(&t1);
                    break;
                    
            	// Player 2
                case '4':
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					p2x = -1; 
					break;
				}
                case '5':
				{
					//playSFX("move", OST and SFX\\move_side.wav",;
					p2y = 1; 
					break;
				}
                case '6':
				{
					//playSFX("move", "OST and SFX\\move_side.wav");
					p2x = 1; 
					break;
				} 
                case '7': 
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					P2rotateTetromino(t2, 1); 
					break;
				}
                case '9':
				{
					//playSFX("rotate", "OST and SFX\\rotate.wav");
					P2rotateTetromino(t2, 0); 
					break;
				}
                case '0':
                    while (!P2collision(t2, P2board, 0, 1)) 
                    {
                        P2moveTetromino(t2, P2board, 0, 1);
                    }
                    P2storeTetromino(t2, P2board, P2colorBoard);
                    //playSFX("drop", "OST and SFX\\drop_impact.wav");
                    
                    return;  // Block has landed, exit the function
                case '+':
                	P2swapTetromino(&t2);
                    break;
                case '=': exit(0);
            }
            

            // Move if no collision
            if (!P1collision(t1, P1board, p1x, p1y))
            {
                P1moveTetromino(t1, P1board, p1x, p1y);
            }
            
            if (!P2collision(t2, P2board, p2x, p2y))
            {
                P2moveTetromino(t2, P2board, p2x, p2y);
            }

        }

        // Gravity logic: Drop based on current speed
        if (GetTickCount() - lastDropTime >= gravityInterval)  
        {
            lastDropTime = GetTickCount();  // Reset only the gravity timer
            
            if (!P1collision(t1, P1board, 0, 1)) 
            {
                P1moveTetromino(t1, P1board, 0, 1);
            }
            else 
            {
                P1storeTetromino(t1, P1board, P1colorBoard);  // Lock the piece when it hits the ground
                P1choice = P1nextChoice;
                P1hasSwapped = false;
                
            }
            
            if (!P2collision(t2, P2board, 0, 1)) 
            {
                P2moveTetromino(t2, P2board, 0, 1);
            }
            else 
            {
                P2storeTetromino(t2, P2board, P2colorBoard);  // Lock the piece when it hits the ground
                P2choice = P2nextChoice;
                P2hasSwapped = false;
                
            }
        }
        
        
        
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

    } while (P2gameOver == false && P1gameOver == false); // issue flag: might reset Player 2/ Player 1

    // Show the cursor again when done
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int P2generateRandomNumber() 
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

int P1generateRandomNumber() 
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

void vsMode()
{
	int P1currentChoice = P1generateRandomNumber();
	int P2currentChoice = P2generateRandomNumber();
	PlaySound("OST and SFX\\Tetris Vs Mode Ost.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	P1gameOver = false;
	P2gameOver = false;
	playSFX("notif", "OST and SFX\\notif.wav");
    while (P1gameOver == false && P2gameOver == false) 
    {
        VSmoveBlock(P1currentChoice, P2currentChoice); 
    }
}






