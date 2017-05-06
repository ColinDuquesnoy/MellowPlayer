#pragma once

#include <memory>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/Logging/LoggingManager.hpp>
#include "PluginMetadata.hpp"
#include "PluginStyle.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Entities)

class PluginScript;

class Plugin: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString author READ getAuthor CONSTANT)
    Q_PROPERTY(QString authorWebsite READ getAuthorWebsite CONSTANT)
    Q_PROPERTY(QString color READ getColor CONSTANT)
    Q_PROPERTY(QString logo READ getLogo CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString url READ getUrl CONSTANT)
    Q_PROPERTY(QString version READ getVersion CONSTANT)
    Q_PROPERTY(PluginScript* script READ getScript CONSTANT)
public:
    Plugin(const PluginMetadata& metadata, const PluginStyle& style = PluginStyle::defaultStyle());
    ~Plugin();

    bool isValid() const;
    const QString& getAuthor() const;
    const QString& getAuthorWebsite() const;
    QString getColor() const;
    QString getLogo() const;
    const QString& getName() const;
    QString getUrl() const;
    const QString& getVersion() const;
    PluginScript* getScript() const;
    const PluginStyle& getStyle() const;

    bool operator==(const Plugin& rhs) const;
    bool operator!=(const Plugin& rhs) const;

private:
    PluginMetadata metadata;
    PluginStyle style;
    std::unique_ptr<PluginScript> script;
};

END_MELLOWPLAYER_NAMESPACE

