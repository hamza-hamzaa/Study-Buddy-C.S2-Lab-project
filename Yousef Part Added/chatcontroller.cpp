#include "chatcontroller.h"
#include <QJsonDocument>
#include <QJsonObject>

ChatController::ChatController(IChatClient *client,
                               const QString &username,
                               const QString &roomName)
    : client(client), username(username), roomName(roomName)
{
}

bool ChatController::sendChatMessage(const QString &message)
{
    QString trimmed = message.trimmed();

    if (trimmed.isEmpty() || client == nullptr)
        return false;

    QString jsonMessage = buildChatJson(trimmed);
    client->sendMessage(jsonMessage);
    return true;
}

QString ChatController::buildChatJson(const QString &message) const
{
    QJsonObject json;
    json["action"] = "CHAT_MSG";
    json["room_id"] = roomName;
    json["sender"] = username;
    json["content"] = message;

    QJsonDocument doc(json);
    QString result = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    result += '\n';
    return result;
}

QString ChatController::buildJoinJson() const
{
    QJsonObject json;
    json["action"] = "JOIN_GROUP";
    json["username"] = username;
    json["room_id"] = roomName;

    QJsonDocument doc(json);
    QString result = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    result += '\n';
    return result;
}
