#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include "StreamingServicePluginMetadata.hpp"
#include "StreamingServiceStyle.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class StreamingServicePluginScript;

class StreamingServicePlugin: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ getAuthor CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
    Q_PROPERTY(QString color READ getColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString url READ getUrl CONSTANT)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(StreamingServicePluginScript* script READ getScript CONSTANT)
public:
    StreamingServicePlugin(const StreamingServicePluginMetadata& metadata, const StreamingServiceStyle& style=StreamingServiceStyle());
    ~StreamingServicePlugin();

    bool isValid() const;
    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getColor() const;
    QString getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;
    StreamingServicePluginScript* getScript() const;
    const StreamingServiceStyle& getStyle() const;

    bool operator==(const StreamingServicePlugin& rhs) const;
    bool operator!=(const StreamingServicePlugin& rhs) const;

private:
    StreamingServicePluginMetadata metadata;
    StreamingServiceStyle style;
    std::unique_ptr<StreamingServicePluginScript> script;
};

END_MELLOWPLAYER_NAMESPACE

