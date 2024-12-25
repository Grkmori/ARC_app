
#pragma once

#include "loader.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "picker.hpp"

using namespace sf;
using json = nlohmann::json;


class Application {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    ContextSettings settings;
    RenderWindow window;
    TaskLoader taskLoader;
    Graphics graphics;
    
    // Runtime Parameters //
    fs::path selectedTaskPath;
    pair<json, json> taskPairsJson;

    vector<Grid> trainInputGrids;
    vector<Grid> trainOutputGrids;
    vector<Grid> testInputGrids;
    vector<Grid> testOutputGrids;
    int testPairsGridIdx;
    int testPairsGridSize;
    Grid testEditGrid;

    Picker cellPicker;

    // Runtime Interface //
    View view;
    Vector2f viewCenterPoint;

    bool scrollBarOn;
    float scrollOffset;

    bool anyTimerOn;
    bool isDragging;
    bool isDraggingScrollBar;


    /* FUNCTION - INITIALIZATION */
    void initialize();

    /* FUNCTIONS - UTILITIES.SUPPORT */
    void resetTask();
    void loadTask(string _string);
    void openTask();
    void newTask();
    void loadTaskPairs(pair<json, json>& _pair);
    void updatedTestPair();


    /* FUNCTIONS - UTILITIES.INTERFACE */
    void handleIfMouseClick(Event& _event);
    void handleIfRightMouseClick(Event& _event);
    void handleIfMouseIsReleased(Event& _event);
    void handleIfMouseIsDragging(Event& _event);
    void handleKeyboardInputs(Event& _event);
    void clearSelection();
    void copyMouseSelection();
    void pasteMouseSelection();
    void submitEditGrid(Grid& _gEdit, Grid& _gTO);
    

public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    Application(const unsigned& _wW, const unsigned& _wH, const string& _appName);
    ~Application(); 


    /* FUNCTIONS - RUNTIME */
    void runMain();
};
