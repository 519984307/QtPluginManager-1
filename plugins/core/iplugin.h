#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QObject>
#include <QString>

#define PluginInterface_iid "org.plugins/1.0"

class IPlugin
{
public:
    virtual ~IPlugin() = default;

    virtual QString getName() const = 0;

    virtual int getId() const = 0;
};

Q_DECLARE_INTERFACE(IPlugin, PluginInterface_iid)

#endif // IPLUGIN_H
