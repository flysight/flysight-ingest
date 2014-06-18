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
