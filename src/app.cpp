
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "app.hpp"
#include "settings.hpp"
#include "loader.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "picker.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;


/* COSTRUCTOR (AND DESTRUCTOR) */
Application::Application(const unsigned& _wW, const unsigned& _wH, const string& _appName) 
    : window(VideoMode(_wW, _wH), _appName) 
    , testEditGrid(EDITGRIDINITIALSIZE, EDITGRIDINITIALSIZE) { 
    cout << "\033[1;46mLoaded Application constructor.\033[0m" << endl;

    settings.antialiasingLevel = 0;
    window.setPosition(Vector2i(WINDOWPOSX, WINDOWPOSY));
    window.setFramerateLimit(FPS);
    //window.setMouseCursorGrabbed(true);
    //window.setKeyRepeatEnabled(false);

    initialize();
}

Application::~Application() { cout << "\033[1;46mApplication destructor called.\033[0m" << endl; }


/* FUNCTION - INITIALIZATION */
/* (private) Initialize application resources */
void Application::initialize() {
    cout << "\033[1;46mInitializing Application...\033[0m" << endl;

    // Classes //
    viewCenterPoint = Vector2f(static_cast<float>(WINDOWW) / 2.f, static_cast<float>(WINDOWH) / 2.f);
    view.setCenter(viewCenterPoint);
    view.setSize((viewCenterPoint.x*2.f), (viewCenterPoint.y*2.f));
    window.setView(view);
    view = window.getView();

    // Initialization //
    taskLoader.initializeJsonFiles();
    graphics.initialize();
    taskLoader.selectTasksDirectory(FILEPATHTRAINING); // CHOICE: Choose tasks path.

    // Containers Reserve Space //
    trainInputGrids.reserve(10);
    trainOutputGrids.reserve(10);
    testInputGrids.reserve(5);
    testOutputGrids.reserve(5);

    // Other //
    testEditGrid.resizeEditGrid();
    testPairsGridIdx = 0;
    isPickerActive = false;

    scrollBarOn = false;
    scrollOffset = 0.f;

    anyTimerOn = false;
    isDragging = false;
    isDraggingScrollBar = false;


    // TEMP // // TODO: Make an opening screen. and Delete.
    loadTask("first");
}


/* FUNCTIONS - RUNTIME */
/* Main runtime function */
void Application::runMain() {
    cout << "\033[1;46mStarting main loop...\033[0m" << endl;

    while (window.isOpen()) {
        Event eventRuntime;
        while (window.pollEvent(eventRuntime)) {
            if (eventRuntime.type == Event::Closed) {
                window.close();
                cout << "\033[1;46mExiting main loop...\033[0m" << endl;
            }

            if (eventRuntime.type == Event::KeyPressed) {
                if (!isInputBoxActive) {
                    switch (eventRuntime.key.code) {
                        case Keyboard::R:
                            loadTask("random");
                            break;
                        case Keyboard::O:
                            openTask();
                            break;
                        case Keyboard::W:
                            loadTask("next");
                            break;
                        case Keyboard::B:
                            if (testPairsGridSize > 1 && testPairsGridIdx > 0) {
                                --testPairsGridIdx;
                                updatedTestPair();
                            } else if (testPairsGridSize > 1 && testPairsGridIdx == 0) {
                                testPairsGridIdx = (testPairsGridSize-1);
                                updatedTestPair();
                            }
                            break;
                        case Keyboard::N:
                            if (testPairsGridSize > 1 && (testPairsGridIdx+1) < testPairsGridSize) {
                                ++testPairsGridIdx;
                                updatedTestPair();
                            } else if (testPairsGridSize > 1 && (testPairsGridIdx+1) == testPairsGridSize) {
                                testPairsGridIdx = 0;
                                updatedTestPair();
                            }
                            break;
                        case Keyboard::Right:
                            if (scrollBarOn) {
                                handleKeyboardInputs(eventRuntime);
                            }
                            break;
                        case Keyboard::Left:
                            if (scrollBarOn) {
                                handleKeyboardInputs(eventRuntime);
                            }
                            break;
                        case Keyboard::C:
                            if (isPickerActive) {
                                copyMouseSelection();
                            }
                            break;
                        case Keyboard::V:
                            if (isPickerActive) {
                                pasteMouseSelection();
                            }
                            break;
                        case Keyboard::S:
                            submitEditGrid(testEditGrid, testOutputGrids[testPairsGridIdx]);
                            break;
                        default:
                            // Optionally log or handle unrecognized keys
                            break;
                    }
                }
            }

            if (eventRuntime.type == Event::MouseButtonPressed) {
                if (eventRuntime.mouseButton.button == Mouse::Left) {
                    handleIfMouseClick(eventRuntime);
                } else if (eventRuntime.mouseButton.button == Mouse::Right) {
                    handleIfRightMouseClick(eventRuntime);
                }
            } 
            if (eventRuntime.type == Event::MouseButtonReleased) {
                if (eventRuntime.mouseButton.button == Mouse::Left) {
                    handleIfMouseIsReleased(eventRuntime);
                } else if (eventRuntime.mouseButton.button == Mouse::Right) {
                    // (...)
                }
            }
            if (eventRuntime.type == Event::MouseMoved) {
                // (...)
            }
            if (eventRuntime.type == Event::LostFocus) {
                handleIfMouseIsReleased(eventRuntime);
                isDragging = false;
            }
        }

        if (anyTimerOn) {
            if (!graphics.checkForTimers() && !graphics.checkForMsgIsDisplayed()) {
                anyTimerOn = false;
            }          
        }

        if (isDragging) {
            handleIfMouseIsDragging(eventRuntime);
        }

        if (isInputBoxActive) {
            handleKeyboardInputs(eventRuntime);
        }

        window.clear(WINDOWBGCOLOR);

        graphics.drawGraphicsToWindow(window, view, scrollBarOn);
        graphics.drawGridsToWindow(window, trainInputGrids, trainOutputGrids, 
            testInputGrids[testPairsGridIdx], testOutputGrids[testPairsGridIdx], testEditGrid, cellPicker, isDraggingScrollBar);
        
        window.display();
    }
}


