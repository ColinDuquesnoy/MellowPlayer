#include "plugins.h"
#include <QObject>

class GroovesharkServiceIntegrationPlugin :
        public QObject,
        public IServiceIntegration
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID IServiceIntegration_iid
                      FILE "grooveshark_plugin.json")
    Q_INTERFACES(IServiceIntegration)

public:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
};
