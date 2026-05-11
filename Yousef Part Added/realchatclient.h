#ifndef REALCHATCLIENT_H
#define REALCHATCLIENT_H

#include "ichatclient.h"
#include <QTcpSocket>
#include <QObject>

class RealChatClient : public QObject, public IChatClient
{
    Q_OBJECT
public:
    explicit RealChatClient(QObject *parent = nullptr);

    void connectToServer();
    void sendMessage(const QString &jsonMessage) override;

private:
    QTcpSocket *socket;
};

#endif
