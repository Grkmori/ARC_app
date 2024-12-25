
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "graphics.hpp"
#include "settings.hpp"
#include "graphics/gsettings.hpp"
#include "graphics/goverlay.hpp"
#include "graphics/gtext.hpp"
#include "graphics/gmsg.hpp"
#include "graphics/gbutton.hpp"
#include "graphics/gchecker.hpp"
#include "graphics/ginputbox.hpp"
#include "graphics/gscrollbar.hpp"
#include "grid.hpp"
#include "picker.hpp"

using namespace std;
using namespace sf;


/* COSTRUCTORS (AND DESTRUCTOR) */
Graphics::Graphics() { cout << "\033[1;46mLoaded Graphics constructor.\033[0m" << endl; }

Graphics::~Graphics() { cout << "\033[1;46mGraphics destructor called.\033[0m" << endl; }


/* FUNCTION - INITIALIZATION */
/* Initialize graphics resources */
void Graphics::initialize() {
    cout << "\033[1;46mInitializing Graphics...\033[0m" << endl;

    // Fonts //
    try {
        if (!tiFont.loadFromFile(TIFONTPATH)) {
            throw runtime_error("Failed to load UI tiFont.");
        }
        if (!bdFont.loadFromFile(BDFONTPATH)) {
            throw runtime_error("Failed to load UI bdFont.");
        }
        if (!msgFont.loadFromFile(MSGFONTPATH)) {
            throw runtime_error("Failed to load UI msgFont.");
        }
        if (!btFont.loadFromFile(BTFONTPATH)) {
            throw runtime_error("Failed to load UI btFont.");
        }
        if (!cFont.loadFromFile(CFONTPATH)) {
            throw runtime_error("Failed to load UI cFont.");
        }
        const_cast<Texture&>(btFont.getTexture(btFontSize)).setSmooth(false);
    } catch(const exception& e) {
        cerr << "\033[1;41mFailed to load UI font: \033[0m" << e.what() << endl;
    }

    // Texture //
    try {
        if (!selCellTexture.loadFromFile(SELCELLTEXPATH)) {
            throw runtime_error("Failed to load selCellTex.");
        }
    } catch(const exception& e) {
        cerr << "\033[1;41mFailed to load texture: \033[0m" << e.what() << endl;
    }

    // Sprite //
    selCellSprite.setTexture(selCellTexture);

    // Overlay Example //
    overlayTrain.update(OVERLAYTRAININITW, OVERLAYTRAINH, OVERLAYTRAINPOSX, OVERLAYTRAINPOSY);
    overlayTrainTi.update(OVERLAYTRAINTIW, OVERLAYTRAINTIH, OVERLAYTRAINTIPOSX, OVERLAYTRAINTIPOSY, MSGTRAINTI, OVERLAYTIROTATION);
    
    // Overlay Test and Tools //
    overlayTestInput.update(OVERLAYTESTINPUTW, OVERLAYTESTINPUTH, OVERLAYTESTINPUTPOSX, OVERLAYTESTINPUTPOSY);
    overlayTestInputTi.update(OVERLAYTESTINPUTTIW, OVERLAYTESTINPUTTIH, OVERLAYTESTINPUTTIPOSX, OVERLAYTESTINPUTTIPOSY, MSGTESTINPUTTI, OVERLAYTIROTATION);
    overlayTools.update(OVERLAYTOOLSW, OVERLAYTOOLSH, OVERLAYTOOLSPOSX, OVERLAYTOOLSPOSY);
    overlayToolsTi.update(OVERLAYTOOLSTIW, OVERLAYTOOLSTIH, OVERLAYTOOLSTIPOSX, OVERLAYTOOLSTIPOSY, MSGTOOLSTI);
    overlayTestOutput.update(OVERLAYTESTOUTPUTW, OVERLAYTESTOUTPUTH, OVERLAYTESTOUTPUTPOSX, OVERLAYTESTOUTPUTPOSY);
    overlayTestOutputTi.update(OVERLAYTESTOUTPUTTIW, OVERLAYTESTOUTPUTTIH, OVERLAYTESTOUTPUTTIPOSX, OVERLAYTESTOUTPUTTIPOSY, MSGTESTOUTPUTTI, OVERLAYTIROTATION);

    // Texts Body //
    textsBodyVector.reserve(7);
    for (int i = 0; i < 7; ++i) {
        textsBodyVector.emplace_back();
    }
    textsBodyVector[0].update(MSGLOADTASK, MSGLOADTASKPOSX, MSGLOADTASKPOSY);
    textsBodyVector[1].update(MSGTASKNAME, MSGTASKNAMEPOSX, MSGTASKNAMEPOSY);
    textsBodyVector[2].update(MSGTASKOUTPUTPAIR, MSGTASKOUTPUTPAIRPOSX, MSGTASKOUTPUTPAIRPOSY);
    textsBodyVector[3].update(MSGSHOWCELLNUMBER, MSGSHOWCELLNUMBERPOSX, MSGSHOWCELLNUMBERPOSY);
    textsBodyVector[4].update(MSGCHANGEGRIDSIZE, MSGCHANGEGRIDSIZEPOSX, MSGCHANGEGRIDSIZEPOSY);
    textsBodyVector[5].update(MSGOTHERCOMMANDS, MSGOTHERCOMMANDSPOSX, MSGOTHERCOMMANDSPOSY);
    textsBodyVector[6].update(MSGCELLPICKER, MSGCELLPICKERPOSX, MSGCELLPICKERPOSY);

    // Messages //
    messageDisplay.update("MSGBASIC", MSGPOSY, MSGINFOCOLOR);

    // Buttons //
    btnsVector.reserve(13);
    for (int i = 0; i < 13; ++i) {
        btnsVector.emplace_back();
    }
    btnsVector[0].update(BUTTONRANDOMW, BUTTONRANDOMH, BUTTONRANDOMPOSX, BUTTONRANDOMPOSY, BUTTONRANDOMMSG);
    btnsVector[1].update(BUTTONOPENW, BUTTONOPENH, BUTTONOPENPOSX, BUTTONOPENPOSY, BUTTONOPENMSG);
    btnsVector[2].update(BUTTONNEXTTASKW, BUTTONNEXTTASKH, BUTTONNEXTTASKPOSX, BUTTONNEXTTASKPOSY, BUTTONNEXTTASKMSG);
    btnsVector[3].update(BUTTONBACKTESTPAIRW, BUTTONBACKTESTPAIRH, BUTTONBACKTESTPAIRPOSX, BUTTONBACKTESTPAIRPOSY, BUTTONBACKTESTPAIRMSG);
    btnsVector[4].update(BUTTONNEXTTESTPAIRW, BUTTONNEXTTESTPAIRH, BUTTONNEXTTESTPAIRPOSX, BUTTONNEXTTESTPAIRPOSY, BUTTONNEXTTESTPAIRMSG);
    btnsVector[5].update(BUTTONRESIZEEDITGRIDW, BUTTONRESIZEEDITGRIDH, BUTTONRESIZEEDITGRIDPOSX, BUTTONRESIZEEDITGRIDPOSY, BUTTONRESIZEEDITGRIDMSG);
    btnsVector[6].update(BUTTONRESETEDITGRIDW, BUTTONRESETEDITGRIDH, BUTTONRESETEDITGRIDPOSX, BUTTONRESETEDITGRIDPOSY, BUTTONRESETEDITGRIDMSG);
    btnsVector[7].update(BUTTONCOPYINPUTW, BUTTONCOPYINPUTH, BUTTONCOPYINPUTPOSX, BUTTONCOPYINPUTPOSY, BUTTONCOPYINPUTMSG);
    btnsVector[8].update(BUTTONCOPYOUTPUTW, BUTTONCOPYOUTPUTH, BUTTONCOPYOUTPUTPOSX, BUTTONCOPYOUTPUTPOSY, BUTTONCOPYOUTPUTMSG);
    btnsVector[9].update(BUTTONCOPYSELW, BUTTONCOPYSELH, BUTTONCOPYSELPOSX, BUTTONCOPYSELPOSY, BUTTONCOPYSELMSG);
    btnsVector[10].update(BUTTONPASTESELW, BUTTONPASTESELH, BUTTONPASTESELPOSX, BUTTONPASTESELPOSY, BUTTONPASTESELMSG);
    btnsVector[11].update(BUTTONFLOODFILLW, BUTTONFLOODFILLH, BUTTONFLOODFILLPOSX, BUTTONFLOODFILLPOSY, BUTTONFLOODFILLMSG);
    btnsVector[12].update(BUTTONSUBMITW, BUTTONSUBMITH, BUTTONSUBMITPOSX, BUTTONSUBMITPOSY, BUTTONSUBMITMSG, BUTTONSUBMITCOLOR);

    // Checkers //
    checkersVector.reserve(2);
    for (int i = 0; i < 2; ++i) {
        checkersVector.emplace_back();
    }
    checkersVector[0].update(CHECKERCELLNS, CHECKERCELLNPOSX, CHECKERCELLNPOSY);
    checkersVector[1].update(CHECKERPICKERS, CHECKERPICKERPOSX, CHECKERPICKERPOSY);
    drawCellNumbers = false;

    // Input Box //
    inputBoxResize.update(INPUTBOXW, INPUTBOXH, INPUTBOXPOSX, INPUTBOXPOSY, INPUTBOXDISPLAY);

    // Scroll Bar //
    scrollBar.update(SCROLLBARBGW, SCROLLBARW, SCROLLBARH);
    contentWidth = 0.f;
}


