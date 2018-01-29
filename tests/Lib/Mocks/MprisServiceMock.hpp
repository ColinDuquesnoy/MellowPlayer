#pragma once

#include <QtCore>

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)

#include <MellowPlayer/Infrastructure/Platform/Linux/IMpris.hpp>
#include <fakeit/fakeit.hpp>
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
