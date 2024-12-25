
#pragma once

#include <random>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;


class TaskLoader {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Initialization //
    fs::path workingDirectory;
    vector<fs::path> filesTraining;
    vector<fs::path> filesEvaluation;
    vector<fs::path> taskFiles;

    // Runtime //
    int taskIdx;
    string selectedTaskName;

    // Randomizer //
    random_device rd;
    mt19937 gen{rd()};


public:
    /* CONSTRUCTOR (AND DESTRUCTOR) */
    TaskLoader();
    ~TaskLoader();
    

    /* FUNCTION - INITIALIZATION */
    void initializeJsonFiles();


    /* FUNCTIONS - UTILITIES.SUPPORT */
    void selectTasksDirectory(const string& _directory);
    fs::path loadTask(string _string);
    fs::path loadTaskFromDialog();
    pair<json, json> extractJsonPairs(fs::path& _slctTP);
    void loadTaskTrainPairs(json& _jTrain);
    void loadTaskTestPairs(json& _jTest);


    /* FUNCTIONS - UTILITIES.GETTERS AND SETTERS */
    int getTaskFilesSize() const { return taskFiles.size(); } // Getter for size of taskFiles.

    int getTaskIdx() const { return taskIdx; } // Getter for taskIdx.
    void setTaskIdx(int _n) { taskIdx = _n; } // Setter for taskIdx.

    string getSelectedTaskName() const { return selectedTaskName; } // Getter for selectedTaskName.
    void setSelectedTaskName(string _sTN) { selectedTaskName = _sTN; } // Setter for selectedTaskName.
};
