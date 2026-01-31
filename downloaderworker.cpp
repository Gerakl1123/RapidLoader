#include "downloaderworker.h"
#include<QtConcurrent/QtConcurrent>
#include<QString>

DownLoaderWorker::DownLoaderWorker(QObject *parent)
: QObject{parent}

{

    N_Manager = new QNetworkAccessManager();


}

DownLoaderWorker::~DownLoaderWorker()
{
    delete N_Manager;


}



void DownLoaderWorker::setUrl(const QUrl & C_url)
{
    url = C_url;
}

QByteArray DownLoaderWorker::GetAnswerServer(size_t start, size_t end)
{


    std::string msg = std::format("Отправка запроса GET: Поток №{}",
                                  (uintptr_t)(QThread::currentThreadId()));

    emit GetInfo(QString::fromStdString(msg));

    QNetworkRequest request(url);

    QString range = QString("bytes=%1-%2").arg(start).arg(end);
    request.setRawHeader("Range", range.toUtf8());

    QNetworkAccessManager manager;
    QNetworkReply* partReply = manager.get(request);

    QEventLoop loop;
    QObject::connect(partReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray data;
    if (partReply->error() == QNetworkReply::NoError) {
        data = partReply->readAll();
        emit GetInfo("Размер части : " + QString::number(data.size()) + " Диапозон байтов " + QString::number(start) + "-" + QString::number(end)+ "\n");

    } else {
        emit GetInfo("Ошибка скачки части: " +  QString::number(start) + "-" + QString::number(end) + ":" + partReply->errorString());
    }

    partReply->deleteLater();
    return data;
}

void DownLoaderWorker::SuccefulSaveData()
{


    QFile ofile("output.rar");

    if (!ofile.open(QIODevice::WriteOnly)) {
        return;
    }

    for(int i = 0; i < COUNT_THREAD; i++)
    {

        QString fileName = QString("download_part_%1.tmp").arg(i);
        QFile ifile(fileName);

        if(ifile.open(QIODevice::ReadOnly))
        {
            ofile.write(ifile.readAll());

            emit GetInfo("файл: " +  QString::number(i) + " Cчитан размер исходного: " + QString::number(ofile.size()));

            ifile.close();
        }

    }

    ofile.close();
}

void DownLoaderWorker::downloadFile()
{

    qDebug() << "start answer";

    files.reserve(COUNT_THREAD);
    threadsList.reserve(COUNT_THREAD);
    std::uint64_t mb_file = getSizeFileFromBytes() / COUNT_THREAD;
    size_t start {0},end {mb_file};


    for(int i = 0; i < COUNT_THREAD; i++)
    {

//       threadsList.append(nullptr);

        start = static_cast<double>(i * mb_file);

        end = ((i+1) * mb_file) - 1;

        if(i == COUNT_THREAD - 1){
            end = mb_file * COUNT_THREAD;
            qDebug() << "end: " << end;
        }

        QString fileName = QString("download_part_%1.tmp").arg(i);
        QFile* file = new QFile(fileName);

        if(!file->open(QIODevice::WriteOnly))
        {
            qDebug() << "delete file";
            delete file;
            emit GetInfo("Файл №:" + QString::number(i) + " Не смог удачно создаться перезапустите программу");
            continue;
        }

        files.append(file);



        // threadsList.push_back(std::jthread(
        //     [this, start, end, i, file = files[i]](std::stop_token token) {
        //         while(!token.stop_requested()) {
        //             this->download_functor(start, end, i, file);
        //         }
        //     }
        //     ));

        threadsList.emplace_back(std::make_unique<std::jthread>(
            [this,start,end,i](std::stop_token token){
                if (!token.stop_requested()) {
                    this->download_functor(start,end,i,files[i]);
                }
            })
        );

    }

    // for(int i = 0; i < COUNT_THREAD; i++)
    // {
    //     threadsList[i]->start();
    // }


}

void DownLoaderWorker::download_functor(size_t startByte, size_t endByte, size_t partIndex, QFile* file)
{
    QMutexLocker locker(&m);

    file->write(GetAnswerServer(startByte,endByte));



    std::string msg = std::format("Поток: {} Скачал часть: {} размер: {} байт",
                                  (uintptr_t)(QThread::currentThreadId()),
                                  partIndex,
                                  file->size());

    emit GetInfo(QString::fromStdString(msg));

}


std::uint64_t DownLoaderWorker::getSizeFileFromBytes() {
    qDebug() << "start size_f";

    QNetworkRequest request(url);
    qDebug() << url.toString();

    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        std::uint64_t contentLength = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
        qint64  c = reply->bytesAvailable();

        if (contentLength > 0) {
            emit GetInfo("Полный размер файла в байтах: " + QString::number(contentLength) + " байт");
            emit GetInfo("Полный размер файла без хедера: " + QString::number(c) + " байт");

            emit GetInfo("Часть каждому потоку: " + QString::number((contentLength / COUNT_THREAD)) + " байт");

             emit GetInfo("Размер в МБ: "
                     + QString::number((contentLength / std::pow(1024, 2)) / COUNT_THREAD));

            reply->deleteLater();

            return contentLength;
        }
    } else {
        emit GetInfo("Ошибка получения размера сервер не отвечает: " + reply->errorString());
        reply->deleteLater();
        return -1;
    }

    return 0;
}
