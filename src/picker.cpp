
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "picker.hpp"
#include "settings.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "cell.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
Picker::Picker() 
    : matrixW(PICKERSIZE) { 
    cout << "\033[1;46mLoaded Picker constructor.\033[0m" << endl; 
    
    matrix.resize(matrixW);
    for(int i = 0; i < matrixW; i++) {
        matrix[i].update(i, cellSel, i, PICKERCELLSIZE, PICKERCELLOUTTHICK, PICKERCELLOUTCOLOR);
    }
}

Picker::~Picker() { cout << "\033[1;46mPicker destructor called.\033[0m" << endl; }


/* FUNCTION - RUNTIME */
/* Runtime draw Picker */
void Picker::draw(RenderWindow& _window, bool& _dCN, bool& _iDSB) {
    if (!_dCN) {
        for (int i = 0; i < matrixW; i++) {
            if (i != cellSel) {
                _window.draw(matrix[i].getShape());
            }
        }
        _window.draw(matrix[cellSel].getShape());
    } else {
        for (int i = 0; i < matrixW; i++) {
            if (i != cellSel) {
                _window.draw(matrix[i].getShape());
                _window.draw(matrix[i].getText());
            }  
        }

        _window.draw(matrix[cellSel].getShape());
        _window.draw(matrix[cellSel].getText());
    }

    if (isPickerActive && isSelecting && !_iDSB) {
        _window.draw(selArea);
    }
}


/* FUNCTIONS - UTILITIES.INTERFACE */
/* Check if (point-scrollOffset) is in bounds of the Picker */
bool Picker::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);

    return bounds.contains(_mPos);
}

/* Copy selection values to selCopy vector */
void Picker::copySel(Grid& _grid) {
    int selMinW = _grid.getMatrixW();
    int selMinH = _grid.getMatrixH();
    int selMaxW = -1;
    int selMaxH = -1;
    for (int i = 0; i < _grid.getMatrixH(); ++i) { 
        for (int j = 0; j < _grid.getMatrixW(); ++j) {
            Cell& cellT = _grid.getMatrix()[i][j];
            if (cellT.getIsSel()) {
                if (j < selMinW) selMinW = j;
                if (j > selMaxW) selMaxW = j;
                if (i < selMinH) selMinH = i;
                if (i > selMaxH) selMaxH = i;
            }
        }
    }
    
    if (selMaxW < selMinW || selMaxH < selMinH) { 
        cerr << "No cells were selected to copy." << endl;
        throw out_of_range("No cells were selected to copy.");
    }
    
    selCopy.clear();
    int selCopyW = selMaxW - selMinW + 1;
    int selCopyH = selMaxH - selMinH + 1;
    selCopy.resize(selCopyH);
    for (int i = 0; i < selCopyH; ++i) {
        selCopy[i].resize(selCopyW);
    } 
    
    for (int i = selMinH; i <= selMaxH; ++i) { 
        for (int j = selMinW; j <= selMaxW; ++j) {
            Cell& cellT = _grid.getMatrix()[i][j];
            if (cellT.getIsSel()) {
                selCopy[i-selMinH][j-selMinW] = cellT.getColor();
            } else {
                selCopy[i-selMinH][j-selMinW] = 0; // Handle unselected cells within the bounds.
                cerr << "There are unselected cells within the bounds." << endl;
            }
        }
    }
}

