
#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "graphics/gtext.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTORS (AND DESTRUCTOR) */
GText::GText() { /* cout << "InputBox constructor created" << ".\n"; */ }

GText::~GText() { /* cout << "Text destructor called" << ".\n"; */ }


/* FUNCTIONS - UTILITIES.CONSTRUCTOR */
/* Update Text values */
void GText::update(const string& _msg, const float& _msgPosX, const float& _msgPosY) {
    // Text //
    text.setFont(bdFont);
    text.setString(_msg);
    text.setCharacterSize(bdFontSize);
    text.setPosition(_msgPosX, _msgPosY);
    text.setFillColor(TEXTCOLOR);
}

/* Update Text values (+ color) */
void GText::update(string _msg, const float& _msgPosX, const float& _msgPosY, const Color _fC) {
    // Text //
    text.setFont(msgFont);
    text.setString(_msg);
    text.setCharacterSize(msgFontSize);
    text.setPosition(_msgPosX, _msgPosY);
    text.setFillColor(_fC);
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update stringStream for textTaskName. */
void GText::updateStringMsg(string _msg, int _tFIdx, int _tFS) { 
    stringMsg = MSGTASKNAME + "  " + _msg + "  #" + to_string(_tFIdx+1) + " of #" + to_string(_tFS);
    
    text.setString(stringMsg);
} 

/* Update stringStream for textTaskOutputPair. */
void GText::updateStringMsg(int& _tPIdx, int _tPS) { 
    stringMsg = MSGTASKOUTPUTPAIR + "  " + to_string(_tPIdx+1) + "/" + to_string(_tPS);
    
    text.setString(stringMsg);
} 
