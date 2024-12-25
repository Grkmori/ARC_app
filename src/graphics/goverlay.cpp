
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/goverlay.hpp"
#include "graphics/gsettings.hpp"

using namespace sf;


/* COSTRUCTOR (AND DESTRUCTOR) */
GOverlay::GOverlay() { /* cout << "Overlay constructor created" << ".\n"; */ }

GOverlay::~GOverlay() { /* cout << "Overlay destructor called" << ".\n"; */ }


/* FUNCTIONS - UTILITIES.CONSTRUCTOR */
/* Update Overlay values */
void GOverlay::update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY) {
    // Shape //
    shape.setSize(Vector2f(_oW, _oH));
    shape.setPosition(_oPosX, _oPosY);
    shape.setFillColor(OVERLAYBGCOLOR);
    shape.setOutlineThickness(OVERLAYOUTLINETHICKNESS);
    shape.setOutlineColor(OVERLAYOUTLINECOLOR);
}

/* Update Overlay and title values */
void GOverlay::update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY, const string& _msg) {
    // Shape //
    shape.setSize(Vector2f(_oW, _oH));
    shape.setPosition(_oPosX, _oPosY);
    shape.setFillColor(OVERLAYTIBGCOLOR);
    shape.setOutlineThickness(OVERLAYTIOUTLINETHICKNESS);
    shape.setOutlineColor(OVERLAYTIOUTLINECOLOR);

    // Text //
    text.setFont(tiFont);
    text.setString(_msg);
    text.setCharacterSize(tiFontSize);
    text.setFillColor(TEXTCOLOR);

    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    text.setPosition(round(shape.getPosition().x + (shape.getSize().x/2.f)), round(shape.getPosition().y + (shape.getSize().y/2.f) + 2.f));
}

/* Update Overlay and title values (+rotation) */
void GOverlay::update(const float& _oW, const float& _oH, const float& _oPosX, const float& _oPosY, const string& _msg, const float& _msgR) {
    // Shape //
    shape.setSize(Vector2f(_oW, _oH));
    shape.setPosition(_oPosX, _oPosY);
    shape.setFillColor(OVERLAYTIBGCOLOR);
    shape.setOutlineThickness(OVERLAYTIOUTLINETHICKNESS);
    shape.setOutlineColor(OVERLAYTIOUTLINECOLOR);

    // Text //
    text.setFont(tiFont);
    text.setString(_msg);
    text.setCharacterSize(tiFontSize);
    text.setRotation(_msgR);
    text.setFillColor(TEXTCOLOR);

    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + (textBounds.width/2.f), textBounds.top + (textBounds.height/2.f));
    text.setPosition(round(shape.getPosition().x + (shape.getSize().x/2.f) + 2.f), round(shape.getPosition().y + (shape.getSize().y/2.f)));
}
