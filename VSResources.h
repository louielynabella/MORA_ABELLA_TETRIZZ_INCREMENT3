#ifndef VSRESOURCES_H
#define VSRESOURCES_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>


// Constants
#define boardCols 10
#define boardRows 24
#define heldBlockX (boardCols * 2 + 12)  // Fixed X position
#define heldBlockY 8                     // Fixed Y position

#define BLACK 0  
#define BLUE 1  
#define GREEN 2  
#define CYAN 3  
#define RED 4  
#define MAGENTA 5  
#define BROWN 6  // Dark Yellow  
#define LIGHT_GRAY 7  
#define DARK_GRAY 8  
#define LIGHT_BLUE 9  
#define LIGHT_GREEN 10  
#define LIGHT_CYAN 11  
#define LIGHT_RED 12  
#define LIGHT_MAGENTA 13  
#define YELLOW 14  
#define WHITE 15  

#define BG_BLACK        (0  << 4)  
#define BG_BLUE         (1  << 4)  
#define BG_GREEN        (2  << 4)  
#define BG_CYAN         (3  << 4)  
#define BG_RED          (4  << 4)  
#define BG_MAGENTA      (5  << 4)  
#define BG_BROWN        (6  << 4)  
#define BG_LIGHT_GRAY   (7  << 4)  
#define BG_DARK_GRAY    (8  << 4)  
#define BG_LIGHT_BLUE   (9  << 4)  
#define BG_LIGHT_GREEN  (10 << 4)  
#define BG_LIGHT_CYAN   (11 << 4)  
#define BG_LIGHT_RED    (12 << 4)  
#define BG_LIGHT_MAGENTA (13 << 4)  
#define BG_YELLOW       (14 << 4)  
#define BG_WHITE        (15 << 4)  

// Data Structures
// Active 
//Player 1
typedef struct P1Block {
    int x, y;
    struct P1Block* next;
} P1Block;

typedef struct 	P1Tetromino {
    P1Block* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} P1Tetromino;

//Player 2
typedef struct P2Block {
    int x, y;
    struct P2Block* next;
} P2Block;

typedef struct P2Tetromino {
    P2Block* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} P2Tetromino;

//ghost
//player 1
typedef struct P1gBlock {
    int gx, gy;
    struct P1gBlock* next;
} P1gBlock;

typedef struct P1gTetromino {
    P1gBlock* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} P1gTetromino;

//ghost
//player 2
typedef struct P2gBlock {
    int gx, gy;
    struct P2gBlock* next;
} P2gBlock;

typedef struct P2gTetromino {
    P2gBlock* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} P2gTetromino;




// Global variable declarations (means they are defined elsewhere)

//SHARE
int difficultyLevel;
DWORD difficultyStartTime;
int i, j, r;
int row, col;
DWORD elapsedGameTime;

// SHARED Function prototypes

void playSFX(const char* alias, const char* file);
//void setColor(int color);
int loadHighScore();
void saveHighScore(int newHighScore);
void gotoxy(int x, int y);
int generateRandomNumber();
int getTetrominoIndex(const char* name);
void moveBlock(int choice);
void game();

void printTetrominoPreview(int choice, int x, int y);

//PLAYER 1

int P1Score = 0;
bool P1gameOver = false;
int P1board[boardRows][boardCols] = {0};
int P1colorBoard[boardRows][boardCols] = {0};
P1Tetromino* P1nextTetromino;
P1Tetromino* P1heldTetromino;
bool P1hasSwapped;
int P1nextChoice;
P1Tetromino* P1generateTetromino(int P1choice, int x, int y);
P1gTetromino* P1createGhostTetromino(P1Tetromino* t);
void P1printSideText();
void P1storeTetromino(P1Tetromino* t, int P1board[boardRows][boardCols], int P1colorBoard[boardRows][boardCols]);
void P1printBoard(P1Tetromino* t, int P1board[boardRows][boardCols], int P1colorBoard[boardRows][boardCols]);
void P1ghostPos(P1gTetromino* g, int P1board[boardRows][boardCols]);
void P1swapTetromino(P1Tetromino** P1currentTetromino);

//PLAYER 2
int P2Score = 0;
bool P2gameOver = false;
char P2CBoard[boardRows][boardCols];
int P2board[boardRows][boardCols];
int P2colorBoard[boardRows][boardCols];
P2Tetromino* P2nextTetromino;
P2Tetromino* P2heldTetromino;
bool P2hasSwapped;
int P2nextChoice;
P2Tetromino* P2generateTetromino(int P2choice, int x, int y);
P2gTetromino* P2createGhostTetromino(P2Tetromino* t);
void P2printSideText();
void P2storeTetromino(P2Tetromino* t, int P2board[boardRows][boardCols], int P2colorBoard[boardRows][boardCols]);
void P2printBoard(P2Tetromino* t, int P2board[boardRows][boardCols], int P2colorBoard[boardRows][boardCols]);
void P2ghostPos(P2gTetromino* g, int P2board[boardRows][boardCols]);
void P2swapTetromino(P2Tetromino** P2currentTetromino);


