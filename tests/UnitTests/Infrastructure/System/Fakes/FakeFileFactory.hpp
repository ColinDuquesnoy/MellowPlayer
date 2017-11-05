#pragma once

#include <QString>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include "UnitTests/Infrastructure/System/Mocks/MockFile.hpp"
#include <QtCore/QList>
#include <QtCore/QMap>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeFileFactory: public IFactory<IFile, QString>
    {
    public:
        std::unique_ptr<IFile> create(QString&& param) override;

        QMap<QString, QString> fileContents;
        QList<QString> callsParam;
        int callCount;
    };
}