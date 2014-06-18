#include <QDir>
#include <QRegExp>

#include "copyworker.h"

CopyWorker::CopyWorker(
        const QString &srcPath,
        const QString &dstPath,
        const QString &stagePath,
        StageMode mode):
    srcDir(srcPath),
    dstDir(dstPath),
    stageDir(stagePath),
    stageMode(mode)
{
    // Initialize here
}

CopyWorker::~CopyWorker()
{
    // Free resources
}

void CopyWorker::process()
{
    if (!dstDir.exists())
    {
        // Create folder
        dstDir.mkpath(".");
    }

    if (!stageDir.exists())
    {
        // Create folder
        stageDir.mkpath(".");
    }

    // Read from oldest to newest
    srcDir.setSorting(QDir::Name | QDir::Reversed);

    // Handle child folders
    foreach (QString path, srcDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        // Check if the folder fits our "date" format
        QRegExp rx("^[0-9]{2}-[0-9]{2}-[0-9]{2}$");

        if (!rx.indexIn(path))
        {
            copyFolder(path);
        }
    }

    // Let main thread know we're done
    emit finished();
}

void CopyWorker::copyFolder(
        const QString &path)
{
    QDir subDir = srcDir.absoluteFilePath(path);

    // Read from oldest to newest
    subDir.setSorting(QDir::Name | QDir::Reversed);

    foreach (QString file, subDir.entryList(QDir::Files))
    {
        // Check if file fits our "time" format
        QRegExp rx("^[0-9]{2}-[0-9]{2}-[0-9]{2}\\.CSV$");

        // Archived/staged filename
        QString newFile = path + "-" + file;

        if (!rx.indexIn(file) && !dstDir.exists(newFile))
        {
            QString srcFilePath  = subDir.absoluteFilePath(file);
            QString dstFilePath  = dstDir.absoluteFilePath(newFile);
            QString stageFilePath = stageDir.absoluteFilePath(newFile);

            if (stageMode == stageAll)
            {
                // Copy file
                QFile::copy(srcFilePath, dstFilePath);

                if (fileIsJump(dstFilePath))
                {
                    // Copy file to "staged" sub-tree
                    QFile::copy(dstFilePath, stageFilePath);
                }
            }
            else if (stageMode == stageLast)
            {
                // Copy file
                QFile::copy(srcFilePath, dstFilePath);

                if (fileIsJump(dstFilePath))
                {
                    // Copy file to "staged" sub-tree
                    QFile::copy(dstFilePath, stageFilePath);

                    // Don't stage again
                    stageMode = stageNone;
                }
            }
            else
            {
                // Create empty placeholder file
                QFile(dstFilePath).open(QIODevice::WriteOnly);
            }
        }
    }
}

bool CopyWorker::fileIsJump(
        const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return false;

    // Throw away first two lines
    file.readLine();
    file.readLine();

    // Performance limits of u-blox module
    double hMin =  50000;
    double hMax = -50000;

    while (!file.atEnd())
    {
        QString line = file.readLine();

        // Parse the line
        QStringList cols = line.split(",");
        if (cols.length() < 12) continue;

        bool ok;
        double hMSL = cols[3].toDouble(&ok);
        if (!ok) continue;

        // Update elevation range
        if (hMSL < hMin) hMin = hMSL;
        if (hMSL > hMax) hMax = hMSL;
    }

    // A jump should have at least 1000 m range
    if (hMax - hMin < 1000) return false;

    return true;
}
