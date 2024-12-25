
#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "graphics/gscrollbar.hpp"
#include "settings.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GScrollBar::GScrollBar() { /* cout << "ScrollBar constructor created" << ".\n"; */ }

GScrollBar::~GScrollBar() { /* cout << "ScrollBar destructor called" << ".\n"; */ }


/* FUNCTION - UTILITIES.CONSTRUCTOR */
/* Update ScrollBar values */
void GScrollBar::update(const float& _sbBGW, const float& _sbW, const float& _sbH) {
    // Shape BG //
    bgShape.setSize(Vector2f(_sbBGW, _sbH));
    bgShape.setPosition(SCROLLBARPOSX, SCROLLBARPOSY);
    bgShape.setFillColor(SCROLLBARBGCOLOR);
    bgShape.setOutlineThickness(SCROLLBAROUTLINETHICKNESS);
    bgShape.setOutlineColor(SCROLLBARBGOUTLINECOLOR);

    // Shape //
    shape.setSize(Vector2f(_sbW, _sbH));
    shape.setPosition(SCROLLBARPOSX, SCROLLBARPOSY);
    shape.setFillColor(SCROLLBARCOLOR);
    shape.setOutlineThickness(SCROLLBAROUTLINETHICKNESS);
    shape.setOutlineColor(SCROLLBAROUTLINECOLOR);

    // Bounds //
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;

    isClicked = false;
    isPressed = false;

    windowW = static_cast<float>(WINDOWW);

    // Dragging //
    difX = bgShape.getSize().x - shape.getSize().x;
    dragStart.x = 0.f;
    dragStart.y = 0.f;
    dragMinPosX = 0.f;
    dragMaxPosX = dragMinPosX + difX;
    offsetMultiplierX = 0.f;
}


/* FUNCTION - UTILITIES.INTERFACE */
/* Check if (point + scrollOffset) is in the ScrollBar */
bool GScrollBar::isInBounds(Vector2f& _mPos) {
    bounds.left = (boundsInitX+shape.getPosition().x);

    return bounds.contains(_mPos);
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update values if ScrollBar is clicked */
void GScrollBar::updateIfClicked(Vector2f& _mPos) {
    shape.setFillColor(SCROLLBARCOLORPRESSED);
    shape.setOutlineColor(SCROLLBAROUTLINECOLORPRESSED);

    isClicked = true;
    isPressed = true;
    timer.restart();

    dragStart.x = _mPos.x - shape.getPosition().x;
}

/* Update values if ScrollBar is released */
void GScrollBar::updateIfReleased() {
    shape.getGlobalBounds();
    
    isPressed = false;
    timer.restart();
}

/* Restores values for clicked ScrollBar after timer duration */
void GScrollBar::restoreAfterTimer() {
    shape.setFillColor(SCROLLBARCOLOR);
    shape.setOutlineColor(SCROLLBAROUTLINECOLOR);

    isClicked = false;
}

/* (runtime) Update values of the ScrollBar while mouse dragging */
float GScrollBar::updateWhileDragging(Window& _window, Event& _event, float& _contentW) {
    if (isPressed) {
        Vector2f mousePos(static_cast<float>(Mouse::getPosition(_window).x), static_cast<float>(Mouse::getPosition(_window).y));

        float newPosX = mousePos.x - dragStart.x;
        newPosX = max(dragMinPosX, min(newPosX, dragMaxPosX));
        shape.setPosition(newPosX, shape.getPosition().y);
        
        timer.restart();

        return (shape.getPosition().x*offsetMultiplierX);
    }

    return shape.getPosition().x;
}

/* Update Scrollbar from keyboard inputs */
void GScrollBar::updateFromKeyboard(float _pos, float& _contentW) {
    float newPosX = max(dragMinPosX, min((_pos/offsetMultiplierX) + shape.getPosition().x, dragMaxPosX));
    shape.setPosition(newPosX , shape.getPosition().y);
}

/* Reset ScrollBar to original values */
void GScrollBar::reset(float& _contentW) {
    shape.setSize(Vector2f((windowW/_contentW) * windowW, SCROLLBARH));
    shape.setPosition(SCROLLBARPOSX, SCROLLBARPOSY);

    bounds = shape.getGlobalBounds();

    difX = bgShape.getSize().x - shape.getSize().x;
    dragStart.x = 0.f;
    dragStart.y = 0.f;
    dragMinPosX = 0.f;
    dragMaxPosX = dragMinPosX + difX;
    offsetMultiplierX = ((1-dragMinPosX) / (dragMaxPosX-dragMinPosX)) * (_contentW-windowW);
}
