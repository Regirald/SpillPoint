#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <list>

using namespace std;

void PrintQ( queue<pair<int,int>> q){
        if(q.empty()){
            cout<<"liste vide!"<<endl;
        }
    while (!q.empty()) {
        cout << "(" << q.front().first << ", " << q.front().second << ") ";
        q.pop();
    }
    cout << endl;
}


list<pair<int,int>>  propagateByLayer(vector<vector<int>>& grid, vector<vector<pair<bool, int>>> & visited ,queue<pair<int, int>> &q,int h) {
    int numRows = grid.size();
    int numCols = grid[0].size();


    // Définir les directions possibles (haut, droite, bas, gauche)
    vector<int> dx = {-1, 0, 1, -1, 0, 1,-1, 0, 1,};
    vector<int> dy = {-1, -1, -1, 0, 0, 0, 1, 1, 1};

    // Créer une file d'attente pour la propagation par couche
    list<pair<int,int>> List_sp;
    queue<pair<int, int>> qNextLevel;
    vector<vector<bool>> visited_sp(numRows, vector<bool>(numCols, false));
    vector<vector<bool>> visited_nl(numRows, vector<bool>(numCols, false));
    // Ajouter le point de départ à la file d'attente et le marquer comme visité
    
    visited[q.front().first][q.front().second] = {true,0};
    int Layer_depth=1;

    // Parcourir chaque couche jusqu'à ce que la file d'attente soit vide
    while (!q.empty()) {
        // Obtenir la taille actuelle de la file d'attente (correspond à la taille de la couche actuelle)
        int layerSize = q.size();
        

        // Parcourir les points de la couche actuelle
        for (int i = 0; i < layerSize; i++) {
            // Récupérer les coordonnées du point courant
            int x = q.front().first;
            int y = q.front().second;
            q.pop();


            // Traiter le point courant (par exemple, afficher sa valeur)
            cout << "Visiting point (" << x << ", " << y << ") with value " << grid[x][y] << endl;

            // Parcourir les directions possibles pour se déplacer
            for (int j = 0; j < 9; j++) {
                int newX = x + dx[j];
                int newY = y + dy[j];

                // Spill Point detection
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && !visited_sp[newX][newY] && grid[newX][newY]<h) {
                        List_sp.push_back({newX, newY});
                        //visited_sp[newX][newY]=true;  to make stats overs outputs
                }
                 // Next level detection
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && !visited_nl[newX][newY] && grid[newX][newY]==h+1) {
                        qNextLevel.push({newX, newY});
                        visited_nl[newX][newY]=true;
                        cout << "H+1 point (" << newX << ", " << newY << ") with value " << grid[newX][newY] << endl;
                }
                // Vérifier si les nouvelles coordonnées sont valides et non visitées
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && grid[newX][newY]==h) {

                    // Ajouter les nouvelles coordonnées à la file d'attente et les marquer comme visitées
                    q.push({newX, newY});
                    visited[newX][newY] = {true,Layer_depth};
                }
            }
        }

        // Passer à la couche suivante
        if (List_sp.size()!=0){
            return List_sp;
        }
        cout << "Moving to the next layer layerdepth: "<<Layer_depth<< endl;
        Layer_depth++;

        // Display the visited map
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[0].size(); j++) {
                cout << visited[i][j].second ;
            }
            cout << endl;
        }   


    } 
    while (!qNextLevel.empty()) {
        q.push(qNextLevel.front());
        qNextLevel.pop();
    }
    return List_sp;
}



void Raise_level(vector<vector<int>>& grid,vector<vector<pair<bool, int>>> &visited, int h){
    int rows = grid.size();
    int cols = grid[0].size();

    // Iterate over the grid and increment values if visited
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++)
            if (visited[i][j].first){
                grid[i][j]=h;
            }
        }
    }




list<pair<int,int>> Find_Spill_Point(vector<vector<int>> grid, int startX, int startY) {

    int rows = grid.size();
    int cols = grid[0].size();

    pair<int,int> coor_spill_pt={startX,startY};
    int h = grid[startX][startY];
    queue<pair<int, int>> q;
    q.push({startX, startY});
    list<pair<int,int>> List_sp;
    vector<vector<pair<bool, int>>> visited(rows, vector<pair<bool, int>>(cols, pair<bool, int>(false, 0)));

    while (h<10){
        if (q.empty()){
            q.push({startX, startY});
        }
        cout << "##########h =  "<<h<<endl;

        list<pair<int,int>>List_sp= propagateByLayer(grid,  visited, q, h);
        cout << "##################q =  "<<endl;
        PrintQ(q);

        if (List_sp.size()!=0){
            return List_sp;
        }
        

        Raise_level(grid, visited,h);
        h++;


/*         for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                cout << grid[i][j] ;
            }
            cout << endl;
        } 
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[0].size(); j++) {
                cout << visited[i][j].first ;
            }
            cout << endl;
        }  */
    }


    list<pair<int,int>> List_null;
    return List_null;
}


int main(){


        vector<vector<int>> grid = {
                                //10
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
    {3, 2, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},//10
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 1, 2, 2, 3},
    {3, 2, 2, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3},
    {3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
    };
    list<pair<int,int>> List_sp=Find_Spill_Point(grid, 10, 6);

    cout << "Spill point detected at coordonate : "<<endl;
    for (const auto& element : List_sp)
    {
        cout << "(" << element.first << ", " << element.second << ")" << endl;
    }
    cout << endl;
}