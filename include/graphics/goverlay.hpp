
#pragma once

using namespace std;
using namespace sf;


class GOverlay {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    RectangleShape shape;
    Text text;


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GOverlay();
    ~GOverlay();


    /* FUNCTIONS - UTILITIES.CONSTRUCTOR */
    void update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY);
    void update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY, const string& _msg);
    void update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY, const string& _msg, const float& _msgR);
    
    
    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RectangleShape getShape() const { return shape; } // Getter for shape.
    
    Text getText() const { return text; } // Getter for text.

    float getSizeW() const { return shape.getSize().x; } // Getter for shape.x.
    void setSize(float _oSW, float _oSH) { shape.setSize(Vector2f(_oSW, _oSH)); } // Setter for overlay size.
};
