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

#ifndef COPYWORKER_H
#define COPYWORKER_H

#include <QDir>
#include <QObject>
#include <QStringList>

class CopyWorker : public QObject
{
    Q_OBJECT
public:
    enum StageMode { stageNone, stageLast, stageAll };

    CopyWorker(const QString &srcPath, const QString &dstPath,
               const QString &stagePath, StageMode mode);
    ~CopyWorker();

public slots:
    void process();

signals:
    void finished();

private:
    QDir srcDir;
    QDir dstDir;
    QDir stageDir;
    StageMode stageMode;

    void copyFolder(const QString &path);
    bool fileIsJump(const QString &fileName);
};

#endif // COPYWORKER_H
