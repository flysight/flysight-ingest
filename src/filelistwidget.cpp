#include "filelistwidget.h"

#include <QDir>

FileListWidget::FileListWidget(QWidget *parent) :
    QListWidget(parent)
{
    // Connect file system watcher
    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)),
                     this,     SLOT(onDirectoryChanged(QString)));
}

void FileListWidget::setRootFolder(
        QString rootFolder)
{
    // Save root folder
    rootDir = QDir (rootFolder);

    // Ensure that the path exists
    rootDir.mkpath(".");

    // Update watcher
    updateWatcher();

    // Clear file list
    clear();

    // Update file list
    updateList(rootDir);
}

void FileListWidget::onDirectoryChanged(
        QString path)
{
    // Update watcher
    updateWatcher();

    // Update copied file list
    updateList(rootDir);
}

void FileListWidget::updateWatcher()
{
    // Get list of folders to be removed
    QStringList oldPaths = watcher.directories();

    // Build list of folders to be added
    QStringList newPaths;

    // Add root folder
    QString rootPath = rootDir.absolutePath();
    newPaths << rootPath;
    oldPaths.removeAll(rootPath);

    // Add child folders
    foreach (QString subDir, rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString subPath = rootDir.absoluteFilePath(subDir);
        newPaths << subPath;
        oldPaths.removeAll(subPath);
    }

    // Remove old watches
    watcher.removePaths(oldPaths);

    // Add new watches
    watcher.addPaths(newPaths);
}

void FileListWidget::updateList(
        const QDir &subDir)
{
    // Get list of files in subfolder
    QString subPath = subDir.absolutePath();
    QStringList newFiles = getFiles(subPath);

    // Get current list from widget
    QStringList oldFiles;
    for (int i = 0; i < count(); ++i)
    {
        oldFiles << subDir.relativeFilePath(item(i)->text());
    }

    // Get items to remove from list
    QStringList toRemove = oldFiles;
    foreach (QString fileName, newFiles)
    {
        toRemove.removeAll(fileName);
    }

    // Get items to add to list
    QStringList toAdd = newFiles;
    foreach (QString fileName, oldFiles)
    {
        toAdd.removeAll(fileName);
    }

    // Remove items from list
    foreach (QString fileName, toRemove)
    {
        foreach (QListWidgetItem *item,
                 findItems(rootDir.relativeFilePath(fileName),
                           Qt::MatchFixedString))
        {
            delete item;
        }
    }

    // Add items to list
    addItems(toAdd);
}

QStringList FileListWidget::getFiles(
        QString path)
{
    QDir dir(path);

    // Add files to list
    QStringList files;
    foreach (QString file, dir.entryList(QDir::Files))
    {
        files << rootDir.relativeFilePath(dir.absoluteFilePath(file));
    }

    // Handle child folders
    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        files << getFiles(dir.absoluteFilePath(subDir));
    }

    return files;
}
