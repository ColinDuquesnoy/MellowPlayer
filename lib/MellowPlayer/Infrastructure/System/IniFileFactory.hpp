#pragma once

class QString;

namespace MellowPlayer::Infrastructure
{
    class IIniFile;
    class IFileFactory;

    class IIniFileFactory
    {
    public:
        virtual ~IIniFileFactory() = default;
        virtual std::shared_ptr<IIniFile> create(const QString& path) const = 0;
    };

    class IniFileFactory: public IIniFileFactory
    {
    public:
        explicit IniFileFactory(IFileFactory& fileFactory);
        std::shared_ptr<IIniFile> create(const QString& path) const override;

    private:
        IFileFactory& fileFactory_;
    };
}
