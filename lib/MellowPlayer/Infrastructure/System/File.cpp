#include "File.hpp"

using namespace MellowPlayer::Infrastructure;

File::File(const QString& path): path_(path), file_(path_)
{

}

bool File::open()
{
    if (file_.open(QFile::ReadOnly)) {
        QTextStream stream(&file_);
        update(stream.readAll());
        return true;
    }
    return false;
}

bool File::exists() const
{
    return file_.exists();
}