/* FUNCTIONS - UTILITIES.INTERFACE */
/* (private) Handles mouse click inputs */
void Application::handleIfMouseClick(Event& _event) {
    Vector2f mousePos(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));
    
    if (graphics.checkForButtonBound(mousePos, 0, scrollOffset)) {
        loadTask("random");
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 1, scrollOffset)) {
        openTask();
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 2, scrollOffset)) {
        loadTask("next");
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 3, scrollOffset)) {
        if (testPairsGridSize > 1 && testPairsGridIdx > 0) {
            --testPairsGridIdx;
            updatedTestPair();
        } else if (testPairsGridSize > 1 && testPairsGridIdx == 0) {
            testPairsGridIdx = (testPairsGridSize-1);
            updatedTestPair();
        }
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 4, scrollOffset)) {
        if (testPairsGridSize > 1 && (testPairsGridIdx+1) < testPairsGridSize) {
            ++testPairsGridIdx;
            updatedTestPair();
        } else if (testPairsGridSize > 1 && (testPairsGridIdx+1) == testPairsGridSize) {
            testPairsGridIdx = 0;
            updatedTestPair();
        }
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 5, scrollOffset)) {
        graphics.resizeEditGridFromInput(testEditGrid);
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 6, scrollOffset)) {
        graphics.resetEditGrid(testEditGrid);
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 7, scrollOffset)) {
        graphics.copyTestInputGridToEditGrid(testEditGrid, testInputGrids[testPairsGridIdx]);
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 8, scrollOffset)) {
        graphics.copyTestOutputGridToEditGrid(testEditGrid, testOutputGrids[testPairsGridIdx]);
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 9, scrollOffset)) {
        if (isPickerActive) {
            copyMouseSelection();
        }
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 10, scrollOffset)) {
        if (isPickerActive) {
            pasteMouseSelection();
        }
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 11, scrollOffset)) {
        if (testEditGrid.checkForFloodFill() == 1) {
            Cell& cell = testEditGrid.getCellForFloodFill();
            testEditGrid.floodFillFromLocation(cell.getCellX(), cell.getCellY(), cellPicker.getCellSel());
            graphics.displayMessage(1, "Successfully activated flood fill.");
        } else if (testEditGrid.checkForFloodFill() == 0) {
            graphics.displayMessage(2, "There are no cells selected.");
        } else {
            graphics.displayMessage(2, "There are too many cells selected.");
        }
        anyTimerOn = true;
    } else if (graphics.checkForButtonBound(mousePos, 12, scrollOffset)) {
        submitEditGrid(testEditGrid, testOutputGrids[testPairsGridIdx]);
        anyTimerOn = true;
    }

    if (graphics.checkForCheckerBound(mousePos, 0, scrollOffset, graphics.getDrawCellNumbers())) {
        graphics.setDrawCellNumbers();
    } else if (graphics.checkForCheckerBound(mousePos, 1, scrollOffset, isPickerActive)) {
        isPickerActive = !isPickerActive;
    }

    if (graphics.checkForInputBoxBound(mousePos, scrollOffset)) {
        anyTimerOn = true;
    }

    if (cellPicker.isInBounds(mousePos, scrollOffset)) {
        cellPicker.updatePickIfClicked(mousePos, scrollOffset);
        if (testEditGrid.getIsSel()) {
            testEditGrid.updateSelectedCells(cellPicker.getCellSel());
        }
    }

    if (scrollBarOn) {
        if (graphics.checkForScrollBarBound(mousePos)) {
            isDraggingScrollBar = true;
            isDragging = true;
            anyTimerOn = true;
        }
    }

    if (isPickerActive) {
        cellPicker.updateSelAreaIfClicked(mousePos, scrollOffset);
        isDragging = true;
    }
}