/* FUNCTIONS - RUNTIME */
/* Runtime draw graphic elements to window */
void Graphics::drawGraphicsToWindow(RenderWindow& _window, View& _view, bool& _sbO) {
    // Overlay Example //
    _window.draw(overlayTrain.getShape());
    _window.draw(overlayTrainTi.getShape());
    _window.draw(overlayTrainTi.getText());

    // Overlay Test and Tools //
    _window.draw(overlayTestInput.getShape());
    _window.draw(overlayTestInputTi.getShape());
    _window.draw(overlayTestInputTi.getText());
    _window.draw(overlayTools.getShape());
    _window.draw(overlayToolsTi.getShape());
    _window.draw(overlayToolsTi.getText());
    _window.draw(overlayTestOutput.getShape());
    _window.draw(overlayTestOutputTi.getShape());
    _window.draw(overlayTestOutputTi.getText());

    // Texts Body //
    for (unsigned i = 0; i < textsBodyVector.size(); ++i) {
        _window.draw(textsBodyVector[i].getText());
    }

    // Messages//
    _window.draw(messageDisplay.getText());

    // Buttons //
    for (unsigned i = 0; i < btnsVector.size(); ++i) {
        _window.draw(btnsVector[i].getShape());
        _window.draw(btnsVector[i].getText());
    }

    // Checkers //
    for (unsigned i = 0; i < checkersVector.size(); ++i) {
        _window.draw(checkersVector[i].getShape());
        if (checkersVector[i].getIsChecked()) {
            _window.draw(checkersVector[i].getCheckMark());
        }
    }

    // Input Box //
    _window.draw(inputBoxResize.getShape());
    _window.draw(inputBoxResize.getText());

    // Scroll Bar //
    _window.setView(_window.getDefaultView()); // Reset to default view (this ensures drawing is not affected by current view transformation)
    _window.draw(scrollBar.getBGShape());
    if (_sbO) {
        _window.draw(scrollBar.getShape());
    }
    _window.setView(_view);  // Restore the original view
}

