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

#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    // Initialize UI object
    ui->setupUi(this);

    // Do not stage jumps
    ui->stageNone->setChecked(true);

    // Message for AutoRun notifications
    queryCancelAutoPlay = RegisterWindowMessage(L"QueryCancelAutoPlay");
}

ConfigDialog::~ConfigDialog()
{
    // Destroy UI object
    delete ui;
}

void ConfigDialog::setName(
        const QString &newName)
{
    ui->name->setText(newName);
}

QString ConfigDialog::name() const
{
    return ui->name->text();
}

bool ConfigDialog::stageNone() const
{
    return ui->stageNone->isChecked();
}

bool ConfigDialog::stageLast() const
{
    return ui->stageLast->isChecked();
}

bool ConfigDialog::stageAll() const
{
    return ui->stageAll->isChecked();
}

bool ConfigDialog::nativeEvent(
        const QByteArray &, // unused
        void             *message,
        long             *result)
{
    MSG *msg = (MSG *) message;

    if (msg->message == queryCancelAutoPlay)
    {
        // Disable AutoRun
        *(result) = 1;
        return true;
    }

    return false;
}
