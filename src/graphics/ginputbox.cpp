
#include <iostream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "graphics/ginputbox.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GInputBox::GInputBox() { /* cout << "InputBox constructor created" << ".\n"; */ }

GInputBox::~GInputBox() { /* cout << "InputBox destructor called" << ".\n"; */ }


/* FUNCTION - UTILITIES.CONSTRUCTOR */
/* Update InputBox values */
void GInputBox::update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg) {
    // Shape //
    shape.setSize(Vector2f(_bW, _bH));
    shape.setPosition(_bPosX, _bPosY);
    shape.setFillColor(INPUTBOXCOLOR);
    shape.setOutlineThickness(INPUTBOXOUTLINETHICKNESS);
    shape.setOutlineColor(INPUTBOXOUTLINECOLOR);

    // Bounds //
    bounds = shape.getGlobalBounds();
    boundsInitX = bounds.left;

    // Others //
    cursorPosition = 0;
    isCursorVisible = false;
    isKeyPressed = false;
    
    // Text //
    text.setFont(btFont);
    text.setString(_msg);
    text.setCharacterSize(btFontSize);
    text.setPosition(shape.getPosition().x+5.f, shape.getPosition().y+1.f);
    text.setFillColor(INPUTBOXTEXTCOLOR);
}


/* FUNCTION - UTILITIES.INTERFACE */
/* Check if (point + scrollOffset) is in bounds of the InputBox */
bool GInputBox::isInBounds(Vector2f& _mPos, float& _sOs) {
    bounds.left = (boundsInitX-_sOs);

    return bounds.contains(_mPos);
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update values if InputBox is clicked */
void GInputBox::updateIfClicked() {
    shape.setOutlineThickness(INPUTBOXOUTLINETHICKNESSPRESSED);
    shape.setOutlineColor(INPUTBOXOUTLINECOLORPRESSED);

    text.setString("");
}

/* Restores values for clicked InputBox after timer duration */
void GInputBox::restoreAfterTimer() {
    shape.setOutlineThickness(INPUTBOXOUTLINETHICKNESS);
    shape.setOutlineColor(INPUTBOXOUTLINECOLOR);
}

/* (runtime) Update InputBox from keyboard inputs */
void GInputBox::updateTextInput(Event& _event) {
    if (_event.type == Event::TextEntered && !isKeyPressed) {
        if (_event.text.unicode < 128) {
            char textInputChar = static_cast<char>(_event.text.unicode);
            if (textInputChar == '\b' && !textInput.empty()) { // Backspace.
                textInput.erase(cursorPosition-1, 1);
                --cursorPosition;
                isKeyPressed = true;
            } else if (textInput.length() < INPUTBOXMAXLENGTH) {
                if (textInputChar >= 32 && textInputChar <= 126) { // Printable characters.
                    textInput.insert(cursorPosition, 1, textInputChar);
                    ++cursorPosition;
                    isKeyPressed = true;
                }
            } 
        }
    } else if (_event.type == Event::KeyPressed) {
        if (_event.key.code == Keyboard::Left && cursorPosition > 0 && !isKeyPressed) { // Left arrow.
            --cursorPosition;
            isKeyPressed = true;
        } else if (_event.key.code == Keyboard::Right && cursorPosition < static_cast<int>(textInput.length()) && !isKeyPressed) { // Right arrow.
            ++cursorPosition;
            isKeyPressed = true;
        } else if (_event.key.code == Keyboard::Delete && cursorPosition < static_cast<int>(textInput.length()) && !isKeyPressed) { // Delete key.
            textInput.erase(cursorPosition, 1);
            isKeyPressed = true;
        }
    } else if (_event.type == Event::KeyReleased) {
        isKeyPressed = false;
    }

    cursorPosition = max(0, min(cursorPosition, static_cast<int>(textInput.length())));
    string displayString = textInput;
    if (isCursorVisible) {
        displayString.insert(cursorPosition, 1, '|');
    }
    text.setString(displayString);
}

/* (runtime) Update InputBox reccurring blinking cursor */
void GInputBox::updateCursor() {
    isCursorVisible = !isCursorVisible;
    string displayString = textInput;
    if (isCursorVisible) {
        displayString.insert(cursorPosition, 1, '|');
    }
    text.setString(displayString);
    cursorTimer.restart();
}

/* Reset InputBox original values */
void GInputBox::reset() {
    shape.setOutlineThickness(INPUTBOXOUTLINETHICKNESS);
    shape.setOutlineColor(INPUTBOXOUTLINECOLOR);

    text.setString(INPUTBOXDISPLAY);

    isCursorVisible = false;
    isKeyPressed = false;
}
