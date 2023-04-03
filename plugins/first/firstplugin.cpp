#include <QDebug>

#include "firstplugin.h"

FirstPlugin::~FirstPlugin()
{
    qWarning() << " delete first plugin";
}

QString FirstPlugin::getName()
{
    return name;
}
