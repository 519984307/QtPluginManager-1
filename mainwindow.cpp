#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , plugins(std::make_unique<std::vector<std::unique_ptr<IPlugin>>>())
    , loadedPluginsModel(std::make_unique<QStandardItemModel>())
{
    ui->setupUi(this);

    loadPlugins();

    ui->loadedPluginsListView->setModel(loadedPluginsModel.get());

    QItemSelectionModel *selectedModel = ui->loadedPluginsListView->selectionModel();

    connect(selectedModel, &QItemSelectionModel::currentChanged, this, &MainWindow::displayFilename);
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
                    addLoadedPlugin(pluginPtr, fullPluginName);
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

void MainWindow::addLoadedPlugin(const IPlugin *plugin, QString filename)
{
    QStandardItem *newItem = new QStandardItem();
    newItem->setData(QVariant(plugin->getName()), Qt::DisplayRole);
    newItem->setData(QVariant(plugin->getId()), Qt::UserRole + 1);
    newItem->setData(QVariant(filename), Qt::UserRole + 2);
    loadedPluginsModel->setItem(loadedPluginsModel->rowCount(), newItem);
}

void MainWindow::displayFilename(const QModelIndex &current, const QModelIndex &previous)
{
    QMessageBox mBox;
    mBox.setText("This plugin loaded from " + current.data(Qt::UserRole + 2).toString());
    mBox.setIcon(QMessageBox::Warning);
    mBox.exec();
}
