#pragma once

#include <QtCore>

#ifdef Q_OS_LINUX

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Controllers/IMprisController.hpp>

USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace fakeit;

class MprisServiceMock {
public:
    static Mock<IMprisController> get() {
        Mock<IMprisController> mock;
        When(Method(mock, start)).AlwaysReturn();
        return mock;
    }
};

#endif