/* Paste selection values from selCopy vector */
void Picker::pasteSel(Grid& _grid) {
    int selMinW = _grid.getMatrixW();
    int selMinH = _grid.getMatrixH();
    int selMaxW = -1;
    int selMaxH = -1;
    for (int i = 0; i < _grid.getMatrixH(); ++i) { 
        for (int j = 0; j < _grid.getMatrixW(); ++j) {
            Cell& cellT = _grid.getMatrix()[i][j];
            if (cellT.getIsSel()) {
                if (j < selMinW) selMinW = j;
                if (j > selMaxW) selMaxW = j;
                if (i < selMinH) selMinH = i;
                if (i > selMaxH) selMaxH = i;
            }
        }
    }

    if (selMaxW < selMinW || selMaxH < selMinH) { 
        cerr << "No cells were selected for paste." << endl;
        throw out_of_range("No cells were selected for paste.");
    }

        
    int destW = selMaxW - selMinW + 1;
    int destH = selMaxH - selMinH + 1;
    if (destW != static_cast<int>(selCopy[0].size()) || destH != static_cast<int>(selCopy.size())) {
        cerr << "Mismatch between selCopy and selection size!" << endl;
        throw out_of_range("Mismatch between selCopy and selection size!");
    }

    for (int i = 0; i < destH; ++i) {
        for (int j = 0; j < destW; ++j) {
            int selJ = selMinW + j;
            int selI = selMinH + i;
            Cell& cellT = _grid.getMatrix()[selI][selJ];
            if (selJ >= 0 && selI >= 0 && selJ < _grid.getMatrixW() && selI < _grid.getMatrixH()) {
                cellT.setColor(selCopy[i][j]);
            }
        }
    }
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Render Picker */
void Picker::render(const float& _pPosX, const float& _pPosY) {
    cellSel = 0;
    
    for (int i = 0; i < matrixW; ++i) {
        Cell& cellT = matrix[i];
        cellT.setSize(cellT.getSize());
        cellT.setPos((i*cellT.getSize().x) + _pPosX, _pPosY);
        cellT.setColor(cellT.getColor());
        if (i != cellSel) {
            cellT.setOutThick(PICKERCELLOUTTHICK);
        } else {
            matrix[cellSel].setOutThick(PICKERCELLOUTTHICKSELECTED);
        }
    }

    shape.setSize(Vector2f(BOXPICKER, PICKERCELLSIZE));
    shape.setPosition(_pPosX, _pPosY);

    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;

    selStart = Vector2f(0, 0);
    selEnd = Vector2f(0, 0);
    selArea.setSize(Vector2f((selEnd.x-selStart.x), (selEnd.y-selStart.y)));
    selArea.setPosition(selStart.x, selStart.y);
    selArea.setFillColor(PICKERSELAREACOLOR);
    selArea.setOutlineThickness(PICKEROUTTHICK);
    selArea.setOutlineColor(PICKERSELAREAOUTCOLOR);

    selAreaBounds = selArea.getGlobalBounds();
}

/* Update picked cell if Picker is clicked */
void Picker::updatePickIfClicked(Vector2f& _mPos, float& _sOs) {
    for (int i = 0; i < matrixW; ++i) {
        if (matrix[i].isInBounds(_mPos, _sOs)) {
            cellSel = i;
            matrix[i].setOutThick(PICKERCELLOUTTHICKSELECTED);
        } else {
            matrix[i].setOutThick(PICKERCELLOUTTHICK);
        }
    }   
}

/* Update selArea if left mouse is clicked */
void Picker::updateSelAreaIfClicked(Vector2f& _mPos, float& _sOs) {
    selStart = _mPos;
    selEnd = _mPos;
    selArea.setPosition(Vector2f((_mPos.x+_sOs), _mPos.y));
    selArea.setSize(Vector2f(0, 0));

    selAreaBounds = selArea.getGlobalBounds();

    isSelecting = true;
}

/* Update selArea if left mouse is released */
FloatRect& Picker::updateSelAreaIfReleased(Vector2f& _mPos, float& _sOs) {
    selEnd = _mPos;
    selArea.setPosition(Vector2f(min(selStart.x, selEnd.x) + _sOs, min(selStart.y, selEnd.y)));
    selArea.setSize(Vector2f(abs(selEnd.x-selStart.x), abs(selEnd.y-selStart.y)));

    selAreaBounds = selArea.getGlobalBounds();
    isSelecting = false;

    return selAreaBounds;
}

/* (runtime) Update values selAraea while mouse dragging */
void Picker::updateSelAreaWhileDragging(Window& _window, Event& _event, float& _sOs) {
    if (isSelecting) {
        Vector2f mousePos(static_cast<float>(Mouse::getPosition(_window).x), static_cast<float>(Mouse::getPosition(_window).y));

        selEnd = mousePos;
        selArea.setPosition(Vector2f(min(selStart.x, selEnd.x) + _sOs, min(selStart.y, selEnd.y)));
        selArea.setSize(Vector2f(abs(selEnd.x-selStart.x), abs(selEnd.y-selStart.y)));
    }
}
