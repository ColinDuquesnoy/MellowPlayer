#include "PluginMetadata.hpp"
#include <MellowPlayer/Infrastructure/System/IIniFile.hpp>

using namespace std;
using namespace MellowPlayer::Infrastructure;

PluginMetadata::PluginMetadata(const shared_ptr<IIniFile>& iniFile)
        : iniFile_(iniFile)
{

}

void PluginMetadata::load()
{
    author_ = iniFile_->value("author").toString();
    authorUrl_ = iniFile_->value("author_website").toString();
    logo_ = QFileInfo(QFileInfo(iniFile_->path()).dir(), iniFile_->value("icon").toString()).absoluteFilePath();
    name_ = iniFile_->value("name").toString();
    version_ = iniFile_->value("version").toString();
}