/* Runtime draw train and test Grids to window */
void Graphics::drawGridsToWindow(RenderWindow& _window, vector<Grid>& _tIGV, vector<Grid>& _tOGV, Grid& _tIG, Grid& _tOG, Grid& _tEG, Picker& _cP, bool& _iDSB) {

    // Train //
    for (unsigned i = 0; i < _tIGV.size(); ++i) {
        _tIGV[i].draw(_window, drawCellNumbers);
        _tOGV[i].draw(_window, drawCellNumbers);
    }

    // Test //
    _tIG.draw(_window, drawCellNumbers);
    _tOG.draw(_window, drawCellNumbers);
    _tEG.draw(_window, drawCellNumbers);

    // Cell Picker //
    _cP.draw(_window, drawCellNumbers, _iDSB);
}

/* Runtime checks if isClicked is true in one of the Buttons/ScrollBar */
bool Graphics::checkForTimers() {
    if (scrollBar.getIsClicked()) {
        if (scrollBar.getTimer().getElapsedTime().asSeconds() > CLICKSCROLLBARDURATION) {
            scrollBar.restoreAfterTimer();
        } 
        
        return true;
    }

    if (isInputBoxActive) {
        if (inputBoxResize.getCursorTimer().getElapsedTime().asSeconds() > INPUTBOXCURSORDURATION) {
            inputBoxResize.updateCursor();
        }

        return true;
    } else if (!isInputBoxActive && inputBoxResize.getIsCursorVisible()) {
        inputBoxResize.updateCursor();
    } else if (!isInputBoxActive && inputBoxResize.getTimer().getElapsedTime().asSeconds() > CLICKINPUTBOXDURATION) {
        inputBoxResize.restoreAfterTimer();
    }

    for (unsigned i = 0; i < btnsVector.size(); ++i) {
        if (btnsVector[i].getIsClicked()) {
            if (btnsVector[i].getTimer().getElapsedTime().asSeconds() > CLICKBUTTONDURATION) {
                if (i == 12) {
                    btnsVector[i].restoreAfterTimer(BUTTONSUBMITCOLOR);
                } else {
                    btnsVector[i].restoreAfterTimer();
                }
            } 
            
            return true;
        }
    }

    return false;
}

