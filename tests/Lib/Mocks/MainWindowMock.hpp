#pragma once
#include <MellowPlayer/Domain/IDeprecatedMainWindow.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class MainWindowMock
{
public:
    static Mock<IDeprecatedMainWindow> get()
    {
        Mock<IDeprecatedMainWindow> mock;
        When(Method(mock, load)).AlwaysReturn();
        When(Method(mock, show)).AlwaysReturn();
        When(Method(mock, hide)).AlwaysReturn();
        return mock;
    }
};
