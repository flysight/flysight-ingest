/***************************************************************************
**                                                                        **
**  FlySight Ingest                                                       **
**  Copyright 2018 Michael Cooper                                         **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>. **
**                                                                        **
****************************************************************************
**  Contact: Michael Cooper                                               **
**  Website: http://flysight.ca/                                          **
****************************************************************************/

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
