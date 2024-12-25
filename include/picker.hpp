
#pragma once

#include "grid.hpp"
#include "cell.hpp"

using namespace std;
using namespace sf;


class Picker {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Parameters //
    vector<Cell> matrix;
    int matrixW;
    int cellSel = 0;
    
    RectangleShape shape;
    FloatRect bounds;
    float boundsInitX;

    RectangleShape selArea;
    FloatRect selAreaBounds;
    Vector2f selStart;
    Vector2f selEnd;
    bool isSelecting;
    vector<vector<int>> selCopy;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    Picker();
    ~Picker();


    /* FUNCTION - RUNTIME */
    void draw(RenderWindow& _window, bool& _dCN, bool& _iDSB);


    /* FUNCTIONS - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);
    void copySel(Grid& _grid);
    void pasteSel(Grid& _grid);
    

    /* FUNCTIONS - UTILITIES.RENDERING */
    void render(const float& _gInitPosX, const float& _gInitPosY);
    void updatePickIfClicked(Vector2f& _mPos, float& _sOs);
    void updateSelAreaIfClicked(Vector2f& _mPos, float& _sOs);
    FloatRect& updateSelAreaIfReleased(Vector2f& _mPos, float& _sOs);
    void updateSelAreaWhileDragging(Window& _window, Event& _event, float& _sOs);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getSelArea() const { return selArea; } // Getter for selArea.

    FloatRect getSelAreaBounds() const { return selAreaBounds; } // Getter for selAreaBounds.

    Vector2f getSelStart() const { return selStart; } // Getter for selStart.

    Vector2f getSelEnd() const { return selEnd; } // Getter for selEnd.

    int getCellSel() const { return cellSel; } // Getter for cell selected.
    void setCellSel(int _sel) { cellSel = _sel; } // Setter for cell selected.
};

