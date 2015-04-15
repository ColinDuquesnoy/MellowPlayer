//---------------------------------------------------------
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
//---------------------------------------------------------

#include "application.h"
#include <QApplication>
#include <QtPlugin>


//---------------------------------------------------------
// Add plugins here
Q_IMPORT_PLUGIN(SoundcloudPlugin)
Q_IMPORT_PLUGIN(MixcloudPlugin)
Q_IMPORT_PLUGIN(DeezerPlugin)
Q_IMPORT_PLUGIN(GroovesharkPlugin)
Q_IMPORT_PLUGIN(HotkeysPlugin)
Q_IMPORT_PLUGIN(NotificationsPlugin)

#ifndef Q_OS_WIN
Q_IMPORT_PLUGIN(GroovesharkmobilePlugin)
#endif

#ifdef Q_OS_LINUX
Q_IMPORT_PLUGIN(Mpris2Plugin)
Q_IMPORT_PLUGIN(GnomemediakeysPlugin)
#endif


//---------------------------------------------------------
int main(int argc, char *argv[]){
    MellowPlayerApp a(argc, argv);
    return a.exec();
}
