#ifndef FILELISTWIDGET_H
#define FILELISTWIDGET_H

#include <QDir>
#include <QFileSystemWatcher>
#include <QListWidget>

class FileListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit FileListWidget(QWidget *parent = 0);

    void setRootFolder(QString rootFolder);

private:
    QFileSystemWatcher watcher;
    QDir rootDir;

    void updateWatcher();
    void updateList(const QDir &subDir);
    QStringList getFiles(QString path);

private slots:
    void onDirectoryChanged(QString path);
};

#endif // FILELISTWIDGET_H
