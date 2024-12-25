
#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/* GRAPHICS PARAMETERS - GENERAL */
// Fonts //
extern Font tiFont;
extern const string TIFONTPATH;
extern int tiFontSize;
extern const float TIFONTROTATION;
extern Font bdFont;
extern const string BDFONTPATH;
extern int bdFontSize;
extern Font msgFont;
extern const string MSGFONTPATH;
extern int msgFontSize;
extern Font btFont;
extern const string BTFONTPATH;
extern int btFontSize;

// Colors //
extern const Color OVERLAYBGCOLOR;
extern const Color OVERLAYOUTLINECOLOR;
extern const Color OVERLAYTIBGCOLOR;
extern const Color OVERLAYTIOUTLINECOLOR;

extern const Color TEXTCOLOR;

extern const Color MSGINFOCOLOR;
extern const Color MSGSUCCESSCOLOR;
extern const Color MSGERRORCOLOR;

extern const Color BUTTONCOLOR;
extern const Color BUTTONOUTLINECOLOR;
extern const Color BUTTONTEXTCOLOR;
extern const Color BUTTONCOLORPRESSED;
extern const Color BUTTONOUTLINECOLORPRESSED;
extern const Color BUTTONSUBMITCOLOR;
extern const Color BUTTONSUBMITCOLORPRESSED;

extern const Color CHECKERCOLOR;
extern const Color CHECKEROUTLINECOLOR;
extern const Color CHECKERCOLORPRESSED;
extern const Color CHECKEROUTLINECOLORPRESSED;
extern const Color CHECKERCHECKMARKCOLOR;

extern const Color INPUTBOXCOLOR;
extern const Color INPUTBOXOUTLINECOLOR;
extern const Color INPUTBOXTEXTCOLOR;
extern const Color INPUTBOXOUTLINECOLORPRESSED;

extern const Color SCROLLBARBGCOLOR;
extern const Color SCROLLBARBGOUTLINECOLOR;
extern const Color SCROLLBARCOLOR;
extern const Color SCROLLBAROUTLINECOLOR;
extern const Color SCROLLBARCOLORPRESSED;
extern const Color SCROLLBAROUTLINECOLORPRESSED;


/* GRAPHICS PARAMETERS - OVERLAYS */
// Overlay Basics //
extern const float BOXTRAINS;
extern const float BOXTESTS;
extern const float MARGINS;
extern const float TIBASICW;
extern const float TIMARGINADJUST;

extern const float OVERLAYOUTLINETHICKNESS;
extern const float OVERLAYTIOUTLINETHICKNESS;
extern const float OVERLAYTIROTATION;

// Overlays Train //
extern const float OVERLAYTRAINW;
extern const float OVERLAYTRAININITW;
extern const float OVERLAYTRAINH;
extern const float OVERLAYTRAINPOSX;
extern const float OVERLAYTRAINPOSY;

extern const float OVERLAYTRAINTIW;
extern const float OVERLAYTRAINTIH;
extern const float OVERLAYTRAINTIPOSX;
extern const float OVERLAYTRAINTIPOSY;

// Overlays Test AND TOOLS //
extern const float OVERLAYTESTINPUTW;
extern const float OVERLAYTESTINPUTH;
extern const float OVERLAYTESTINPUTPOSX;
extern const float OVERLAYTESTINPUTPOSY;

extern const float OVERLAYTESTINPUTTIW;
extern const float OVERLAYTESTINPUTTIH;
extern const float OVERLAYTESTINPUTTIPOSX;
extern const float OVERLAYTESTINPUTTIPOSY;

extern const float OVERLAYTOOLSW;
extern const float OVERLAYTOOLSH;
extern const float OVERLAYTOOLSPOSX;
extern const float OVERLAYTOOLSPOSY;

extern const float OVERLAYTOOLSTIW;
extern const float OVERLAYTOOLSTIH;
extern const float OVERLAYTOOLSTIPOSX;
extern const float OVERLAYTOOLSTIPOSY;

extern const float OVERLAYTESTOUTPUTW;
extern const float OVERLAYTESTOUTPUTH;
extern const float OVERLAYTESTOUTPUTPOSX;
extern const float OVERLAYTESTOUTPUTPOSY;

