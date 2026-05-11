#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include "ichatclient.h"
#include <QString>

class ChatController
{
public:
    ChatController(IChatClient *client,
                   const QString &username,
                   const QString &roomName);

    bool sendChatMessage(const QString &message);
    QString buildChatJson(const QString &message) const;
    QString buildJoinJson() const;

private:
    IChatClient *client;
    QString username;
    QString roomName;
};

#endif // CHATCONTROLLER_H
