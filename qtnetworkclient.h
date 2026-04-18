#ifndef QTNETWORKCLIENT_H
#define QTNETWORKCLIENT_H

#include "networkclient.h"
#include <QTcpSocket>
#include <QJsonDocument>

class QtNetworkClient : public NetworkClient {
    Q_OBJECT
public:
    explicit QtNetworkClient(QObject *parent = nullptr);
    ~QtNetworkClient();

    void connectToServer(const QString& host, int port) override;
    void sendMessage(const QJsonObject& message) override;
    void disconnectFromServer() override;

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* m_socket;
    QByteArray m_buffer;
};

#endif // QTNETWORKCLIENT_H