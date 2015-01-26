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

#ifndef PLUGINMETADATA
#define PLUGINMETADATA

#include <QIcon>
#include <QString>


/*!
 * \brief The PluginMetaData struct contains the metadata of a
 * MellowPlayer plugin.
 */
struct PluginMetaData
{
    QString name;           /*!< Name of the plugin */
    QString author;         /*!< Author of the plugin */
    QString author_website; /*!< Plugin website (usually a link to the author's
                                 github account) */
    QString version;        /*!< Plugin version */
    QString description;    /*!< Plugin description, use html for streaming
                                 services integration plugins */
    QIcon   icon;           /*!< Plugin icon, optional*/
};

#endif // PLUGINMETADATA

