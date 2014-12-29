#include <QObject>
#include <mellowplayer/plugins.h>


class GroovesharkIntegrationPlugin :
        public QObject,
        public ServiceIntegrationInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID ServiceIntegrationInterface_iid
                      FILE "grooveshark.json")
    Q_INTERFACES(ServiceIntegrationInterface)

public:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
};
