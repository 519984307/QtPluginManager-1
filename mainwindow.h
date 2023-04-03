#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPluginLoader>

#include <plugins/core/iplugin.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void loadPlugins();

    void addWrongFiles(QString pluginFileName);

    void addLoadedPlugin(QString pluginFileName);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<std::vector<std::unique_ptr<IPlugin>>> plugins;
};
#endif // MAINWINDOW_H