extern const float OVERLAYTESTOUTPUTTIW;
extern const float OVERLAYTESTOUTPUTTIH;
extern const float OVERLAYTESTOUTPUTTIPOSX;
extern const float OVERLAYTESTOUTPUTTIPOSY;


/* GRAPHICS PARAMETERS - GRID BOXES */
// Grid Boxes //
extern const float GRIDTRAININPUTINITPOSX;
extern const float GRIDTRAININPUTINITPOSY;
extern const float GRIDTRAININPUTADDOFFSETX;
extern const float GRIDTRAININPUTADDOFFSETY;

extern const float GRIDTRAINOUTPUTINITPOSX;
extern const float GRIDTRAINOUTPUTINITPOSY;
extern const float GRIDTRAINOUTPUTADDOFFSETX;
extern const float GRIDTRAINOUTPUTADDOFFSETY;

extern const float GRIDTESTINPUTINITPOSX;
extern const float GRIDTESTINPUTINITPOSY;

extern const float GRIDTESTOUTPUTINITPOSX;
extern const float GRIDTESTOUTPUTINITPOSY;

extern const float GRIDTESTEDITINITPOSX;
extern const float GRIDTESTEDITINITPOSY;


/* GRAPHICS PARAMETERS - TEXTS */
// Texts Titles //
extern const string MSGTRAINTI;
extern const float MSGTRAINTIPOSX;
extern const float MSGTRAINTIPOSY;

extern const string MSGTESTINPUTTI;
extern const float MSGTESTINPUTTIPOSX;
extern const float MSGTESTINPUTTIPOSY;

extern const string MSGTOOLSTI;
extern const float MSGTOOLSTIPOSX;
extern const float MSGTOOLSTIPOSY;

extern const string MSGTESTOUTPUTTI;
extern const float MSGTESTOUTPUTTIPOSX;
extern const float MSGTESTOUTPUTTIPOSY;

// Texts Body //
extern const string MSGLOADTASK;
extern const float MSGLOADTASKPOSX;
extern const float MSGLOADTASKPOSY;

extern const string MSGTASKNAME;
extern const float MSGTASKNAMEPOSX;
extern const float MSGTASKNAMEPOSY;

extern const string MSGTASKOUTPUTPAIR;
extern const float MSGTASKOUTPUTPAIRPOSX;
extern const float MSGTASKOUTPUTPAIRPOSY;

extern const string MSGSHOWCELLNUMBER;
extern const float MSGSHOWCELLNUMBERPOSX;
extern const float MSGSHOWCELLNUMBERPOSY;

extern const string MSGCHANGEGRIDSIZE;
extern const float MSGCHANGEGRIDSIZEPOSX;
extern const float MSGCHANGEGRIDSIZEPOSY;

extern const string MSGOTHERCOMMANDS;
extern const float MSGOTHERCOMMANDSPOSX;
extern const float MSGOTHERCOMMANDSPOSY;

extern const string MSGCELLPICKER;
extern const float MSGCELLPICKERPOSX;
extern const float MSGCELLPICKERPOSY;


/* GRAPHICS PARAMETERS - MESSAGES */
// Messages Basics //
extern const float MSGDURATION;

extern const string MSGBASIC;

// Messages //
extern const float MSGPOSY;


/* GRAPHICS PARAMETERS - BUTTONS */
// Buttons Basics //
extern const float CLICKBUTTONDURATION;

extern const float BUTTONH;
extern const float BUTTONOUTLINETHICKNESS;
extern const float BUTTONOUTLINETHICKNESSPRESSED;

extern const float BUTTONOFFSETY;
extern const float BUTTONSPACING;

// Buttons //
extern const string BUTTONRANDOMMSG;
extern const float BUTTONRANDOMW; 
extern const float BUTTONRANDOMH;
extern const float BUTTONRANDOMPOSX;
extern const float BUTTONRANDOMPOSY;

extern const string BUTTONOPENMSG;
extern const float BUTTONOPENW; 
extern const float BUTTONOPENH;
extern const float BUTTONOPENPOSX;
extern const float BUTTONOPENPOSY;

extern const string BUTTONNEXTTASKMSG;
extern const float BUTTONNEXTTASKW; 
extern const float BUTTONNEXTTASKH;
extern const float BUTTONNEXTTASKPOSX;
extern const float BUTTONNEXTTASKPOSY;

