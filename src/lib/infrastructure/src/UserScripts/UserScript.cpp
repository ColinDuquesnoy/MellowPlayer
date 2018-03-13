#include <QtCore/QDir>
#include <QtCore/QUuid>
#include <QDebug>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScript.hpp>

using namespace MellowPlayer::Domain;
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
    QString sourceUrl = sourcePath;
    sourceUrl = sourceUrl.replace("file://", "");
    UserScriptDirectory directory;
    bool exists = QFile::exists(sourceUrl);
    if (directory.create() && exists)
    {
        QString destinationPath = directory.generateFileName();
        path_ = destinationPath;
        qDebug() << "importing" << sourceUrl << " to " << destinationPath;
        if (QFile::copy(sourceUrl, destinationPath))
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

void UserScript::removeFile() const
{
    QFile::remove(path_);
}
