#include "realchatclient.h"
#include <QDebug>

RealChatClient::RealChatClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, [](){
        qDebug() << "Connected to server";
    });

    connect(socket, &QTcpSocket::errorOccurred, this, [](QAbstractSocket::SocketError){
        qDebug() << "Socket error occurred";
    });

    connectToServer();
}

void RealChatClient::connectToServer()
{
    socket->connectToHost("127.0.0.1", 54321);
}

void RealChatClient::sendMessage(const QString &jsonMessage)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
    socket->write((jsonMessage + "\n").toUtf8());
        socket->flush();
        qDebug() << "Sent:" << jsonMessage;
    }
}
