#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QByteArray>
#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include"chatselectionwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class chatwindow;
}
QT_END_NAMESPACE

class chatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatwindow(const QString &username,
                        const QString &roomName,
                        QTcpSocket *socket,
                        QWidget *parent = nullptr
                        ,ChatSelectionWindow* p=nullptr);
    ~chatwindow();

private slots:
    void on_sendButton_clicked();
    void readFromServer();

    void on_pushButton_clicked();

private:
    Ui::chatwindow *ui;
    QTcpSocket *socket;
    QString username;
    QString currentRoom;
    QByteArray buffer;
    ChatSelectionWindow* p;
    void sendChatMessage(const QString &message);
    void addMessageToTop(const QString &sender, const QString &message);
};

#endif // CHATWINDOW_H
