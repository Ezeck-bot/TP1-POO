#include "entrypoint.h"
#include "mes_classes.h"


//Tâche à faire
/*
 - Déssiner d'abord une grille
 - Arriver à changer la couleur d'un bloc lorsque je clique sur lui et récuperer sa position
 - Arriver à chnager la couleur du bloque si je clique sur un bloc
 - intégrer le sytème de true ou false des blocs
 - Ensuite savoir qu'elle est l'état des cellules 8 voisines à partir de la cellule selectionné
 - Puis faire la logique de naissance ou de mort
 Voilà comment j'ai séquencé le TP mais j'ai eu plus de difficulté sur les mises à jour d'état puis l'IA GROK m'a suggérer des modifications comme l'ajout du KEY_SPACE. La logique pour voir les voisins à la base j'avais fait : 
 for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
    int count = 0;
    if (celluleEtat[i - 1][j - 1])
    {
        count++;
    }

    if (celluleEtat[i - 1][j])
    {
        count++;
    }

    if (celluleEtat[i - 1][j + 1])
    {
        count++;
    }

    if (celluleEtat[i][j - 1])
    {
        count++;
    }

    if (celluleEtat[i][j + 1])
    {
        count++;
    }

    if (celluleEtat[i + 1][j - 1])
    {
        count++;
    }
    
    if (celluleEtat[i + 1][j])
    {
        count++;
    }

    if (celluleEtat[i + 1][j + 1])
    {
        count++;
    }
}
}

    Puis il m'a sugérer des faires des boucles for comprenant des vérifications.
    Aussi pour la position du bloc je le récuperais sans faire la division par la taille de la cellule.
    De même pour la méthode Ecran() à la base je l'ajoutais et j'avais vraiment des blocs qui parraissait n'importe comment.
*/

void Ecran::Update(Vector2 mousePos) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int i = (int)(mousePos.y / tailleCellule);
        int j = (int)(mousePos.x / tailleCellule);
        if (i >= 0 && i < rows && j >= 0 && j < cols) {
            celluleEtat[i][j] = !celluleEtat[i][j];
        }
    }

    if (IsKeyDown(KEY_SPACE)) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                //Chercher les voisins
                int count = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                            if (celluleEtat[ni][nj]){
                                count++;
                            }
                        }
                    }
                }
                cellueSuivante[i][j] = false;
                if (celluleEtat[i][j]) {
                    if (count == 2 || count == 3)
                    {
                        cellueSuivante[i][j] = true;
                    }
                } else {
                    if (count == 3)
                    {
                        cellueSuivante[i][j] = true;
                    }
                }
            }
        }
        // Mise à jour de l’état
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                celluleEtat[i][j] = cellueSuivante[i][j];
            }
        }
    }
}

void Ecran::Draw() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            blocColor[i][j] = celluleEtat[i][j] ? YELLOW : LIGHTGRAY;
            DrawRectangle(j * tailleCellule, i * tailleCellule, tailleCellule - 2, tailleCellule - 2, blocColor[i][j]);
        }
    }
}

//Creer votre class Engin ici et appeler une fonction start que vous définisser à la classe dans la fonction raylib_start plus bas.
void raylib_start(void){
    // Initialization
    Ecran ecran;

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Jeu de la vie");
    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        ecran.Update(mousePos);

        BeginDrawing();

            ClearBackground(DARKGRAY);

            ecran.Draw();
            DrawText("Appuyez sur ESPACE pour avancer", 10, 10, 40, RED);

        EndDrawing();
    }

    CloseWindow();
}