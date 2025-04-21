#include <stdio.h>
#include <stdlib.h>

#define YELLOW 14
#define DIM_YELLOW 6 // A darker yellow para sa selection
#define WHITE 15

int game() {
    int choice = 1;
    int ch;

     while (1) {
        // Display menu
        gotoxy(46, 20);
        setColor(WHITE);
        printf("Enter Mode to play");

        // Highlight with an arrow and change color
        gotoxy(46, 21);
        if (choice == 1) {
            setColor(DIM_YELLOW); 
            printf("> [1] Solo Mode    ");
        } else {
            setColor(WHITE);
            printf("   [1] Solo Mode    ");
        }

        gotoxy(46, 22);
        if (choice == 2) {
            setColor(DIM_YELLOW); 
            printf("> [2] Versus Mode  ");
        } else {
            setColor(WHITE);
            printf("   [2] Versus Mode  ");
        }

        gotoxy(46, 23);
        if (choice == 3) {
            setColor(DIM_YELLOW); 
            printf("> [3] Why am I here?");
        } else {
            setColor(WHITE);
            printf("   [3] Why am I here?");
        }

        

        ch = _getch(); // get character input without Enter

        if (ch == 224) { // Arrow keys prefix
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    choice--;
                    if (choice < 1) choice = 3;
                    break;
                case 80: // Down arrow
                    choice++;
                    if (choice > 3) choice = 1;
                    break;
            }
        } else if (ch == 13) { // Enter key
            break;
        }
    }

    gotoxy(46, 27);
    printf("You selected option %d!\n", choice);

    // Now handle the choice
    switch(choice)
    {
        case 1: 
        	system("cls");
            soloMode();
            break;
        case 2: 
        	system("cls");
            vsMode();
            break;
        case 3:
            gotoxy(46, 29);
            system("cls");
            printf("Idk. You tell me....\n\n"); 
            exit(0); 
            break;
        default: 
            gotoxy(46, 29);
            system("cls");
            printf("Not even in the choices, bud.\n\n"); 
            break;
    }

    return 0;
}

