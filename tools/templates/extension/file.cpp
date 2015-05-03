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

#include <QWidget>
#include <mellowplayer.h>
#include "%(name)s.h"

//---------------------------------------------------------
%(classname)s::%(classname)s(QObject *parent):
    QObject(parent)
{
}

//---------------------------------------------------------
void %(classname)s::setup()
{
    // setup your extension here
}

//---------------------------------------------------------
const PluginMetaData &%(classname)s::metaData() const
{
    static PluginMetaData meta;
    meta.name = "%(name_cap)s";
    meta.author = "YOUR NAME";
    meta.author_website = "YOUR GITHUB PROFILE";
    meta.version = "1.0";
    meta.description =tr("Plugin description");
    return meta;
}

