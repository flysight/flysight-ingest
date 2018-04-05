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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>

#include <QMainWindow>
#include <QString>

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message, long *result);

private:
    Ui::MainWindow *ui;

    int  copyThreads;
    UINT queryCancelAutoPlay;

    bool exportBusy;

    void setRootFolder(QString rootFolder);

    void enableExportButtons();

    bool fileIsJump(const QString &fileName);

    QString readConfigId(QString fileName);
    bool writeConfigId(QString fileName, QString id);
    bool archiveFolderExists(QString id);

    void handleDeviceInsert(int driveNum);
    void handleDeviceRemove(int driveNum);

private slots:
    void on_browseButton_clicked();
    void on_removeButton_clicked();
    void on_exportButton_clicked();
    void on_reexportButton_clicked();

    void on_fileList_itemSelectionChanged();
    void on_exportList_itemSelectionChanged();

    void onCopyFinished();
    void onExportReady();

    void exportItem(QListWidgetItem *item);
    void reexportItem(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
