#include "../include/Layer_Propagation.h"

using namespace std;



/* // Raise the altitude level at h in the global grid for the cases maked as "1" in visited
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
    } */


/* int findMin(vector<vector<int>>& grid, queue<pair<int,int>> q) {
    int minVal = INT_MAX; // Valeur maximale possible d'un entier

    while (!q.empty()) {
        if (grid[q.front().first][q.front().second] < minVal) {
            minVal = grid[q.front().first][q.front().second]; // Met à jour la valeur minimale si une valeur inférieure est trouvée
        }
        q.pop(); // Supprime le premier élément de la queue
    }

    return minVal; // Retourne la valeur minimale
} */

// print the values of a pair<int,int> queue
void PrintQ( queue<pair<int,int>> q){
        if(q.empty()){
            cout<<"empty list!"<<endl;
        }
    while (!q.empty()) {
        cout << "(" << q.front().first << ", " << q.front().second << ") ";
        q.pop();
    }
    cout << endl;
}

// Find the maximum of a vector<vector<int>> grid
int findMaxValue( vector<vector<int>>& grid) {
    int maxValue = INT_MIN;  

    for (const auto& row : grid) {
        for (int value : row) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
    }
    return maxValue;
}

// Update the queue to use for the next level by first concatenating the elements of the frontier queue that are at the current level (and remove them from it),
// then all the elements of the initial queue. This allows the algorithm to first consider cases closest to the starting point that are now ready to be considered from the previous level up
queue<pair<int, int>> UpdateFront(vector<vector<int>>& grid, queue<pair<int, int>> &q, queue<pair<int, int>> &qFront,int &h){
    
    queue<pair<int, int>> qUpdt;
    // add qFront elements whicha are equals to the level h
    int qFrontSize = qFront.size(); 

    for (int i = 0; i < qFrontSize; i++) {
        if (grid[qFront.front().first][qFront.front().second] ==h) {
            qUpdt.push(qFront.front()); 
        }
        else{
            qFront.push(qFront.front()); 
        }
        qFront.pop();
    }
    // concatate the q queue at last
    while (!q.empty()) {
        qUpdt.push(q.front());
        q.pop(); 

    }
    return qUpdt;
}

// Function which is called for a given level h. It returns an empty list if no spill point has been detected, if so, the list contains all the spill points detected at the same level h.
// It is possible to specify if you want a uniqueness of the element of the list or not (useful to choose a spill point in a random draw)
// Also, the function modify both queue: q and qFront
list<pair<int,int>>  propagateByLayer(vector<vector<int>>& grid, vector<vector<pair<bool, int>>> & visited, queue<pair<int, int>> &q, queue<pair<int, int>> &qFront,int &h) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // neighbor visiting directions (N, NE, E, SE, S, SW, W, NW)
    vector<int> dx = {1, -1, 0, 0, 1, -1, 1, -1};
    vector<int> dy = {0, 0, 1, -1, 1, -1, -1, 1};

    // Declaration of List_sp intended to contain the spill point detected, qNextLevel the furur queue for the h+1 process (contain the element of altitude h+1),
    // qSupp the boundary queue (contain the element of altitude >h+1)
    list<pair<int,int>> List_sp;
    queue<pair<int, int>> qNextLevel;
    queue<pair<int, int>> qSupp;

    // Visited is a global grid of pair <bool, int> which indicates by bool if a case of the global grid "grid" has been visited, and by int the layer (minimum number of neighbors from a starting point)
    // We frist initialize visited with the starting point contained in q
    // It is important to note that the visited layer component is purely convenient for the user to see the propagation but it does not interfere in the algorithm    
    visited[q.front().first][q.front().second] = {true,0};
    int Layer_depth=1;

    // Cycle through each layer until the queue is empty
    while (!q.empty()) {

        int layerSize = q.size();

        // Cycle through points in current layer
        for (int i = 0; i < layerSize; i++) {
            // Retrieve the coordinates of the current point
            int x = q.front().first;
            int y = q.front().second;
            q.pop();


            // Process the current point (and display its value)
            cout << "Visiting point (" << x << ", " << y << ") with value " << grid[x][y] << endl;

            // Browse possible directions to move
            for (int j = 0; j < 9; j++) {
                int newX = x + dx[j];
                int newY = y + dy[j];

                // Spill Point detection(lvl < h+1)
                if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && grid[newX][newY]<h) {
                        List_sp.push_back({newX, newY});
                        //visited[newX][newY] = {true,Layer_depth+1}; // Uncomment to accept duplicates (ana make statisitics)
                }
                 // Next level detection (lvl = h+1)
                else if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && !visited[newX][newY].first && grid[newX][newY]==h+1) {
                        qNextLevel.push({newX, newY});
                        visited[newX][newY] = {true,Layer_depth+1};
                        cout << "H+1 point (" << newX << ", " << newY << ") with value " << grid[newX][newY] << endl;
                }
                // Supperiors level detection (lvl > h+1)
                else if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && !visited[newX][newY].first && grid[newX][newY]>h+1) {
                        qFront.push({newX, newY});
                        visited[newX][newY] = {true,Layer_depth+1};
                        cout << "H+Nsupp  point (" << newX << ", " << newY << ") with value " << grid[newX][newY] << endl;
                }
                // Same level detection (lvl = h)
                else if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols && !visited[newX][newY].first && grid[newX][newY]==h) {
                    q.push({newX, newY});
                    visited[newX][newY] = {true,Layer_depth};
                }
            }
        }

        // break condition
        if (List_sp.size()!=0){
            return List_sp;
        }

        cout << "Moving to the next layer layerdepth: "<<Layer_depth<< endl;
        Layer_depth++;

        // Display the visited map
        cout<< "VISITED (layer):"<<endl;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[0].size(); j++) {
                cout << visited[i][j].second ;
            }
            cout << endl;
        }   


    } 
    // When q is empty, we fill it with th values of the next level queue qNextLevel
    if (!qNextLevel.empty()){
        while (!qNextLevel.empty()) {
            q.push(qNextLevel.front());
            qNextLevel.pop();
        }
    }
    return List_sp;
}






