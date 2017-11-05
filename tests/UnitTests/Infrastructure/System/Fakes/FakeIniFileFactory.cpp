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

    callCount++;
    callsParam.append(path);

    return file;
}