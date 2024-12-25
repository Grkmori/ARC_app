
#pragma once

using namespace std;
using namespace sf;


class GButton {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape shape;
    Text text;

    // Parameters //
    FloatRect bounds;
    float boundsInitX;
    
    Clock timer;
    bool isClicked;
    bool isPressed;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GButton();
    ~GButton();


    /* FUNCTION - UTILITIES.CONSTRUCTOR */
    void update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg);
    void update(const float& _bW, const float& _bH, const float& _bPosX, const float& _bPosY, const string& _msg, const Color& _bC);


    /* FUNCTION - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateIfClicked();
    void updateIfClicked(const Color& _bCP);
    void updateIfReleased();
    void restoreAfterTimer();
    void restoreAfterTimer(const Color& _bCP);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getShape() const { return shape; } // Getter for shape.

    Text getText() const { return text; } // Getter for text.

    void updateBounds() { bounds = shape.getGlobalBounds(); } // Update bounds.

    Clock getTimer() const { return timer; } // Getter for timer.

    bool getIsClicked() const { return isClicked; } // Getter for isClicked.
};
