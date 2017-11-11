#include "IniFile.hpp"
#include "IFile.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

IniFile::IniFile(const shared_ptr<IFile>& file): file_(file), settings_(file_->path(), QSettings::IniFormat)
{

}

QVariant IniFile::value(const QString& key) const
{
    return settings_.value(key, QVariant());
}

QString IniFile::path() const
{
    return file_->path();
}
