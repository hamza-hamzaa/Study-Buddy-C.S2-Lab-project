#ifndef MOCKNETWORKCLIENT_H
#define MOCKNETWORKCLIENT_H

#include "networkclient.h"
#include <QJsonObject>
#include <QList>

class MockNetworkClient : public NetworkClient {
    Q_OBJECT
public:
    explicit MockNetworkClient(QObject *parent = nullptr) : NetworkClient(parent) {}

    void connectToServer(const QString& host, int port) override {
        m_connected = true;
        emit connected();
    }

    void sendMessage(const QJsonObject& message) override {
        m_sentMessages.append(message);
    }

    void disconnectFromServer() override {
        m_connected = false;
        emit disconnected();
    }

    QList<QJsonObject> getSentMessages() const { return m_sentMessages; }
    void clearSentMessages() { m_sentMessages.clear(); }
    void simulateReceivedMessage(const QJsonObject& message) {
        emit messageReceived(message);
    }

private:
    bool m_connected = false;
    QList<QJsonObject> m_sentMessages;
};

#endif // MOCKNETWORKCLIENT_H