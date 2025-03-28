#pragma once
#include <raylib.h>

class Ecran {
private:
    const int tailleCellule = 20;
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int cols = screenWidth / tailleCellule;
    const int rows = screenHeight / tailleCellule;
    Color blocColor[30][40];
    bool celluleEtat[30][40];
    bool cellueSuivante[30][40];

public:
    Ecran() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                celluleEtat[i][j] = false;
                cellueSuivante[i][j] = false;
                blocColor[i][j] = LIGHTGRAY;
            }
        }
        celluleEtat[10][10] = true;
        celluleEtat[10][11] = true;
        celluleEtat[10][12] = true;
    }

    void Update(Vector2 mousePos);
    void Draw();
};