//PLAYER 1
P1Block* P1createBlock(int x, int y) 
{
	P1Block* newBlock = (P1Block*)malloc(sizeof(P1Block));
	if (!newBlock) return NULL;
	
	newBlock->x = x;
	newBlock->y = y;
	newBlock->next = NULL;
	return newBlock;
	
}

P1gTetromino* P1createGhostTetromino(P1Tetromino* t) 
{
    P1gTetromino* ghost = (P1gTetromino*)malloc(sizeof(P1gTetromino));
    if (!ghost) return NULL;

    strcpy(ghost->type, t->type);
    ghost->bgColor = BG_DARK_GRAY;  // Ghost blocks have a dark gray background
    ghost->isOBlock = t->isOBlock;
    ghost->head = NULL;

    // Copy active Tetromino
    P1Block* temp = t->head;
    P1gBlock* prev = NULL;
    while (temp) {
        P1gBlock* newBlock = (P1gBlock*)malloc(sizeof(P1gBlock));
        if (!newBlock) return NULL;

        newBlock->gx = temp->x;
        newBlock->gy = temp->y;
        newBlock->next = NULL;

        if (!ghost->head) ghost->head = newBlock;
        else prev->next = newBlock;

        prev = newBlock;
        temp = temp->next;
    }

    return ghost;
}

P1Tetromino* P1LineBlock(int x, int y) //line block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x,y);//head A1
	t->head->next = P1createBlock(x,y+1);//A2
	t->head->next->next = P1createBlock(x,y+2);//A3
	t->head->next->next->next = P1createBlock(x,y+3);//A4
	t->isOBlock = false;
	t->bgColor = BG_BLUE;
	strcpy(t->type, "Line");
	return t;
}

P1Tetromino* P1tBlock(int x, int y) //T block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x-1,y);//head A1
	t->head->next = P1createBlock(x, y);//pivot A2
	t->head->next->next = P1createBlock(x+1,y);
	t->head->next->next->next = P1createBlock(x,y+1);
	t->isOBlock = false;
	t->bgColor = BG_GREEN;
	strcpy(t->type, "T");
	return t;
}
P1Tetromino* P1lBlock(int x, int y) //L block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x-1,y+1);//5,0
	t->head->next = P1createBlock(x, y);//4,0 
	t->head->next->next = P1createBlock(x-1,y);//4,1
	t->head->next->next->next = P1createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_RED;
	strcpy(t->type, "L");
	return t;
}
P1Tetromino* P1OBlock(int x, int y) //O block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x,y);
	t->head->next = P1createBlock(x-1,y);
	t->head->next->next = P1createBlock(x-1,y+1);
	t->head->next->next->next = P1createBlock(x,y+1);
	t->isOBlock = true;
	t->bgColor = BG_BROWN;
	strcpy(t->type, "Square");
	return t;
}

P1Tetromino* P1JBlock(int x, int y) //J block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x-1,y);//5,0
	t->head->next = P1createBlock(x, y);//4,0
	t->head->next->next = P1createBlock(x+1,y);//6,0
	t->head->next->next->next = P1createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_MAGENTA;
	strcpy(t->type, "J");
	return t;
}

P1Tetromino* P1SBlock(int x, int y) //S block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x-1,y+1);//4,1
	t->head->next = P1createBlock(x,y+1);//5,1
	t->head->next->next = P1createBlock(x,y);//5,0
	t->head->next->next->next = P1createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_CYAN;
	strcpy(t->type, "S");
	return t;
}

P1Tetromino* P1ZBlock(int x, int y) //Z block
{
	P1Tetromino* t = (P1Tetromino*)malloc(sizeof(P1Tetromino));
	if(!t) return NULL;
	
	t->head = P1createBlock(x-1,y);//4,0
	t->head->next = P1createBlock(x,y);//5,0
	t->head->next->next = P1createBlock(x,y+1);//5,1
	t->head->next->next->next = P1createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_RED;
	strcpy(t->type, "Z");
	return t;
}

P2Block* P2createBlock(int x, int y) 
{
	P2Block* newBlock = (P2Block*)malloc(sizeof(P2Block));
	if (!newBlock) return NULL;
	
	newBlock->x = x;
	newBlock->y = y;
	newBlock->next = NULL;
	return newBlock;
	
}



