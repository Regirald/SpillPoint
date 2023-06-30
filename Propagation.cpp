#include <iostream>
#include <vector>
#include <climits>
#include <map>

using namespace std;

// Fonction pour vérifier si les coordonnées (i, j) sont valides dans la grille
bool isValidCoordinate(int i, int j, int rows, int cols) {
    return i >= 0 && i < rows && j >= 0 && j < cols;
}

// Fonction pour déterminer le max d'un vecteur 2D
int getMaxValue(vector<vector<int>>& grid) {
    int maxVal = INT_MIN;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            maxVal = max(maxVal, grid[i][j]);
        }
    }

    return maxVal;
}
// Fonction récursive pour trouver les points voisins de même altitude
void findSameAltitudeNeighbors(vector<vector<int>>& grid, vector<vector<bool>>& visited, int row, int col, int altitude, vector<pair<int, int>>& neighbors) {
    // Coordonnées des voisins (haut, bas, gauche, droite)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    int rows = grid.size();
    int cols = grid[0].size();

    // Marquer la case courante comme visitée
    visited[row][col] = true;

    // Vérifier les voisins
    for (int k = 0; k < 4; k++) {
        int newRow = row + dx[k];
        int newCol = col + dy[k];

        // Vérifier si les coordonnées du voisin sont valides
        if (isValidCoordinate(newRow, newCol, rows, cols) && !visited[newRow][newCol]) {
            // Vérifier si le voisin a la même altitude
            if (grid[newRow][newCol] == altitude) {
                // Ajouter le voisin à la liste des voisins de même altitude
                neighbors.push_back({newRow, newCol});

                // Rechercher les voisins du voisin récursivement
                findSameAltitudeNeighbors(grid, visited, newRow, newCol, altitude, neighbors);
            }
        }
    }
}

// Fonction pour trouver tous les points voisins de même altitude
vector<pair<int, int>> findAllSameAltitudeNeighbors(vector<vector<int>>& grid, int row, int col) {
    int altitude = grid[row][col];
    int rows = grid.size();
    int cols = grid[0].size();

    // Initialiser la matrice de visite
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Liste des voisins de même altitude
    vector<pair<int, int>> neighbors;
    neighbors.push_back({row, col});

    // Rechercher les voisins de même altitude récursivement
    findSameAltitudeNeighbors(grid, visited, row, col, altitude, neighbors);

    return neighbors;
}

int main() {
    vector<vector<int>> grid = {
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
    {3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3},
    {3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
    };

    int row = 10;
    int col = 13;
    map<pair<int, int>, bool> mask;
    cout<<"  max alt: "<< getMaxValue(grid) << endl;

    for (int i=grid[row][col];i<getMaxValue(grid); i++){

        cout<<"  alt: "<< i << endl;
        // Trouver tous les voisins de même altitude pour le point (row, col)
        vector<pair<int, int>> neighbors = findAllSameAltitudeNeighbors(grid, row, col);

        // Créer une map pour indiquer si chaque case fait partie des voisins
        for (const auto& neighbor : neighbors) {
            mask[neighbor] = true;

            int x = neighbor.first;
            int y = neighbor.second;
            grid[x][y]++;
        }

        // Afficher la map avec l'indication de l'appartenance des cases aux voisins
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                cout << mask[{i, j}] ;
            }
            cout << endl;
    }
    }



    return 0;
}

