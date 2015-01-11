#ifndef SHORCTUTS
#define SHORCTUTS

#include <QKeySequence>

#define DEFAULT_SHORTCUT_SELECT_SV      "F8"
#define DEFAULT_SHORTCUT_PREFERENCES    "F2"
#define DEFAULT_SHORTCUT_QUIT           "Ctrl+Q"

#ifdef __kde_support__
    // kde is the only place where media keys works reliably.
    #define DEFAULT_SHORTCUT_PLAY           "Media Play"
    #define DEFAULT_SHORTCUT_STOP           "Media Stop"
    #define DEFAULT_SHORTCUT_NEXT           "Media Next"
    #define DEFAULT_SHORTCUT_PREVIOUS       "Media Previous"
#else
    #define DEFAULT_SHORTCUT_PLAY       "Ctrl+Alt+P"
    #define DEFAULT_SHORTCUT_STOP       "Ctrl+Alt+S"
    #define DEFAULT_SHORTCUT_NEXT       "Ctrl+Alt+F"
    #define DEFAULT_SHORTCUT_PREVIOUS   "Ctrl+Alt+B"
#endif

#define DEFAULT_SHORTCUT_ABOUT          "F1"
#define DEFAULT_SHORTCUT_REPORT         "F3"

#endif // SHORCTUTS

