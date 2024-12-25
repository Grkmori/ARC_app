
#pragma once

using namespace std;
using namespace sf;


class GChecker {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape shape;

    // Parameters //
    FloatRect bounds;
    float boundsInitX;

    bool isChecked;

    ConvexShape checkMark;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GChecker();
    ~GChecker();


    /* FUNCTION - UTILITIES.CONSTRUCTOR */
    void update(const float& _cS, const float& _cPosX, const float& _cPosY);


    /* FUNCTION - UTILITIES.INTERFACE */
    bool isInBounds(Vector2f& _mPos, float& _sOs);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateIfClicked();
    void restoreIfClicked();


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getShape() const { return shape; } // Getter for shape.

    ConvexShape getCheckMark() const {return checkMark; } // Getter for checkMark.

    void updateBounds() { bounds = shape.getGlobalBounds(); } // Update bounds.

    bool getIsChecked() const { return isChecked; } // Getter for isChecked.
};
