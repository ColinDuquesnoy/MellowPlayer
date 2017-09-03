#include "StreamingServicesControllerViewModel.hpp"
#include <MellowPlayer/Application/IWorkDispatcher.hpp>
#include <MellowPlayer/Application/ICommandLineParser.hpp>
#include <MellowPlayer/Application/Player/Player.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWebEngine/QtWebEngine>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StreamingServicesControllerViewModel::StreamingServicesControllerViewModel(StreamingServicesController& streamingServices, Players& players,
                                                                           Settings& settings, IWorkDispatcher& workDispatcher,
                                                                           IStreamingServiceCreator& streamingServiceCreator,
                                                                           ICommandLineParser& commandLineParser)
        : QObject(),
          streamingServices_(streamingServices),
          players_(players),
          settings_(settings),
          currentServiceSetting_(settings.get(SettingKey::PRIVATE_CURRENT_SERVICE)),
          workDispatcher_(workDispatcher),
          streamingServiceCreator_(streamingServiceCreator),
          commandLineParser_(commandLineParser),
          allServices_(new StreamingServiceListModel(this, QByteArray(), "name")),
          enabledServices_(allServices_)
{

    connect(&streamingServices, &StreamingServicesController::added, this, &StreamingServicesControllerViewModel::onServiceAdded);

    for (auto& service : streamingServices.toList()) {
        onServiceAdded(service.get());
    }
}

void StreamingServicesControllerViewModel::initialize()
{
    auto currentServiceName = currentServiceSetting_.value().toString();
    if (!commandLineParser_.service().isEmpty())
        currentServiceName = commandLineParser_.service();
    for (auto service : allServices_->toList()) {
        if (service->name().toLower() == currentServiceName.toLower())
            setCurrentService(service);
    }
}

StreamingServiceViewModel* StreamingServicesControllerViewModel::currentService() const
{
    return currentService_;
}

int StreamingServicesControllerViewModel::currentIndex() const
{
    return currentIndex_;
}

void StreamingServicesControllerViewModel::setCurrentService(QObject* value)
{
    if (currentService_ == value)
        return;

    auto service = static_cast<StreamingServiceViewModel*>(value);

    QModelIndex sourceIndex = allServices_->index(allServices_->toList().indexOf(service), 0, QModelIndex());

    setCurrentIndex(enabledServices_.mapFromSource(sourceIndex).row());
}

void StreamingServicesControllerViewModel::setCurrentIndex(int value)
{
    int sourceIndex = enabledServices_.mapToSource(enabledServices_.index(value, 0, QModelIndex())).row();

    if (currentIndex_ == sourceIndex)
        return;

    currentIndex_ = sourceIndex;
    currentService_ = allServices_->at(sourceIndex);

    if (currentService_ == nullptr) {
        currentServiceSetting_.setValue("");
        streamingServices_.setCurrent(nullptr);
    } else {
        currentServiceSetting_.setValue(currentService_->name());
        streamingServices_.setCurrent(currentService_->streamingService());
    }
    emit currentIndexChanged(currentIndex_);
    emit currentServiceChanged(currentService_);
    onPlayerRunningChanged();
}

void StreamingServicesControllerViewModel::reload()
{
    streamingServices_.load();
}

void StreamingServicesControllerViewModel::onServiceAdded(StreamingService* streamingService)
{
    auto* sv = new StreamingServiceViewModel(*streamingService, settings_.settingsProvider(), players_, this);
    Player* player = sv->player();
    connect(player, &Player::isRunningChanged, this, &StreamingServicesControllerViewModel::onPlayerRunningChanged);
    connect(sv, &StreamingServiceViewModel::isEnabledChanged, this, &StreamingServicesControllerViewModel::onServiceEnabledChanged);
    allServices_->append(sv);
}

void StreamingServicesControllerViewModel::next()
{
    int index = nextIndex(currentIndex_);

    while (index != currentIndex_) {
        auto* sv = allServices_->at(index);
        if (sv->isRunning()) {
            setCurrentService(sv);
            break;
        }
        index = nextIndex(index);
    }
}

void StreamingServicesControllerViewModel::previous()
{
    int index = previousIndex(currentIndex_);

    while (index != currentIndex_) {
        auto* sv = allServices_->at(index);
        if (sv->isRunning() && sv->isEnabled()) {
            setCurrentService(sv);
            break;
        }
        index = previousIndex(index);
    }
}

void StreamingServicesControllerViewModel::createService(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                                         const QString& authorWebsite)
{
    workDispatcher_.invoke([=]() {
        QString pluginDir = streamingServiceCreator_.create(serviceName, serviceUrl, authorName, authorWebsite);
        emit serviceCreated(pluginDir);
        streamingServices_.load();
    });
}

int StreamingServicesControllerViewModel::nextIndex(int index) const
{
    int nextIndex = index + 1;
    if (nextIndex >= allServices_->count())
        nextIndex = 0;
    return nextIndex;
}

int StreamingServicesControllerViewModel::previousIndex(int index) const
{
    int previousIndex = index - 1;
    if (previousIndex < 0)
        previousIndex = allServices_->count() - 1;
    return previousIndex;
}

void StreamingServicesControllerViewModel::onPlayerRunningChanged()
{
    bool wasCurrentServiceRunning = isCurrentServiceRunning_;
    isCurrentServiceRunning_ = false;
    if (currentService_ != nullptr)
        isCurrentServiceRunning_ = currentService_->isRunning();

    if (wasCurrentServiceRunning != isCurrentServiceRunning_) {
        emit isCurrentServiceRunningChanged();
    }
}

int StreamingServicesControllerViewModel::webViewIndex(const QString& serviceName) const
{
    return allServices_->indexOf(serviceName);
}

void StreamingServicesControllerViewModel::onServiceEnabledChanged()
{
    if (sender() == currentService_) {
        setCurrentIndex(-1);
        emit currentIndexChanged(-1);
    }
}

bool StreamingServicesControllerViewModel::isCurrentServiceRunning() const
{
    return isCurrentServiceRunning_;
}
StreamingServiceListModel* StreamingServicesControllerViewModel::allServices()
{
    return allServices_;
}
StreamingServiceProxyListModel* StreamingServicesControllerViewModel::enabledServices()
{
    return &enabledServices_;
}
