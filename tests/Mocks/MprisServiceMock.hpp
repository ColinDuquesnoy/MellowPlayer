#pragma once

#include <QtCore>

#ifdef Q_OS_LINUX

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/IMprisService.hpp>

USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

class MprisServiceMock {
public:
    static Mock<IMprisService> get() {
        Mock<IMprisService> mock;
        When(Method(mock, start)).AlwaysReturn();
        return mock;
    }
};

#endif
