
#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/* GLOBAL PARAMETERS */
// Main Window //
extern const string windowTi;
extern const unsigned WINDOWW;
extern const unsigned WINDOWH;
extern const int WINDOWPOSX;
extern const int WINDOWPOSY;
extern const int FPS;

// Loader //
extern const string FILEPATHTRAINING;
extern const string FILEPATHEVALUATION;

// Other //
extern const string NONAME;

extern bool isInputBoxActive;

// Fonts //
extern Font cFont;
extern const string CFONTPATH;
extern int cFontSize;

// Texture //
extern Texture selCellTexture;
extern const string SELCELLTEXPATH;

// Sprite //
extern Sprite selCellSprite;

// Colors //
extern const Color WINDOWBGCOLOR;

extern const Color CELLOUTLINECOLOR;
extern const Color CELLTEXTCOLOR;

extern const Color PICKERCELLOUTCOLOR;
extern const Color PICKERSELAREACOLOR;
extern const Color PICKERSELAREAOUTCOLOR;


/* CELLS PARAMETERS */
extern const float MAXCELLSIZE;
extern const float CELLSIZE;
extern const float CELLOUTTHICK;


/* GRID PARAMETERS */
extern const int MAXGRIDSIZE;
extern const int EDITGRIDINITIALSIZE;


/* CELL PICKER PARAMETERS */
extern const float PICKERSIZE;

extern const float PICKERCELLSIZE;
extern const float PICKERCELLOUTTHICK;
extern const float PICKERCELLOUTTHICKSELECTED;

extern const float BOXPICKER;
extern const float BOXPICKERPOSX;
extern const float BOXPICKERPOSY;
extern const float PICKEROUTTHICK;

extern bool isPickerActive;
