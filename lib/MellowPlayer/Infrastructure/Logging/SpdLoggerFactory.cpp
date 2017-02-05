#include "SpdLoggerFactory.hpp"
#include "SpdLogger.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

unique_ptr<ILogger> SpdLoggerFactory::create(const string &name, const LoggerConfig &loggerConfig) const {
    return make_unique<SpdLogger>(name, loggerConfig);
}
