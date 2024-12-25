
#include <windows.h>
#include <commdlg.h> 
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "loader.hpp"
#include "settings.hpp"

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;


/* CONSTRUCTOR (AND DESTRUCTOR) */
TaskLoader::TaskLoader() { cout << "\033[1;46mLoaded TaskLoader constructor.\033[0m" << endl; } 

TaskLoader::~TaskLoader() { cout << "\033[1;46mTaskLoader destructor called.\033[0m" << endl; }


/* FUNCTION - INITIALIZATION */
/* Initialize .json data files */
void TaskLoader::initializeJsonFiles() {
    cout << "\033[1;46mInitializing .json data files...\033[0m" << endl;
    
    try {
        error_code ec;
        filesTraining.reserve(500);
        if (!fs::exists(FILEPATHTRAINING) || !fs::is_directory(FILEPATHTRAINING)) {
            cerr << "\033[1;41mTask subset directory not found: \033[0m" + FILEPATHTRAINING << endl;
        }
        for (const fs::directory_entry& fileEntry : fs::directory_iterator(FILEPATHTRAINING)) {
            if (ec) {
                cerr << "\033[1;41mError while iterating directory: \033[0m" << ec.message() << endl;
                continue;
            }
            if (fileEntry.is_regular_file() && fileEntry.path().extension() == ".json") {
                try {
                    filesTraining.emplace_back(fileEntry.path());
                } catch (const bad_alloc& e) {
                    cerr << "\033[1;41mMemory allocation failed while adding file: \033[0m" << fileEntry.path()
                        << "\n\033[1;41mCurrent vector size: \033[0m" << filesTraining.size() << endl;
                    throw; 
                }
            }
        }

        cout << "Number of files in filesTraining: " << filesTraining.size() << ".\n";

        filesEvaluation.reserve(500); 
        if (!fs::exists(FILEPATHEVALUATION) || !fs::is_directory(FILEPATHEVALUATION)) {
            cerr << "\033[1;41mTask subset directory not found: \033[0m" + FILEPATHEVALUATION << endl;
        }
        for (const fs::directory_entry& fileEntry : fs::directory_iterator(FILEPATHEVALUATION)) {
            if (ec) {
                cerr << "\033[1;41mError while iterating directory: \033[0m" << ec.message() << endl;
                continue;
            }
            if (fileEntry.is_regular_file() && fileEntry.path().extension() == ".json") {
                try {
                    filesEvaluation.emplace_back(fileEntry.path());
                } catch (const bad_alloc& e) {
                    cerr << "\033[1;41mMemory allocation failed while adding file: \033[0m" << fileEntry.path()
                        << "\n\033[1;41mCurrent vector size: \033[0m" << filesTraining.size() << endl;
                    throw; 
                }
            }
        }

        cout << "Number of files in filesEvaluation: " << filesEvaluation.size() << ".\n";
    } catch (const exception& e) {
        cerr << "\033[1;41mTaskLoader initialization failed: \033[0m" << e.what() << endl;
        throw;
    }
}


/* FUNCTIONS - UTILITIES.SUPPORT */
/* Selects between training and evaluation files */
void TaskLoader::selectTasksDirectory(const string& _directory) {
    taskFiles.reserve(500);
    if (_directory == FILEPATHTRAINING) {
        taskFiles = filesTraining;
        cout << "\033[1;46mTraining directory selected for tasks. \033[0m" << endl;
    } else if (_directory == FILEPATHEVALUATION) {
        taskFiles = filesEvaluation;
        cout << "\033[1;46mEvaluation directory selected for tasks. \033[0m" << endl;
    } else {
        cerr << "\033[1;41mDirectory is not valid: \033[0m" + _directory << endl;
    }

    workingDirectory = fs::current_path();
    cout << "Number of files in taskFiles: " << taskFiles.size() << ".\n";
}

/* Selects the Task from the list */
fs::path TaskLoader::loadTask(string _string) { 
    cout << "Loading training task" << ".\n";

    if (taskFiles.empty()) {
        cerr << "\033[1;41mNo task files found in tasKFiles directory.\033[0m" << endl;
    }

    fs::path selectedTaskPath;
    if (_string == "first") {
        taskIdx = 0;
        selectedTaskPath = taskFiles[taskIdx];
    } else if (_string == "next") {
        taskIdx += 1;
        selectedTaskPath = taskFiles[taskIdx];
    } else if (_string == "random") {
        uniform_int_distribution<> dis(0, taskFiles.size() - 1);
        taskIdx = dis(gen);
        selectedTaskPath = taskFiles[taskIdx];
    }
    
    return selectedTaskPath;
}

/* Opens Windows File Open dialog to select a .json file from directory, try to extract train and test data */
fs::path TaskLoader::loadTaskFromDialog() {
    cout << "Loading training task from dialog" << ".\n";

    OPENFILENAMEA ofn; // Structure to store dialog settings.
    char fileName[MAX_PATH] = ""; // Buffer to store the selected file path.

    ZeroMemory(&ofn, sizeof(ofn)); // Clear memory for safety.
    ofn.lStructSize = sizeof(ofn); // Set the size of the structure.
    ofn.hwndOwner = nullptr; // No parent window (use nullptr for console apps).
    ofn.lpstrFilter = "JSON Files\0*.json\0All Files\0*.*\0"; // JSON filter and all files.
    ofn.lpstrFile = fileName; // Pointer to buffer that receives the file path.
    ofn.nMaxFile = MAX_PATH; // Size of the buffer.
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST; // Dialog behavior options.

    
    if (GetOpenFileNameA(&ofn)) { // Display the dialog and check if a file was selected.
        fs::path selectedTaskPath = fileName;
        taskIdx = -1;

        fs::current_path(workingDirectory); // Restore the working directory

        return selectedTaskPath;
    } else {
        DWORD error = CommDlgExtendedError(); // Retrieve extended error information.
        if (error == 0) { // 0: The dialog was canceled (normal behavior).
            cout << "No file selected (dialog canceled)" << ".\n";
        } else { // Non-zero: Indicates an error occurred in the file dialog.
            cerr << "\033[1;41Error opening file dialog. Error code: \033[0m" << error << endl;
        }

        fs::current_path(workingDirectory); // Restore the working directory
    }

    throw runtime_error("File selection was canceled or failed."); // Exit the function early with an error or a default return value.
}

/* Try to extract train and test Json pairs */
pair<json, json> TaskLoader::extractJsonPairs(fs::path& _slctTP) {
    selectedTaskName = _slctTP.filename().string();
    cout << "Loaded task: " + selectedTaskName << ".\n";
    cout << "Absolute path: " << absolute(_slctTP) << ".\n";

    json taskJson;
    try {
        ifstream taskFile(_slctTP);
        if (!taskFile.is_open()) {
            throw runtime_error("Unable to open file: " + _slctTP.string());
        }
        stringstream buffer;
        buffer << taskFile.rdbuf(); // Read entire file into the buffer.
        string fileContent = buffer.str(); // Store the content as a string.
        taskJson = json::parse(fileContent); // Deserializing the JSON data into 'nlohmann::json' object.
    } catch (const exception& e) {
        cerr << "\033[1;41mFailed to read or parse task file: \033[0m" << e.what() << endl;
    }

    json train;
    json test;
    pair<json, json> taskJsonPairs(train, test);
    try {
        taskJsonPairs.first = taskJson.at("train");
        taskJsonPairs.second = taskJson.at("test");
    } catch (const exception& e) {
        cerr << "\033[1;41mBad file format: \033[0m" << e.what() << endl;
    }

    return taskJsonPairs;
}
