#include <iostream>
#include <QtCore>
#include "grooveshark_plugin.h"


void GroovesharkServiceIntegrationPlugin::play()
{
    qDebug() << "Play" << this->webView;
}


void GroovesharkServiceIntegrationPlugin::pause()
{
    qDebug() << "Pause";
}

void GroovesharkServiceIntegrationPlugin::stop()
{
    qDebug() << "Stop";
}

void GroovesharkServiceIntegrationPlugin::next()
{
    qDebug() << "Next";
}

void GroovesharkServiceIntegrationPlugin::previous()
{
    qDebug() << "Previous";
}

