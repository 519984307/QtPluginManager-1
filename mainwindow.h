#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPluginLoader>
#include <QStandardItemModel>

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

    void addLoadedPlugin(const IPlugin *plugin, QString filename);

private slots:
    void displayFilename(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<std::vector<std::unique_ptr<IPlugin>>> plugins;

    std::unique_ptr<QStandardItemModel> loadedPluginsModel;
};
#endif // MAINWINDOW_H