/* Runtime checks if isDisplayed is true */
bool Graphics::checkForMsgIsDisplayed() {
    if (messageDisplay.getIsDisplayed()) {
        if (messageDisplay.getTimer().getElapsedTime().asSeconds() > MSGDURATION) {
            messageDisplay.resetString();
        }
        
        return true;
    } 
    
    return false;
}


/* FUNCTIONS - UTILITIES.INTERFACE */
/* Check if mouse click is inside Button bounds, and update values */
bool Graphics::checkForButtonBound(Vector2f& _mPos, int _btnsVIdx, float& _sOs) {
    if (btnsVector[_btnsVIdx].isInBounds(_mPos, _sOs)) {
        if (_btnsVIdx == 12) {
            btnsVector[_btnsVIdx].updateIfClicked(BUTTONSUBMITCOLORPRESSED);
        } else {
            btnsVector[_btnsVIdx].updateIfClicked();
        }

        return true;
    }

    return false;
}

/* Check if mouse click in inside Checker bounds, and update values */
bool Graphics::checkForCheckerBound(Vector2f& _mPos, int _btnsVIdx, float& _sOs, bool _b) {
    if (checkersVector[_btnsVIdx].isInBounds(_mPos, _sOs)) {
        if (!_b) {
            checkersVector[_btnsVIdx].updateIfClicked();
        } else if (_b) {
            checkersVector[_btnsVIdx].restoreIfClicked();
        }

        return true;
    } 
    
    return false;
}

/* Check if mouse click in inside InputBox bounds, and update values */
bool Graphics::checkForInputBoxBound(Vector2f& _mPos, float& _sOs) {
    if (inputBoxResize.isInBounds(_mPos, _sOs)) {
        inputBoxResize.updateIfClicked();
        isInputBoxActive = true;

        return true;
    } else if (isInputBoxActive && !inputBoxResize.isInBounds(_mPos, _sOs)) {
        inputBoxResize.resetTimer();
        isInputBoxActive = false;

        return false;
    }
    
    return false;
}

/* Check if mouse click in inside ScrollBar bounds, and update values */
bool Graphics::checkForScrollBarBound(Vector2f& _mPos) {
    if (scrollBar.isInBounds(_mPos)) {
        scrollBar.updateIfClicked(_mPos);

        return true;
    } 
    
    return false;
}

/* Update if mouse is released from Button/ScrollBar bounds, and update values */
void Graphics::updateMouseIsReleased(bool& _iD) {
    for (unsigned i = 0; i < btnsVector.size(); ++i) {
        btnsVector[i].updateIfReleased();
    }

    if (_iD) {
        scrollBar.updateIfReleased();
    }
}

