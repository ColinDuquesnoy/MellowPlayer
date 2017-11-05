#include "PluginMetadata.hpp"
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

PluginMetadata::PluginMetadata(IFactory<IIniFile, QString>& iniFileFactory, const QString& path)
        : iniFileFactory_(iniFileFactory), path_(path)
{

}

void PluginMetadata::load()
{
    auto iniFilePtr = iniFileFactory_.create(move(path_));
    auto& iniFile = *iniFilePtr; 

    author_ = iniFile.value("author").toString();
    authorUrl_ = iniFile.value("author_website").toString();
    logo_ = QFileInfo(QFileInfo(path_).dir(), iniFile.value("icon").toString()).absoluteFilePath();
    name_ = iniFile.value("name").toString();
    version_ = iniFile.value("version").toString();
}
