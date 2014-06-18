#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <windows.h>

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

    void setName(const QString &newName);
    QString name() const ;

    bool stageNone() const ;
    bool stageLast() const ;
    bool stageAll() const ;

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message, long *result);

private:
    Ui::ConfigDialog *ui;

    UINT queryCancelAutoPlay;
};

#endif // CONFIGDIALOG_H