/* (private) Handles right mouse click inputs */
void Application::handleIfRightMouseClick(Event& _event) {
    Vector2f mousePos(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));

    if (testEditGrid.isInBounds(mousePos, scrollOffset)) {
        testEditGrid.updateCellIfRightClicked(mousePos, scrollOffset, cellPicker.getCellSel());
    }
}


/* (private) Handles mouse inputs if mouse is released */
void Application::handleIfMouseIsReleased(Event& _event) {
    Vector2f mousePos(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y));
    
    if (anyTimerOn) {
        graphics.updateMouseIsReleased(isDragging);
        
    }

    if (isPickerActive && !isDraggingScrollBar) {
        if (cellPicker.getSelStart() == cellPicker.getSelEnd()) {
            clearSelection();
            Vector2f selPoint = cellPicker.getSelAreaBounds().getPosition();
            if (testEditGrid.isInBounds(selPoint)) {
                testEditGrid.updateCellIfClicked(selPoint);
            } else if (testInputGrids[testPairsGridIdx].isInBounds(selPoint)) {
                testInputGrids[testPairsGridIdx].updateCellIfClicked(selPoint);
            } else if (testOutputGrids[testPairsGridIdx].isInBounds(selPoint)) {
                testOutputGrids[testPairsGridIdx].updateCellIfClicked(selPoint);
            }
        } else {
            clearSelection();
            FloatRect& selArea = cellPicker.updateSelAreaIfReleased(mousePos, scrollOffset);
            if (testEditGrid.isInBounds(selArea)) {
                testEditGrid.updateCellIfAreaSelected(selArea);
            } else if (testInputGrids[testPairsGridIdx].isInBounds(selArea)) {
                testInputGrids[testPairsGridIdx].updateCellIfAreaSelected(selArea);
            } else if (testOutputGrids[testPairsGridIdx].isInBounds(selArea)) {
                testOutputGrids[testPairsGridIdx].updateCellIfAreaSelected(selArea);
            }
        }
    }

    isDraggingScrollBar = false;
    isDragging = false;
}

/* (private) Handles mouse inputs if mouse isDragging */
void Application::handleIfMouseIsDragging(Event& _event) {
    if (isPickerActive && !isDraggingScrollBar) {
        cellPicker.updateSelAreaWhileDragging(window, _event, scrollOffset);
    }

    if (isDraggingScrollBar) {
        scrollOffset = graphics.updatedScrollBarMouseDragging(window, _event);
        view.setCenter((scrollOffset+viewCenterPoint.x), viewCenterPoint.y);
        window.setView(view);
    }
}

/* (private) Clear selection (support function) */
void Application::clearSelection() {
    if (testEditGrid.getIsSel()) {
        testEditGrid.updateCellIfNotSelected();
    }
    if (testInputGrids[testPairsGridIdx].getIsSel()) {
        testInputGrids[testPairsGridIdx].updateCellIfNotSelected();
    }
    if (testOutputGrids[testPairsGridIdx].getIsSel()) {
        testOutputGrids[testPairsGridIdx].updateCellIfNotSelected();
    }
}