extern const string BUTTONBACKTESTPAIRMSG;
extern const float BUTTONBACKTESTPAIRW; 
extern const float BUTTONBACKTESTPAIRH;
extern const float BUTTONBACKTESTPAIRPOSX;
extern const float BUTTONBACKTESTPAIRPOSY;

extern const string BUTTONNEXTTESTPAIRMSG;
extern const float BUTTONNEXTTESTPAIRW; 
extern const float BUTTONNEXTTESTPAIRH;
extern const float BUTTONNEXTTESTPAIRPOSX;
extern const float BUTTONNEXTTESTPAIRPOSY;

extern const string BUTTONRESIZEEDITGRIDMSG;
extern const float BUTTONRESIZEEDITGRIDW; 
extern const float BUTTONRESIZEEDITGRIDH;
extern const float BUTTONRESIZEEDITGRIDPOSX;
extern const float BUTTONRESIZEEDITGRIDPOSY;

extern const string BUTTONRESETEDITGRIDMSG;
extern const float BUTTONRESETEDITGRIDW; 
extern const float BUTTONRESETEDITGRIDH;
extern const float BUTTONRESETEDITGRIDPOSX;
extern const float BUTTONRESETEDITGRIDPOSY;

extern const string BUTTONCOPYINPUTMSG;
extern const float BUTTONCOPYINPUTW; 
extern const float BUTTONCOPYINPUTH;
extern const float BUTTONCOPYINPUTPOSX;
extern const float BUTTONCOPYINPUTPOSY;

extern const string BUTTONCOPYOUTPUTMSG;
extern const float BUTTONCOPYOUTPUTW; 
extern const float BUTTONCOPYOUTPUTH;
extern const float BUTTONCOPYOUTPUTPOSX;
extern const float BUTTONCOPYOUTPUTPOSY;

extern const string BUTTONCOPYSELMSG;
extern const float BUTTONCOPYSELW; 
extern const float BUTTONCOPYSELH;
extern const float BUTTONCOPYSELPOSX;
extern const float BUTTONCOPYSELPOSY; 

extern const string BUTTONPASTESELMSG;
extern const float BUTTONPASTESELW; 
extern const float BUTTONPASTESELH;
extern const float BUTTONPASTESELPOSX;
extern const float BUTTONPASTESELPOSY; 

extern const string BUTTONFLOODFILLMSG;
extern const float BUTTONFLOODFILLW; 
extern const float BUTTONFLOODFILLH;
extern const float BUTTONFLOODFILLPOSX;
extern const float BUTTONFLOODFILLPOSY;

extern const string BUTTONSUBMITMSG;
extern const float BUTTONSUBMITW; 
extern const float BUTTONSUBMITH;
extern const float BUTTONSUBMITPOSX;
extern const float BUTTONSUBMITPOSY; 


/* GRAPHICS PARAMETERS - CHECKERS */
// Checkers //
extern const float CHECKEROUTLINETHICKNESS;
extern const float CHECKEROUTLINETHICKNESSPRESSED;

extern const float CHECKERH;
extern const float CHECKEROFFSETY;

extern const float CHECKERCELLNS; 
extern const float CHECKERCELLNPOSX;
extern const float CHECKERCELLNPOSY;

extern const float CHECKERPICKERS;
extern const float CHECKERPICKERPOSX;
extern const float CHECKERPICKERPOSY;


/* GRAPHICS PARAMETERS - INPUTBOXES */
// Input Boxes //
extern const float CLICKINPUTBOXDURATION;
extern const float INPUTBOXCURSORDURATION;

extern const float INPUTBOXMAXLENGTH;

extern const float INPUTBOXW;
extern const float INPUTBOXH;
extern const float INPUTBOXPOSX;
extern const float INPUTBOXPOSY;
extern const float INPUTBOXOUTLINETHICKNESS;
extern const float INPUTBOXOUTLINETHICKNESSPRESSED;
extern const string INPUTBOXDISPLAY;


/* GRAPHICS PARAMETERS - SCROLL BAR */
// Scroll Bar //
extern const float CLICKSCROLLBARDURATION;

extern const float SCROLLBARH;
extern const float SCROLLBARPOSX;
extern const float SCROLLBARPOSY;

extern const float SCROLLBAROUTLINETHICKNESS;

extern const float SCROLLBARBGW; 

extern const float SCROLLBARW; 


