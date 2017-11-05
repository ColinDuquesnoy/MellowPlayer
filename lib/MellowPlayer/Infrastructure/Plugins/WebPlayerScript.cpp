#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>
#include "WebPlayerScript.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

WebPlayerScript::WebPlayerScript(IFactory<IFile, QString>& fileFactory, const QString& path)
        : fileFactory_(fileFactory)
{
    path_ = path;
}

void WebPlayerScript::load()
{
    auto file = fileFactory_.create(move(path_));
    if (file->openReadOnly()) {
        code_ = file->readAll();
        if (!isValid())
            throw std::runtime_error("Invalid web player script");
    }
    else
        throw std::runtime_error("failed to open integration.js");
}
