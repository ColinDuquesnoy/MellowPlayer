#pragma once

#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class IFile;

    class WebPlayerScript: public Domain::WebPlayerScript
    {
    public:
        WebPlayerScript(IFactory<IFile, QString>& fileFactory, const QString& path);
        void load() override;

    private:
        IFactory<IFile, QString>& fileFactory_;
    };
}
