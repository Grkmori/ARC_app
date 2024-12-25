
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "grid.hpp"
#include "settings.hpp"
#include "graphics/gsettings.hpp"
#include "cell.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTORS (AND DESTRUCTOR) */
Grid::Grid() { cout << "Basic Grid" << ".\n"; }

Grid::Grid(int _gW, int _gH) 
    : matrixW(_gW)
    , matrixH(_gH) {
     
    matrix.resize(matrixH);
    for (int i = 0; i < matrixH; ++i) {
        matrix[i].resize(matrixW);
        for (int j = 0; j < matrixW; ++j) {
            matrix[i][j].update(i, j);
        }
    }

    /* cout << "Matrix Size: " << matrix.size() << "." << matrix[0].size() << ".\n"; */
}

Grid::Grid(int _gW, int _gH, const vector<vector<int>>& _gData)
    : matrixW(_gW)
    , matrixH(_gH) { 

    matrix.resize(matrixH);
    for (int i = 0; i < matrixH; ++i) {
        matrix[i].resize(matrixW);
        for (int j = 0; j < matrixW; ++j) {
            if (_gData[i][j] >= 0 && _gData[i][j] <= 9) {
                matrix[i][j].update(i, j, _gData[i][j]);
            } else {
                matrix[i][j].update(i, j);
            }
        }
    }

    /* cout << "Matrix Size: " << matrix.size() << "." << matrix[0].size() << ".\n"; */
}

Grid::~Grid() { /* cout << "Grid destructor called. Matrix Size: " << matrix.size() << "." << matrix[0].size() << "\n"; */ }


/* FUNCTION - RUNTIME */
/* Runtime draw Grid */
void Grid::draw(RenderWindow& _window, bool& _dCN) {
    if (!_dCN) {
        for (int i = 0; i < matrixH; ++i) {
            for (int j = 0; j < matrixW; ++j) {
                Cell& cellT = matrix[i][j];
                if (!matrix[i][j].getIsSel()) {
                    _window.draw(cellT.getShape());
                } else {
                    _window.draw(cellT.getShape());
                    selCellSprite.setPosition(cellT.getPos().x, cellT.getPos().y);
                    selCellSprite.setScale((cellT.getSize().x/selCellSprite.getTexture()->getSize().x), (cellT.getSize().y/selCellSprite.getTexture()->getSize().y));
                    _window.draw(selCellSprite);
                }
            }
        }
    } else {
        for (int i = 0; i < matrixH; ++i) {
            for (int j = 0; j < matrixW; ++j) {
                Cell& cellT = matrix[i][j];
                if (!matrix[i][j].getIsSel()) {
                    _window.draw(cellT.getShape());
                    _window.draw(cellT.getText());
                } else {
                    _window.draw(cellT.getShape());
                    _window.draw(cellT.getText());
                    selCellSprite.setPosition(cellT.getPos().x, cellT.getPos().y);
                    selCellSprite.setScale((cellT.getSize().x/selCellSprite.getTexture()->getSize().x), (cellT.getSize().y/selCellSprite.getTexture()->getSize().y));
                    _window.draw(selCellSprite);
                }
            }
        }
    }
}


/* FUNCTIONS - UTILITIES.INTERFACE */
/* Check if (point+scrollOffset) is in bounds of the Grid */
bool Grid::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);
    
    return bounds.contains(_mPos);
}

/* Check if (point) is in bounds of the Grid */
bool Grid::isInBounds(Vector2f& _mPos) {
    return bounds.contains(_mPos);
}

/* Check if (rect) is in bounds of the Grid */
bool Grid::isInBounds(FloatRect& _sAB) {
    return bounds.intersects(_sAB);
}

/* Update Cells if is in selection */
void Grid::updateCellIfClicked(Vector2f& _mPos) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.isInBounds(_mPos)) {
                cellT.setIsSelTrue();
            } else {
                cellT.setIsSelFalse();
            }
        }    
    }

    isSel = true;
}

/* Update Cells if is in selection area */
void Grid::updateCellIfAreaSelected(FloatRect& _sAB) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.isInBounds(_sAB)) {
                cellT.setIsSelTrue();
            } else {
                cellT.setIsSelFalse();
            }
        }    
    }

    isSel = true;
}

/* Update Cells if is out of selection */
void Grid::updateCellIfNotSelected() {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (isSel) {
                cellT.setIsSelFalse();
            }
        }    
    }

    isSel = false;
}

/* Check number of Cells selected for flood fill function */
int Grid::checkForFloodFill() {
    int numOfSel = 0;
        for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.getIsSel()) {
                ++numOfSel;
            }
        }    
    }

    return numOfSel;
}

/* Get selected Cell for flood fill function */
Cell& Grid::getCellForFloodFill() {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.getIsSel()) {
                return cellT;
            }
        }    
    }
    throw runtime_error("No selected cell found for flood fill.");
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Render train Grid */
void Grid::renderTrainGrid(int _tPGIdx, const float& _gPosX, const float& _gAOffsetX, const float& _gPosY) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            cellT.setSize(cellT.getSize());
            cellT.setPos((j*cellT.getSize().x) + _gPosX + (_gAOffsetX*_tPGIdx), (i*cellT.getSize().y) + _gPosY);
            cellT.setColor(cellT.getColor());
        }    
    }

    this->updateTrainBounds(_gPosX, _gPosY);
}

