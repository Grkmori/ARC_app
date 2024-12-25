
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/gchecker.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GChecker::GChecker() { /* cout << "Checker constructor created" << ".\n"; */ }

GChecker::~GChecker() { /* cout << "Checker destructor called" << ".\n"; */ }


/* FUNCTION - UTILITIES.CONSTRUCTOR */
/* Update Checker values */
void GChecker::update(const float& _cS, const float& _cPosX, const float& _cPosY) {
    // Shape //
    shape.setSize(Vector2f(_cS, _cS));
    shape.setPosition(_cPosX, _cPosY);
    shape.setFillColor(CHECKERCOLOR);
    shape.setOutlineThickness(CHECKEROUTLINETHICKNESS);
    shape.setOutlineColor(CHECKEROUTLINECOLOR);

    // Bounds //
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    
    isChecked = false;

    // CheckMark //
    checkMark.setPointCount(8);
    checkMark.setPoint(0, Vector2f(shape.getPosition().x + shape.getSize().x, shape.getPosition().y));
    checkMark.setPoint(1, Vector2f(shape.getPosition().x + (shape.getSize().x*0.5f), shape.getPosition().y + (shape.getSize().y*0.85f)));
    checkMark.setPoint(2, Vector2f(shape.getPosition().x + (shape.getSize().x*0.4f), shape.getPosition().y + (shape.getSize().y*0.85f)));
    checkMark.setPoint(3, Vector2f(shape.getPosition().x + (shape.getSize().x*0.2f), shape.getPosition().y + (shape.getSize().y*0.65f)));
    checkMark.setPoint(4, Vector2f(shape.getPosition().x, shape.getPosition().y + (shape.getSize().y*0.45f)));
    checkMark.setPoint(5, Vector2f(shape.getPosition().x, shape.getPosition().y + (shape.getSize().y*0.35f)));
    checkMark.setPoint(6, Vector2f(shape.getPosition().x + (shape.getSize().x*0.4f), shape.getPosition().y + shape.getSize().y));
    checkMark.setPoint(7, Vector2f(shape.getPosition().x + (shape.getSize().x*0.5f), shape.getPosition().y + shape.getSize().y));      
    checkMark.setFillColor(CHECKERCHECKMARKCOLOR); // CHECKERCHECKMARKCOLOR
}


/* FUNCTION - UTILITIES.INTERFACE */
/* Check if (point + scrollOffset) in bounds of the Checker */
bool GChecker::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);

    return bounds.contains(_mPos);
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update values if Checker is clicked */
void GChecker::updateIfClicked() {
    shape.setFillColor(CHECKERCOLORPRESSED);
    shape.setOutlineThickness(CHECKEROUTLINETHICKNESSPRESSED);
    shape.setOutlineColor(CHECKEROUTLINECOLORPRESSED);

    isChecked = true;
}

/* Restores values if Checker is not clicked */
void GChecker::restoreIfClicked() {
    shape.setFillColor(CHECKERCOLOR);
    shape.setOutlineThickness(CHECKEROUTLINETHICKNESS);
    shape.setOutlineColor(CHECKEROUTLINECOLOR);

    isChecked = false;
}