/* (private) Handles keyboard inputs */
void Application::handleKeyboardInputs(Event& _event) {
    if (isInputBoxActive) {
        graphics.editInputBoxText(_event);
    } else if (!isInputBoxActive && scrollBarOn) {
        float changeOffset = 5.f;
        if (_event.key.code == Keyboard::Right) {
            if ((scrollOffset+changeOffset) < (graphics.getContentWidth()-static_cast<float>(WINDOWW))) {
                scrollOffset = (scrollOffset+changeOffset);
            } else {
                changeOffset = (graphics.getContentWidth()-static_cast<float>(WINDOWW)) - scrollOffset;
                scrollOffset = (graphics.getContentWidth()-static_cast<float>(WINDOWW));
            }
        } else if (_event.key.code == Keyboard::Left) {
            if ((scrollOffset-changeOffset) > 0.f) {
                changeOffset = -changeOffset;
                scrollOffset = (scrollOffset+changeOffset);
            } else {
                changeOffset = -scrollOffset;
                scrollOffset = 0.f;
            }
        }

        graphics.updateScrollBarFromKeyboard(_event.key, changeOffset);
        view.setCenter((scrollOffset+viewCenterPoint.x), viewCenterPoint.y);
        window.setView(view);
    }

}


/* FUNCTIONS - UTILITIES.SUPPORT */
/* (private) Reset default values for new task */
void Application::resetTask() {
    // Application //
    taskPairsJson.first.clear();
    taskPairsJson.second.clear();
    trainInputGrids.clear();
    trainOutputGrids.clear();
    testInputGrids.clear();
    testOutputGrids.clear();
    testPairsGridIdx = 0;
    testPairsGridSize = 1;

    // Graphics //
    view.setCenter(viewCenterPoint);
    window.setView(view);
    scrollOffset = 0.f;

    graphics.displayMessage(0, "");

    // Other //
    //cellPicker.setSelected(0);
}

/* (private) Load task */
void Application::loadTask(string _string) {
    selectedTaskPath = taskLoader.loadTask(_string);
    resetTask();
    taskPairsJson = taskLoader.extractJsonPairs(selectedTaskPath);
    newTask();
}

/* (private) Open task from directory */
void Application::openTask() {
    try {
        selectedTaskPath = taskLoader.loadTaskFromDialog();
    } catch (const runtime_error& e) {
        cerr << "\033[1;41mError: \033[0m" << e.what() << endl;
        graphics.displayMessage(0, "No file was selected");
        return;
    }
    resetTask();
    taskPairsJson = taskLoader.extractJsonPairs(selectedTaskPath);
    newTask();
}

/* (private) New task procedures */
void Application::newTask() {
    testPairsGridSize = static_cast<int>(taskPairsJson.second.size());
    loadTaskPairs(taskPairsJson);

    graphics.updateNewTaskGraphics(trainInputGrids, trainOutputGrids, testInputGrids[testPairsGridIdx], testOutputGrids[testPairsGridIdx], testEditGrid,
        taskLoader.getSelectedTaskName(), taskLoader.getTaskIdx(), taskLoader.getTaskFilesSize(), testPairsGridIdx, testPairsGridSize, cellPicker);
    graphics.resetGraphicsElements(scrollOffset);
    scrollBarOn = graphics.needsForScroolBar();
    graphics.displayMessage(1, "Successfully loaded task: " + taskLoader.getSelectedTaskName());

    cout << "TaskPairsTrain size: " << taskPairsJson.first.size() << ". TaskPairsTest size: " << testPairsGridSize << ".\n";
}

