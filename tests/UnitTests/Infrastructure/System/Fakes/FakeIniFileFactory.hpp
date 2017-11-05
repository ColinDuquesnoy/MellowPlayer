#pragma once

#include <QString>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include "UnitTests/Infrastructure/System/Mocks/MockIniFile.hpp"
#include <QtCore/QList>
#include <QtCore/QMap>


namespace MellowPlayer::Infrastructure::Tests
{
    class FakeIniFileFactory: public IFactory<IIniFile, QString>
    {
    public:
        std::unique_ptr<IIniFile> create(QString&& param) override;

        QMap<QString, QMap<QString, QVariant>> iniFileContents;
        QList<QString> callsParam;
        int callCount;
    };
}