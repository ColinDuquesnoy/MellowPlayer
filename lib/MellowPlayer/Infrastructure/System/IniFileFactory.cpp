#include "IniFileFactory.hpp"
#include "IniFile.hpp"
#include "IFile.hpp"
#include "FileFactory.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

IniFileFactory::IniFileFactory(IFileFactory& fileFactory)
        : fileFactory_(fileFactory)
{

}

std::shared_ptr<IIniFile> IniFileFactory::create(const QString& path) const
{
    return make_shared<IniFile>(fileFactory_.create(path));
}
