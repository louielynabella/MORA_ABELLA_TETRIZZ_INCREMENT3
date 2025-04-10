#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>

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

#define fx (ex+mx)
#define mx (ex+3)
#define ex 3

#define cx (dx+nx-1)
#define nx (dx-3)
#define dx -2



void printShadowTETRIZ() 
{
    
	gotoxy(11 + fx, 7); setColor(BG_RED); printf("          "); setColor(0);
    gotoxy(11+ fx, 8); printf("   "); setColor(BG_RED); printf("    "); setColor(0); printf("   ");
    gotoxy(11+ fx, 9); printf("   "); setColor(BG_RED); printf("    "); setColor(0); printf("   ");
    gotoxy(11+ fx, 10); printf("   "); setColor(BG_RED); printf("    "); setColor(0); printf("   ");
    gotoxy(11+ fx, 11); printf("   "); setColor(BG_RED); printf("    "); setColor(0); printf("   ");
    
    gotoxy(26+ mx, 7); setColor(BG_BROWN); printf("          "); setColor(0);
    gotoxy(26+ mx, 8); setColor(BG_BROWN); printf("    "); setColor(0);
    gotoxy(26+ mx, 9); setColor(BG_BROWN); printf("        "); setColor(0);
    gotoxy(26+ mx, 10); setColor(BG_BROWN); printf("    "); setColor(0);
    gotoxy(26+ mx, 11); setColor(BG_BROWN); printf("          "); setColor(0);
    
    gotoxy(41+ ex, 7); setColor(BG_LIGHT_GREEN); printf("          "); setColor(0);
    gotoxy(41+ ex, 8); printf("   "); setColor(BG_LIGHT_GREEN); printf("    "); setColor(0); printf("   ");
    gotoxy(41+ ex, 9); printf("   "); setColor(BG_LIGHT_GREEN); printf("    "); setColor(0); printf("   ");
    gotoxy(41+ ex, 10); printf("   "); setColor(BG_LIGHT_GREEN); printf("    "); setColor(0); printf("   ");
    gotoxy(41+ ex, 11); printf("   "); setColor(BG_LIGHT_GREEN); printf("    "); setColor(0); printf("   ");
    
    gotoxy(56, 7); setColor(BG_MAGENTA);printf("          "); setColor(0);
    gotoxy(56, 8); setColor(BG_MAGENTA); printf("    "); setColor(0); gotoxy(63, 8); setColor(BG_MAGENTA); printf("    "); setColor(0);
    gotoxy(56, 9); setColor(BG_MAGENTA);printf("          "); setColor(0);
    gotoxy(56, 10); setColor(BG_MAGENTA); printf("    "); setColor(0); gotoxy(63, 10); setColor(BG_MAGENTA); printf("    "); setColor(0);
    gotoxy(56, 11); setColor(BG_MAGENTA); printf("    "); setColor(0); gotoxy(64, 11); setColor(BG_MAGENTA); printf("    "); setColor(0);
    
    gotoxy(72 + dx, 7); setColor(BG_BLUE); printf("            "); setColor(0);
    gotoxy(76+ dx, 8); setColor(BG_BLUE); printf("    "); setColor(0); 
    gotoxy(76+ dx, 9); setColor(BG_BLUE); printf("    "); setColor(0);
    gotoxy(76+ dx, 10); setColor(BG_BLUE); printf("    "); setColor(0);
    gotoxy(72+ dx, 11); setColor(BG_BLUE); printf("            "); setColor(0);
    
    gotoxy(89+ nx, 7); setColor(BG_CYAN); printf("          "); setColor(0);
    gotoxy(89+ nx, 8); setColor(BG_CYAN); printf("    "); setColor(0);
    gotoxy(91+ nx, 9); setColor(BG_CYAN); printf("    "); setColor(0);
    gotoxy(93+ nx, 10); setColor(BG_CYAN); printf("    "); setColor(0);
    gotoxy(89+ nx, 11); setColor(BG_CYAN); printf("          "); setColor(0);
    
    gotoxy(104+ cx, 7); setColor(BG_LIGHT_MAGENTA); printf("          "); setColor(0);
    gotoxy(104+ cx, 8); setColor(BG_LIGHT_MAGENTA); printf("    "); setColor(0);
    gotoxy(106+ cx, 9); setColor(BG_LIGHT_MAGENTA); printf("    "); setColor(0);
    gotoxy(108+ cx, 10); setColor(BG_LIGHT_MAGENTA); printf("    "); setColor(0);
    gotoxy(104+ cx, 11); setColor(BG_LIGHT_MAGENTA); printf("          "); setColor(0);

    
    
}

void printTETRIZ() 
{
    gotoxy(10+ fx, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(13+ fx, 7); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(13+ fx, 8); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(13+ fx, 9); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(13+ fx, 10); setColor(BG_WHITE); printf("    "); setColor(0);
    // Print E
    gotoxy(25+ mx, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(25+ mx, 7); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(25+ mx, 8); setColor(BG_WHITE); printf("        ");
    gotoxy(25+ mx, 9); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(25+ mx, 10); setColor(BG_WHITE); printf("          "); setColor(0);

    // Print T

    gotoxy(40+ ex, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(43+ ex, 7); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(43+ ex, 8); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(43+ ex, 9); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(43+ ex, 10); setColor(BG_WHITE); printf("    "); setColor(0);

    // Print R
    gotoxy(55, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(55, 7); setColor(BG_WHITE); printf("    "); setColor(0); gotoxy(62, 7); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(55, 8); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(55, 9); setColor(BG_WHITE); printf("    "); setColor(0); gotoxy(62, 9); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(55, 10); setColor(BG_WHITE); printf("    "); setColor(0); gotoxy(63, 10); setColor(BG_WHITE); printf("    "); setColor(0);

    // Print I
    gotoxy(71+ dx, 6); setColor(BG_WHITE); printf("            "); setColor(0);
    gotoxy(75+ dx, 7); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(75+ dx, 8); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(75+ dx, 9); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(71+ dx, 10); setColor(BG_WHITE); printf("            "); setColor(0);

    // Print Z
    gotoxy(88+ nx, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(88+ nx, 7); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(90+ nx, 8); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(92+ nx, 9); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(88+ nx, 10); setColor(BG_WHITE); printf("          "); setColor(0);
    
    
    gotoxy(103+ cx, 6); setColor(BG_WHITE); printf("          "); setColor(0);
    gotoxy(103+ cx, 7); setColor(BG_WHITE); printf("    "); setColor(0);
    gotoxy(105+ cx, 8); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(107+ cx, 9); setColor(BG_WHITE); printf("    "); setColor(0); 
    gotoxy(103+ cx, 10); setColor(BG_WHITE); printf("          "); setColor(0);
}

int main(int argc, char *argv[]) 
{
	char press;
	system("cls"); // Clear screen before printing
	PlaySound("OST and SFX\\TetrizMenuTheme.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    printShadowTETRIZ();
    printTETRIZ();
	
    // Wait for user to press ENTER
    gotoxy(46,20);
    setColor(7);
    printf("Press any key to continue...");
    
    _getch(); // Waits for any key press
    game();   // Proceed to game after key press
	return 0;
}


