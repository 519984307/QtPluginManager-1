#ifndef SECONDPLUGIN_H
#define SECONDPLUGIN_H

#include <QString>

#include "../../plugins/core/iplugin.h"

class SecondPlugin : public QObject, public IPlugin
{
public:
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugins.second/1.0")
    Q_INTERFACES(IPlugin)

public:
    SecondPlugin()          = default;
    virtual ~SecondPlugin() = default;

    QString getName() const override;

    int getId() const override;

private:
    QString name = "Second Plugin";

    const int pluginId = 2;
};

#endif
