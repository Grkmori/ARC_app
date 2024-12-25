
#pragma once

using namespace std;
using namespace sf;


class GScrollBar {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape bgShape;
    RectangleShape shape;

    // Parameters //
    FloatRect bounds;
    float boundsInitX;

    Clock timer;
    bool isClicked;
    bool isPressed;

    float windowW;
    float difX;
    Vector2f dragStart;
    float dragMinPosX;
    float dragMaxPosX;
    float offsetMultiplierX;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GScrollBar();
    ~GScrollBar();


    /* FUNCTION - UTILITIES.CONSTRUCTOR */
    void update(const float& _sbBGW, const float& _sbW, const float& _sbH);


    /* FUNCTION - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateIfClicked(Vector2f& _mPos);
    void updateIfReleased();
    void restoreAfterTimer();
    float updateWhileDragging(Window& _window, Event& _event, float& _contentW);
    void updateFromKeyboard(float _pos, float& _contentW);
    void reset(float& _contentW);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getBGShape() const { return bgShape; } // Getter for bgShape.

    RectangleShape getShape() const { return shape; } // Getter for shape.

    Clock getTimer() const { return timer; } // Getter for timer.

    bool getIsClicked() const { return isClicked; } // Getter for isClicked.
};
