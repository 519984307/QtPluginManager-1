#ifndef FIRSTPLUGIN_H
#define FIRSTPLUGIN_H

#include <QString>

#include "iplugin.h"

class FirstPlugin : IPlugin
{
public:
    Q_PLUGIN_METADATA(IID "org.plugins.first/1.0")
    Q_INTERFACES(IPlugin)

public:
    FirstPlugin()          = default;
    virtual ~FirstPlugin() = default;

    QString getName() override;

private:
    QString name = "First Plugin";
};

#endif
