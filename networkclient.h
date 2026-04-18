#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QJsonObject>

class NetworkClient : public QObject {
    Q_OBJECT
public:
    explicit NetworkClient(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~NetworkClient() {}

    virtual void connectToServer(const QString& host, int port) = 0;
    virtual void sendMessage(const QJsonObject& message) = 0;
    virtual void disconnectFromServer() = 0;

signals:
    void messageReceived(const QJsonObject& message);
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
};

#endif // NETWORKCLIENT_H