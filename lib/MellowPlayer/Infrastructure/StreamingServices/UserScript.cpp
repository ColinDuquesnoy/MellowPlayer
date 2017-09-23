#include <QtCore/QDir>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <QtCore/QUuid>
#include "UserScript.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

bool UserScriptDirectory::create() const
{
    QString path = FileHelper::userScriptsDirectory();
    QDir qDir(path);
    if (!qDir.exists())
        return qDir.mkpath(path);
    return true;
}

QString UserScriptDirectory::generateFileName() const {
    return path() + QDir::separator() + QUuid::createUuid().toString() + ".js";
}

QString UserScriptDirectory::path() const {
    return FileHelper::userScriptsDirectory();
}

bool UserScript::import(const QString& sourcePath)
{
    UserScriptDirectory directory;
    if (directory.create() && QFile::exists(sourcePath))
    {
        QString destinationPath = directory.generateFileName();
        path_ = destinationPath;
        qDebug() << "importing" << sourcePath << " to " << destinationPath;
        if (QFile::copy(sourcePath, destinationPath))
            return load(destinationPath);
        return true;
    }
    return false;
}

bool UserScript::load(const QString& path)
{
    qDebug() << "loading" << path;
    path_ = path;

    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        auto content = file.readAll();
        code_ = QString::fromUtf8(content);
        return true;
    }
    return false;
}
