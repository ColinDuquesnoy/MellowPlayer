#ifndef ICONS_H
#define ICONS_H

#include <QIcon>

/*!
 * \brief The Icons class contains a set of static functions for easily
 * accessing the application icons.
 *
 * The returned icons will always use the define icon theme on linux and
 * fallback to the icons stored in mellowplayer.qrc.
 */
class Icons
{
public:
    /*!
     * \brief Gets the "play" icon
     * \return QIcon
     */
    static QIcon play();

    /*!
     * \brief Gets the "pause" icon
     * \return QIcon
     */
    static QIcon pause();

    /*!
     * \brief Gets the "stop" icon
     * \return QIcon
     */
    static QIcon stop();

    /*!
     * \brief Gets the "loading" icon
     * \return QIcon
     */
    static QIcon loading();

    /*!
     * \brief Gets the "next" icon
     * \return QIcon
     */
    static QIcon next();

    /*!
     * \brief Gets the "previous" icon
     * \return QIcon
     */
    static QIcon previous();

    /*!
     * \brief Gets the "select cloud service" icon
     * \return QIcon
     */
    static QIcon selectCloudService();

    /*!
     * \brief Gets the "preferences" icon
     * \return QIcon
     */
    static QIcon preferences();

    /*!
     * \brief Gets the "quit" icon
     * \return QIcon
     */
    static QIcon quit();

    /*!
     * \brief Gets the "about" icon
     * \return QIcon
     */
    static QIcon about();

    /*!
     * \brief Gets the "report bug" icon
     * \return QIcon
     */
    static QIcon reportBug();

    /*!
     * \brief Gets the application icon
     * \return QIcon
     */
    static QIcon mellowPlayer();
};

#endif // ICONS_H