/* (private) Process training data pairs (input and output) and add to containers */
void Application::loadTaskPairs(pair<json, json>& _pairs) {
    if (!_pairs.first.empty() && !_pairs.second.empty()) {
        for (unsigned i = 0; i < _pairs.first.size(); ++i) {
            vector<vector<int>> inputGData = _pairs.first[i].at("input").get<vector<vector<int>>>();
            trainInputGrids.emplace_back(inputGData[0].size(), inputGData.size(), inputGData);
            trainInputGrids[i].resizeCellsSize(BOXTRAINS);

            vector<vector<int>> outputGData = _pairs.first[i].at("output").get<vector<vector<int>>>();
            trainOutputGrids.emplace_back(outputGData[0].size(), outputGData.size(), outputGData);
            trainOutputGrids[i].resizeCellsSize(BOXTRAINS);
        }

        for (unsigned i = 0; i < _pairs.second.size(); ++i) {
            vector<vector<int>> inputGData = _pairs.second[i].at("input").get<vector<vector<int>>>();
            testInputGrids.emplace_back(inputGData[0].size(), inputGData.size(), inputGData);
            testInputGrids[i].resizeCellsSize(BOXTESTS);
            
            vector<vector<int>> outputGData = _pairs.second[i].at("output").get<vector<vector<int>>>();
            testOutputGrids.emplace_back(outputGData[0].size(), outputGData.size(), outputGData);
            testOutputGrids[i].resizeCellsSize(BOXTESTS);
        }

        testEditGrid.resizeEditGrid();
    } else {
        cerr << "\033[1;41mTestJsonPairs is empty.\033[0m" << endl;
    }
}

/* (private) Load next/back task pair */
void Application::updatedTestPair() {
    cout << "Updating test Pair" << ".\n";

    testInputGrids[testPairsGridIdx].resizeCellsSize(BOXTESTS);
    testOutputGrids[testPairsGridIdx].resizeCellsSize(BOXTESTS);
    testEditGrid.resizeEditGrid();

    graphics.updateNextTestPairGraphics(testInputGrids[testPairsGridIdx], testOutputGrids[testPairsGridIdx], testEditGrid, 
        testPairsGridIdx, testPairsGridSize, cellPicker);
}

/* (private) Copy mouse selection */
void Application::copyMouseSelection() {
    try {
        if (testEditGrid.getIsSel()) {
            cellPicker.copySel(testEditGrid);
            graphics.displayMessage(1, "Copied selection from edit Grid.");
        }
        if (testInputGrids[testPairsGridIdx].getIsSel()) {
            cellPicker.copySel(testInputGrids[testPairsGridIdx]);
            graphics.displayMessage(1, "Copied selection from test input Grid.");
        }
        if (testOutputGrids[testPairsGridIdx].getIsSel()) {
            cellPicker.copySel(testOutputGrids[testPairsGridIdx]);
            graphics.displayMessage(1, "Copied selection from test output Grid.");
        }
    } catch (const out_of_range& e) {
        graphics.displayMessage(2, "Out of range error: " + string(e.what()));
        cerr << "\033[1;41mOut of range error: \033[0m" << e.what() << endl;
    }
}

/* (private) Paste mouse selection */
void Application::pasteMouseSelection() {
    try {
        if (testEditGrid.getIsSel()) {
            cellPicker.pasteSel(testEditGrid);
            graphics.displayMessage(1, "Pasted selection on edit Grid.");
        }
        if (testInputGrids[testPairsGridIdx].getIsSel()) {
            graphics.displayMessage(2, "Trying to paste on invalid test input Grid.");
        }
        if (testOutputGrids[testPairsGridIdx].getIsSel()) {
            graphics.displayMessage(2, "Trying to paste on invalid test output Grid.");
        }
    } catch (const out_of_range& e) {
        graphics.displayMessage(2, "Out of range error: " + string(e.what()));
        cerr << "\033[1;41mOut of range error: \033[0m" << e.what() << endl;
    }
}

/* Submit edit Grid and check  */
void Application::submitEditGrid(Grid& _gEdit, Grid& _gTO) {
    bool success = true;
    try {
        if (_gEdit.getMatrixW() != _gTO.getMatrixW() || _gEdit.getMatrixH() != _gTO.getMatrixH()) {
            success = false;
            throw out_of_range("Edit Grid and outcome dimensions don't match.");
        }

        for (int i = 0; i < _gEdit.getMatrixH(); ++i) {
            for (int j = 0; j < _gEdit.getMatrixW(); ++j) {
                if (_gEdit.getMatrix()[i][j].getColor() == _gTO.getMatrix()[i][j].getColor()) {
                    continue;
                } else {
                    success = false;
                    throw out_of_range("Edit Grid and outcome values don't match.");
                }
            }
        }
    } catch (const out_of_range& e) {
        graphics.displayMessage(2, "Error: " + string(e.what()));
        cerr << "\033[1;41mError: \033[0m" << e.what() << endl;
    }

    if (success) {
        graphics.displayMessage(1, "Edit Grid has been submitted successfully.");
        cout << "Edit Grid has been submitted successfully." << endl;
    }
}
