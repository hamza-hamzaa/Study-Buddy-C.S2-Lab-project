#ifndef ICHATCLIENT_H
#define ICHATCLIENT_H

#include <QString>

class IChatClient
{
public:
    virtual ~IChatClient() = default;
    virtual void sendMessage(const QString &jsonMessage) = 0;
};

#endif // ICHATCLIENT_H
