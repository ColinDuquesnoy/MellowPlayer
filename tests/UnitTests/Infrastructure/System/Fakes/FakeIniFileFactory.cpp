#include "FakeIniFileFactory.hpp"

using namespace testing;
using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

unique_ptr<IIniFile> FakeIniFileFactory::create(QString&& path)
{
    auto file = make_unique<testing::NiceMock<MockIniFile>>();

    ON_CALL(*file, value(_, _)).WillByDefault(Invoke([&](const QString& key, const QVariant& defaultValue)
    {
        return iniFileContents.value(path).value(key, defaultValue);
    }));

    ON_CALL(*file, value(_)).WillByDefault(Invoke([&](const QString& key)
    {
        return iniFileContents.value(path).value(key);
    }));

    ON_CALL(*file, path()).WillByDefault(Return(path));

    callCount++;
    callsParam.append(path);

    return move(file);
}