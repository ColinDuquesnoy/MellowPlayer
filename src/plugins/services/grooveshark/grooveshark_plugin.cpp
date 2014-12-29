#include <iostream>
#include "grooveshark_plugin.h"


void GroovesharkServiceIntegrationPlugin::play()
{
    std::cout << "Play" << std::endl;
}


void GroovesharkServiceIntegrationPlugin::pause()
{
    std::cout << "Pause" << std::endl;
}

void GroovesharkServiceIntegrationPlugin::stop()
{
    std::cout << "Stop" << std::endl;
}

void GroovesharkServiceIntegrationPlugin::next()
{
    std::cout << "Next" << std::endl;
}

void GroovesharkServiceIntegrationPlugin::previous()
{
    std::cout << "Previous" << std::endl;
}

