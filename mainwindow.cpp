#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , plugins(std::make_unique<std::vector<std::unique_ptr<IPlugin>>>())
{
    ui->setupUi(this);
    loadPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");

    qWarning() << "Plugins directory: " << QApplication::applicationDirPath() + "/plugins";

    pluginsDir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    const QStringList dirs = pluginsDir.entryList(QDir::Dirs);

    QPluginLoader pluginLoader(this);

    for (auto &dir : dirs)
    {
        if (dir == "." || dir == "..")
        {
            continue;
        }

        pluginsDir.cd(dir);

        const QStringList files = pluginsDir.entryList(QDir::Files);

        for (const QString &fileName : files)
        {
            QString fullPluginName = pluginsDir.absoluteFilePath(fileName);
            pluginLoader.setFileName(fullPluginName);

            if (!pluginLoader.load())
            {
                qWarning() << "Unable to load file" << fullPluginName << pluginLoader.errorString();
                addWrongFiles(fullPluginName);
            }

            QObject *plugin = pluginLoader.instance();
            if (plugin)
            {
                IPlugin *pluginPtr = qobject_cast<IPlugin *>(plugin);
                if (pluginPtr)
                {
                    plugins->push_back(std::move(std::unique_ptr<IPlugin>{pluginPtr}));
                    qWarning() << "Loaded plugin from: " << pluginPtr->getName()
                               << "from: " << fileName;
                    addLoadedPlugin(fullPluginName);
                }
            }
        }

        pluginsDir.cd("..");
    }
}

void MainWindow::addWrongFiles(QString pluginFileName)
{
    ui->locatedList->addItem(pluginFileName);
}

void MainWindow::addLoadedPlugin(QString pluginFileName)
{
    ui->loadedList->addItem(pluginFileName);
}