/* Render test (or edit) Grid */
void Grid::renderTestGrid(const float& _gPosX, const float& _gPosY) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            cellT.setSize(cellT.getSize());
            cellT.setPos((j*cellT.getSize().x) + _gPosX, (i*cellT.getSize().y) + _gPosY);
            cellT.setColor(cellT.getColor());
        }    
    }

    this->updateTestBounds(_gPosX, _gPosY);
}

/* Update Grid's train bounds */
void Grid::updateTrainBounds(const float& _gPosX, const float& _gPosY) {
    shape.setSize(Vector2f(BOXTRAINS, BOXTRAINS));
    shape.setPosition(_gPosX, _gPosY);

    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    isSel = false;
}

/* Update Grid's test bounds */
void Grid::updateTestBounds(const float& _gPosX, const float& _gPosY) {
    shape.setSize(Vector2f(BOXTESTS, BOXTESTS));
    shape.setPosition(_gPosX, _gPosY);

    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    isSel = false;
}

/* Update selected Cells from Pickers choice */
void Grid::updateSelectedCells(int _cC) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.getIsSel()) {
                cellT.setColor(_cC);
            }
        }    
    }
}

/* Update Cells if is in selection */
void Grid::updateCellIfRightClicked(Vector2f& _mPos, float& _sOs, int _cC) {
    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            Cell& cellT = matrix[i][j];
            if (cellT.isInBounds(_mPos, _sOs)) {
                cellT.setColor(_cC);
            } 
        }    
    }
}

/* Implements "flood-fill algorithm" replacing connected cells (in a grid) that share the same value with a specified target color */
void Grid::floodFillFromLocation(int _tX, int _tY, int _cC) {
    int targetColor = matrix[_tX][_tY].getColor();
    if (targetColor == _cC) return; // No operation needed if already the same.

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    queue<pair<int, int>> toVisit;
    toVisit.push({_tX, _tY});

    matrix[_tX][_tY].setColor(_cC);
    while (!toVisit.empty()) {
        auto [row, col] = toVisit.front();
        toVisit.pop();

        for (const auto& [dRow, dCol] : directions) {
            int newRow = row + dRow;
            int newCol = col + dCol;

            if (newRow >= 0 && newRow < matrixH &&
                newCol >= 0 && newCol < matrixW &&
                matrix[newRow][newCol].getColor() == targetColor) {
                matrix[newRow][newCol].setColor(_cC);
                toVisit.push({newRow, newCol});
            }
        }
    }
}

/* FUNCTIONS - UTILITIES.SUPPORT */
/* Resize Grid's cellSize to box size */
void Grid::resizeCellsSize(const float& _boxSize) {
    float maxCellSizeW = _boxSize / matrixW;
    float maxCellSizeH = _boxSize / matrixH;
    float boxMaxCellSize = min(maxCellSizeW, maxCellSizeH);
    boxMaxCellSize = min(MAXCELLSIZE, boxMaxCellSize);

    for (int i = 0; i < matrixH; ++i) {
        for (int j = 0; j < matrixW; ++j) {
            matrix[i][j].setSize(Vector2f(boxMaxCellSize, boxMaxCellSize));
        }
    }
}

/* Reset edit Grid */
void Grid::resizeEditGrid() {
    matrixW = EDITGRIDINITIALSIZE;
    matrixH = EDITGRIDINITIALSIZE;

    matrix.clear();
    matrix.resize(matrixH);
    for (int i = 0; i < matrixH; ++i) {
        matrix[i].resize(matrixW);
        for (int j = 0; j < matrixW; ++j) {
            matrix[i][j].update(i, j);
        }
    }

    this->resizeCellsSize(BOXTESTS);
}

/* Resize edit Grid */
void Grid::resizeEditGrid(int& _oGW, int& _oGH) {
    matrixW = _oGW;
    matrixH = _oGH;

    matrix.clear();
    matrix.resize(matrixH);
    for (int i = 0; i < matrixH; ++i) {
        matrix[i].resize(matrixW);
        for (int j = 0; j < matrixW; ++j) {
            matrix[i][j].update(i, j);
        }
    }

    this->resizeCellsSize(BOXTESTS);
}

/* Copy Grid values to other Grid */
void Grid::copyGridToGrid(Grid& _gCopied) {
    matrixW = _gCopied.matrixW;
    matrixH = _gCopied.matrixH;

    matrix.resize(matrixH);
    for (int i = 0; i < matrixH; ++i) {
        matrix[i].resize(matrixW);
        for (int j = 0; j < matrixW; ++j) {
            matrix[i][j].copyCellFromGrid(_gCopied.getMatrix()[i][j]);
        }
    }

    this->resizeCellsSize(BOXTESTS);
}
