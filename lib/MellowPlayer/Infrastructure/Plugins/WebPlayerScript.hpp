#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>

namespace MellowPlayer::Infrastructure
{
    class IFile;

    class WebPlayerScript: public Domain::WebPlayerScript
    {
    public:
        WebPlayerScript(const std::shared_ptr<IFile>& file);
        void load() override;

    private:
        std::shared_ptr<IFile> file_;
    };
}
