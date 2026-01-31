#include "RapidNetworkManager.h"

RapidNetworkManager::RapidNetworkManager(QObject *parent)
    : QObject{parent}
{}

RapidNetworkManager::RapidNetworkManager(const QUrl &url)
    :
    MainUrl(url)
    , NetworkManager(std::make_unique<QNetworkAccessManager>())
{

}

std::uint64_t RapidNetworkManager::getSizeFileFromBytes()
{
    // QNetworkRequest request(url);
    // qDebug() << url.toString();

    // QNetworkReply* reply = NetworkManager->get(request);

    // QEventLoop loop;
    // QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    // loop.exec();

    // if (reply->error() == QNetworkReply::NoError) {
    //     std::uint64_t contentLength = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
    //     qint64 c = reply->bytesAvailable();

    //     if (contentLength > 0) {
    //         emit GetInfo("Полный размер файла в байтах: " + QString::number(contentLength) + " байт");
    //         emit GetInfo("Полный размер файла без хедера: " + QString::number(c) + " байт");

    //         emit GetInfo("Часть каждому потоку: " + QString::number((contentLength / COUNT_THREAD)) + " байт");

    //         emit GetInfo("Размер в МБ: "
    //                      + QString::number((contentLength / std::pow(1024, 2)) / COUNT_THREAD));

    //         reply->deleteLater();

    //         return contentLength;
    //     }
    // } else {
    //     emit GetInfo("Ошибка получения размера сервер не отвечает: " + reply->errorString());
    //     reply->deleteLater();
    //     return -1;
    // }

    return 0;
}