//PLAYER 2

P2gTetromino* P2createGhostTetromino(P2Tetromino* t) 
{
    P2gTetromino*   ghost = (P2gTetromino*)malloc(sizeof(P2gTetromino));
    if (!ghost) return NULL;

    strcpy(ghost->type, t->type);
    ghost->bgColor = BG_DARK_GRAY;  // Ghost blocks have a dark gray background
    ghost->isOBlock = t->isOBlock;
    ghost->head = NULL;

    // Copy active Tetromino
    P2Block* temp = t->head;
    P2gBlock* prev = NULL;
    while (temp) {
        P2gBlock* newBlock = (P2gBlock*)malloc(sizeof(P2gBlock));
        if (!newBlock) return NULL;

        newBlock->gx = temp->x;
        newBlock->gy = temp->y;
        newBlock->next = NULL;

        if (!ghost->head) ghost->head = newBlock;
        else prev->next = newBlock;

        prev = newBlock;
        temp = temp->next;
    }

    return ghost;
}
P2Tetromino* P2LineBlock(int x, int y) //line block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x,y);//head A1
	t->head->next = P2createBlock(x,y+1);//A2
	t->head->next->next = P2createBlock(x,y+2);//A3
	t->head->next->next->next = P2createBlock(x,y+3);//A4
	t->isOBlock = false;
	t->bgColor = BG_BLUE;
	strcpy(t->type, "Line");
	return t;
}

P2Tetromino* P2tBlock(int x, int y) //T block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x-1,y);//head A1
	t->head->next = P2createBlock(x, y);//pivot A2
	t->head->next->next = P2createBlock(x+1,y);
	t->head->next->next->next = P2createBlock(x,y+1);
	t->isOBlock = false;
	t->bgColor = BG_GREEN;
	strcpy(t->type, "T");
	return t;
}

P2Tetromino* P2lBlock(int x, int y) //L block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x-1,y+1);//5,0
	t->head->next = P2createBlock(x, y);//4,0 
	t->head->next->next = P2createBlock(x-1,y);//4,1
	t->head->next->next->next = P2createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_RED;
	strcpy(t->type, "L");
	return t;
}

P2Tetromino* P2OBlock(int x, int y) //O block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x,y);
	t->head->next = P2createBlock(x-1,y);
	t->head->next->next = P2createBlock(x-1,y+1);
	t->head->next->next->next = P2createBlock(x,y+1);
	t->isOBlock = true;
	t->bgColor = BG_BROWN;
	strcpy(t->type, "Square");
	return t;
}

P2Tetromino* P2JBlock(int x, int y) //J block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x-1,y);//5,0
	t->head->next = P2createBlock(x, y);//4,0
	t->head->next->next = P2createBlock(x+1,y);//6,0
	t->head->next->next->next = P2createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_MAGENTA;
	strcpy(t->type, "J");
	return t;
}

P2Tetromino* P2SBlock(int x, int y) //S block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x-1,y+1);//4,1
	t->head->next = P2createBlock(x,y+1);//5,1
	t->head->next->next = P2createBlock(x,y);//5,0
	t->head->next->next->next = P2createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_CYAN;
	strcpy(t->type, "S");
	return t;
}

P2Tetromino* P2ZBlock(int x, int y) //Z block
{
	P2Tetromino* t = (P2Tetromino*)malloc(sizeof(P2Tetromino));
	if(!t) return NULL;
	
	t->head = P2createBlock(x-1,y);//4,0
	t->head->next = P2createBlock(x,y);//5,0
	t->head->next->next = P2createBlock(x,y+1);//5,1
	t->head->next->next->next = P2createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_RED;
	strcpy(t->type, "Z");
	return t;
}

// preview tetromino arrays
char VStetrominoShapes[7][4][4] = {
    {  // Line Block
        {' ', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    {  // T Block
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', 'O'},
        {' ', ' ', 'O', ' '},
        {' ', ' ', ' ', ' '}
    },
    {  // L Block
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', 'O'},
        {' ', 'O', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },
    {  // Square Block (O Block)
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', ' '},
        {' ', 'O', 'O', ' '},
        {' ', ' ', ' ', ' '}
    },
    {  // J Block
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', 'O'},
        {' ', ' ', ' ', 'O'},
        {' ', ' ', ' ', ' '}
    },
    {  // S Block
        {' ', ' ', ' ', ' '},
        {' ', ' ', 'O', 'O'},
        {' ', 'O', 'O', ' '},
        {' ', ' ', ' ', ' '}
    },
    {  // Z Block
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', ' '},
        {' ', ' ', 'O', 'O'},
        {' ', ' ', ' ', ' '}
    }
};


#endif

