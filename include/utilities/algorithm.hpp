
#pragma once

#include <vector>
#include <functional>

using namespace std;


/* void floodFill(vector<vector<int>>& grid, int x, int y, int symbol) {
    int target = grid[x][y];
    
    if (target == symbol) {
        return;
    }

    function<void(int, int)> flow = [&](int i, int j) {
        if (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size()) {
            if (grid[i][j] == target) {
                grid[i][j] = symbol;
                flow(i - 1, j);
                flow(i + 1, j);
                flow(i, j - 1);
                flow(i, j + 1);
            }
        }
    };

    flow(x, y);
} */
