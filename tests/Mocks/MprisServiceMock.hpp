#pragma once

#include <QtCore>

#ifdef Q_OS_LINUX

#include <MellowPlayer/Application/Controllers/IMprisController.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

class MprisServiceMock
{
public:
    static Mock<IMprisController> get()
    {
        Mock<IMprisController> mock;
        When(Method(mock, start)).AlwaysReturn();
        return mock;
    }
};

#endif