/* Edit keyboard inputs of the InputBox */
void Graphics::editInputBoxText(Event& _event) {
    if (_event.key.code == Keyboard::Enter) {
        inputBoxResize.restoreAfterTimer();
        isInputBoxActive = false;
    }
    
    inputBoxResize.updateTextInput(_event);
}

/* Update ScrollBar while mouse is dragging */
float Graphics::updatedScrollBarMouseDragging(Window& _window, Event& _event) {
    float tempOffsetX = scrollBar.updateWhileDragging(_window, _event , contentWidth);

    return tempOffsetX;
}

/* Update ScrollBar dragging from keyboard inputs */
void Graphics::updateScrollBarFromKeyboard(Event::KeyEvent& _key, float& _sOs) {
    if (_key.code == Keyboard::Right) {
        scrollBar.updateFromKeyboard(_sOs, contentWidth);
    } else if (_key.code == Keyboard::Left) {
        scrollBar.updateFromKeyboard(_sOs, contentWidth);
    }
}


/* FUNCTIONS - UTILITIES.RENDERING */
/* Update new task graphics values */
void Graphics::updateNewTaskGraphics(vector<Grid>& _tIGV, vector<Grid>& _tOGV, Grid& _tIG, Grid& _tOG, Grid& _tEG, string _msg, int _tFIdx, int _tFS, int& _tPIdx, int _tPS, Picker& _cP) {
    cout << "Updated graphics for new task" << ".\n";

    // Rendering Grids //
    float trainVertorS = static_cast<float>(_tIGV.size());
    for (int i = 0; i < trainVertorS; ++i) {
        _tIGV[i].renderTrainGrid(i, GRIDTRAININPUTINITPOSX, GRIDTRAININPUTADDOFFSETX, GRIDTRAININPUTINITPOSY);
        _tOGV[i].renderTrainGrid(i, GRIDTRAINOUTPUTINITPOSX, GRIDTRAINOUTPUTADDOFFSETX, GRIDTRAINOUTPUTINITPOSY);
    }
    _tIG.renderTestGrid(GRIDTESTINPUTINITPOSX, GRIDTESTINPUTINITPOSY);
    _tOG.renderTestGrid(GRIDTESTOUTPUTINITPOSX, GRIDTESTOUTPUTINITPOSY);
    _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);

    // Updating Values //
    overlayTrain.setSize((OVERLAYTRAINW*trainVertorS) + OVERLAYTRAINTIW + TIMARGINADJUST, OVERLAYTRAINH);
    textsBodyVector[1].updateStringMsg(_msg, _tFIdx, _tFS);
    textsBodyVector[2].updateStringMsg(_tPIdx, _tPS);
    _cP.render(BOXPICKERPOSX, BOXPICKERPOSY);

    contentWidth = (MARGINS*2) + overlayTrain.getSizeW();
    scrollBar.reset(contentWidth);
}

/* Update next pairs graphics values */
void Graphics::updateNextTestPairGraphics(Grid& _tIG, Grid& _tOG, Grid& _tEG, int& _tPIdx, int _tPS, Picker& _cP) {
    cout << "Updated graphics for next test pair" << ".\n";

    // Rendering Grids //
    _tIG.renderTestGrid(GRIDTESTINPUTINITPOSX, GRIDTESTINPUTINITPOSY);
    _tOG.renderTestGrid(GRIDTESTOUTPUTINITPOSX, GRIDTESTOUTPUTINITPOSY);
    _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);

    // Updating Values //
    textsBodyVector[2].updateStringMsg(_tPIdx, _tPS);
    _cP.render(BOXPICKERPOSX, BOXPICKERPOSY);

    inputBoxResize.reset();
    isInputBoxActive = false;
}

/* Reset graphic elements for new task */
void Graphics::resetGraphicsElements(float& _offset) {
    for(unsigned i = 0; i < btnsVector.size(); ++i) {
        btnsVector[i].updateBounds();
    }
    for (unsigned i = 0; i < checkersVector.size(); ++i) {
        checkersVector[i].updateBounds();
    }
    inputBoxResize.updateBounds();
    inputBoxResize.reset(); 
    isInputBoxActive = false;
}

