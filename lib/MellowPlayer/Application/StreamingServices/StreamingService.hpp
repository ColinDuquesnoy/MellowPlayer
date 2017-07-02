#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include "StreamingServiceMetadata.hpp"
#include "StreamingServiceStyle.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class StreamingServiceScript;

class StreamingService: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ getAuthor CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString url READ getUrl CONSTANT)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(StreamingServiceScript* script READ getScript CONSTANT)
public:
    StreamingService(const StreamingServiceMetadata& metadata, const StreamingServiceStyle& style=StreamingServiceStyle());
    ~StreamingService();

    bool isValid() const;
    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;
    StreamingServiceScript* getScript() const;
    const StreamingServiceStyle& getStyle() const;

    bool operator==(const StreamingService& rhs) const;
    bool operator!=(const StreamingService& rhs) const;

private:
    StreamingServiceMetadata metadata;
    StreamingServiceStyle style;
    std::unique_ptr<StreamingServiceScript> script;
};

END_MELLOWPLAYER_NAMESPACE

