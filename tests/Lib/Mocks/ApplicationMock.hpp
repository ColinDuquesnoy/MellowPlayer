#pragma once
#include <MellowPlayer/Infrastructure/Applications/IDeprecatedApplication.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Infrastructure;
using namespace fakeit;

class ApplicationMock
{
public:
    static Mock<IDeprecatedApplication> get()
    {
        Mock<IDeprecatedApplication> mock;
        When(Method(mock, initialize)).AlwaysReturn();
        When(Method(mock, restoreWindow)).AlwaysReturn();
        When(Method(mock, run)).AlwaysReturn();
        When(Method(mock, quit)).AlwaysReturn();
        return mock;
    }
};
