#include "chatwindow.h"
#include "ui_chatwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QAbstractSocket>

chatwindow::chatwindow(const QString &username,
                       const QString &roomName,
                       QTcpSocket *socket,
                       QWidget *parent)
    : QDialog(parent),
    ui(new Ui::chatwindow),
    socket(socket),
    username(username),
    currentRoom(roomName)
{
    ui->setupUi(this);

    ui->Chatroom->setText(currentRoom);
    ui->ChatMessages->setReadOnly(true);

    if (this->socket && this->socket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonObject joinJson;
        joinJson["action"] = "JOIN_GROUP";
        joinJson["username"] = username;
        joinJson["room_id"] = currentRoom;

        QJsonDocument joinDoc(joinJson);
        QByteArray joinData = joinDoc.toJson(QJsonDocument::Compact);
        joinData.append('\n');

        this->socket->write(joinData);
        this->socket->flush();

        connect(this->socket, &QTcpSocket::readyRead,
                this, &chatwindow::readFromServer);
    }
}

chatwindow::~chatwindow()
{
    delete ui;
}

void chatwindow::on_sendButton_clicked()
{
    QString message = ui->Inputbox->text().trimmed();

    if (message.isEmpty())
        return;

    sendChatMessage(message);
    ui->Inputbox->clear();
}

void chatwindow::sendChatMessage(const QString &message)
{
    if (socket && socket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonObject json;
        json["action"] = "CHAT_MSG";
        json["room_id"] = currentRoom;
        json["sender"] = username;
        json["content"] = message;

        QJsonDocument doc(json);
        QByteArray data = doc.toJson(QJsonDocument::Compact);
        data.append('\n');

        socket->write(data);
        socket->flush();
    }
    else
    {
        addMessageToTop(username, message);
    }
}

void chatwindow::readFromServer()
{
    if (!socket)
        return;

    buffer.append(socket->readAll());

    while (buffer.contains('\n'))
    {
        int newlineIndex = buffer.indexOf('\n');
        QByteArray oneMessage = buffer.left(newlineIndex).trimmed();
        buffer.remove(0, newlineIndex + 1);

        if (oneMessage.isEmpty())
            continue;

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(oneMessage, &error);

        if (error.error != QJsonParseError::NoError || !doc.isObject())
            continue;

        QJsonObject json = doc.object();
        QString action = json["action"].toString();

        if (action == "CHAT_MSG")
        {
            QString roomId = json["room_id"].toString();
            QString sender = json["sender"].toString();
            QString content = json["content"].toString();

            if (roomId == currentRoom)
            {
                addMessageToTop(sender, content);
            }
        }
    }
}

void chatwindow::addMessageToTop(const QString &sender, const QString &message)
{
    QString newMessage = sender + ": " + message;
    QString oldMessages = ui->ChatMessages->toPlainText();

    if (oldMessages.isEmpty())
        ui->ChatMessages->setPlainText(newMessage);
    else
        ui->ChatMessages->setPlainText(newMessage + "\n" + oldMessages);
}
