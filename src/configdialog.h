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
