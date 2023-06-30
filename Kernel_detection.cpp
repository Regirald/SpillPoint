#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> applyMask(const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> maskedGrid(rows, vector<int>(cols, 0));

    vector<vector<int>> kernel = {
        {-1, 1, -1},
        {0, 1, 0},
        {-1, 1, -1}
    };

    vector<vector<int>> rotatedKernel = {
        {-1, 0, -1},
        {1, 1, 1},
        {-1, 0, -1}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int current = grid[i][j];
            bool neighborComparison = true;
            bool neighborComparison2 = true;

            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    if (i + k - 1 >= 0 && i + k - 1 < rows && j + l - 1 >= 0 && j + l - 1 < cols) {
                        int neighbor = grid[i + k - 1][j + l - 1];
                        int kernelValue = kernel[k][l];
                        int rotatedKernelValue = rotatedKernel[k][l];

                        if (kernelValue == -1) {
                            continue; // Ignore the value of the current kernel cell
                        } else if (kernelValue == 1 && neighbor < current) {
                            neighborComparison = false;
                            break;
                        } else if (kernelValue == 0 && neighbor >= current) {
                            neighborComparison = false;
                            break;
                        }

                        if (rotatedKernelValue == -1) {
                            continue; // Ignore the value of the current rotated kernel cell
                        } else if (rotatedKernelValue == 1 && neighbor < current) {
                            neighborComparison2 = false;
                            break;
                        } else if (rotatedKernelValue == 0 && neighbor >= current) {
                            neighborComparison2 = false;
                            break;
                        }
                    }
                }

                if (!neighborComparison && !neighborComparison2) {
                    break;
                }
            }

            if (neighborComparison|| neighborComparison2) {
                maskedGrid[i][j] = 1; // The neighborhood comparison is satisfied
            }
        }
    }

    return maskedGrid;
}

int main() {
    vector<vector<int>> grid = {
        {5, 2, 4, 5, 3},
        {6, 9, 8, 9, 2},
        {5, 9, 3, 9, 5},
        {3, 9, 9, 9, 1},
        {2, 1, 4, 5, 2}
    };

    vector<vector<int>> maskedGrid = applyMask(grid);

    // Print the masked grid
    for (const auto& row : maskedGrid) {
        for (const int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}
