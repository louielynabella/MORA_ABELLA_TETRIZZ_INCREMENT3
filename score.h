#ifndef SCORE_H
#define SCORE_H

int score = 0;
int highScore = 0;

int loadHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    return highScore;
}

void saveHighScore(int newHighScore) {
    FILE *file = fopen("highscore.txt", "w");  
    if (file) {
        fprintf(file, "%d", newHighScore);
        fclose(file);
    }
}

#endif
