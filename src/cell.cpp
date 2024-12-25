
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "cell.hpp"
#include "settings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
Cell::Cell() { /* cout << "Cell constructor created" << ".\n"; */ }

Cell::~Cell() { /* cout << "Cell destructor called" << ".\n"; */ }


/* FUNCTIONS - UTILITIES.CONSTRUCTOR */
/* Update Cell values */
void Cell::update(int& _pX, int& _pY) {
    cellX = _pX;
    cellY = _pY;
    cellColor = 0; // Color black as default.

    this->updateShape(cellX, cellY);
    this->updateText();
    this->updateBounds();
}

/* Update Cell values (and color) */
void Cell::update(int& _pX, int& _pY, const int& _cC) {
    cellX = _pX;
    cellY = _pY;
    cellColor = _cC;

    this->updateShape(cellX, cellY);
    this->updateText();
    this->updateBounds();
}

/* Update Cell values (color, size and outline thickeness) */
void Cell::update(int& _pX, int& _pY, int& _cC, const float& _cS, const float& _cOT, const Color& _cOC) {
    cellX = _pX;
    cellY = _pY;
    cellColor = _cC;

    shape.setSize(Vector2f(_cS, _cS));
    shape.setPosition(cellX * _cS, cellY * _cS);
    shape.setFillColor(pickColor(cellColor));
    shape.setOutlineThickness(_cOT);
    shape.setOutlineColor(_cOC);

    this->updateText();
    this->updateBounds();
}

/* (private) Update shape values */
void Cell::updateShape(int& _pX, int& _pY) {
    shape.setSize(Vector2f(CELLSIZE, CELLSIZE));
    shape.setPosition(cellX * CELLSIZE, cellY * CELLSIZE);
    shape.setFillColor(pickColor(cellColor));
    shape.setOutlineThickness(CELLOUTTHICK);
    shape.setOutlineColor(CELLOUTLINECOLOR);
}

/* (private) Update text values */
void Cell::updateText() {
    text.setFont(cFont);
    text.setString(to_string(cellColor));
    text.setCharacterSize(cFontSize);
    text.setFillColor(CELLTEXTCOLOR);
}

/* (private) Update textBounds values */
void Cell::updateBounds() {
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    isSel = false;
    
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    text.setPosition(round(shape.getPosition().x + (shape.getSize().x/2.f)), round(shape.getPosition().y + (shape.getSize().y/2.f)));
}

/* (private) Gets cellColor from int provided */
Color Cell::pickColor(int _cC) {
    switch (_cC) {
        case 0: return Color(0, 0, 0); break;       // Black #000 . 
        case 1: return Color(0, 116, 217); break;   // Blue #0074D9 .
        case 2: return Color(255, 65, 54); break;   // Red #FF4136 .
        case 3: return Color(46, 204, 64); break;   // Green #2ECC40 .
        case 4: return Color(255, 220, 0); break;   // Yellow #FFDC00 .
        case 5: return Color(170, 170, 170); break; // Grey #AAAAAA .
        case 6: return Color(240, 18, 190); break;  // Fuschia #F012BE .
        case 7: return Color(255, 133, 27); break;  // Orange #FF851B .
        case 8: return Color(127, 219, 255); break; // Teal #7FDBFF .
        case 9: return Color(135, 12, 37); break;   // Brown #870C25 .
        default: 
            cerr << "\033[1;41mAlert: Invalid color code provided: \033[0m" << _cC << endl;
            return Color(0, 0, 0); // Return a default color Black #000.
    }
}


/* FUNCTIONS - UTILITIES.INTERFACE */
/* Check if (point-scrollOffset) is in bounds of the Cell */
bool Cell::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);

    return bounds.contains(_mPos);
}

/* Check if (point) is in bounds of the Cell */
bool Cell::isInBounds(Vector2f& _mPos) {
    return bounds.contains(_mPos);
}

/* Check if (rect) is in bounds of the Cell */
bool Cell::isInBounds(FloatRect& _sAB) {
    return bounds.intersects(_sAB);
}


/* FUNCTIONS - UTILITIES.SUPPORT */
/* Copy Cell values from another Grid Cell */
void Cell::copyCellFromGrid(Cell& _cell) {
    cellX = _cell.cellX;
    cellY = _cell.cellY;
    cellColor = _cell.cellColor;

    this->updateShape(cellX, cellY);
    this->updateText();
    this->updateBounds();
}


/* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
/* Setter implmentation cellColor from int provided */
void Cell::setColor(int _cC) {
    cellColor = _cC; 
    shape.setFillColor(pickColor(cellColor));
    text.setString(to_string(cellColor));

    this->updateBounds();
}
