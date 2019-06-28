#include "filesystemwatcher.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>

FileSystemWatcher *FileSystemWatcher::m_pInstance = NULL;

FileSystemWatcher::FileSystemWatcher(QObject *parent) : QObject(parent)
{

}

FileSystemWatcher::~FileSystemWatcher()
{

}

void FileSystemWatcher::addWatchPath(const QString &path){
    qDebug()<<QString("add to path %1").arg(path);

    if (m_pInstance == NULL){
        m_pInstance = new FileSystemWatcher();
        m_pInstance->m_pSystemWatcher = new QFileSystemWatcher();

        connect(m_pInstance->m_pSystemWatcher,SIGNAL(directoryChanged(QString)),m_pInstance,SLOT(directoryUpdated(QString)));
        connect(m_pInstance->m_pSystemWatcher,SIGNAL(fileChanged(QString)),m_pInstance,SLOT(fileUpdated(QString)));
    }
    m_pInstance->m_pSystemWatcher->addPath(path);

    QFileInfo file(path);
    if (file.isDir()){
        QDir dirw(path);
        m_pInstance->m_currentContentsMap[path] = dirw.entryList(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Files,QDir::DirsFirst);
    }
}

void FileSystemWatcher::directoryUpdated(const QString &path){
    qDebug()<<QString("Directory %1 is updated");
    //比较新的内容和保存的变化
    QStringList currEntryList = m_pInstance->m_currentContentsMap[path];
    QDir dirw(path);
    QStringList newEntyrList = dirw.entryList(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Files,QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntyrList);
    QSet<QString> currDirSet = QSet<QString>::fromList(currEntryList);

    //添加的文件
    QSet<QString> newFiles = newDirSet - currDirSet;
    QStringList newFile =newFiles.toList();

    //删除的文件
    QSet<QString> deletedFiles = currDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    //保存当前配置
    m_pInstance->m_currentContentsMap[path] = newEntyrList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // 文件/目录重命名
        if ((newFile.count() == 1) && (deleteFile.count() == 1))
        {
            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
        }
    }
    else
    {
        // 添加新文件/目录至Dir
        if (!newFile.isEmpty())
        {

            qDebug() << "New Files/Dirs added: " << newFile;

            foreach (QString file, newFile)
            {
                // 处理操作每个新文件....
             }
         }
        // 从Dir中删除文件/目录
        if (!deleteFile.isEmpty())
        {
            qDebug() << "Files/Dirs deleted: " << deleteFile;

            foreach(QString file, deleteFile)
            {
                   // 处理操作每个被删除的文件....
            }
        }
    }

}

void FileSystemWatcher::fileUpdated(const QString &path){
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strFile = file.fileName();
    qDebug()<<QString("file is %1 at path %2 is updated").arg(strFile).arg(strPath);
}
