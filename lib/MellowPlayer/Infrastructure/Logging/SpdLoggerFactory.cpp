#include "SpdLoggerFactory.hpp"
#include "SpdLogger.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace std;

unique_ptr<ILogger> SpdLoggerFactory::create(const string &name, const LoggerConfig &loggerConfig) const {
    return make_unique<SpdLogger>(name, loggerConfig);
}