/* Display messages to the screen on demand */
void Graphics::displayMessage(int _ie, string _msg) {
    if (_ie == 0) { // Info.
        messageDisplay.updateStringInfo(_msg);
    } else if (_ie == 1) { // Success.
        messageDisplay.updateStringSuccess(_msg);
    } else if (_ie == 2) { // Error.
        messageDisplay.updateStringError(_msg);
    }
}


/* FUNCTIONS - UTILITIES.SUPPORT */
/* Checks if Application needs a scroll bar based on contents width */
bool Graphics::needsForScroolBar() {
    unsigned mayWidth = static_cast<unsigned>(floor(max(contentWidth, 
        (MARGINS*2) + overlayTestInput.getSizeW() +  overlayTools.getSizeW() + overlayTestOutput.getSizeW())));
    if (mayWidth > WINDOWW) {
        return true;
    }
    
    return false;
}

/* Get edit Grid resize string to be parsed and update edit Grid */
void Graphics::resizeEditGridFromInput(Grid& _tEG) {
    pair<int, int> resizeEditGrid = parseSizePair(inputBoxResize.getTextInput(), _tEG.getMatrixW(), _tEG.getMatrixH());
    if (resizeEditGrid.first == _tEG.getMatrixW() && resizeEditGrid.second == _tEG.getMatrixH()) {
        // (...)
    } else {
        _tEG.resizeEditGrid(resizeEditGrid.first, resizeEditGrid.second);
        _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);
        displayMessage(1, "Successfully resized Edit Grid.");
    }
}

/* Reset edit Grid to initial values */
void Graphics::resetEditGrid(Grid& _tEG) {
    _tEG.resizeEditGrid();
    _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);
    inputBoxResize.reset();
    displayMessage(1, "Successfully reset Edit Grid.");
}

/* Copy values from test input Grid to the edit Grid */
void Graphics::copyTestInputGridToEditGrid(Grid& _tEG, Grid& _tIG) {
    _tEG.copyGridToGrid(_tIG);
    _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);
    displayMessage(1, "Successfully copied Test Input Grid.");
}

/* Copy values from test output Grid to the edit Grid */
void Graphics::copyTestOutputGridToEditGrid(Grid& _tEG, Grid& _tOG) {
    _tEG.copyGridToGrid(_tOG);
    _tEG.renderTestGrid(GRIDTESTEDITINITPOSX, GRIDTESTEDITINITPOSY);
    displayMessage(1, "Successfully copied Test Output Grid.");
}

/* (could be private) Process a Grid size string, validate its format and range, and return the size as an array if it meets all criteria */
pair<int, int> Graphics::parseSizePair(string _sGS, int _gW, int _gH) {  
    pair<int, int> newGridSize(_gW, _gH);

    try { 
        stringstream ss(_sGS);
        int pairFirst, pairSecond;
        char delimiter;

        if (!(ss >> pairFirst >> delimiter >> pairSecond) || delimiter != 'x') { // Read the width, delimiter, and height from the string.
            displayMessage(2, "Invalid format. Expected 'WxH' format.");
            throw invalid_argument("Invalid format. Expected 'WxH' format.");
        }

        if (pairFirst < 1 || pairSecond < 1) { // Validate parsed dimensions.
            displayMessage(2, "Grid size should be at least 1x1. Cannot have a grid with no cells.");
            throw out_of_range("Grid size should be at least 1x1. Cannot have a grid with no cells.");
        }
        if (pairFirst > MAXGRIDSIZE || pairSecond > MAXGRIDSIZE) { // Validate parsed dimensions.
            displayMessage(2, "Grid size should be at most 30x30. Pick a smaller size.");
            throw out_of_range("Grid size should be at most 30x30. Pick a smaller size.");
        }

        newGridSize.first = pairFirst;
        newGridSize.second = pairSecond;
    } catch (const invalid_argument& e) { // Conversion failed for one of the strings.
        displayMessage(2, "Invalid argument error: " + string(e.what()));
        cerr << "\033[1;41mInvalid argument error: \033[0m" << e.what() << endl;
    } catch (const out_of_range& e) { // Conversion failed due to number being out of integer range.
        displayMessage(2, "Out of range error: " + string(e.what()));
        cerr << "\033[1;41mOut of range error: \033[0m" << e.what() << endl;
    }

    return newGridSize;
}
