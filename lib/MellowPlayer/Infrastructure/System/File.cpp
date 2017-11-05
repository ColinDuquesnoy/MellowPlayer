#include "File.hpp"

using namespace MellowPlayer::Infrastructure;

File::File(const QString& path): path_(path), file_(path_)
{

}

bool File::openReadOnly()
{
    return file_.open(QFile::ReadOnly);
}

bool File::exists() const
{
    return file_.exists();
}

QString File::readAll()
{
    return QString::fromUtf8(file_.readAll());
}
