#pragma once

class QString;

namespace MellowPlayer::Infrastructure
{
    class IFile;

    class IFileFactory
    {
    public:
        virtual ~IFileFactory() = default;
        virtual std::shared_ptr<IFile> create(const QString& path) const = 0;
    };

    class FileFactory: public IFileFactory
    {
    public:
        std::shared_ptr<IFile> create(const QString& path) const override;
    };
}
