
#pragma once

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


class Graphics {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Overlays Example //
    GOverlay overlayTrain;
    GOverlay overlayTrainTi;
    
    // Overlays Test and Tools //
    GOverlay overlayTestInput;
    GOverlay overlayTestInputTi;
    GOverlay overlayTools;
    GOverlay overlayToolsTi;
    GOverlay overlayTestOutput;
    GOverlay overlayTestOutputTi;

    // Container for Texts Body // Buttons created by emplace_back inside textsBodyVector.
    vector<GText> textsBodyVector;
    //GText textLoadTask; // or textsBodyVector[0]
    //GText textTaskName; // or textsBodyVector[1]
    //GText textTaskOutputPair; // or textsBodyVector[2]
    //GText textChangeGridSize; // or textsBodyVector[3]
    //GText textShowColorNumber; // or textsBodyVector[4]
    //GText textOtherCommands; // or textsBodyVector[5]
    //GText textCellPicker; // or textsBodyVector[6]

    // Messages //
    GMessage messageDisplay;

    // Container for Buttons // Buttons created by emplace_back inside btnsVector.
    vector<GButton> btnsVector;
    //GButton buttonRandomTask; // or btnsVector[0]
    //GButton buttonOpenTask; // or btnsVector[1]
    //GButton buttonNextTask; // or btnsVector[2]
    //GButton buttonBackTestPair; // or btnsVector[3]
    //GButton buttonNextTestPair; // or btnsVector[4]
    //GButton buttonResizeEditGrid; // or btnsVector[5]
    //GButton buttonResetEditGrid; // or btnsVector[6]
    //GButton buttonCopyFromInput; // or btnsVector[7]
    //GButton buttonCopyFromOutput; // or btnsVector[8]
    //GButton buttonCopySel; // or btnsVector[9]
    //GButton buttonPasteSel; // or btnsVector[10]
    //GButton buttonFloodFill; // or btnsVector[11]
    //GButton buttonSubmit; // or btnsVector[12]
    
    // Container for Checkers // Checkers created by emplace_back inside checkersVector.
    vector<GChecker> checkersVector;
    //GChecker checkerCellN; // or checkersVector[0]
    //GChecker checkerPicker; // or checkersVector[1]
    bool drawCellNumbers;

    // Input Box // 
    GInputBox inputBoxResize;

    // Scroll Bar //
    GScrollBar scrollBar;
    float contentWidth;


public:
    /* COSTRUCTORS (AND DESTRUCTOR) */
    Graphics();
    ~Graphics();


    /* FUNCTION - INITIALIZATION */
    void initialize();


    /* FUNCTIONS - RUNTIME */
    void drawGraphicsToWindow(RenderWindow& _window, View& _view, bool& _sbO);
    void drawGridsToWindow(RenderWindow& _window, vector<Grid>& _tIGV, vector<Grid>& _tOGV, Grid& _tIG, Grid& _tOG, Grid& _tEG, Picker& _cP, bool& _iDSB);
    bool checkForTimers();
    bool checkForMsgIsDisplayed();


    /* FUNCTIONS - UTILITIES.INTERFACE */
    bool checkForButtonBound(Vector2f& _mPos, int _btnsVIdx, float& _sOs);
    bool checkForCheckerBound(Vector2f& _mPos, int _btnsVIdx, float& _sOs, bool _b);
    bool checkForInputBoxBound(Vector2f& _mPos, float& _sOs);
    bool checkForScrollBarBound(Vector2f& _mPos);
    void updateMouseIsReleased(bool& _iD);
    void editInputBoxText(Event& _key);
    float updatedScrollBarMouseDragging(Window& _window, Event& _event);
    void updateScrollBarFromKeyboard(Event::KeyEvent& _key, float& _sOs);


    /* FUNCTIONS - UTILITIES.RENDERING */
    void updateNewTaskGraphics(vector<Grid>& _tIGV, vector<Grid>& _tOGV, Grid& _tIG, Grid& _tOG, Grid& _tEG, string _msg, int _tFIdx, int _tFS, int& _tPIdx, int _tPS, Picker& _cP);
    void updateNextTestPairGraphics(Grid& _tIG, Grid& _tOG, Grid& _tEG, int& _tPIdx, int _tPS, Picker& _cP);
    void displayMessage(int _ie, string _msg);
    void resetGraphicsElements(float& _offset);


    /* FUNCTIONS - UTILITIES.SUPPORT */
    bool needsForScroolBar();
    void resizeEditGridFromInput(Grid& _tEG);
    void resetEditGrid(Grid& _tEG);
    void copyTestInputGridToEditGrid(Grid& _tEG, Grid& _tIG);
    void copyTestOutputGridToEditGrid(Grid& _tEG, Grid& _tOG);
    pair<int, int> parseSizePair(string _sGS, int _gW, int _gH);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    RenderWindow& getWindow(); // Getter for window.

    vector<GButton> getVectorButtons() { return btnsVector; } // Getter for the vector btnsVector.

    float getContentWidth() const { return contentWidth; } // Getter for contentWidth.

    bool getDrawCellNumbers() const { return drawCellNumbers; } // Getter for drawCellNumbers.
    void setDrawCellNumbers() { drawCellNumbers = !drawCellNumbers; } // Setter for drawCellNumbers.
};
