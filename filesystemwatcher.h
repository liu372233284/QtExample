#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QMap>
#include <QFileSystemWatcher>

class FileSystemWatcher : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemWatcher(QObject *parent = 0);
    ~FileSystemWatcher();
    static void addWatchPath(const QString &path);
signals:


public slots:
    void directoryUpdated(const QString &path);
    void fileUpdated(const QString &path);
private:
    static FileSystemWatcher *m_pInstance;
    QFileSystemWatcher *m_pSystemWatcher;
    QMap<QString,QStringList> m_currentContentsMap;
};

#endif // FILESYSTEMWATCHER_H
