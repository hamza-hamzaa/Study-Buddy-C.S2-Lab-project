#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QByteArray>
#include <QDialog>
#include <QtNetwork/QTcpSocket>

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
                        QWidget *previousWindow = nullptr,
                        QWidget *parent = nullptr);
    ~chatwindow();

private slots:
    void on_sendButton_clicked();
    void readFromServer();

    void on_backButton_clicked();

private:
    Ui::chatwindow *ui;
    QTcpSocket *socket;
    QWidget *previousWindow;
    QString username;
    QString currentRoom;
    QByteArray buffer;

    void sendChatMessage(const QString &message);
    void addMessageToTop(const QString &sender, const QString &message);
};

#endif // CHATWINDOW_H