// Function that will simulate the rose of altitude by cycling the propagateByLayer function and incrementing h the current altitude of the water h,
// that is initaly determined by the altitude of the strating point (a local minimum)
// It return the list filled by the propagateByLayer function
list<pair<int,int>> Find_Spill_Point(vector<vector<int>> grid, int startX, int startY) {

    int rows = grid.size();
    int cols = grid[0].size();

    int h = grid[startX][startY];
    int hmax= findMaxValue(grid);
    // Dectaration of global objects needed by propagateByLayer
    queue<pair<int, int>> q;
    q.push({startX, startY});
    queue<pair<int, int>> qFront;
    list<pair<int,int>> List_sp;
    vector<vector<pair<bool, int>>> visited(rows, vector<pair<bool, int>>(cols, pair<bool, int>(false, 0)));

    // Cycle as long as a spill point is not detected, max iteration = 100 (to be adapted according to the case study)
    while (List_sp.empty() && h<=hmax){
        
        cout << "################### h =  "<<h<<endl;
        
        // Call propagateByLayer : store spill point value at altitude h and modify q to be ready for the next level h
        list<pair<int,int>>List_sp= propagateByLayer(grid,  visited, q, qFront, h);
        cout << "################## qFront =  "<<endl;
        PrintQ(qFront);
        cout << "################## q =  "<<endl;
        PrintQ(q);

        // breck the cycle is a spill point is detected
        if (List_sp.size()!=0){
            return List_sp;
        }
        // Incerement the level h and update the queue q with values of qFront as long as q is empty
        // Note that there is no risk of looping to infinity because all the neighbors encountered are either in q or in Front
        do{
            h++;
            cout <<"h="<<h<<endl;
            q=UpdateFront(grid, q,qFront,h);
        }while(q.empty() && h<=hmax);

        cout << "################## updated qFront =  "<<endl;
        PrintQ(qFront);
        cout << "################## updated q =  "<<endl;
        PrintQ(q);

        // Display grid and visited
        cout<< "GRID :"<<endl;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                cout << grid[i][j] ;
            }
            cout << endl;
        } 
        cout<< "VISITED :"<<endl;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[0].size(); j++) {
                cout << visited[i][j].first ;
            }
            cout << endl;
        } 
    }
    list<pair<int,int>> List_null;
    return List_null;
}
