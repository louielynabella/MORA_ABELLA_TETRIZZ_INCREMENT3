#ifndef RESOURCES_H
#define RESOURCES_H

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
typedef struct Block {
    int x, y;
    struct Block* next;
} Block;

typedef struct Tetromino {
    Block* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} Tetromino;

//ghost
typedef struct gBlock {
    int gx, gy;
    struct gBlock* next;
} gBlock;

typedef struct gTetromino {
    gBlock* head;
    char type[10];
    int bgColor;
    bool isOBlock;
} gTetromino;

// Global variable declarations (extern means they are defined elsewhere)
int i, j, r;
int row, col;
DWORD elapsedGameTime;
char CBoard[boardRows][boardCols];
int board[boardRows][boardCols];
int colorBoard[boardRows][boardCols];
Tetromino* nextTetromino;
Tetromino* heldTetromino;
bool hasSwapped;
int nextChoice;
int difficultyLevel;
DWORD difficultyStartTime;

// Function prototypes
gTetromino* createGhostTetromino(Tetromino* t);
void playSFX(const char* alias, const char* file);
void setColor(int color);
int loadHighScore();
void saveHighScore(int newHighScore);
void gotoxy(int x, int y);
int generateRandomNumber();
void printSideText();
Tetromino* generateTetromino(int choice, int x, int y);
int getTetrominoIndex(const char* name);
void printTetrominoPreview(int choice, int x, int y);
void printBoard(Tetromino* t, int board[boardRows][boardCols], int colorBoard[boardRows][boardCols]);
void moveBlock(int choice);
void ghostPos(gTetromino* g, int board[boardRows][boardCols]);
void game();
void swapTetromino(Tetromino** currentTetromino);
void storeTetromino(Tetromino* t, int board[boardRows][boardCols], int colorBoard[boardRows][boardCols]);

void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Block* createBlock(int x, int y) 
{
	Block* newBlock = (Block*)malloc(sizeof(Block));
	if (!newBlock) return NULL;
	
	newBlock->x = x;
	newBlock->y = y;
	newBlock->next = NULL;
	return newBlock;
	
}

gTetromino* createGhostTetromino(Tetromino* t) 
{
    gTetromino* ghost = (gTetromino*)malloc(sizeof(gTetromino));
    if (!ghost) return NULL;

    strcpy(ghost->type, t->type);
    ghost->bgColor = BG_DARK_GRAY;  // Ghost blocks have a dark gray background
    ghost->isOBlock = t->isOBlock;
    ghost->head = NULL;

    // Copy active Tetromino
    Block* temp = t->head;
    gBlock* prev = NULL;
    while (temp) {
        gBlock* newBlock = (gBlock*)malloc(sizeof(gBlock));
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


Tetromino* LineBlock(int x, int y) //line block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x,y);//head A1
	t->head->next = createBlock(x,y+1);//A2
	t->head->next->next = createBlock(x,y+2);//A3
	t->head->next->next->next = createBlock(x,y+3);//A4
	t->isOBlock = false;
	t->bgColor = BG_BLUE;
	strcpy(t->type, "Line");
	return t;
}

Tetromino* tBlock(int x, int y) //T block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x-1,y);//head A1
	t->head->next = createBlock(x, y);//pivot A2
	t->head->next->next = createBlock(x+1,y);
	t->head->next->next->next = createBlock(x,y+1);
	t->isOBlock = false;
	t->bgColor = BG_GREEN;
	strcpy(t->type, "T");
	return t;
}

Tetromino* lBlock(int x, int y) //L block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x-1,y+1);//5,0
	t->head->next = createBlock(x, y);//4,0 
	t->head->next->next = createBlock(x-1,y);//4,1
	t->head->next->next->next = createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_RED;
	strcpy(t->type, "L");
	return t;
}

Tetromino* OBlock(int x, int y) //O block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x,y);
	t->head->next = createBlock(x-1,y);
	t->head->next->next = createBlock(x-1,y+1);
	t->head->next->next->next = createBlock(x,y+1);
	t->isOBlock = true;
	t->bgColor = BG_BROWN;
	strcpy(t->type, "Square");
	return t;
}

Tetromino* JBlock(int x, int y) //J block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x-1,y);//5,0
	t->head->next = createBlock(x, y);//4,0
	t->head->next->next = createBlock(x+1,y);//6,0
	t->head->next->next->next = createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_LIGHT_MAGENTA;
	strcpy(t->type, "J");
	return t;
}

Tetromino* SBlock(int x, int y) //S block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x-1,y+1);//4,1
	t->head->next = createBlock(x,y+1);//5,1
	t->head->next->next = createBlock(x,y);//5,0
	t->head->next->next->next = createBlock(x+1,y);//6,0
	t->isOBlock = false;
	t->bgColor = BG_CYAN;
	strcpy(t->type, "S");
	return t;
}

Tetromino* ZBlock(int x, int y) //Z block
{
	Tetromino* t = (Tetromino*)malloc(sizeof(Tetromino));
	if(!t) return NULL;
	
	t->head = createBlock(x-1,y);//4,0
	t->head->next = createBlock(x,y);//5,0
	t->head->next->next = createBlock(x,y+1);//5,1
	t->head->next->next->next = createBlock(x+1,y+1);//6,1
	t->isOBlock = false;
	t->bgColor = BG_RED;
	strcpy(t->type, "Z");
	return t;
}

// preview tetromino arrays
char tetrominoShapes[7][4][4] = {
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

