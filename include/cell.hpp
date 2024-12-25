
#pragma once

using namespace std;
using namespace sf;


class Cell {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape shape;
    Text text;

    // Parameters //
    int cellX;
    int cellY;
    int cellColor; 

    FloatRect bounds;
    float boundsInitX;
    bool isSel;


    /* FUNCTIONS - UTILITIES.CONSTRUCTOR */
    void updateShape(int& _pX, int& _pY);
    void updateText();
    void updateBounds();
    Color pickColor(int _cC);


public:
    /* CONSTRUCTOR (AND DESTRUCTOR) */
    Cell();
    ~Cell();


    /* FUNCTIONS - UTILITIES.CONSTRUCTOR */
    void update(int& _pX, int& _pY);
    void update(int& _pX, int& _pY, const int& _cC);
    void update(int& _pX, int& _pY, int& _cC, const float& _cS, const float& _cOT, const Color& _cOC);


    /* FUNCTIONS - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);
    bool isInBounds(Vector2f& _mPos);
    bool isInBounds(FloatRect& _sAB);
    

    /* FUNCTIONS - UTILITIES.SUPPORT */
    void copyCellFromGrid(Cell& _cell);
    

    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getShape() const { return shape; } // Getter for shape.

    Text getText() const { return text; } // Getter for text.

    int getCellX() const { return cellX; } // Getter for cellX.
    int getCellY() const { return cellY; } // Getter for cellY.

    Vector2f getSize() const { return shape.getSize(); } // Getter for shape size.
    void setSize(Vector2f _cS) { shape.setSize(_cS); } // Setter for shape size.

    Vector2f getPos() const { return shape.getPosition(); } // Getter for shape position.
    void setPos(float _cPosX, float _cPosY) { shape.setPosition(Vector2f(_cPosX, _cPosY)); } // Setter for shape position.

    float getOutThick() const { return shape.getOutlineThickness(); } // Getter for shape outline thickness.
    void setOutThick(const float& _cOT) { shape.setOutlineThickness(_cOT); } // Setter for shape outline thickness.

    int getColor() const { return cellColor; } // Getter for cellColor.
    void setColor(int _cC); // Setter for cellColor, implementation in .cpp

    bool getIsSel() const { return isSel; } // Getter for isSel.
    void setIsSelTrue() { isSel = true; } // Setter for isSel true.
    void setIsSelFalse() { isSel = false; } // Setter for isSel false.
};
