#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <MellowPlayer/Infrastructure/System/IFile.hpp>
#include "WebPlayerScript.hpp"
#include <iostream>

using namespace std;
using namespace MellowPlayer::Infrastructure;

WebPlayerScript::WebPlayerScript(const std::shared_ptr<IFile>& file)
        : file_(file)
{
}

void WebPlayerScript::load()
{
    if (file_->openReadOnly()) {
        code_ = file_->readAll();
        if (!isValid()) {
            cout << "invalid script <" << file_->path().toStdString() << ">: " << code_.toStdString() << endl;
            throw std::runtime_error("Invalid web player script");
        }
    }
    else {
        cout << "script does not exist: " << file_->path().toStdString() << endl;
        throw std::runtime_error("failed to open " + file_->path().toStdString());
    }
}
