
#include <string>

#include <SFML/Graphics.hpp>

#include "settings.hpp"

using namespace std;
using namespace sf;


/* GLOBAL PARAMETERS */
// Main Window //
const string windowTi = "ARC Task Solver";
const unsigned WINDOWW = 1804;
const unsigned WINDOWH = 998;
const int WINDOWPOSX = 55;
const int WINDOWPOSY = 5;
const int FPS = 30;

// Loader //
const string FILEPATHTRAINING = "data\\training\\";
const string FILEPATHEVALUATION = "data\\evaluation\\";

// Other //
const string NONAME = "";

bool isInputBoxActive = false;

// Fonts //
Font cFont;
const string CFONTPATH = ".\\resources\\fonts\\SourceSans3-Light.ttf";
int cFontSize = 12;

// Texture //
Texture selCellTexture;
const string SELCELLTEXPATH = ".\\resources\\img\\brushed-alum.png";

// Sprite //
Sprite selCellSprite;

// Colors //
const Color WINDOWBGCOLOR = Color(20, 20, 30);

const Color CELLOUTLINECOLOR = Color(60, 60, 70);
const Color CELLTEXTCOLOR = Color(240, 240, 250);

const Color PICKERCELLOUTCOLOR = Color(100, 100, 200);
const Color PICKERSELAREACOLOR = Color(240, 240, 250, 40);
const Color PICKERSELAREAOUTCOLOR = Color(240, 240, 250, 80);


/* CELLS PARAMETERS */
const float MAXCELLSIZE = 80.f;
const float CELLSIZE =  16.f;
const float CELLOUTTHICK = 1.f;
    

/* GRID PARAMETERS */
const int MAXGRIDSIZE = 30;
const int EDITGRIDINITIALSIZE =  3;


/* CELL PICKER PARAMETERS */
const float PICKERSIZE = 10;

const float PICKERCELLSIZE = 30.f;
const float PICKERCELLOUTTHICK = 0.f;
const float PICKERCELLOUTTHICKSELECTED = 3.f;

const float BOXPICKER = (PICKERCELLSIZE*10);
const float BOXPICKERPOSX = 496 + (400-BOXPICKER) / 2; // overlayToolPosX + (BoxTestW-BoxPicker) / 2
const float BOXPICKERPOSY = 876;
const float PICKEROUTTHICK = 1.f;

bool isPickerActive = false;
