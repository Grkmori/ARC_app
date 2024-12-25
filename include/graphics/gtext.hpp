
#pragma once

using namespace std;
using namespace sf;

class GText {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    Text text;
    string stringMsg;


public:    
    /* COSTRUCTORS (AND DESTRUCTOR) */
    GText();
    ~GText();


    /* FUNCTIONS - UTILITIES.CONSTRUCTOR */
    void update(const string& _msg, const float& _msgPosX, const float& _msgPosY);
    void update(string _msg, const float& _msgPosX, const float& _msgPosY, const Color _fC);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateStringMsg(string _msg, int _tFIdx, int _tFS);
    void updateStringMsg(int& _tPIdx, int _tPS);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    Text getText() const { return text; } // Getter for text.
};
