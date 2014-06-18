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
