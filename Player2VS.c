#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include "resources.h"
#include "score.h"

void P1printBoard(P1Tetromino* t, int P1board[boardRows][boardCols], int P1colorBoard[boardRows][boardCols])
{
	P1gTetromino* g = P1createGhostTetromino(t);
	if (!g) return;
	P1ghostPos(g, BOARD);
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
            if (P1Cboard[i][j] == 1)
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
    printSideText();
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

     //Display Score and High Score
    gotoxy(boardCols * 2 + 33, 6);
    printf("Score: %d", score);
   
    // Display Time & Level
    int elapsedMinutes = elapsedGameTime / 60000;  // Convert to minutes
    int elapsedSeconds = (elapsedGameTime % 60000) / 1000;  // Remaining seconds
    gotoxy(14, 20);
    printf("Time: %d:%02d", elapsedMinutes, elapsedSeconds);
    gotoxy(14, 22);
    printf("Level: %d", difficultyLevel + 1);
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


void P1swapTetromino(P1Tetromino** currentTetromino)  
{
    if (hasSwapped) 
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
        P1heldTetromino = *currentTetromino;
        *currentTetromino = generateTetromino(nextChoice, 5, 1); // Reset to x=5, y=1
        nextChoice = generateRandomNumber(); // Prepare new next piece
    } 
    else 
    {
        // Swap CURRENT and HELD block
        P1Tetromino* temp = P1heldTetromino;
        heldTetromino = *currentTetromino;  
        *currentTetromino = temp; // Bring back held block

        // Reset ALL blocks in the Tetromino to start at (x = 5, y = 1)
        P1Block* block = (*currentTetromino)->head;
        
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

