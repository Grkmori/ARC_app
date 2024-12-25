
#pragma once

using namespace std;
using namespace sf;


class GInputBox {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape shape;
    Text text;

    // Parameters //
    FloatRect bounds;
    float boundsInitX;

    string textInput;
    Clock timer;
    
    Clock cursorTimer;
    int cursorPosition;
    bool isCursorVisible;
    bool isKeyPressed;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GInputBox();
    ~GInputBox();


    /* FUNCTION - UTILITIES.CONSTRUCTOR */
    void update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg);


    /* FUNCTION - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateIfClicked();
    void restoreAfterTimer();
    void updateTextInput(Event& _event);
    void updateCursor();
    void reset();


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getShape() const { return shape; } // Getter for shape.

    Text getText() const { return text; } // Getter for text.

    void updateBounds() { bounds = shape.getGlobalBounds(); } // Update bounds.

    Clock getTimer() const { return timer; } // Getter for timer.
    void resetTimer() { timer.restart(); } // Reset timer.

    Clock getCursorTimer() const { return cursorTimer; } // Getter for cursorTimer.

    String getTextInput() const { return textInput; } // Getter for textInput.

    bool getIsCursorVisible() const { return isCursorVisible; } // Getter for isCursorVisible.
    
    void setIsKeyPressed(bool _value) { isKeyPressed = _value; } // Setter for isKeyPressed.
    bool getIsKeyPressed() const { return isKeyPressed; } // Getter for isKeyPressed.
};
