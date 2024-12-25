
#pragma once

using namespace std;
using namespace sf;

class GMessage {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    Text text;

    // Parameters //
    Clock timer;
    bool isDisplayed;

    float overlayPosX;
    float overlayW;


public:    
    /* COSTRUCTOR (AND DESTRUCTOR) */
    GMessage();
    ~GMessage();


    /* FUNCTION - UTILITIES.CONSTRUCTOR */
    void update(string _msg, const float& _msgPosY, const Color _fC);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateStringInfo(string _msg);
    void updateStringSuccess(string _msg);
    void updateStringError(string _msg);
    void resetString();


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    Text getText() const { return text; } // Getter for text.

    Clock getTimer() const { return timer; } // Getter for timer.

    bool getIsDisplayed() const { return isDisplayed; } // Getter for isDisplayed.
};
