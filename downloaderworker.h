#ifndef DOWNLOADERWORKER_H
#define DOWNLOADERWORKER_H

#include <QObject>
#include<QThread>
//#include"downloadermanager.h"
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QtNetwork>
#include<thread>
#include<memory>

class MainWindow;

enum class AnswerServer
{
    ERROR,
    WAITING,
    SUCCEC
};


class DownLoaderWorker : public QObject
{
    Q_OBJECT
public:
    explicit DownLoaderWorker(QObject *parent = nullptr);
    ~DownLoaderWorker();
signals:
    void getSize(quint64 size);
    void GetInfo(const QString& information);

public:

    void setUrl(const QUrl& url);

    void setThread(int count){
        COUNT_THREAD = count+1;
    }

    QByteArray GetAnswerServer(size_t start, size_t end);

    void SuccefulSaveData();
    void downloadFile();
private:
    QUrl url;

    std::vector<std::unique_ptr<std::jthread>> threadsList;

    QList<QFile*> files;

    QMutex m;
    void download_functor(size_t startByte, size_t endByte, size_t partIndex, QFile *file);

    std::uint64_t getSizeFileFromBytes();

    QNetworkReply* M_reply;

    QNetworkAccessManager* N_Manager;

    int COUNT_THREAD { 1 };


};

#endif // DOWNLOADERWORKER_H
