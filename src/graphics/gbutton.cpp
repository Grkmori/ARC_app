
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/gbutton.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GButton::GButton() { /* cout << "Button constructor created" << ".\n"; */ }

GButton::~GButton() { /* cout << "Button destructor called" << ".\n"; */ }


/* FUNCTION - UTILITIES.CONSTRUCTOR */
/* Update Button values */
void GButton::update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg) {
    // Shape //
    shape.setSize(Vector2f(_bW, _bH));
    shape.setPosition(_bPosX, _bPosY);
    shape.setFillColor(BUTTONCOLOR);
    shape.setOutlineThickness(BUTTONOUTLINETHICKNESS);
    shape.setOutlineColor(BUTTONOUTLINECOLOR);
    
    // Bounds //
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    
    isClicked = false;
    isPressed = false;

    // Text //
    text.setFont(btFont);
    text.setString(_msg);
    text.setCharacterSize(btFontSize);
    text.setFillColor(BUTTONTEXTCOLOR);

    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    text.setPosition(round(shape.getPosition().x + (shape.getSize().x/2.f)), round(shape.getPosition().y + (shape.getSize().y/2.f)));
}

/* Update Button values (+color) */
void GButton::update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg, const Color& _bC) {
    // Shape //
    shape.setSize(Vector2f(_bW, _bH));
    shape.setPosition(_bPosX, _bPosY);
    shape.setFillColor(BUTTONSUBMITCOLOR);
    shape.setOutlineThickness(BUTTONOUTLINETHICKNESS);
    shape.setOutlineColor(BUTTONOUTLINECOLOR);
    
    // Bounds //
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;
    
    isClicked = false;
    isPressed = false;

    // Text //
    text.setFont(btFont);
    text.setString(_msg);
    text.setCharacterSize(btFontSize);
    text.setFillColor(BUTTONTEXTCOLOR);

    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    text.setPosition(round(shape.getPosition().x + (shape.getSize().x/2.f)), round(shape.getPosition().y + (shape.getSize().y/2.f)));
}


/* FUNCTION - UTILITIES.INTERFACE */
/* Check if (point + scrollOffset) is in bounds of the Button */
bool GButton::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);

    return bounds.contains(_mPos);
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update values if Button is clicked */
void GButton::updateIfClicked() {
    shape.setFillColor(BUTTONCOLORPRESSED);
    shape.setOutlineThickness(BUTTONOUTLINETHICKNESSPRESSED);
    shape.setOutlineColor(BUTTONOUTLINECOLORPRESSED);

    isClicked = true;
    isPressed = true;
    timer.restart();
}

/* Update values if Button is clicked (+color) */
void GButton::updateIfClicked(const Color& _bCP) {
    shape.setFillColor(_bCP);
    shape.setOutlineThickness(BUTTONOUTLINETHICKNESSPRESSED);
    shape.setOutlineColor(BUTTONOUTLINECOLORPRESSED);

    isClicked = true;
    isPressed = true;
    timer.restart();
}

/* Update values if Button click is released */
void GButton::updateIfReleased() { 
    timer.restart();
    isPressed = false;
}

/* Restores values for clicked Button after timer duration */
void GButton::restoreAfterTimer() {
    if (!isPressed) {
        shape.setFillColor(BUTTONCOLOR);
        shape.setOutlineThickness(BUTTONOUTLINETHICKNESS);
        shape.setOutlineColor(BUTTONOUTLINECOLOR);

        isClicked = false;
    }
}

/* Restores values for clicked Button after timer duration (+color) */
void GButton::restoreAfterTimer(const Color& _bCP) {
    if (!isPressed) {
        shape.setFillColor(_bCP);
        shape.setOutlineThickness(BUTTONOUTLINETHICKNESS);
        shape.setOutlineColor(BUTTONOUTLINECOLOR);

        isClicked = false;
    }
}
