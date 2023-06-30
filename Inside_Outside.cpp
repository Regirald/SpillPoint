#include <iostream>
#include <vector>

bool isShapeFull(const std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    bool insideShape = false;

    for (int row = 0; row < numRows; row++) {
        int intersectCount = 0;
        for (int col = 0; col < numCols; col++) {
            if (grid[row][col] == 1) {
                if (!insideShape) {
                    insideShape = true;
                    intersectCount++;
                }
            } else {
                insideShape = false;
            }
        }

        if (intersectCount % 2 != 0) {
            return false;  // La forme est lacunaire
        }
    }

    return true;  // La forme est pleine
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    bool isFull = isShapeFull(grid);

    if (isFull) {
        std::cout << "La forme est pleine." << std::endl;
    } else {
        std::cout << "La forme est lacunaire." << std::endl;
    }

    return 0;
}
