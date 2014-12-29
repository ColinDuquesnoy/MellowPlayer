#include <iostream>
#include <QtCore>
#include "grooveshark.h"


void GroovesharkIntegrationPlugin::play()
{
    qDebug() << "Play" << this->webView;
}


void GroovesharkIntegrationPlugin::pause()
{
    qDebug() << "Pause";
}

void GroovesharkIntegrationPlugin::stop()
{
    qDebug() << "Stop";
}

void GroovesharkIntegrationPlugin::next()
{
    qDebug() << "Next";
}

void GroovesharkIntegrationPlugin::previous()
{
    qDebug() << "Previous";
}

