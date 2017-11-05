#include "FakeFileFactory.hpp"
#include <UnitTests/Infrastructure/System/Mocks/MockFile.hpp>
#include <iostream>

using namespace testing;
using namespace std;
using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Infrastructure::Tests;

unique_ptr<IFile> FakeFileFactory::create(QString&& path)
{
    auto stdPath = path.toStdString();
    auto stdContent = fileContents.value(path).toStdString();
    auto file = make_unique<testing::NiceMock<MockFile>>();

    ON_CALL(*file, exists()).WillByDefault(Return(true));
    ON_CALL(*file, openReadOnly()).WillByDefault(Return(true));
    ON_CALL(*file, readAll()).WillByDefault(Return(fileContents.value(path, "")));

    callCount++;
    callsParam.append(path);

    return file;
}
