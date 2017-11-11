#include "FileFactory.hpp"
#include "File.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;


std::shared_ptr<IFile> FileFactory::create(const QString& path) const
{
    return make_shared<File>(path);
}
