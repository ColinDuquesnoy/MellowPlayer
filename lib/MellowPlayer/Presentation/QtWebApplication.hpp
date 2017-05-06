#pragma once

#include <QApplication>
#include <QQmlApplicationEngine>
#include <MellowPlayer/UseCases/Interfaces/IQtApplication.hpp>
#include "ViewModels/StreamingServicesViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class QtWebApplication: public UseCases::IQtApplication, public QApplication {
public:
    QtWebApplication(int &argc, char **argv);

    int run() override;
    void quit() override;
};

END_MELLOWPLAYER_NAMESPACE
