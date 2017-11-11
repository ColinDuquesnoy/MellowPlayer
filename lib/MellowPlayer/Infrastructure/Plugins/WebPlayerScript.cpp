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
    cout << "WebPlayerScript::load" << endl;
    if (file_->open()) {
        cout << "Reading file" << endl;
        code_ = file_->content();
        if (!isValid())
            throw std::runtime_error("Invalid web player script");
        cout << "script is valid" << endl;
    }
    else
        throw std::runtime_error("failed to open " + file_->path().toStdString());
}
