#ifndef FIRSTPLUGIN_H
#define FIRSTPLUGIN_H

#include <QString>

#include "../../plugins/core/iplugin.h"

class FirstPlugin : public QObject, public IPlugin
{
public:
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugins.first/1.0")
    Q_INTERFACES(IPlugin)

public:
    FirstPlugin() = default;
    virtual ~FirstPlugin();

    QString getName() const override;

    int getId() const override;

private:
    QString name = "First Plugin";

    const int pluginId = 1;
};

#endif
