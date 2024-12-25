
#pragma once

#include "cell.hpp"

using namespace std;


class Grid {
private:
    /* COSTRUCTORS - PARAMETERS */
    // Parameters //
    vector<vector<Cell>> matrix;
    int matrixW;
    int matrixH;

    RectangleShape shape;
    FloatRect bounds;
    float boundsInitX;
    bool isSel;

    
public:
    /* COSTRUCTORS (AND DESTRUCTOR) */
    Grid();
    Grid(int _gW, int _gH);
    Grid(int _gW, int _gH, const vector<vector<int>>& _gData);
    ~Grid();


    /* FUNCTION - RUNTIME */
    void draw(RenderWindow& _window, bool& _dCN);


    /* FUNCTIONS - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);
    bool isInBounds(Vector2f& _mPos);
    bool isInBounds(FloatRect& _sAB);
    void updateCellIfClicked(Vector2f& _mPos);
    void updateCellIfAreaSelected(FloatRect& _sAB);
    void updateCellIfNotSelected();
    int checkForFloodFill();
    Cell& getCellForFloodFill();

    
    /* FUNCTIONS - UTILITIES.RENDERING */
    void renderTrainGrid(int _tPGIdx, const float& _gPosX, const float& _gAOffsetX, const float& _gPosY);
    void renderTestGrid(const float& _gPosX, const float& _gPosY);
    void updateTrainBounds(const float& _gPosX, const float& _gPosY);
    void updateTestBounds(const float& _gPosX, const float& _gPosY);
    void updateSelectedCells(int _cC);
    void updateCellIfRightClicked(Vector2f& _mPos, float& _sOs, int _cC);
    void floodFillFromLocation(int _tX, int _tY, int _cC);
    

    /* FUNCTIONS - UTILITIES.SUPPORT */
    void resizeCellsSize(const float& _boxSize);
    void resizeEditGrid();
    void resizeEditGrid(int& _oGW, int& _oGH);
    void copyGridToGrid(Grid& _gCopied);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    int getMatrixW() const { return matrixW; } // Getter for matrixW.

    int getMatrixH() const { return matrixH; } // Getter for matrixH.

    vector<vector<Cell>>& getMatrix() { return matrix; } // Getter for matrix.

    bool getIsSel() const { return isSel; } // Getter for isSel.
    void setIsSelTrue() { isSel = true; } // Setter for isSel true.
    void setIsSelFalse() { isSel = false; } // Setter for isSel false.
};
