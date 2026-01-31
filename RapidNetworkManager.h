#ifndef RAPIDNETWORKMANAGER_H
#define RAPIDNETWORKMANAGER_H

#include <QObject>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QtNetwork>
#include<memory>

class RapidNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit RapidNetworkManager(QObject *parent = nullptr);
    RapidNetworkManager(const QUrl& url);

    RapidNetworkManager(const RapidNetworkManager& rapid) = delete;
    // RapidNetworkManager(RapidNetworkManager&& rapid);
    // RapidNetworkManager(const RapidNetworkManager& rapid) = delete;

signals:

public:

    std::uint64_t getSizeFileFromBytes();

private:
    QUrl MainUrl;
    std::unique_ptr<QNetworkAccessManager> NetworkManager;
};

#endif // RAPIDNETWORKMANAGER_H
