//---------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------

#ifndef SHORCTUTS
#define SHORCTUTS

#include <QtCore>

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
#ifdef Q_OS_MAC
#define DEFAULT_SHORTCUT_FAVORITE       "Ctrl+Alt+L"
#else
#define DEFAULT_SHORTCUT_FAVORITE       "Ctrl+Alt+F"
#endif
#define DEFAULT_SHORTCUT_ABOUT          "F1"
#define DEFAULT_SHORTCUT_REPORT         "F3"

#endif // SHORCTUTS

