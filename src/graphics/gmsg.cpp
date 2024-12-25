
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/gmsg.hpp"
#include "graphics/gsettings.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GMessage::GMessage() { }

GMessage::~GMessage() { }


/* FUNCTION - UTILITIES.CONSTRUCTOR */
/* Update GMessage values */
void GMessage::update(string _msg, const float& _msgPosY, const Color _fC) {
    // Text //
    text.setFont(msgFont);
    text.setString(_msg);
    text.setCharacterSize(msgFontSize);
    text.setFillColor(_fC);

    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + (bounds.width/2.f), bounds.top + (bounds.height/2.f));
    text.setPosition(round(overlayPosX + (overlayW/2.f)), _msgPosY);

    // Others //
    overlayPosX = OVERLAYTOOLSPOSX;
    overlayW = OVERLAYTOOLSW;
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update string for Info */
void GMessage::updateStringInfo(string _msg) { 
    text.setString(_msg);
    text.setFillColor(MSGINFOCOLOR);
    
    isDisplayed = true;
    timer.restart();

    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + (bounds.width/2.f), bounds.top + (bounds.height/2.f));
    text.setPosition(round(overlayPosX + (overlayW/2.f)), text.getPosition().y);
} 

/* Update string for Success */
void GMessage::updateStringSuccess(string _msg) {  
    text.setString(_msg);
    text.setFillColor(MSGSUCCESSCOLOR);

    isDisplayed = true;
    timer.restart();

    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + (bounds.width/2.f), bounds.top + (bounds.height/2.f));
    text.setPosition(round(overlayPosX + (overlayW/2.f)), text.getPosition().y);
} 

/* Update string for Error */
void GMessage::updateStringError(string _msg) { 
    text.setString(_msg);
    text.setFillColor(MSGERRORCOLOR);

    isDisplayed = true;
    timer.restart();

    FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + (bounds.width/2.f), bounds.top + (bounds.height/2.f));
    text.setPosition(round(overlayPosX + (overlayW/2.f)), text.getPosition().y);
}

/* Reset values of string after timer duration */
void GMessage::resetString() {
    text.setString("");
    text.setFillColor(MSGINFOCOLOR);

    isDisplayed = false;
}
