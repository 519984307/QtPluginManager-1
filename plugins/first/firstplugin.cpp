#include <QDebug>

#include "firstplugin.h"

FirstPlugin::~FirstPlugin()
{
    qWarning() << " delete first plugin";
}

QString FirstPlugin::getName() const
{
    return name;
}

int FirstPlugin::getId() const
{
    return pluginId;
}
