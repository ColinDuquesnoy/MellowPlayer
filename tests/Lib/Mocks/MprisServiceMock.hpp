#pragma once

#include <QtCore>

#ifdef Q_OS_LINUX

#include <MellowPlayer/Infrastructure/Platform/Linux/IMpris.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

class MprisServiceMock
{
public:
    static Mock<IMpris> get()
    {
        Mock<IMpris> mock;
        When(Method(mock, start)).AlwaysReturn();
        return mock;
    }
};

#endif
